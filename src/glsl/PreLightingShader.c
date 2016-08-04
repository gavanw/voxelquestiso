#version 120

// pages fbo
uniform sampler2D Texture0;
uniform sampler2D Texture1;

// pal fbo
uniform sampler2D Texture2;

// world space fbo
uniform sampler2D Texture3;
// uniform sampler2D Texture4;
// uniform sampler2D Texture5;
// uniform sampler2D Texture6;

uniform float holderMod;
uniform float cameraZoom;
uniform float timeOfDay;
uniform float pixelsPerMeter;
uniform float blockSizeInMeters;
uniform float tiltAmount;
uniform vec2 bufferDim;
uniform vec2 mouseCoords;
uniform vec2 resolution;

uniform bool testOn;
uniform bool gridOn;
uniform float curTime;

uniform vec3 cameraPos;

uniform float lightCount;
uniform vec4 lightArr[4 * 6];

const float TEX_GRASS = 12.0 / 255.0;
const float TEX_GRASS2 = 13.0 / 255.0;
const int VECS_PER_LIGHT = 4;

const float TEX_NULL = 0.0;
const float TEX_WATER =     32.0 / 255.0;
const float TEX_METAL =     33.0 / 255.0;
const float TEX_GLASS =     35.0 / 255.0;

const float TEX_PLASTER =   28.0 / 255.0;
const float TEX_MORTAR =  	16.0 / 255.0;

const float TEX_EARTH =   36.0 / 255.0;
const float TEX_BARK =    42.0 / 255.0;


const float TEX_SAND =    14.0 / 255.0;
const float TEX_SAND2 =    15.0 / 255.0;


uniform int iNumSteps;

float offV[2] = float[](
	0.03125,
	0.125
);

float minRad[2] = float[](
	1.0,
	29.0
);
float maxRad[2] = float[](
	32.0,
	255.0
);

varying vec2 TexCoord0;

$

void main()
{

	TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
	gl_Position = gl_Vertex;
}

$



int intMod(int lhs, int rhs)
{
	return lhs - ( (lhs / rhs) * rhs );
}

vec2 pack16(float num)
{

	int iz = int(num);
	int ir = intMod(iz, 256);
	int ig = (iz) / 256;

	vec2 res;

	res.r = float(ir) / 255.0;
	res.g = float(ig) / 255.0;

	return res;

}

float unpack16(vec2 num)
{
	return num.r * 255.0 + num.g * 65280.0;
}

float randf(vec2 co)
{
	return fract(sin(dot(co.xy , vec2(12.9898, 78.233))) * 43758.5453);
}


bool isGeom(float aVal)
{
	return aVal >= 0.5;
	// int test = int(unpack16(num));
	// return (test >= 32768);
}


vec3 unpackColorGeom(vec2 num)
{
	int test = int(unpack16(num));
	ivec3 intRGB;
	vec3 res = vec3(0.0);

	test -= 32768;

	intRGB.b = test / 1024;
	test -= intRGB.b * 1024;

	intRGB.g = test / 32;
	test -= intRGB.g * 32;

	intRGB.r = test;

	res = vec3(intRGB) / 31.0;

	return res;
}

vec3 unpackColor(vec2 num, float lightVal)
{
	return texture2D( Texture2, vec2(lightVal, (num.g * 255.0 + num.r * 2.0 + 0.5) / 255.0 ) ).rgb; //vec3(lightVal);//
	//return vec3(num.r);//
}

vec3 rgb2hsv(vec3 c)
{
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
	vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;
	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}


vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}




vec3 getGlobLightCol()
{

	vec3 glCol = vec3(0.0);

	// 0: moon is high, 1: sun is high

	float timeLerp = 0.0;

	if (timeOfDay < 0.5)
	{
		timeLerp = timeOfDay * 2.0;

		glCol = mix(
							vec3(@lightColRNight@, @lightColGNight@, @lightColBNight@),
							vec3(1.0, 0.8, 0.7),
							timeLerp
						);
	}
	else
	{
		timeLerp = (timeOfDay - 0.5) * 2.0;

		glCol = mix(
							vec3(1.0, 0.8, 0.7),
							vec3(1.0),
							timeLerp
						);
	}

	return glCol;
}

vec3 getFogColor(float lv)
{
	float lvBase = (lv-0.5)*tiltAmount*1.3 + 0.5;
	
	float newlv = clamp( 1.0 - pow( (lvBase - 0.5) * 2.0, 2.0 ), 0.0, 1.0);
	float newlv2 = clamp( 1.0 - pow( (lvBase - 0.5) * 4.0 - 1.0, 2.0 ), 0.0, 1.0);

	vec3 fogColor1 = vec3(0.0);
	vec3 fogColor2 = vec3(0.0);

	// 0: moon is high, 1: sun is high

	float timeLerp = 0.0;

	if (timeOfDay < 0.5)
	{
		timeLerp = timeOfDay * 2.0;

		fogColor1 = mix(
									vec3(0.0, 0.0, 0.05),
									vec3(0.3, 0.1, 0.05),
									timeLerp
								);
		fogColor2 = mix(
									vec3(0.025, 0.0, 0.1),
									vec3(1.0, 0.8, 0.7),
									timeLerp
								);
	}
	else
	{
		timeLerp = (timeOfDay - 0.5) * 2.0;

		fogColor1 = mix(
									vec3(0.3, 0.1, 0.05),
									vec3(0.05, 0.1, 0.3),
									timeLerp
								);
		fogColor2 = mix(
									vec3(1.0, 0.8, 0.7),
									vec3(0.7, 0.8, 1.0),
									timeLerp
								);
	}

	return mix(fogColor1, fogColor2, newlv ) + pow(newlv2, 4.0) * timeLerp / 4.0;
}


void main()
{
	int i;
	int j;
	int k;
	
	float fj;
	float fi;

	float fNumSteps = float(iNumSteps);

	vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
	vec4 tex1 = texture2D(Texture1, TexCoord0.xy);
	vec4 tex3 = texture2D(Texture3, TexCoord0.xy);


	float newZoom = min(cameraZoom, 1.0);
	float tot = float(tex0.r + tex0.g + tex0.b + tex0.a > 0.0);


	bool valIsGeom = isGeom(tex0.a);

	vec3 worldPosition = tex3.xyz;
	

	float totHits = 0.0;
	
	
	
	
	// int rad = 2;
	// vec3 worldPositionAvg = vec3(0.0);
	// for (i = -rad; i <= rad; i++) {
	// 	fi = float(i);
	// 	for (j = -rad; j <= rad; j++) {
	// 		fj = float(j);
			
	// 		worldPositionAvg += texture2D(Texture3, TexCoord0.xy + vec2(fi,fj)/bufferDim ).xyz;
	// 		totHits += 1.0;
	// 	}
	// }
	// worldPositionAvg /= totHits;
	// totHits = 0.0;
	
	
	
	float baseHeight = worldPosition.z;


	vec4 lightPosWS = vec4(0.0);
	vec2 lightPosSS = vec2(0.0);
	vec3 lightVec = vec3(0.0);
	vec3 resColor = vec3(0.0);
	vec3 resColorTemp = vec3(0.0);

	//float resComp3 = 1.0;
	//float resComp2 = 1.0;
	float resComp = 1.0;
	float aoval = tex1.a;
	float notBlank = 1.0;//float(aoval != 0.0);

	float colAmount = mix(0.0625,0.25,timeOfDay);//25;//25;//0.65;



	
	int baseInd;
	float flerp = 0.0;
	float curHeight = 0.0;
	
	float totHits2 = 0.0;
	float wasHit = 0.0;
	//float lastHit = 0.0;

	vec4 oneVec = vec4(1.0);



	vec3 wStartPos = worldPosition;
	vec2 sStartPos = TexCoord0.xy;
	vec3 wEndPos = vec3(0.0);
	vec2 sEndPos = vec2(0.0);

	//vec3 globLightCol = vec3(0.0);

	vec3 wCurPos;
	vec2 sCurPos;
	vec4 samp;
	vec3 resColGS = vec3(0.0);

	vec3 tempVec = vec3(0.0);
	vec3 tempVec2 = vec3(0.0);

	vec3 hsvVal = vec3(0.0);
	vec3 rgbVal = vec3(0.0);

	float ssao = 1.0;
	float totRays;
	float tempv;
	vec2 offsetCoord = vec2(0.0);

	vec4 testTex = vec4(0.0);
	vec3 bucket = vec3(0.0);//tex1.xyz;
	vec3 myVec = vec3(0.0);




	for (i = -2; i <= 2; i += 2)
	{
		fi = float(i);
		for (j = -2; j <= 2; j += 2)
		{
			fj = float(j);

			testTex = texture2D(Texture1, TexCoord0.xy + vec2(fi, fj) / (bufferDim/holderMod) );

			if (testTex.x == 1.0)
			{
				bucket.x += 1.0;
			}
			if (testTex.y == 1.0)
			{
				bucket.y += 1.0;
			}
			if (testTex.z == 1.0)
			{
				bucket.z += 1.0;
			}

		}
	}


	if (aoval == 0.0)
	{

		if (bucket.x > bucket.y)
		{
			if (bucket.x > bucket.z)
			{
				myVec.x = 1.0;
			}
			else
			{
				myVec.z = 1.0;
			}
		}
		else
		{
			if (bucket.y > bucket.z)
			{
				myVec.y = 1.0;
			}
			else
			{
				myVec.z = 1.0;
			}
		}

	}
	else
	{
		myVec = normalize( (tex1.rgb - 0.5) * 2.0 );
	}


	// outlines

	vec2 dirModXY[4];
	dirModXY[0] = vec2(1.0, 0.0);
	dirModXY[1] = vec2(-1.0, 1.0);
	dirModXY[2] = vec2(0.0, 1.0);
	dirModXY[3] = vec2(0.0, -1.0);
	float testHeight = 0.0;
	float bestHeight = 0.0;
	float maxDif = 512.0;
	
	float waterMod;

	float resCompTot = 0.0;
	float frontLightTot = 0.0;

	for (i = 0; i < 4; i++)
	{

		//testTex = texture2D(Texture0, TexCoord0.xy + dirModXY[i].xy/bufferDim );
		testTex = texture2D(Texture3, TexCoord0.xy + dirModXY[i].xy / (bufferDim/holderMod) );

		

		testHeight = abs( baseHeight - testTex.z ); //unpack16(testTex.rg)
		if (testHeight > bestHeight)
		{
			bestHeight = testHeight;
		}


	}
	float outDif = clamp(bestHeight / maxDif, 0.0, 1.0) * 0.25;
	if (tex0.a == TEX_WATER || tex0.a == TEX_NULL) {
		outDif = 0.0;
	}


	float pi = 3.14159;



	float curMin = 1.0;
	float curMax = 1.0;

	float curRad = 0.0;

	float hitCount;

	float minRotInc = pi;
	float maxRotInc = 0.01;
	float curRotInc = 0.0;

	float curRot = 0.0;
	vec2 newTC = vec2(2.0);

	float totDirLight = 0.0;




	float frontLight = 0.0;
	float backLight = 0.0;
	float topLight = 0.0;
	float bottomLight = 0.0;
	float behindLight = 0.0;
	float lightVal = 0.0;
	float newAO = 0.0;
	float lightRes = 0.0;
	float lightFlooding = 0.0;

	float lightDis = 0.0;
	float totLightDis = 0.0;

	float lightColorization = 0.0;
	float totColorization = 0.0;

	float lightIntensity = 0.0;
	float totLightIntensity = 0.0;

	float totNonColored = 0.0;
	float curAO = 0.0;
	float curOff = 0.0;

	vec3 totLightColor = vec3(0.0);
	vec3 totLightColorNoShadow = vec3(0.0);
	vec3 curLightColor = vec3(0.0);
	vec3 testVec = vec3(0.0);

	vec3 globDayColor = getGlobLightCol();

	if (tot == 0.0)
	{
		resColor = getFogColor(TexCoord0.y);
	}
	else
	{



		for (j = 0; j < 2; j++)
		{
			totHits = 0.0;
			totRays = 0.0;

			curMin = minRad[j];
			curMax = maxRad[j];
			curOff = offV[j]*pixelsPerMeter;

			for (i = 0; i < iNumSteps; i++)
			{

				fi = float(i) / fNumSteps;

				curRad = mix(curMin, curMax, fi);
				curRotInc = mix(minRotInc, maxRotInc, fi);

				offsetCoord.x = cos(curRot) * curRad;
				offsetCoord.y = sin(curRot) * curRad;

				newTC = TexCoord0.xy + (offsetCoord) / (bufferDim / newZoom);

				//samp = texture2D(Texture0, newTC );
				//curHeight = unpack16(samp.rg);
				//totHits += (clamp((curHeight - (baseHeight))/(fNumSteps),-1.0,1.0)+1.0)/2.0; // - length(offsetCoord)


				samp = texture2D(Texture3, newTC );
				
				testVec = normalize(samp.xyz - (worldPosition.xyz + myVec * curOff));
				curAO = clamp ( clamp(  ( dot(testVec, myVec) ), 0.0, 1.0), 0.0, 1.0);
				totHits += curAO;
				
				//curHeight = samp.z;
				//totHits += (clamp((curHeight - (baseHeight))/(fNumSteps),-1.0,1.0)+1.0)/2.0; // - length(offsetCoord)
				
				
				
				totRays += 1.0;

				curRot += curRotInc;
			}
			
			// if (j == 1) {
			// 	ssao = clamp( 1.0 - ( totHits / totRays ), 0.0, 1.0) * 2.0 - 1.0;
			// }
			
			curAO = clamp(1.0-( totHits / totRays), 0.0, 1.0);
			//curAO = mix(0.0,1.0,curAO);
			
			ssao *= curAO;
			
			
			
		}
		
		
		
		newAO = clamp(
			ssao
			//(sqrt(ssao)-0.5)*2.0
			
		, 0.0, 1.0);
		
		


		// LIGHT LOOP START
		for (k = 0; k < lightCount; k++)
		{
			baseInd = k * VECS_PER_LIGHT;
			lightPosWS = lightArr[baseInd + 0];
			
			// if (k != 0) {
			// 	lightPosWS.w = 20.0*pixelsPerMeter;
			// }


			if (distance(worldPosition, lightPosWS.xyz) <= lightPosWS.w)
			{
				lightPosSS = lightArr[baseInd + 1].xy;
				curLightColor = lightArr[baseInd + 2].xyz;



				lightDis = 1.0 - clamp(distance(worldPosition, lightPosWS.xyz) / lightPosWS.w, 0.0, 1.0);
				lightVec = normalize(lightPosWS.xyz - worldPosition);
				wEndPos = lightPosWS.xyz;
				sEndPos = lightPosSS;


				lightIntensity = lightArr[baseInd + 2].w;
				lightColorization = lightArr[baseInd + 3].r;
				lightFlooding = lightArr[baseInd + 3].g;

				if (k == 0)
				{
					curLightColor = globDayColor;
					lightIntensity = mix(@lightIntensityNight@, 1.0, timeOfDay);
					lightColorization = mix(@lightColorizationNight@, 0.0, timeOfDay);
					lightFlooding = mix(@lightFloodingNight@, 0.0, timeOfDay);
				}



				// shadows


				

				totHits = 0.0;
				totHits2 = 0.0;
				totRays = 0.0;
				hitCount = 0.0;
				for (i = 0; i < iNumSteps; i++)
				{
					fi = float(i);
					flerp = fi / fNumSteps;

					wCurPos = mix(wStartPos, wEndPos, flerp);
					sCurPos = mix(sStartPos, sEndPos, flerp);

					//samp = texture2D(Texture0, sCurPos);
					//curHeight = unpack16(samp.rg);
					curHeight = texture2D(Texture3, sCurPos).z;
					
					samp = texture2D(Texture0, sCurPos);

					// todo: fix for windows

					//if ( (samp.a < 0.5) && ((samp.a < TEX_METAL) || (samp.a > TEX_GLASS)) ) {//(samp.b*samp.a < 1.0) { // isGeom
					wasHit = float( curHeight > wCurPos.z + 2.0 ); // *clamp(flerp+0.1,0.0,1.0);
					
					waterMod = float( ((samp.a < TEX_WATER) || (samp.a > TEX_GLASS))&&(!isGeom(samp.a)) );
						//float(samp.a != TEX_WATER);
					
					totHits += wasHit*waterMod;
					hitCount += waterMod;
					
					
					//totHits2 += wasHit*float(abs(curHeight - wCurPos.z) <= 64.0);
					//lastHit = mix(lastHit, flerp, wasHit);
					//hitCount += 1.0;
					//}




				}
				// * 4.0 / fNumSteps
				resComp = mix(1.0, 0.0, clamp(totHits/hitCount,0.0,1.0)); // mix(totHits2*16.0/fNumSteps, totHits*4.0/fNumSteps, 1.0));// clamp(distance(sStartPos,sEndPos)*4.0,0.0,1.0)) );
				
				// if (k == 0) {
				// 	resComp3 = mix(1.0, 0.0, clamp(totHits*4.0/hitCount,0.0,1.0));
				// }
				
				//resComp2 = clamp(resComp, 0.3, 1.0);
				resComp = clamp(pow(resComp,2.0), 0.0, 1.0);
				
				resComp = mix(
					resComp,
					resComp*0.75 + 0.25,
					timeOfDay
				);

				// if (aoval == 0.0)
				// {
				// 	resComp *= clamp(dot(myVec, lightVec),0.0,1.0);
				// }
				
				


				frontLight = clamp(dot(myVec, lightVec), 0.0, 1.0);
				backLight = clamp(dot(myVec, -lightVec), 0.0, 1.0);
				
				//frontLight = clamp(frontLight + backLight * 0.2, 0.0, 1.0);
				
				//frontLight = frontLight + backLight*0.2;
				
				topLight = clamp(dot(myVec, vec3(lightVec.x, lightVec.y, -lightVec.z)), 0.0, 1.0);
				bottomLight = clamp(dot(myVec, vec3(0.0, 0.0, -1.0)), 0.0, 1.0);
				behindLight = clamp(dot(myVec, vec3(-lightVec.x, -lightVec.y, 0.0)), 0.0, 1.0);


				totLightDis += lightDis;
				
				//lightColorization *= (1.0-frontLight);
				

				totNonColored += lightDis * resComp * (1.0 - lightColorization);

				totColorization += lightColorization * lightDis * clamp(resComp + lightFlooding, 0.0, 1.0);
				totLightIntensity += lightIntensity * lightDis * resComp;

				totLightColor += frontLight * resComp * curLightColor * lightDis;
				totDirLight += frontLight * resComp * lightDis * float(k != 0);

				totLightColor += vec3(0.0, 1.0, 1.0) * colAmount * (bottomLight) * 0.5 * lightDis;
				totLightColor += vec3(0.9, 0.5, 0.2) * colAmount * (timeOfDay * 0.5 + 0.5) * behindLight * 0.5 * lightDis * (1.0 - frontLight);


				resCompTot += resComp * lightDis;
				frontLightTot += frontLight * lightDis;

				if ( (tex0.a == TEX_GLASS) && (k != 0) )
				{
					//totLightColorNoShadow += vec3(1.0) * curLightColor //max( (backLight + frontLight), 1.0); // 
					totLightColorNoShadow +=  min( (backLight + frontLight), 1.0) * curLightColor * min(lightDis * 4.0, 1.0);
					
				}

			}
		}
		// LIGHT LOOP END


		totNonColored = clamp(totNonColored, 0.0, 1.0);
		resCompTot = clamp(resCompTot, 0.0, 1.0);
		frontLightTot = clamp(frontLightTot, 0.0, 1.0);


		if (valIsGeom)
		{
			resColorTemp = unpackColorGeom(tex0.ba);
		}
		else
		{

			lightVal = clamp( sqrt(dot(oneVec.xyz, totLightColor.xyz) / 3.0), 0.0, 1.0);
			//lightVal = pow(lightVal,0.5);

			lightRes = mix(newAO * 0.1, lightVal*0.8+newAO*0.2, lightVal);
			lightRes = clamp(
				//mix(lightRes,lightRes,clamp(totNonColored,0.0,1.0)),
				lightRes-0.1,
				1.0/255.0,
				1.0
			);
			
			//@lightPower@
			//lightRes = pow(lightRes,lightRes*4.0)*0.2 + lightRes*0.8;


			lightRes = pow(lightRes,0.5)*0.8 + pow(lightRes*0.5+newAO*0.5,4.0)*0.2;
			

			//lightRes *= 0.75;
			
			totHits2 = clamp((totColorization + newAO ) * (1.0 - totNonColored), 0.0, 1.0);

			resColorTemp = unpackColor(tex0.ba, lightRes);
			
			
			
			
			resColorTemp = mix(
				 mix(
					 resColorTemp * vec3(0.2) * newAO * totLightColor + vec3(0.0, 0.0, 0.02),
					 resColorTemp * vec3(0.7, 0.8, 1.0) * newAO + vec3(0.0, 0.0, 0.1),
					 timeOfDay
				 ),
				 resColorTemp,
				 min(frontLightTot + 0.5, 1.0)
			 );//mix(totLightColorNoShadow,vec3(0.0),timeOfDay);



			resColorTemp = mix(
				 resColorTemp,
				 mix(
					 resColorTemp + clamp(totLightColor, 0.0, 1.0) * (lightRes),
					 clamp(totLightColor, 0.0, 1.0) * (lightRes + clamp(totLightDis, 0.0, 1.0) ), //*totLightIntensity
					 totHits2
				 ),

				 totHits2
			 ) * clamp(totLightIntensity, 0.0, 1.0) + totLightColor * 0.2;

			// hsvVal = rgb2hsv(resColorTemp);
			// hsvVal.g = mix(hsvVal.g, hsvVal.g * 0.5, lightRes);
			// hsvVal.b = mix(hsvVal.b, min(hsvVal.b * 2.0, 1.0), lightRes);
			// resColorTemp = hsv2rgb(hsvVal);

			

			resColorTemp = clamp(resColorTemp, 0.0, 1.0);
			
			

			// resColGS = vec3( dot(resColorTemp,oneVec.xyz)/3.0 );

			// resColorTemp = mix(
			//     resColGS,
			//     resColorTemp,
			//     clamp(1.0-distance(resColGS,resColorTemp),0.0,1.0)*1.5//*mix(0.5,1.0,totLightDis)
			// );

		}



		resColor = resColorTemp;
	}


	resColor = clamp(resColor - outDif * float(!valIsGeom), 0.0, 1.0);


	// USE THIS TO DEBUG MODVAL;
	//resColor = mix(resColor*0.2,resColor,tex0.b*2.0);//vec3(tex0.b);






	if ((tot != 0.0) && (!valIsGeom))
	{

		resColorTemp = resColor;

		tempVec = clamp( (worldPosition.xyz - (cameraPos.xyz)) / 2048.0, 0.0, 1.0);

		tempVec2.r = abs(sin( (tempVec.r * 0.25 + tempVec.g * 0.5 + tempVec.b * 0.0) * 4.0 ));
		tempVec2.g = abs(sin( (tempVec.r * 0.0 + tempVec.g * 0.25 + tempVec.b * 0.5) * 4.0 ));
		tempVec2.b = abs(sin( (tempVec.r * 0.5 + tempVec.g * 0.0 + tempVec.b * 0.25) * 4.0 ));

		

		resColorTemp += colAmount * tempVec2 * 0.2 * (newAO) * (1.0 - timeOfDay); //mix(resColorTemp, resColorTemp*tempVec2*newAO, 0.5);

		tempv = 1.0 - dot(resColorTemp.xyz, oneVec.xyz) / 3.0;
		
		
			resColorTemp.r = mix(resColorTemp.r * (newAO + tempv * 0.25), resColorTemp.r, resColorTemp.r * newAO);
			resColorTemp.g = mix(resColorTemp.g * (newAO + tempv * 0.25), resColorTemp.g, resColorTemp.g * newAO);
			resColorTemp.b = mix(resColorTemp.b * (newAO + tempv * 0.25), resColorTemp.b, resColorTemp.b * newAO);

		// resColorTemp.r = mix(resColorTemp.r * newAO, resColorTemp.r, resColorTemp.r * newAO);
		// resColorTemp.g = mix(resColorTemp.g * newAO, resColorTemp.g, resColorTemp.g * newAO);
		// resColorTemp.b = mix(resColorTemp.b * newAO, resColorTemp.b, resColorTemp.b * newAO);

		
		
		hsvVal = rgb2hsv(resColorTemp);
		hsvVal.b += (lightRes + newAO*0.5) * 0.1 * timeOfDay;
		//hsvVal.b += lightRes*(1.0-timeOfDay);
		//hsvVal.g -= resCompTot*(1.0-timeOfDay)*0.25;
		hsvVal.g = hsvVal.g + 0.6 * (1.0 - lightRes);
		hsvVal.b *= mix(resCompTot * 0.25 + 0.25, 1.0, timeOfDay);

		
		if (
			(
				(tex0.a >= TEX_EARTH) &&
				(tex0.a <= TEX_BARK)
			) ||
			(
				(tex0.a >= TEX_SAND) &&
				(tex0.a <= TEX_SAND2)
			)
								
		) {
			tempv = (1.0+sin( worldPosition.z/(@earthScale@*8000.0) ) )/2.0;  //sin( dot(worldPosition.xyz,oneVec.xyz)/5235.0 )
			// tempv = (
			// 	1.0 + 
			// 	sin(
			// 		dot(worldPosition.xyz,oneVec.xyz)/(@earthScale@*8000.0)
			// 	)
			// )/2.0;
			hsvVal.g += mix(-0.1*lightRes,0.2*lightRes,tempv);
			hsvVal.b -= mix(-0.1*lightRes,0.3*lightRes,tempv);
		}
		
		// if (
		// 	(tex0.a >= TEX_GRASS) &&
		// 	(tex0.a <= TEX_GRASS2)	
		// ) {
		// 	hsvVal.r += abs(sin( dot(worldPosition.xyz,oneVec.xyz)/1234.0 )*0.12);
		// 	hsvVal.g += abs(sin( dot(worldPosition.xyz,oneVec.xyz)/1234.0 )*0.3);
		// 	hsvVal.b -= abs(sin( dot(worldPosition.xyz,oneVec.xyz)/1234.0 )*0.2);
			
		// 	//hsvVal.b += abs(sin( dot(worldPosition.xyz,oneVec.xyz)/1742.0 )*0.1);
		// }
		

		// if (
		// 	(tex0.a == TEX_PLASTER)	
		// ) {
		// 	hsvVal.g *= 0.5;
		
		// }
		
		
		
		hsvVal = clamp(hsvVal, 0.0, 1.0);
		resColorTemp = hsv2rgb(hsvVal);
		
		
		//resColorTemp += pow(lightRes*1.4,10.0)*(1.0-timeOfDay)*0.5;



		//resColorTemp += totLightColor * (1.0-timeOfDay);

		resColorTemp = mix(
			mix(resColorTemp*0.25,resColorTemp,pow(newAO,2.0)),
			resColorTemp,
			resCompTot
			//pow(lightRes,4.0)
		);

		resColorTemp += pow( clamp(totDirLight, 0.0, 1.0), 4.0) * (1.0-timeOfDay)*0.5;
		
		resColorTemp += (totLightColorNoShadow*0.5 + dot(totLightColorNoShadow.rgb,oneVec.rgb)/6.0) * (1.0-timeOfDay) ;
		
		resColorTemp += pow(lightRes,4.0)*0.1;
		
		resColor = resColorTemp;


	}


	//TODO: make this based on gridSize
	float unitSizeInPixels = pixelsPerMeter*blockSizeInMeters;
	vec3 grid0 = abs(mod(worldPosition, unitSizeInPixels) - unitSizeInPixels / 2.0) * 2.0;
	float gridVal0 = float(
										 (grid0.x >= (unitSizeInPixels - 4.0 / newZoom)) ||
										 (grid0.y >= (unitSizeInPixels - 4.0 / newZoom))
									 ) * float(aoval != 0.0) * float(!valIsGeom) * clamp(myVec.z - 0.4, 0.0, 1.0);
	
	if (!gridOn)
	{
		gridVal0 = 0.0;
	}
		
	// if (testOn && (!valIsGeom)) {
	// 	resColor = vec3(newAO); //newAO //resCompTot //lightRes
	// }
	
	
	//resColor.rgb += lightRes*0.2*(1.0-timeOfDay);
	

	gl_FragData[0].rgb = resColor;
	gl_FragData[0].rb += gridVal0;
	
	
	// if (texture2D(Texture0, TexCoord0).a == TEX_WATER) {
	// 	gl_FragData[0].rgb = vec3(1.0);
	// }
	
	//gl_FragData[0].rgb = vec3(texture2D(Texture0, TexCoord0).a*4.0);
	
	float gridAmount = 512.0;
	
	//gl_FragData[0].rgb = (worldPosition.xyz-floor(worldPosition.xyz/gridAmount)*gridAmount)/gridAmount;
	//gl_FragData[0].b = 0.0;
	
	
	gl_FragData[0].a = tot;
	
	//gl_FragData[0] = tex1;

}
