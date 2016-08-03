uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_Zoom;
uniform vec2 u_Resolution;
uniform float u_MaxLayers;

varying vec2 v_TexCoords;
varying vec3 v_Position;

$



$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords = uv.xy;
	v_Position = position.xyz;
	gl_Position = vec4( position.xyz, 1.0 );

}

$

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}



void main()	{

	vec4 baseval = texture2D( u_Texture0, v_TexCoords );



	vec3 offsetNorm;
	offsetNorm.rg = (baseval.rg-0.5)*2.0;
	offsetNorm.b = abs(sqrt( abs(1.0-(offsetNorm.r*offsetNorm.r+offsetNorm.g*offsetNorm.g) )));

	offsetNorm *= 2.0;

	vec4 samp;
	vec3 tc;

	int i;
	int j;
	int k;
	float fl;
	float fi;
	float fj;
	float fk;
	float dis;

	float fit;
	float fjt;

	float rad;

	const int iMax = 8;
	const int jMax = 5;
	const float fiMax = float(iMax);
	const float fjMax = float(jMax);
	const float pi = 3.14159;

	
	

	float totHits = 0.0;
	float totRays = 0.0;

	float hitPower;

	float phi;
	float theta;

	int counter = 1;

	

	for (int j = 2; j < jMax; j++) {

		fjt = pow( 2.0, float(j) );

		hitPower = (fjMax-fjt)/fjMax;

		

		for (int i = 0; i < iMax; i++) {

			fit = float(i)*pi/fiMax;

			theta = fit/2.0;//1.5*pi;////2.0*pi - fit/2.0;
			phi = 2.0*fit;

			rad = fjt*fit/pi;

			fi = rad*cos(phi+fjt)*sin(theta);
			fj = rad*sin(phi+fjt)*sin(theta);
			fk = rad*cos(theta);

			tc.x = (fi + offsetNorm.x)/u_Resolution.x;
			tc.y = ( (fj - offsetNorm.y) + (fk + offsetNorm.z)  )/u_Resolution.y;
			tc.z = clamp(baseval.b + (fk + offsetNorm.z)/255.0,0.0,u_MaxLayers);

			dis = clamp(sqrt(fi*fi+fj*fj+fk*fk)/fjt,0.0,1.0);

			samp = texture2D( u_Texture0, v_TexCoords + tc.xy );

			if (samp.b < tc.z) {
				totHits += hitPower;
			}

			totRays += hitPower;
		}

		counter++;
	}

	float resVal = (totHits/totRays);

	resVal = clamp(resVal,0.0,1.0);
	resVal = pow(resVal,6.0);

	



	gl_FragColor = vec4(baseval.rgb,resVal);
	//gl_FragColor = vec4(resVal,resVal,resVal,1.0);
	
}