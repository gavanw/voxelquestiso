#version 120

varying vec2 TexCoord0;

uniform float waveSpacing;
uniform float curTime;
uniform float cameraZoom;

uniform vec3 cameraPos;
uniform vec2 bufferDim;
uniform vec2 mapDimInPixels;

// world space fbo
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;
uniform sampler2D Texture7;


uniform float tiltAmount;

const float timeScale = 0.0002;
const float pi = 3.14159;
const int numWaves = 8;

float amplitude[8] = float[]( 1.0/16.0, 1.0/32.0, 1.0/2.0, 1.0/4.0, 1.0/8.0, 1.0/64.0, 1.0/128.0, 1.0/256.0 );
float wavelength[8] = float[]( 48.0/1.0, 48.0/5.0, 48.0/9.0, 48.0/19.0, 48.0/29.0, 48.0/41.0, 48.0/53.0, 48.0/68.0 );
float speed[8] = float[]( 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
vec2 direction[8] = vec2[](
    vec2(cos(-0.7),sin(-0.7)),
    vec2(cos(0.4),sin(0.4)),
    vec2(cos(0.1),sin(0.1)),
    vec2(cos(-0.75),sin(-0.75)),
    vec2(cos(-0.2),sin(-0.2)),
    vec2(cos(0.3),sin(0.3)),
    vec2(cos(-0.1),sin(-0.1)),
    vec2(cos(-0.25),sin(-0.25))
);



$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
    gl_Position = gl_Vertex;
}

$



int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}
float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
}


float wave(int i, float x, float y) {
    float frequency = 2.0*pi/(wavelength[i]);// + (sin( (TexCoord0.x + TexCoord0.y)*4.0 + curTime/1000.0 ))*0.001 ;
    float phase = speed[i] * frequency;
    float theta = dot(direction[i], vec2(x, y));
    return amplitude[i] * sin(theta * frequency + curTime*timeScale * phase);
}

float waveHeight(vec2 param) {

    float x = param.x;
    float y = param.y;

    float height = 0.0;
    for (int i = 0; i < numWaves; ++i) {
        height += wave(i, x, y);
    }
    return height;
}

float dWavedx(int i, float x, float y) {
    float frequency = 2*pi/wavelength[i];
    float phase = speed[i] * frequency;
    float theta = dot(direction[i], vec2(x, y));
    float A = amplitude[i] * direction[i].x * frequency;
    float res = A * cos(theta * frequency + curTime*timeScale * phase);
    return res*2.0;
}

float dWavedy(int i, float x, float y) {
    float frequency = 2*pi/wavelength[i];
    float phase = speed[i] * frequency;
    float theta = dot(direction[i], vec2(x, y));
    float A = amplitude[i] * direction[i].y * frequency;
    float res =  A * cos(theta * frequency + curTime*timeScale * phase);
    return res*2.0;
}

vec3 waveNormal(vec2 param) {
    float x = param.x;
    float y = param.y;
    float dx = 0.0;
    float dy = 0.0;
    for (int i = 0; i < numWaves; ++i) {
        dx += dWavedx(i, x, y);
        dy += dWavedy(i, x, y);
    }
    vec3 n = vec3(-dx, -dy, 1.0);
    return normalize(n);
}



void main() {


    float newZoom = min(cameraZoom,1.0);
    
    
    
    // vec4 tex4 = texture2D(Texture4, TexCoord0.xy);
    // vec4 tex5 = texture2D(Texture5, TexCoord0.xy);
    // vec4 tex6 = texture2D(Texture6, TexCoord0.xy);
    
    vec4 tex7 = texture2D(Texture7, TexCoord0.xy);
    vec3 worldPosition = tex7.xyz;
    








    // vec2 tcMod = (vec2(TexCoord0.x,1.0-TexCoord0.y)*2.0-1.0 );
    // tcMod.x *= bufferDim.x/(newZoom);
    // tcMod.y *= bufferDim.y/(newZoom);
    // tcMod.y -= cameraPos.z;
    
    // vec3 worldPosition = vec3(0.0,0.0,0.0);
    // worldPosition.x = tcMod.y + tcMod.x/2.0;
    // worldPosition.y = tcMod.y - tcMod.x/2.0;
    // worldPosition.x += cameraPos.x;
    // worldPosition.y += cameraPos.y;
    // worldPosition.z = 0.0;
    
    
    
    // float tilt = tiltAmount;
    // float itilt = 1.0-tiltAmount;
    // float baseHeight = 0.0;

    // vec3 worldPosition = vec3(0.0,0.0,0.0);
    // vec2 ssCoord = vec2(0.0);
    
    // ssCoord = vec2(TexCoord0.x,1.0-TexCoord0.y)*2.0-1.0;
    // ssCoord.x *= bufferDim.x/(newZoom);
    // ssCoord.y *= bufferDim.y/(newZoom);
    // ssCoord.y -= cameraPos.z*tilt*2.0;
    // ssCoord.y += baseHeight*tilt*2.0;

    // worldPosition.x = (ssCoord.y*0.5/itilt + ssCoord.x*0.5);
    // worldPosition.y = (ssCoord.y*0.5/itilt - ssCoord.x*0.5);
    // worldPosition.z = baseHeight;
    // worldPosition.x += cameraPos.x;
    // worldPosition.y += cameraPos.y;
    
    
    

    vec2 newPos = worldPosition.xy/waveSpacing;

    // float wm = mix(
    //     abs( 
    //         sin(
    //             (curTime)/500.0 + (TexCoord0.x + TexCoord0.y) * 12.0
    //         )
    //     ),
    //     0.25,
    //     1.0
    // )*2.0;

    float waveh = (waveHeight(newPos) )*0.5+0.5;
    vec3 waven = (normalize( waveNormal(newPos) )+1.0)/2.0;

    gl_FragData[0] = vec4(waven,waveh);


}


