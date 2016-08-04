uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;

uniform vec2 u_Resolution;
uniform float u_Zoom;
uniform float u_Section;
//uniform vec4 u_SourceRect;
//uniform vec4 u_DestRect;


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

	vec2 newTC = mod(v_TexCoords*4.0,2.0)/2.0;
	vec2 newTC2 = v_TexCoords;
	newTC2.y = 1.0-newTC2.y;


	vec4 baseval = texture2D( u_Texture0, newTC );
	vec4 basevalo = texture2D( u_Texture0, v_TexCoords );
	
	float res;
	vec4 res2;

	if (u_Section == 0.0) {
		if (newTC2.x < 0.5 && newTC2.y < 0.5 ) {
			res = baseval.r;
			res2 = vec4(1.0,0.0,0.0,1.0);
		}
		if (newTC2.x >= 0.5 && newTC2.y < 0.5 ) {
			res = baseval.g;
			res2 = vec4(0.0,1.0,0.0,1.0);
		}
		if (newTC2.x < 0.5 && newTC2.y >= 0.5 ) {
			res = baseval.b;
			res2 = vec4(0.0,0.0,1.0,1.0);
		}
		if (newTC2.x >= 0.5 && newTC2.y >= 0.5 ) {
			res = baseval.a;
			res2 = vec4(1.0,1.0,0.0,1.0);
		}


		gl_FragColor = mix(vec4(res,res,res,1.0),res2,0.3);
	}

	if (u_Section == 1.0) {
		gl_FragColor = vec4(basevalo.rrr,1.0);
	}
	if (u_Section == 2.0) {
		gl_FragColor = vec4(basevalo.ggg,1.0);
	}
	if (u_Section == 3.0) {
		gl_FragColor = vec4(basevalo.bbb,1.0);
	}
	if (u_Section == 4.0) {
		gl_FragColor = vec4(basevalo.aaa,1.0);
	}

	if (u_Section == 5.0) {
		gl_FragColor = vec4(basevalo.rgb,1.0);
	}

	
	
}