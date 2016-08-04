// result fbo
uniform sampler2D Texture0;
uniform vec2 bufferDim;

varying vec2 v_TexCoords;

$

void main()
{
    gl_Position = gl_Vertex;
    v_TexCoords = gl_MultiTexCoord0.xy;

}

$

void main()
{
    vec4 res = texture2D( Texture0, v_TexCoords );
    res += texture2D( Texture0, v_TexCoords+vec2(0.0/bufferDim.x,1.0/bufferDim.y) );
    res += texture2D( Texture0, v_TexCoords+vec2(1.0/bufferDim.x,0.0/bufferDim.y) );
    res += texture2D( Texture0, v_TexCoords+vec2(1.0/bufferDim.x,1.0/bufferDim.y) );

    gl_FragData[0] = vec4(res.rgb/4.0,1.0);

}
