uniform sampler2D Texture0; // main fbo
uniform sampler2D Texture1;

uniform sampler2D Texture2; // water fbo
uniform sampler2D Texture3;

uniform sampler2D Texture4; // geom fbo
uniform sampler2D Texture5;

varying vec2 TexCoord0;


uniform vec2 resolution;
uniform vec2 mouseCoords;
uniform vec3 cameraPos;
uniform vec2 bufferDim;
uniform float cameraZoom;
uniform float tiltAmount;
uniform int iMax;



$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
    gl_Position = gl_Vertex;
}

$

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

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

// vec3 randV3(vec3 co) {
//     return vec3(
//                      fract(sin(dot(co.xyz , vec3(12.989, 78.233, 98.422))) * 43758.8563),
//                      fract(sin(dot(co.zyx , vec3(93.989, 67.345, 54.256))) * 24634.6345),
//                      fract(sin(dot(co.yxz , vec3(43.332, 93.532, 43.734))) * 56445.2345)
//                  );
// }


void main() {

    vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
    vec4 tex2 = texture2D(Texture2, TexCoord0.xy);
    vec4 tex4 = texture2D(Texture4, TexCoord0.xy);
    
    vec4 tex5 = texture2D(Texture5, TexCoord0.xy);

    //vec4 texFinal = tex0;
    //texFinal.b = mix( tex0.b, tex2.b, float(tex2.a > 0.0) );

    float objectId = unpack16(tex5.rg);//float(tex4.a > 0.0);
    float newZoom = min(cameraZoom,1.0);
    float baseHeight[4];
    
    baseHeight[0] = unpack16(tex0.rg);
    baseHeight[1] = unpack16(tex2.rg);
    baseHeight[2] = max(unpack16(tex4.rg),baseHeight[0]);
    baseHeight[3] = max(max(baseHeight[0], baseHeight[1]),baseHeight[2]);
    
    float tilt = tiltAmount;
    float itilt = 1.0-tiltAmount;

    vec3 worldPosition = vec3(0.0,0.0,0.0);
    vec2 ssCoord = vec2(0.0);
    
    int i;

    for (i = 0; i < iMax; i++) {
        ssCoord = vec2(TexCoord0.x,1.0-TexCoord0.y)*2.0-1.0;
        
        
        ssCoord.xy *= bufferDim.xy/(newZoom);

        ssCoord.y -= cameraPos.z*tilt*2.0;
        ssCoord.y += baseHeight[i]*tilt*2.0;

        worldPosition.x = (ssCoord.y*0.5/itilt + ssCoord.x*0.5);
        worldPosition.y = (ssCoord.y*0.5/itilt - ssCoord.x*0.5);
        worldPosition.z = baseHeight[i];
        worldPosition.x += cameraPos.x;
        worldPosition.y += cameraPos.y;

        gl_FragData[i] = vec4( worldPosition.xyz, objectId );
    }

    
    
}
