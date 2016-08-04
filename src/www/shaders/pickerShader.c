uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_Zoom;
uniform vec2 u_Resolution;
uniform vec2 u_MouseCoords;

uniform vec4 u_PalPos;
uniform vec2 u_PalCoords;

varying vec2 v_TexCoords;
varying vec2 v_Position;




$



$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords.xy = uv.xy;
	//v_TexCoords.y = 1.0-v_TexCoords.y;
	gl_Position = vec4( position.xy*0.5 - 0.5, position.z, 1.0 );

}

$

void main()	{
	vec4 baseVal = texture2D( u_Texture0, v_TexCoords );
	vec4 resVal = baseVal;

	vec2 newMC;
	newMC.x = floor( (u_MouseCoords.x + 1.0)*32.0)/32.0;
	newMC.y = floor( (u_MouseCoords.y + 1.0)*32.0)/32.0;

	float tileSize = 1.0/32.0;
	float borderSize = tileSize/8.0;
	float tempVar = 0.0;

	if (
		(newMC.x >= (v_TexCoords.x-tileSize) ) &&
		(newMC.x <= v_TexCoords.x)
		
	) {

		if (
			(newMC.y >= (v_TexCoords.y-tileSize) ) &&
			(newMC.y <= v_TexCoords.y)
		) {


			tempVar = 1.0;
			
			if (
				(newMC.x >= (v_TexCoords.x-tileSize + borderSize) ) &&
				(newMC.x <= v_TexCoords.x - borderSize)
				
			) {

				if (
					(newMC.y >= (v_TexCoords.y-tileSize) + borderSize ) &&
					(newMC.y <= v_TexCoords.y - borderSize)
				) {
					tempVar = 0.0;
				}
			}


			resVal.rgb = mix(baseVal.rgb,vec3(1.0,0.0,1.0),tempVar);
		}

		
	}


	gl_FragColor = resVal;
	
}