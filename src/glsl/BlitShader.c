
uniform sampler2D Texture0;
uniform sampler2D Texture1;

uniform float zOffset;

varying vec2 TexCoord0;

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
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
        
        vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
        vec4 tex1 = texture2D(Texture1, TexCoord0.xy);

        float tot = tex0.r + tex0.g + tex0.b + tex0.a;

        if (tot == 0.0) {
            discard;
        }
        
        float newHeight = unpack16(tex0.rg);
        newHeight += zOffset;
        tex0.rg = pack16(newHeight);

        gl_FragData[0] = tex0;
        gl_FragData[1] = tex1;

}


