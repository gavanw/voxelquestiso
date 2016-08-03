uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_Zoom;
uniform vec2 u_Resolution;

uniform vec4 u_PalCol;
uniform vec2 u_PalCoords;

varying vec2 v_TexCoords;
varying vec2 v_Position;




$



$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords = uv.xy;
	

	vec2 startCorner = ((u_PalCoords-128.0)*2.0)/256.0;
	vec2 endCorner = ((u_PalCoords-128.0)*2.0 + 2.0)/256.0;

	vec2 newPos;
	newPos.x = mix(startCorner.x, endCorner.x, uv.x);
	newPos.y = mix(startCorner.y, endCorner.y, uv.y);

	newPos.y *= -1.0;


	//v_Position = (position.xy/256.0 - (255.0/256.0));

	//v_Position += 1.0/256.0;

	/*
	v_Position = position.xy/256.0;
	v_Position += u_PalCoords;

	v_Position.xy -= 1.0;
	v_Position.y *= -1.0;
	*/
	
	gl_Position = vec4( newPos.xy, position.z, 1.0 );

}

$

void main()	{

	gl_FragColor = u_PalCol;
	
}