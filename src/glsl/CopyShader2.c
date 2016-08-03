#version 120

uniform sampler2D Texture0;
uniform sampler2D Texture1;
varying vec2 TexCoord0;

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
}

$

void main() {
    gl_FragData[0] = texture2D(Texture0, TexCoord0.xy);
    gl_FragData[1] = texture2D(Texture1, TexCoord0.xy);
}


