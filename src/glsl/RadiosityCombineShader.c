// result fbo
uniform sampler2D Texture0;

// radiosity buffer
uniform sampler2D Texture1;

// combineFBOWithWater
uniform sampler2D Texture2;

uniform bool testOn;

varying vec2 TexCoord0;

$

void main() {

	TexCoord0 = gl_MultiTexCoord0.xy;
	gl_Position = gl_Vertex;
}

$

void main() {

	vec4 oneVec = vec4(1.0);

	vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
	vec4 tex1 = texture2D(Texture1, TexCoord0.xy);
	vec4 tex2 = texture2D(Texture2, TexCoord0.xy);

	vec3 newRad = pow(tex1.rgb, vec3(1.0) );

	vec3 finalCol = mix(tex0.rgb, tex0.rgb + newRad, newRad * 0.2);
	vec3 resColGS = vec3( clamp(dot(finalCol, oneVec.xyz) / 3.0, 0.0, 1.0) );

	if (tex2.a < 0.5) {
		finalCol = mix(
								 resColGS,
								 finalCol,
								 clamp(1.0 - distance(resColGS, finalCol), 0.0, 1.0) * 1.5 //*mix(0.5,1.0,totLightDis)
							 );
	}
	else {
		finalCol = tex0.rgb;
	}



	if (testOn) {
		finalCol = newRad;
	}
	//finalCol = newRad;// *dot(tex0.rgb,oneVec.rgb)/3.0;
	gl_FragData[0] = vec4(finalCol, 1.0);




}
