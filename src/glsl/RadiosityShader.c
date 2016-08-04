// pages fbo
uniform sampler2D Texture0;
uniform sampler2D Texture1;

// result fbo
uniform sampler2D Texture2;

// result fbo blurred
//uniform sampler2D Texture3;


// world space waves fbo
uniform sampler2D Texture4;


//uniform sampler2D Texture5;
//uniform sampler2D Texture6;
//uniform sampler2D Texture7;


uniform float cameraZoom;
uniform vec2 bufferDim;
uniform vec2 resolution;
uniform vec3 cameraPos;
uniform vec3 lightPosWS;

varying vec2 TexCoord0;

uniform int iNumSteps;

$

void main() {

	TexCoord0 = gl_MultiTexCoord0.xy;
	gl_Position = gl_Vertex;
}

$

int intMod(int lhs, int rhs) {
	return lhs - ( (lhs / rhs) * rhs );
}

vec2 pack16(float num) {

	int iz = int(num);
	int ir = intMod(iz, 256);
	int ig = (iz) / 256;

	vec2 res;

	res.r = float(ir) / 255.0;
	res.g = float(ig) / 255.0;

	return res;

}

// float unpack16(vec2 num) {
// 	return num.r * 255.0 + num.g * 65280.0;
// }

// float isNotGeom(vec2 num) {
// 	return float ( (unpack16(num)) < 32768.0);
// }


void main() {

	float fNumSteps = float(iNumSteps);

	vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
	vec4 tex1 = texture2D(Texture1, TexCoord0.xy);
	vec4 tex2 = texture2D(Texture2, TexCoord0.xy);
	vec3 oneVec = vec3(1.0);
	
	vec4 tex7 = texture2D(Texture4, TexCoord0.xy);

	float newZoom = min(cameraZoom, 1.0);
	
	
	vec3 worldPosition = tex7.xyz;
	float baseHeight = tex7.z;
	

	vec3 lightVec = normalize(lightPosWS - worldPosition);



	float totHits = 0.0;
	float totRays = 0.0;
	int i;
	int j;
	float fi;
	float fj;



	float curHeight;
	vec2 offsetCoord = vec2(0.0);
	vec4 samp = vec4(0.0);
	vec4 samp2 = vec4(0.0);
	vec4 samp3 = vec4(0.0);
	vec3 newTC = vec3(0.0);
	vec3 baseTC = vec3(0.0);
	vec3 newRes = vec3(0.0);

	vec3 baseNormOrig = normalize((tex1.rgb - 0.5) * 2.0);
	//vec3 baseNormRef = normalize(reflect(lightVec, baseNormOrig));
	vec3 testNormOrig = vec3(0.0);
	vec3 testNormRef = vec3(0.0);

	float pi = 3.14159;

	float minRad = 2.0;
	
	float divVal = 1.0-clamp( distance(TexCoord0.xy,vec2(0.5,0.5))/0.5 ,0.0,1.0);
	
	float maxRad = bufferDim.y / 4.0;//mix(1.0,4.0,divVal);
	float curRad = 0.0;

	float minRotInc = pi;
	float maxRotInc = 0.01;
	float curRotInc = 0.0;
	float curRot = 0.0;

	float minV = 0.0;
	float maxV = 0.0;
	float curV = 0.0;

	float totMin = 0.0;
	float totMax = 0.0;
	float avgVal = 0.0;

	vec3 minMaxCur = vec3(0.0);
	vec3 avgVec = vec3(0.0);

	baseTC.xy = TexCoord0.xy;
	baseTC.z = baseHeight / bufferDim.x;

	vec3 baseVec = vec3(0.0);
	vec3 testVec = vec3(0.0);



	float finalRes = 0.0;
	float disMult = 0.0;

	for (i = 0; i < iNumSteps; i++) {


		fi = float(i) / fNumSteps;

		curRad = mix(minRad, maxRad, fi);
		curRotInc = mix(minRotInc, maxRotInc, fi);

		offsetCoord.x = cos(curRot) * curRad;
		offsetCoord.y = sin(curRot) * curRad;

		newTC.xy = TexCoord0.xy + offsetCoord / (bufferDim / newZoom);
		samp = texture2D(Texture2, newTC.xy );
		samp2 = texture2D(Texture1, newTC.xy );

		testNormOrig = normalize( (samp2.rgb - 0.5) * 2.0 );
		testNormRef = normalize(reflect(lightVec, testNormOrig));

		disMult = clamp(
			//distance(samp3.xyz+testNormRef.xyz*256.0,worldPosition.xyz+baseNormOrig.xyz*256.0)/256.0,
			(samp3.z - worldPosition.z)/256.0,
			0.0,
			1.0
		);

		samp3 = texture2D(Texture4, newTC.xy );
		// newTC.z = samp3.z / bufferDim.x;//unpack16(samp3.rg) / bufferDim.x;
		// testVec = normalize(baseTC - newTC);
		// baseVec = -testVec;

		// finalRes = //(tex2.a * tex1.a * samp.a * samp2.a) *
		// 					 clamp(dot(testNormOrig, testVec), 0.0, 1.0) *
		// 					 clamp(dot(baseNormOrig, baseVec), 0.0, 1.0) *
		// 					 (1.25 - fi);// * float(samp3.a < 0.5); //isNotGeom
		// //* float( dot(lightVec,baseVec) > 0.0 );// *(1.0-dot(oneVec,samp.rgb)/3.0);


		// newRes += finalRes * samp.rgb * clamp(max(dot(baseNormOrig, testNormRef), dot(baseNormRef, -testNormRef)), 0.0, 1.0); // *(1.25-fi); //
		// totRays += mix(finalRes, 1.0, 0.5); // *(1.25-fi);


		newRes += 
			tex2.a * tex1.a * samp.a * samp2.a *
			samp.rgb *
			disMult *
			clamp(dot(testNormRef, baseNormOrig), 0.0, 1.0);
		
		totRays += 1.0;

		curRot += curRotInc;
	}

	newRes = clamp(newRes / (totRays / 16.0), 0.0, 1.0);
	newRes = pow(newRes, vec3(2.0));
	//newRes = min(newRes,normalize(newRes));
	gl_FragData[0] = vec4(newRes*divVal, 1.0);







}
