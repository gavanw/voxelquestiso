#version 120

uniform sampler2D Texture0;
uniform sampler2D Texture1;

// noise FBO
uniform sampler2D Texture2;


varying vec2 TexCoord0;

uniform float seaLevel;
uniform vec2 bufferDim;

const float TEX_GRASS = 12.0/255.0;
const float TEX_GRASS2 = 13.0/255.0;

float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
}


$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
}

$

void main() {

	vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
	vec4 tex2 = texture2D(Texture2, TexCoord0.xy);

	float baseHeight = unpack16(tex0.rg);

	float gmod = clamp( (baseHeight - (seaLevel + 128.0) )/128.0, 0.0, 1.0);
	float isGrass = float(((tex0.a >= TEX_GRASS))&&(tex0.a <= TEX_GRASS2));

    gl_FragData[0] = vec4(isGrass,isGrass*gmod*mix(0.5,1.0,tex2.r),0.0,1.0);
}


