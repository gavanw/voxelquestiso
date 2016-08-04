uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform sampler2D u_Texture4;
uniform float u_Time;
uniform float u_Zoom;
uniform vec2 u_Resolution;
uniform vec2 u_MouseCoords;

varying vec2 v_TexCoords;
varying vec2 v_Position;
varying vec2 v_MouseCoords;
varying vec2 v_NewMouse;
varying vec2 v_NewPos;



$



$

void main()	{

	vec2 a_TexCoords = uv.xy;
	v_TexCoords = uv.xy;
	

	v_Position = position.xy;
	v_MouseCoords = u_MouseCoords;

	float minDis = min(u_Resolution.x,u_Resolution.y);

	v_NewMouse = vec2(v_MouseCoords.x*u_Resolution.x,v_MouseCoords.y*u_Resolution.y)/minDis;
	v_NewPos = vec2(v_Position.x*u_Resolution.x,v_Position.y*u_Resolution.y)/minDis;

	

	
	gl_Position = vec4( position.xyz, 1.0 );

}

$

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}

vec2 pack16(float num) {

    int iz = int(num);
    int ir = intMod(iz,256);
    int ig = (iz)/256;

    vec2 res;

    res.r = float(ir)/255.0;
    res.g = float(ig)/255.0;

    return res;

}

float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
}

void main()	{

	vec4 baseval = texture2D( u_Texture0, v_TexCoords );
	vec4 baseval2 = texture2D( u_Texture1, v_TexCoords );
	vec4 baseval3 = texture2D( u_Texture2, v_TexCoords );

	


	vec2 newMC = v_MouseCoords;

	newMC.x = (newMC.x+1.0)/2.0;
	newMC.y = (newMC.y+1.0)/2.0;

	vec4 idAtMouse = texture2D( u_Texture2, newMC );

	float lMod = float(idAtMouse.g == baseval3.g) * float(baseval3.g > 0.0);

	float palInd = unpack16(baseval3.ba);
	float matInd = baseval3.b;


	float matIndU = texture2D( u_Texture2, vec2(v_TexCoords.x,v_TexCoords.y-1.0/u_Resolution.y) ).a;
	float matIndD = texture2D( u_Texture2, vec2(v_TexCoords.x,v_TexCoords.y+1.0/u_Resolution.y) ).a;
	float matIndL = texture2D( u_Texture2, vec2(v_TexCoords.x-1.0/u_Resolution.x,v_TexCoords.y) ).a;
	float matIndR = texture2D( u_Texture2, vec2(v_TexCoords.x+1.0/u_Resolution.x,v_TexCoords.y) ).a;
	
	//float outMod = float ( float(matInd != matIndU) + float(matInd != matIndD) + float(matInd != matIndL) + float(matInd != matIndR) );
	//float outMod = float ( float(matInd < matIndU) + float(matInd < matIndD) + float(matInd < matIndL) + float(matInd < matIndR) );
	//float outMod2 = float ( float(matInd > matIndU) + float(matInd > matIndD) + float(matInd > matIndL) + float(matInd > matIndR) );



	vec3 finalNorm;
	finalNorm.rg = (baseval.rg-0.5)*2.0;
	finalNorm.b = abs(sqrt( abs(1.0-(finalNorm.r*finalNorm.r+finalNorm.g*finalNorm.g) )));
	finalNorm = normalize(finalNorm);
	
	//vec3 upNorm = vec3(0.0,0.0,1.0);
	//finalNorm = mix(upNorm,finalNorm,baseval.b*255.0/40.0);
	//finalNorm = normalize(finalNorm);

	vec3 lightVec;


	//timedLight.x -= 0.2;
	//timedLight.y -= 0.2;
	//timedLight.y += cos(u_Time/100.0)/20.0;

	//float disVal = clamp(1.0-clamp(distance(timedLight, v_Position)*1.0,0.0,1.0),0.0,1.0);
	
	/*
	float dis1 = distance(timedLight,vec2(-1.0,-1.0));
	float dis2 = distance(timedLight,vec2(1.0,-1.0));
	float dis3 = distance(timedLight,vec2(1.0,1.0));
	float dis4 = distance(timedLight,vec2(-1.0,1.0));

	float dis5 = max(dis1,dis2);
	float dis6 = max(dis3,dis4);
	float dis7 = max(dis5,dis6);
	*/




	float disVal = (1.0-clamp(distance( v_NewMouse, v_NewPos )*0.5,0.0,1.0));



	disVal += (disVal)*abs(sin(atan( (v_NewMouse.y-v_NewPos.y),(v_NewMouse.x-v_NewPos.x) )*10.0))*0.01;
	disVal = clamp(disVal,0.0,1.0);

	lightVec.xy = v_MouseCoords - v_Position;
	//lightVec.xy = normalize(lightVec.xy);
	lightVec.z = 60.0/255.0;
	lightVec = normalize(lightVec);
	lightVec.y = -lightVec.y;


	

	///////


	vec4 samp;
	vec3 tc;

	int j;
	int k;
	float fi;
	float fj;
	float fk;
	float dis;

	const int loopMax = 64;
	int stepAmount = 1;
	float fLoopMax = float(loopMax);

	float totHits = 0.0;
	float totRays = 0.0;
	float bias = 2.0/255.0;

	//vec3 offsetNorm;

	float lerpVal;
	float heightAtCurPos;
	float lightHeight = 60.0/255.0;

	vec3 startPos = vec3(v_MouseCoords.xy,lightHeight);
	vec3 endPos = vec3(v_Position.xy,baseval.b);
	//vec2 offPos = normalize(endPos.xy-startPos.xy);
	//startPos.xy += offPos.yx*0.1;


	vec3 rayPos;
	float lastHit = 1.0;

	for (int i = 1; i <= loopMax; i ++) {

		fi = float(i);

		lerpVal = fi/fLoopMax;

		rayPos = mix(startPos,endPos,lerpVal);
		heightAtCurPos = texture2D( u_Texture0, (rayPos.xy+1.0)/2.0 ).b;

		if (heightAtCurPos > rayPos.z+bias) {
			totHits += 1.0;
			lastHit = lerpVal;
		}

		totRays += 1.0;


	}

	float shadVal = clamp((1.0 - pow(lastHit,16.0) ) + (1.0-float(totHits>0.0)),0.0,1.0);// 1.0-clamp(float(totHits>0.0)+lastHit,0.0,1.0); //mix(clamp(totHits/totRays,0.0,1.0),float(totHits>0.0),totHits/totRays);

	//shadVal = pow(shadVal,0.3);

	//resVal = clamp(pow(resVal,2.0),0.0,1.0);

	float aoVal = baseval.a;

	float lVal = clamp(dot(finalNorm,lightVec),0.0,1.0)*shadVal*disVal;
	lVal = mix(aoVal*(0.05+disVal*0.25),lVal,lVal); //(lVal+abs(aoVal-0.5)*lVal)/1.5
	lVal *= float(baseval.b > 0.0);

	//lVal = lVal*disVal;


	//lVal += pow(sin((v_TexCoords.x + v_TexCoords.y + u_Time/10000.0)*4.0),10.0)/2.0;//*(u_Time/100.0) );

	//lVal = pow(lVal,0.5)*disVal;

	//lVal = clamp(lVal+abs(aoVal-0.5),0.0,1.0);

	
	//float lValOrig = lVal;
	//float lVal2 = floor(lVal*16.0)/16.0;
	//float dithVal = rand(v_TexCoords)*(lValOrig-lVal2)*16.0;
	

	float dithVal = mod(v_TexCoords.x*u_Resolution.x+v_TexCoords.y*u_Resolution.y, 2.0 );

	//lVal += dithVal/128.0;

	//lVal -= outMod*0.1;//mix(0.0,outMod,lVal)*0.2;

	// - lMod*0.1 + outMod2*lMod + outMod*lMod*0.3

	lVal = clamp(lVal,0.0,1.0);//pow(clamp(lVal-outMod*lMod,0.0,1.0),1.0-lMod*0.5);// pow(,1.0 - lMod*0.3);
	

	vec4 matCol = texture2D( u_Texture3, vec2(lVal, (matInd*255.0 + 0.5)/256.0  ) ); //matInd
	//vec4 matColSel = texture2D( u_Texture3, vec2(lVal,1.0/255.0 + 0.5/255.0) ); //matInd
	

	//vec4 iMatCol = 1.0-texture2D( u_Texture3, vec2(1.0-lVal,matInd + 0.5/255.0) );
	//vec4 palCol = texture2D( u_Texture3, vec2(palInd,0.0) );

	vec4 resCol = matCol;

	int tempInt;
	int hInt;
	int sInt;
	int vInt;
	vec2 resTC = vec2(0.0,0.0);

	if (palInd >= 32768.0 ) {
		palInd -= 32768.0;

		tempInt = int(palInd);

		hInt = tempInt / (32 * 32);
		sInt = (tempInt - (hInt*32*32))/32;
		vInt = tempInt - ((hInt*32 + sInt)*32);

		resTC.x = (float(vInt*32 + hInt) + 0.5)/1024.0;
		resTC.y = (float(31-sInt)+0.5)/96.0;

		resCol.rgb = texture2D(u_Texture4, resTC ).rgb;

	}

	//vec4 matCol2 = matCol;
	//matCol2.r += 0.1;
	//matCol2.g += 0.1;
	//matCol2.b += 0.1;

	//vec4(finalNorm,1.0);//
	//vec4(aoVal,aoVal,aoVal,1.0);//

	//matCol.rgb -= lMod*outMod;
	//matCol.rgb += lMod*outMod2;

	//vec4(lVal,lVal,lVal,1.0);//
	//mix(matCol,matColSel,lMod*0.3);
	resCol.rgb *= float(baseval.b > 0.0);

	gl_FragColor = resCol;//mix(matCol,matCol2,lMod);//vec4(lVal,lVal,lVal,1.0);//mix(palCol,matCol,float(matInd > 0.0));
	
}