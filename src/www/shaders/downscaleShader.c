uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_Zoom;

uniform vec2 u_Resolution;
uniform vec2 u_TexResolution;


varying vec2 v_TexCoords;

$



$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords = uv.xy;
	gl_Position = vec4( position.xyz, 1.0 );

}

$

void main()	{


	vec4 baseval00 = texture2D( u_Texture0, v_TexCoords );
	vec4 baseval01 = texture2D( u_Texture0, v_TexCoords+vec2(0.0/u_TexResolution.x,1.0/u_TexResolution.y) );
	vec4 baseval10 = texture2D( u_Texture0, v_TexCoords+vec2(1.0/u_TexResolution.x,0.0/u_TexResolution.y) );
	vec4 baseval11 = texture2D( u_Texture0, v_TexCoords+vec2(1.0/u_TexResolution.x,1.0/u_TexResolution.y) );

    gl_FragColor = (baseval00+baseval01+baseval10+baseval11)/4.0;

}