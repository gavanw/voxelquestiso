uniform sampler2D Texture0; // pagesFBO
uniform sampler2D Texture1;

uniform sampler2D Texture2; // geom fbo
uniform sampler2D Texture3;

varying vec2 TexCoord0;

$

void main() {
    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
}

$

int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}

vec2 pack16(float num) {

    int iz = int(num);
    int ir = intMod(iz,256);
    int ig = (iz)/256;

    vec2 res;

    res.r = float(ir)/255.0;
    res.g = float(ig)/255.0;

    return res;

}

float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
}


void main() {

    // pages
    vec4 tex0 = texture2D(Texture0, TexCoord0 );
    vec4 tex1 = texture2D(Texture1, TexCoord0 );

    // geom
    vec4 tex2 = texture2D(Texture2, TexCoord0 );
    vec4 tex3 = texture2D(Texture3, TexCoord0 );


    float bh1 = unpack16(tex0.rg);
    float bh2 = unpack16(tex2.rg);


    vec4 res0 = vec4(0.0);
    vec4 res1 = vec4(0.0);
    
    if (bh2 > bh1) {
        res0 = tex2;
        res1 = tex3;
    }
    else {
        res0 = tex0;
        res1 = tex1;
    }
    
    gl_FragData[0] = res0;
    gl_FragData[1] = res1;


}
