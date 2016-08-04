uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;

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


	//float isFilled = float(curVal < u_Params.x)*isNotDiv;
	//float isFilled2 = float(curVal < u_Params.y)/2.0;

	//float toggleAmount = (1.0-isBorderF)*(isFilled-isFilled2);
	
	//vec2 coords1 = vec2(v_TexCoords.y,u_TexLookup);
	//vec2 coords2 = vec2(v_TexCoords.y,u_TexLookup + 1.0/255.0);
	//vec4 ltex = texture2D(u_Texture1, coords2);
	//vec4 dtex = texture2D(u_Texture1, coords1);



	float fillAmount = v_Data1.x;
	float isFilled = float((v_TexCoords.x+1.0)/2.0 < fillAmount);// *(1.0-isBorderF);

	
	vec4 ltex = vec4(1.0,0.0,0.0,1.0);
	vec4 dtex = vec4(0.0,1.0,0.0,1.0);
	vec4 res = ltex;//mix(dtex,ltex,toggleAmount);



	//////
	

	vec4 gIdRGBA;

	float groupId = v_Data0.z;
	gIdRGBA.rg = pack16(groupId);
	//gIdRGBA.r = floor(groupId/256.0)/255.0;
	//gIdRGBA.g = mod(groupId,256.0)/255.0;

	float matId = mix(  mix(v_Data0.w,v_Data1.w,isFilled*(1.0-isBorderF)),  v_Data1.z,  isBorderF);
	gIdRGBA.ba = pack16(matId);
	//gIdRGBA.b = floor(matId/256.0)/255.0;
	//gIdRGBA.a = mod(matId,256.0)/255.0;


	float aVal = mix(1.0,isOpaque,isBorderF);// *u_AlphaMod;

	if (aVal < 1.0) {
		discard;
	}

	
	gl_FragColor = gIdRGBA;
	
}