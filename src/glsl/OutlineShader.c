#version 120

uniform sampler2D Texture0;
varying vec2 TexCoord0;
uniform float mapStep;
uniform float texPitch;
uniform float doDilate;

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
}

$

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {

    int i;
    float offsetAmount = 1.0/512.0;

    vec4 tex1 = texture2D(Texture0, TexCoord0.xy);
    
    vec4 tex1u = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y + offsetAmount) );
    vec4 tex1d = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y - offsetAmount) );
    vec4 tex1l = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y) );
    vec4 tex1r = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y) );

    vec4 tex1ul = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex1ur = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex1dl = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y - offsetAmount) );
    vec4 tex1dr = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y - offsetAmount) );


    float thresh = 4.0/255.0;

    float curA = tex1.a;

    if (curA <= thresh) {

    }
    else {
        if (tex1u.a >= thresh) {
            curA = 1.0;
        }
        if (tex1l.a >= thresh) {
            curA = 1.0;
        }
    }

    vec4 finalRes = vec4(curA);   
   


    gl_FragData[0] = finalRes;
}


