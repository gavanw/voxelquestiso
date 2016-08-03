uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform float u_Time;

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

	
	vec4 heightRT = texture2D( u_Texture0, v_TexCoords );
	vec4 normRT = texture2D( u_Texture1, v_TexCoords );
	vec3 baseNorm = (normRT.rgb-0.5)*2.0;
	baseNorm.z = 0.0;
	baseNorm = normalize(baseNorm);

	vec3 faceNorm = vec3(0.0,0.0,1.0);
	float curDis = heightRT.b;
	float maxDis = 128.0/255.0;
	float startZ = 0.0;
	float endZ = 1.0;
	float lerpPow = 2.0;
	float lerpAmount = max(maxDis-curDis,0.0)/maxDis;
	
	/*
	// sharp bevel
	lerpAmount = 0.5;
	if (curDis >= 80.0/255.0) {
		lerpAmount = 0.0;
	}*/
	if (curDis <= 16.0/255.0) {
		lerpAmount = 1.0;
	}

	vec3 finalNorm = mix(faceNorm, baseNorm, lerpAmount );

	finalNorm = normalize(finalNorm);


	float alphaVal = heightRT.g;

	
	if (alphaVal == 0.0) {
		discard;
	}

	

	vec4 gIdRGBA;

	float groupId = v_Data0.z;
	gIdRGBA.rg = pack16(groupId);
	//gIdRGBA.r = floor(groupId/256.0)/255.0;
	//gIdRGBA.g = mod(groupId,256.0)/255.0;

	float matId = v_Data0.w;

	gIdRGBA.ba = pack16(matId);
	//gIdRGBA.b = floor(matId/256.0)/255.0;
	//gIdRGBA.a = mod(matId,256.0)/255.0;


	
	gl_FragColor = gIdRGBA;
	
	
}