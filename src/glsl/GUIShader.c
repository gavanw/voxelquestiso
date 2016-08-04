varying vec3 worldPos;
varying vec4 viewportPos;
uniform vec2 windowSize;
uniform vec2 resolution;

uniform sampler2D Texture0; // chars
uniform sampler2D Texture1; // icons
uniform sampler2D Texture2; // background

uniform float passNum;
uniform float zoom;

//tex coords, position
varying vec4 TexCoord0;

//dimensions, border, cornerRad
varying vec4 TexCoord1;

//bg/fg/tg
varying vec4 TexCoord2;
varying vec4 TexCoord3;
varying vec4 TexCoord4;

//unused
varying vec4 TexCoord5;

//border col
varying vec4 TexCoord6;

//roundness,value
varying vec4 TexCoord7;


$


void main() {
	
	TexCoord0 = gl_MultiTexCoord0;
	TexCoord1 = gl_MultiTexCoord1;
	TexCoord2 = gl_MultiTexCoord2;
	TexCoord3 = gl_MultiTexCoord3;
	TexCoord4 = gl_MultiTexCoord4;
	TexCoord5 = gl_MultiTexCoord5;
	TexCoord6 = gl_MultiTexCoord6;
	TexCoord7 = gl_MultiTexCoord7;

	gl_Position = gl_Vertex;
	worldPos = gl_Vertex.xyz;
	viewportPos = gl_Position;
	
}


$


void main() {
	
	vec3 wp = worldPos;
	vec2 viewportScaled = viewportPos.xy/viewportPos.w;
	
	vec4 placeholder1 = TexCoord4;
	vec4 placeholder2 = TexCoord5;
	
	float cornerRad = TexCoord1.w;
	float borderThresh = 1.0-(TexCoord1.z/cornerRad);
	vec2 cornerDis = (1.0-abs(TexCoord0.zw - 0.5)*2.0);
	vec2 cornerDisScaled = vec2(cornerDis.x*TexCoord1.x*0.5/cornerRad, cornerDis.y*TexCoord1.y*0.5/cornerRad) ;
	
	cornerDisScaled = clamp(1.0-cornerDisScaled,0.0,1.0);

	float resVal = max(cornerDisScaled.x,cornerDisScaled.y);
	float resVal2 = resVal;

	if (cornerDisScaled.x > 0.0 && cornerDisScaled.y > 0.0) {
		resVal2 = length(cornerDisScaled.xy);
	}

	float roundness = TexCoord7.x;

	resVal = mix(resVal,resVal2,roundness);

	vec4 oneVec = vec4(1.0);

	vec4 texel0 = texture2D(Texture0, TexCoord0.xy);
	vec4 texel1 = texture2D(Texture1, TexCoord0.xy);
	
	bool isIcon = TexCoord5.x != 0.0;
	bool isShadow = TexCoord5.y != 0.0;
	
	float yMin = TexCoord5.z;
	float yMax = TexCoord5.w;
	
	float alphaMult = 1.0;
	
	if (worldPos.y > yMin) {
		alphaMult = 1.0-clamp((worldPos.y - yMin)*resolution.y/8.0,0.0,1.0);
	}
	if (worldPos.y < yMax) {
		alphaMult = 1.0-clamp((yMax - worldPos.y)*resolution.y/8.0,0.0,1.0);
	}
	
	vec4 shadowCol = vec4(0.0,0.0,0.0,0.5*alphaMult);
	texel1.a *= alphaMult;
	
	if (isIcon) {
		
		if (dot(texel1.rgb,oneVec.rgb) == 0.0) {
			discard;
		}
		
		if (isShadow) {
			gl_FragColor = shadowCol;
		}
		else {
			gl_FragColor = texel1;
		}
		
		
		
		
		return;
	}
	
	vec4 bgcol = TexCoord2;//mix(TexCoord2, TexCoord3, TexCoord0.w);
	vec4 fgcol = TexCoord3;//mix(TexCoord4, TexCoord5, TexCoord0.w);

	float value = TexCoord7.y;

	if (value > TexCoord0.z) {
		bgcol = TexCoord4;
	}


	float alphaVal = float(resVal < 1.0);
	bgcol.w *= alphaVal;
	bgcol.xyz *= (1.0-resVal/2.0);

	float bval = float(resVal > borderThresh);

	vec4 borderCol = TexCoord6;
	borderCol.w *= alphaVal;
	bval *= borderCol.w;

	bgcol = mix(bgcol,borderCol,bval);


	vec4 resultCol = mix(bgcol,fgcol,texel0.x);
	vec2 bgCoords = (wp.xy+1.0)/2.0;
	

	if (passNum == 0.0) {
		bgCoords += (pow(TexCoord0.zw-vec2(0.5,0.25),vec2(3.0)) )*0.05;
		resultCol = texture2D(Texture2,
			((bgCoords-0.5)*2.0/max(1.0,zoom)+1.0)/2.0
		);
		resultCol.w = 1.0;
	}
	else {
		//resultCol.xyz += pow(clamp( 1.0-distance(TexCoord0.w,0.25), 0.0, 1.0),3.0)*0.3;
	}
	

	if (isShadow) {
		resultCol.rgb = shadowCol.rgb;
		if (resultCol.a > 0.0) {
			resultCol.a = shadowCol.a;
		}
	}
	
	


	resultCol.a *= alphaMult;

	gl_FragColor = resultCol;


}
