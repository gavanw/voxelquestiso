uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;
uniform float u_MaxLayers;

uniform vec2 u_Scroll;
uniform vec2 u_Resolution;
uniform float u_Zoom;
uniform float u_BorderRad;
uniform float u_CornerRad;
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

	
	//uniforms
	vec4 u_Params = vec4(0.5,0.0,0.0,0.0); //x: value, y:? , z:isSelected, w:segments
	//float u_AlphaMod;

	vec2 tcCubed;

	float borderRad = u_BorderRad;

	tcCubed.x = v_TexCoords.x*v_TexCoords.x*v_TexCoords.x;
	tcCubed.y = v_TexCoords.y*v_TexCoords.y*v_TexCoords.y;

	vec2 samp = abs(v_TexCoords);
	float fillRad = borderRad*2.0;
	
	float cornerRad = u_CornerRad;

	vec2 u_Dimensions = v_Data0.xy;

	vec2 sampScaled = samp;
	sampScaled.x *= u_Dimensions.x;
	sampScaled.y *= u_Dimensions.y;

	vec2 cornerPoint = vec2(u_Dimensions-cornerRad);
	vec2 edgePoint = vec2(u_Dimensions-borderRad);
	vec2 edgePointF = vec2(u_Dimensions-fillRad);
	vec2 cornerLengthVec = vec2(sampScaled.x - cornerPoint.x,sampScaled.y - cornerPoint.y);
	float cornerLength = length(cornerLengthVec);

	float isGX = float(sampScaled.x > cornerPoint.x);
	float isGY = float(sampScaled.y > cornerPoint.y);

	float isCorner = isGX*isGY;
	float isNotCorner = 1.0-isCorner;

	float isSide = isNotCorner*isGX;
	float isTop = isNotCorner*isGY;

	float isOpaque = min(float(cornerLength/cornerRad <= 1.0) + isNotCorner,1.0);

	float isEdgeBorder = min(float(sampScaled.x > edgePoint.x) + float(sampScaled.y > edgePoint.y),1.0);
	float isCornerBorder = float(cornerLength > cornerRad-borderRad);
	float isBorder = mix(isEdgeBorder, isCornerBorder, isCorner);

	float isEdgeBorderF = min(float(sampScaled.x > edgePointF.x) + float(sampScaled.y > edgePointF.y),1.0);
	float isCornerBorderF = float(cornerLength > cornerRad-fillRad);
	float isBorderF = mix(isEdgeBorderF, isCornerBorderF, isCorner);

	float bDis;

	if (isCorner == 1.0) {
		bDis = abs(cornerLength - (cornerRad-borderRad) );
	}
	else {
		if (isSide == 1.0) {
			bDis = abs(sampScaled.x - edgePoint.x);
		}
		else {
			bDis = abs(sampScaled.y - edgePoint.y);
		}
	}

	bDis = clamp(1.0-bDis/borderRad,0.0,1.0);

	float bDis2 = 1.0-(max(samp.x*samp.x,samp.y*samp.y));




	//float divAmount = 0.05;
	//float iDivAmount = 1.0-divAmount;
	//float curVal = max(v_TexCoords.x*u_Params.w, v_TexCoords.x);
	//float isNotDiv = float(mod(curVal,1.0) < iDivAmount );
	//isNotDiv = min(isNotDiv + float(v_TexCoords.x > iDivAmount) + float(u_Params.w <= 1.0), 1.0);


	float fillAmount = v_Data1.x;
	float baseDepth = v_Data1.y;
	float isFilled = float((v_TexCoords.x+1.0)/2.0 < fillAmount);// *(1.0-isBorderF);


	//float isFilled2 = float(curVal < u_Params.y)/2.0;

	//float toggleAmount = (1.0-isBorderF)*(isFilled-isFilled2);
	
	//vec2 coords1 = vec2(v_TexCoords.y,u_TexLookup);
	//vec2 coords2 = vec2(v_TexCoords.y,u_TexLookup + 1.0/255.0);
	//vec4 ltex = texture2D(u_Texture1, coords2);
	//vec4 dtex = texture2D(u_Texture1, coords1);
	
	vec4 ltex = vec4(1.0,0.0,0.0,1.0);
	vec4 dtex = vec4(0.0,1.0,0.0,1.0);
	vec4 res = ltex;//mix(dtex,ltex,toggleAmount);



	//////

	
	vec3 norm;
	norm.z = 0.0;
	norm.xy = mix(-tcCubed,tcCubed,isBorder);

	norm = normalize(norm);

	vec3 faceNorm = vec3(0.0,0.0,1.0);
	float curDis = mix(bDis2,bDis,isBorderF);
	float maxDis = 255.0/255.0;
	float startZ = 0.0;
	float endZ = 1.0;
	float lerpPow = 2.0;
	float lerpAmount = clamp(max(maxDis-curDis,0.0)/maxDis,0.0,1.0);
	if (curDis <= 32.0/255.0) {
		if (isBorderF == 1.0) {
			lerpAmount = 1.0;
		}
	}
	vec3 finalNorm = mix(faceNorm, norm, pow(lerpAmount,lerpPow) );

	finalNorm = normalize(finalNorm);
	
	//////




	vec3 normOuter = vec3(bDis);//vec3(cornerLength/fillRad);//vec3(tcCubed.xy,0.0);
	vec3 normInner = vec3(bDis);//vec3(cornerLength/fillRad);//vec3(-tcCubed.xy,0.0);

	//float isStripe = float(mod(v_TexCoords.x*40.0 + v_TexCoords.y*20.0 , 2.0) > 1.0)/16.0;

	vec3 borderCol = finalNorm;//mix(normInner,normOuter,isBorder);//(cornerLengthVec),0.0);

	vec4 colBG;
	colBG.xyz = (borderCol+1.0)/2.0;
	colBG.z = mix((0.25+0.5*isFilled),(1.0),isBorderF)*u_MaxLayers; //(20.0+sin(v_Position.x*50.0+v_Position.y*50.0)*10.0)
	colBG.w = 0.0;//v_Data0.w;

	float aVal = mix(1.0,isOpaque,isBorderF);// *u_AlphaMod;

	if (aVal < 1.0) {
		discard;
	}
	
	//vec4 colBG = vec4(1.0,0.0,0.0,0.5);
	gl_FragColor = colBG;
	
}