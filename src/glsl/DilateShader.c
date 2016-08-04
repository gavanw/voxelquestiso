#version 120

uniform sampler2D Texture0; //cityFBO
uniform sampler2D Texture1; //hmFBO
varying vec2 TexCoord0;
uniform float mapStep;
uniform float texPitch;
uniform float doDilate;
uniform float seaLevel;

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


    float offsetAmount = 1.0/texPitch;
    float testHeight = 0.0;
    float heightMod = 0.0;
    float tot = 0.0;
    float rand1 = 0.0;
    float rand2 = 0.0;
    float v1 = 0.0;
    float v2 = 0.0;
    float v3 = 0.0;


    vec4 tex1 = texture2D(Texture0, TexCoord0.xy);
    
    vec4 tex1u = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y + offsetAmount) );
    vec4 tex1d = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y - offsetAmount) );
    vec4 tex1l = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y) );
    vec4 tex1r = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y) );

    vec4 tex1ul = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex1ur = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex1dl = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y - offsetAmount) );
    vec4 tex1dr = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y - offsetAmount) );


    vec4 tex2 = texture2D(Texture1, TexCoord0.xy);
    
    vec4 tex2u = texture2D(Texture1, vec2(TexCoord0.x, TexCoord0.y + offsetAmount) );
    vec4 tex2d = texture2D(Texture1, vec2(TexCoord0.x, TexCoord0.y - offsetAmount) );
    vec4 tex2l = texture2D(Texture1, vec2(TexCoord0.x - offsetAmount, TexCoord0.y) );
    vec4 tex2r = texture2D(Texture1, vec2(TexCoord0.x + offsetAmount, TexCoord0.y) );

    vec4 tex2ul = texture2D(Texture1, vec2(TexCoord0.x - offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex2ur = texture2D(Texture1, vec2(TexCoord0.x + offsetAmount, TexCoord0.y + offsetAmount) );
    vec4 tex2dl = texture2D(Texture1, vec2(TexCoord0.x - offsetAmount, TexCoord0.y - offsetAmount) );
    vec4 tex2dr = texture2D(Texture1, vec2(TexCoord0.x + offsetAmount, TexCoord0.y - offsetAmount) );

    

    vec4 finalRes = tex1;
    


    

    if (doDilate == 1.0) {


        if (tex2.r > seaLevel) {
            
            tex1u.b *= float(tex2u.r > seaLevel);
            tex1d.b *= float(tex2d.r > seaLevel);
            tex1l.b *= float(tex2l.r > seaLevel);
            tex1r.b *= float(tex2r.r > seaLevel);
            tex1ul.b *= float(tex2ul.r > seaLevel);
            tex1ur.b *= float(tex2ur.r > seaLevel);
            tex1dl.b *= float(tex2dl.r > seaLevel);
            tex1dr.b *= float(tex2dr.r > seaLevel);

        }
        else {
            tex1u.b *= float(tex2u.r <= seaLevel);
            tex1d.b *= float(tex2d.r <= seaLevel);
            tex1l.b *= float(tex2l.r <= seaLevel);
            tex1r.b *= float(tex2r.r <= seaLevel);
            tex1ul.b *= float(tex2ul.r <= seaLevel);
            tex1ur.b *= float(tex2ur.r <= seaLevel);
            tex1dl.b *= float(tex2dl.r <= seaLevel);
            tex1dr.b *= float(tex2dr.r <= seaLevel);
        }


        // //tex2.r = float(tex2.r > seaLevel);
        // tex2u.b = float(tex2u.r > seaLevel);
        // tex2d.b = float(tex2d.r > seaLevel);
        // tex2l.b = float(tex2l.r > seaLevel);
        // tex2r.b = float(tex2r.r > seaLevel);
        // tex2ul.b = float(tex2ul.r > seaLevel);
        // tex2ur.b = float(tex2ur.r > seaLevel);
        // tex2dl.b = float(tex2dl.r > seaLevel);
        // tex2dr.b = float(tex2dr.r > seaLevel);


        // tex1u.b *= float(tex2u.r == tex2.r);
        // tex1d.b *= float(tex2d.r == tex2.r);
        // tex1l.b *= float(tex2l.r == tex2.r);
        // tex1r.b *= float(tex2r.r == tex2.r);
        // tex1ul.b *= float(tex2ul.r == tex2.r);
        // tex1ur.b *= float(tex2ur.r == tex2.r);
        // tex1dl.b *= float(tex2dl.r == tex2.r);
        // tex1dr.b *= float(tex2dr.r == tex2.r);
        

        v1 = max( max(tex1u.b,tex1d.b), max(tex1l.b,tex1r.b) );
        v2 = max( max(tex1ul.b,tex1dl.b), max(tex1ur.b,tex1dr.b) );
        finalRes.b = max( max(v1,v2), tex1.b);
        //tex1.b = max( v1, tex1.b);
    }
    else {

        //v3 = tex1u.b + tex1d.b + tex1l.b + tex1r.b + tex1ur.b + tex1ul.b + tex1dr.b + tex1dl.b;

        // if (v1 >= 3.0) {
        //     tex1.b = 0.0;
        // }
        // else {
        //     tex1.b = 1.0;
        // }

        // if ( (tex1.b > 0.0) && (v3 <= 4.0) ) {

        // }
        // else {
            
        // }

        v1 = min( min(tex1u.b,tex1d.b), min(tex1l.b,tex1r.b) );
        v2 = min( min(tex1ul.b,tex1dl.b), min(tex1ur.b,tex1dr.b) );
        finalRes.b = min( min(v1,v2), tex1.b);
        //tex1.b = min( v1, tex1.b);

        
    }
    


    gl_FragData[0] = finalRes;
}


