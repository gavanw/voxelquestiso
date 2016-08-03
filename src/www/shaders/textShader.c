uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_MaxLayers;

uniform vec2 u_Scroll;
uniform vec2 u_Resolution;
uniform float u_Zoom;
uniform vec2 u_MouseCoords;
//uniform vec4 u_SourceRect;
//uniform vec4 u_DestRect;


varying vec2 v_TexCoords;
varying vec2 v_Position;
varying vec4 v_Data0;
varying vec4 v_Data1;
varying vec2 v_MouseCoords;

$

attribute vec4 a_Data0;
attribute vec4 a_Data1;


$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords = uv.xy;
	v_Data0 = a_Data0;
	v_Data1 = a_Data1;


	v_Position.x = position.x/u_Resolution.x;
	v_Position.y = position.y/u_Resolution.y;

	v_MouseCoords.x = u_MouseCoords.x / u_Resolution.x;
	v_MouseCoords.y = u_MouseCoords.y / u_Resolution.y;

	vec2 newPos = vec2(-1.0 + ( (position.x*u_Zoom+u_Scroll.x)/u_Resolution.x)*2.0, 1.0 - ( (position.y*u_Zoom+u_Scroll.y )/u_Resolution.y)*2.0);
	gl_Position = vec4( newPos.xy, position.z, 1.0 );

}

$

void main()	{

	
	vec4 heightRT = texture2D( u_Texture0, v_TexCoords );
	vec4 normRT = texture2D( u_Texture1, v_TexCoords );
	vec3 sideNorm = (normRT.rgb-0.5)*2.0;
	sideNorm.z = 0.0;
	sideNorm = normalize(sideNorm);

	vec3 upNorm = vec3(0.0,0.0,1.0);
	float curDis = heightRT.b;
	float maxDis = 128.0/255.0;
	float startZ = 0.0;
	float endZ = 1.0;
	float lerpPow = 2.0;



	vec3 finalNorm = mix(sideNorm, upNorm, min(pow(heightRT.b,2.0)*3.5,1.0) );

	finalNorm = normalize(finalNorm);


	float alphaVal = heightRT.g;

	
	if (alphaVal == 0.0) {
		discard;
	}

	gl_FragColor = vec4((finalNorm.xy+1.0)/2.0, 1.0*u_MaxLayers, 0.0);//v_Data0.w ); //+sin(v_Position.x*v_Position.y*100.0)*10.0
	
	
}