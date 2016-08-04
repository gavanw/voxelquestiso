#version 120
#extension GL_ARB_uniform_buffer_object : enable

uniform sampler3D Texture0; //volume texture nearest
uniform sampler3D Texture1; //volume texture linear
uniform sampler2D Texture2; //terrain heightmap
uniform sampler2D Texture3; //terrainID // no longer used
uniform sampler3D Texture4; //ter tex




uniform	float totLayers;
uniform	float pixelsPerMeter;
uniform float volumePitch;

uniform vec4 worldMinBufInPixels;
uniform vec4 worldMaxBufInPixels;

uniform int numEntries;
uniform int paramsPerEntry;

uniform bool hasTree;
uniform bool hasGeom;
uniform bool hasTerrain;
uniform bool hasLines;


uniform vec4 voroArr[27];

uniform vec3 paramArr[256];
uniform float matCountArr[16];

varying vec2 TexCoord0;


float globalFloat;
float shingleMod;
float voroId;
float voroGrad;
vec3 voroPos;
vec4 matResultTer;

const float PI = 3.14159;
const float PIO2 = PI / 2.0;
const float PIO4 = PI / 4.0;
const float invalid = 99999.0;

const int E_GP_VISMININPIXELST = 0;
const int E_GP_VISMAXINPIXELST = 1;
const int E_GP_BOUNDSMININPIXELST = 2;
const int E_GP_BOUNDSMAXINPIXELST = 3;
const int E_GP_CORNERDISINPIXELS = 4;
const int E_GP_POWERVALS = 5;
const int E_GP_POWERVALS2 = 6;
const int E_GP_THICKVALS = 7;
const int E_GP_CENTERPOINT = 8;
const int E_GP_MATPARAMS = 9; // must be last
const int E_GP_LENGTH = 10;

const int E_AP_VISMININPIXELST = 			0;
const int E_AP_VISMAXINPIXELST = 			1;
const int E_AP_ORG = 						2; // origin
const int E_AP_TAN = 						3; // tangent (normalized)
const int E_AP_BIT = 						4; // bitangent (normalized)
const int E_AP_NOR = 						5; // normal (normalized)
const int E_AP_RAD0 = 						6; // radius
const int E_AP_RAD1 = 						7;
const int E_AP_UNUSED1 = 					8;
const int E_AP_MATPARAMS = 					9; // must be last
const int E_AP_LENGTH = 					10;


const float TEX_NULL =    0.0;
const float TEX_GOLD =    1.0;
const float TEX_DIRT =    8.0;
const float TEX_STONE =   10.0;
const float TEX_GRASS =   12.0;
const float TEX_SAND =    14.0;
const float TEX_MORTAR =  16.0;
const float TEX_WOOD =    18.0;
const float TEX_BRICK =   20.0;
const float TEX_SHINGLE =   22.0;
const float TEX_PLASTER =   28.0;
const float TEX_DEBUG =   30.0;
const float TEX_WATER =   32.0;
const float TEX_METAL =   33.0;
const float TEX_GLASS =   35.0;
const float TEX_EARTH =   36.0;
const float TEX_BARK =    41.0;
const float TEX_TREEWOOD =  43.0;
const float TEX_LEAF =    45.0;


const float E_ENT_SUBPARAM_NOT_SEL = 		0.0;
const float E_ENT_SUBPARAM_SEL = 			1.0;
const float E_ENT_SUBPARAM_LENGTH = 		2.0;


const float E_ENT_PARAM_GEOM =		0.0;
const float E_ENT_PARAM_LINES =		1.0; // must be last
const float E_ENT_PARAM_LENGTH =      	2.0;




vec2 dirVecs[4] = vec2[](
										vec2( 1.0,  0.0 ), // right
										vec2( -1.0,  0.0 ), // left
										vec2( 0.0,  1.0 ), // up
										vec2( 0.0,  -1.0 ) // down

									);

vec3 dirVecs2[6] = vec3[](
										 vec3( 1.0,  0.0, 0.0 ), // right
										 vec3( -1.0, 0.0, 0.0 ), // left
										 vec3( 0.0, 1.0, 0.0 ), // up
										 vec3( 0.0, -1.0, 0.0 ), // down
										 vec3( 0.0, 0.0, 1.0 ), // above
										 vec3( 0.0, 0.0, -1.0 ) // below
									 );


mat2 dirMats[4] = mat2[](
										mat2( 0.0, 1.0, -1.0, 0.0 ),   // right
										mat2( 0.0, 1.0, 1.0, 0.0 ),  // left
										mat2( 1.0, 0.0, 0.0, -1.0 ), // up
										mat2( 1.0, 0.0, 0.0, 1.0 )   // down

									);


vec3 voroOffsets[27] = vec3[](
												 vec3(  -1.0,  -1.0,  -1.0  ),
												 vec3(  -1.0,  -1.0,  0.0  ),
												 vec3(  -1.0,  -1.0,  1.0  ),

												 vec3(  -1.0,  0.0,  -1.0  ),
												 vec3(  -1.0,  0.0,  0.0  ),
												 vec3(  -1.0,  0.0,  1.0  ),

												 vec3(  -1.0,  1.0,  -1.0  ),
												 vec3(  -1.0,  1.0,  0.0  ),
												 vec3(  -1.0,  1.0,  1.0  ),



												 vec3(  0.0,  -1.0,  -1.0  ),
												 vec3(  0.0,  -1.0,  0.0  ),
												 vec3(  0.0,  -1.0,  1.0  ),

												 vec3(  0.0,  0.0,  -1.0  ),
												 vec3(  0.0,  0.0,  0.0  ),
												 vec3(  0.0,  0.0,  1.0  ),

												 vec3(  0.0,  1.0,  -1.0  ),
												 vec3(  0.0,  1.0,  0.0  ),
												 vec3(  0.0,  1.0,  1.0  ),



												 vec3(  1.0,  -1.0,  -1.0  ),
												 vec3(  1.0,  -1.0,  0.0  ),
												 vec3(  1.0,  -1.0,  1.0  ),

												 vec3(  1.0,  0.0,  -1.0  ),
												 vec3(  1.0,  0.0,  0.0  ),
												 vec3(  1.0,  0.0,  1.0  ),

												 vec3(  1.0,  1.0,  -1.0  ),
												 vec3(  1.0,  1.0,  0.0  ),
												 vec3(  1.0,  1.0,  1.0  )

											 );






$




void main() {

	TexCoord0 = gl_MultiTexCoord0.xy;
	gl_Position = gl_Vertex;

}

$

float unpack16(vec2 num) {
	return num.r * 255.0 + num.g * 65280.0;
}

int intMod(int lhs, int rhs) {
	return lhs - ( (lhs / rhs) * rhs );
}

float intModF(float v1, int rhs) {
	int lhs = int(v1);
	return float( lhs - ( (lhs / rhs) * rhs ) );
}

vec3 intModFV(vec3 v1, vec3 v2) {
	ivec3 rhs = ivec3(v2);
	ivec3 lhs = ivec3(v1);
	return vec3(lhs - ( (lhs / rhs) * rhs ));
}

float randf(vec2 co) {
	return fract(sin(dot(co.xy , vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 rand(vec3 co) {
	return vec3(
					 fract(sin(dot(co.xyz , vec3(12.989, 78.233, 98.422))) * 43758.8563),
					 fract(sin(dot(co.zyx , vec3(93.989, 67.345, 54.256))) * 24634.6345),
					 fract(sin(dot(co.yxz , vec3(43.332, 93.532, 43.734))) * 56445.2345)
				 );
}
float randf3(vec3 co) {
	return fract(sin(dot(co.xyz , vec3(12.989, 78.233, 98.422))) * 43758.8563);
}



vec3 getShingle(vec3 uvwBase, float uvscale, float baseDepth, float maxDepth) {
	vec3 color;
	vec3 position, useBrick;
	vec3 brickDim;
	vec3 uvw = uvwBase.xyz / uvscale;
	vec3 myResult = vec3(0.0);

	float numScales = 2.0;
	float finalDis = 0.0;

	ivec2 iUV = ivec2(uvw.xy * numScales);
	vec2 dis = uvw.xy * numScales - floor(uvw.xy * numScales);

	dis.y = 1.0 - dis.y;

	float myMod;

	if ( intMod(iUV.x + iUV.y, 2) == 0 ) {

	}
	else {
		dis.x = 1.0 - dis.x;
	}

	myMod = float(intMod(iUV.y, 2));

	if (length(dis) < 1.0) { //(dis.x+dis.y)

		myResult.x = myMod;
		finalDis = 1.0 - (dis.y * 0.5 + 0.5);
	}
	else {
		myResult.x = 1.0 - myMod;
		finalDis = 1.0 - dis.y * 0.5;
	}

	shingleMod = finalDis;//+abs(sin( (uvwBase.x+uvwBase.y)/(2.0*pixelsPerMeter) ));//randf(vec2(finalDis,finalDis));


	if ( baseDepth > ( finalDis * maxDepth ) ) {
		myResult.y = TEX_SHINGLE;
	}
	else {
		myResult.y = TEX_NULL;
	}


	//myResult.w = randf(vec2(iUV.x+iUV.y);

	return myResult;

}

bool brick(vec3 uvw, vec3 uvscale, bool isVert) {
	vec3 color;
	vec3 position, useBrick;
	vec3 brickDim;


	vec3 bricksize;
	bricksize = vec3(1.0, 0.5, 1.0) * uvscale;

	vec3 brickPct = vec3(0.8, 0.8, 0.8);

	position = uvw.xyz / bricksize.xyz;


	if (isVert) {

		if (fract(position.y * 0.5) > 0.5) {
			position.x += 0.5;
		}
	}
	else {
		if (fract(position.y * 0.5) > 0.5) {
			position.x += 0.5;
		}
	}

	position = fract(position - 0.1);
	useBrick = step(position, brickPct.xyz);

	return (useBrick.x * useBrick.y * useBrick.z) > 0.0;
}


float getIntervalF(float valInPix, float intervalInMeters, float widthInMeters ) {

	float intervalInPixels = intervalInMeters * pixelsPerMeter;
	float widthInPixels = widthInMeters * pixelsPerMeter;

	return  abs(abs( mod (valInPix, intervalInPixels) ) - intervalInPixels / 2.0) * 2.0
					-
					(intervalInPixels - widthInPixels);
}

bool getInterval(float valInPix, float intervalInMeters, float widthInMeters ) {

	float intervalInPixels = intervalInMeters * pixelsPerMeter;
	float widthInPixels = widthInMeters * pixelsPerMeter;

	return ( abs(abs( mod (valInPix, intervalInPixels) ) - intervalInPixels / 2.0) * 2.0 > (intervalInPixels - widthInPixels) );
}

float getIntervalSpaced(float valInPix, float intervalInMeters, float spacingInMeters) {

	float r0 = 1.0 - float(getInterval(valInPix + 0.5 * intervalInMeters * pixelsPerMeter, intervalInMeters, spacingInMeters));
	float r1 = float(getInterval(valInPix, 2.0 * intervalInMeters, intervalInMeters));

	return r0 * (r1 + 1.0);

}

float getBoardSpaced(vec3 coords, vec3 dimInMeters, float boardSpacing) {


	vec4 res = vec4(0.0);
	vec3 zeroVec = vec3(0.0);

	res.y = getIntervalSpaced(
						coords.y,
						dimInMeters.y,
						boardSpacing
					);
	res.x = getIntervalSpaced(
						coords.x + (0.5 * dimInMeters.x) * pixelsPerMeter * float(res.y > 1.0),
						dimInMeters.x,
						boardSpacing
					);

	res.z = getIntervalSpaced(
						coords.z,
						dimInMeters.z,
						boardSpacing
					);


	return float(all(greaterThan(res.xyz, zeroVec))) * (res.x + res.y * 2.0);


}

float getWoodGrain(float normalUID, vec3 worldPosInPixels, float woodRad, float boardDir, float stretchAmount) {
	float woodDiam = woodRad * 2.0;

	vec3 newPos = vec3(0.0);//worldPosInPixels.xyz;

	if (boardDir == 0.0) {
		newPos = worldPosInPixels.xyz;
	}
	if (boardDir == 1.0) {
		newPos = worldPosInPixels.yxz;
	}
	if (boardDir == 2.0) {
		newPos = worldPosInPixels.zyx;
	}
	if (boardDir == 3.0) {
		newPos = worldPosInPixels.zyx;
		//worldPosInPixels.y += worldPosInPixels.z;

	}

	vec2 woodCenter = floor( (newPos.xy + woodRad) / woodDiam) * woodDiam;
	vec2 woodVec = normalize(newPos.xy - woodCenter);
	float woodLen = newPos.z;


	woodCenter.y *= stretchAmount;
	newPos.y *= stretchAmount;


	float woodAngle = atan(woodVec.y, woodVec.x);
	float finalMod = (sin(

											( distance(newPos.xy + mod(normalUID, 4.0) * pixelsPerMeter, woodCenter) + (woodRad / 2.0) ) *
											( (8.0 + sin(woodAngle * 24.0 ) * 0.0625 + sin(woodAngle * 12.0 ) * 0.125 + sin(woodLen / 16.0) * 0.5 + sin(woodLen / 4.0) * 0.25  ) / (woodRad / sqrt(2.0)) )

										));
	if (finalMod < 0.0) {
		finalMod = (1.0 - finalMod) / 2.0;
	}

	return finalMod;
}

float getBoard(vec2 coords, float boardPitch, float boardLength) {

	if ( getInterval(coords.y, 2.0 * boardPitch, boardPitch) ) {
		if ( getInterval(coords.x, 2.0 * boardLength, boardLength) ) {
			return 0.0;
		}
		else {
			return 1.0;
		}
	}
	else {
		if ( getInterval(coords.x + (0.5 * boardLength)*pixelsPerMeter, 2.0 * boardLength, boardLength) ) {
			return 2.0;
		}
		else {
			return 3.0;
		}
	}


}


float cell3D(vec3 P) {
	// source: http://github.com/BrianSharpe/Wombat/blob/master/Cellular3D.glsl

	//  establish our grid cell and unit position
	vec3 Pi = floor(P);
	vec3 Pf = P - Pi;

	// clamp the domain
	Pi.xyz = Pi.xyz - floor(Pi.xyz * ( 1.0 / 69.0 )) * 69.0;
	vec3 Pi_inc1 = step( Pi, vec3( 69.0 - 1.5 ) ) * ( Pi + 1.0 );

	// calculate the hash ( over -1.0->1.0 range )
	vec4 Pt = vec4( Pi.xy, Pi_inc1.xy ) + vec2( 50.0, 161.0 ).xyxy;
	Pt *= Pt;
	Pt = Pt.xzxz * Pt.yyww;
	const vec3 SOMELARGEFLOATS = vec3( 635.298681, 682.357502, 668.926525 );
	const vec3 ZINC = vec3( 48.500388, 65.294118, 63.934599 );
	vec3 lowz_mod = vec3( 1.0 / ( SOMELARGEFLOATS + Pi.zzz * ZINC ) );
	vec3 highz_mod = vec3( 1.0 / ( SOMELARGEFLOATS + Pi_inc1.zzz * ZINC ) );
	vec4 hash_x0 = fract( Pt * lowz_mod.xxxx ) * 2.0 - 1.0;
	vec4 hash_x1 = fract( Pt * highz_mod.xxxx ) * 2.0 - 1.0;
	vec4 hash_y0 = fract( Pt * lowz_mod.yyyy ) * 2.0 - 1.0;
	vec4 hash_y1 = fract( Pt * highz_mod.yyyy ) * 2.0 - 1.0;
	vec4 hash_z0 = fract( Pt * lowz_mod.zzzz ) * 2.0 - 1.0;
	vec4 hash_z1 = fract( Pt * highz_mod.zzzz ) * 2.0 - 1.0;

	//  generate the 8 point positions
	const float JITTER_WINDOW = 0.166666666;  // 0.166666666 will guarentee no artifacts.
	hash_x0 = ( ( hash_x0 * hash_x0 * hash_x0 ) - sign( hash_x0 ) ) * JITTER_WINDOW + vec4( 0.0, 1.0, 0.0, 1.0 );
	hash_y0 = ( ( hash_y0 * hash_y0 * hash_y0 ) - sign( hash_y0 ) ) * JITTER_WINDOW + vec4( 0.0, 0.0, 1.0, 1.0 );
	hash_x1 = ( ( hash_x1 * hash_x1 * hash_x1 ) - sign( hash_x1 ) ) * JITTER_WINDOW + vec4( 0.0, 1.0, 0.0, 1.0 );
	hash_y1 = ( ( hash_y1 * hash_y1 * hash_y1 ) - sign( hash_y1 ) ) * JITTER_WINDOW + vec4( 0.0, 0.0, 1.0, 1.0 );
	hash_z0 = ( ( hash_z0 * hash_z0 * hash_z0 ) - sign( hash_z0 ) ) * JITTER_WINDOW + vec4( 0.0, 0.0, 0.0, 0.0 );
	hash_z1 = ( ( hash_z1 * hash_z1 * hash_z1 ) - sign( hash_z1 ) ) * JITTER_WINDOW + vec4( 1.0, 1.0, 1.0, 1.0 );

	//  return the closest squared distance
	vec4 dx1 = Pf.xxxx - hash_x0;
	vec4 dy1 = Pf.yyyy - hash_y0;
	vec4 dz1 = Pf.zzzz - hash_z0;
	vec4 dx2 = Pf.xxxx - hash_x1;
	vec4 dy2 = Pf.yyyy - hash_y1;
	vec4 dz2 = Pf.zzzz - hash_z1;
	vec4 d1 = dx1 * dx1 + dy1 * dy1 + dz1 * dz1;
	vec4 d2 = dx2 * dx2 + dy2 * dy2 + dz2 * dz2;


	float divAmount = 1.0;

	d1 = min(d1, d2);
	d1.xy = min(d1.xy, d1.wz);
	float finalRes = min(d1.x, d1.y) * ( 9.0 / 12.0 ); // return a value scaled to 0.0->1.0


	return finalRes;

}


// return vec2
// x: distance from line sp0->sp1
// y: percentage between sp0->sp1 (0.0->1.0)

vec4 pointSegDistance(vec3 testPoint, vec3 sp0, vec3 sp1)
{
	vec3 v = sp1 - sp0;
	vec3 w = testPoint - sp0;

	float d0 = distance(testPoint, sp0);
	float d1 = distance(testPoint, sp1);
	float d2 = distance(sp0, sp1);

	float newVal = -1.0;

	float c1 = dot(w, v);
	if ( c1 <= 0 ) {
		return vec4(sp0, 0.0);
	}

	float c2 = dot(v, v);
	if ( c2 <= c1 ) {
		return vec4(sp1, 1.0);
	}

	float b = c1 / c2;
	vec3 testPoint2 = sp0 + b * v; // testPoint2 is the nearest point on the line
	return vec4(testPoint2, distance(testPoint2, sp0) / d2 );
}


void getCobble(vec3 worldPosInPixels) {

	vec4 myResult = vec4(0.0);

	vec4 curPos;
	vec3 bestPos = vec3(0.0);
	vec3 nextBestPos = vec3(0.0);
	float curVoroDis;
	float notValid = 99999.0;
	float minDis1 = notValid;
	float minDis2 = notValid;
	float gradVal;
	vec3 randNum = vec3(0.0);
	vec3 oneVec = vec3(1.0);
	float bestRand;

	int i;

	for (i = 0; i < 27; i++) {
		curPos = voroArr[i];

		curVoroDis = distance(curPos.xyz, worldPosInPixels);// *wpz;

		if (curVoroDis < minDis1) {
			nextBestPos = bestPos;
			bestPos = curPos.xyz;

			minDis2 = minDis1;
			minDis1 = curVoroDis;
		}
		else {
			if (curVoroDis < minDis2) {
				nextBestPos = curPos.xyz;
				minDis2 = curVoroDis;
			}
		}
	}

	bestRand = randf3(bestPos);

	gradVal = (clamp(1.0 - (minDis1 * 2.0 / (minDis1 + minDis2)), 1.0 / 255.0, 1.0));

	voroId = floor(bestRand * 120.0) + 1.0;
	voroGrad = gradVal;
	voroPos = bestPos;

}

vec4 getSlats(vec4 newUVW, float thickness, vec3 origin, vec3 worldPosInPixels, vec3 visMinInPixels, vec3 visMaxInPixels, bool isVert, float isWindow) {

	vec4 myResult = vec4(0.0);
	vec3 orig = vec3(0.0);
	vec3 rad = vec3(0.0);
	bool bDis1 = false;
	bool bDis2 = false;
	bool bDis3 = false;
	bool bIsWindow = bool(isWindow);

	float thickMod = 0.0;

	if (isVert) {

	}
	else {
		worldPosInPixels.xy = worldPosInPixels.yx;
		visMinInPixels.xy = visMinInPixels.yx;
		visMaxInPixels.xy = visMaxInPixels.yx;
		origin.xy = origin.yx;
	}

	orig = (visMaxInPixels + visMinInPixels) / 2.0;
	rad = (visMaxInPixels - visMinInPixels) / 2.0;


	thickMod = mix(0.1875, 0.1875 / 2.0, isWindow);
	bDis2 = distance(worldPosInPixels.x, origin.x) < thickMod * pixelsPerMeter;





	bDis1 = (
						(distance(worldPosInPixels.z, orig.z + 0.5 * pixelsPerMeter) < thickMod * pixelsPerMeter / 2.0) ||
						(distance(worldPosInPixels.z, orig.z - 0.5 * pixelsPerMeter) < thickMod * pixelsPerMeter / 2.0)
					) && (!bIsWindow);

	bDis3 = (distance(worldPosInPixels.z, orig.z) < thickMod * pixelsPerMeter / 2.0) && bIsWindow;

	if (bDis1 || bDis2 || bDis3) {
		myResult.y = mix(TEX_WOOD, TEX_METAL, isWindow);
		myResult.w = float(isVert);
		myResult.x = 20.0 + float(bDis2);
	}
	else {

		if (
			(distance(worldPosInPixels.y, orig.y) < rad.y / 2.0) &&
			(!bDis2)
		) {
			myResult.y = mix(TEX_WOOD, TEX_GLASS, isWindow);
			myResult.w = 2.0;
			myResult.x = (1.0 + floor(distance(worldPosInPixels.x, visMinInPixels.x) / (0.375 * pixelsPerMeter) )) * (1.0 - isWindow);
		}
		else {
			myResult.y = TEX_NULL;
		}


	}




	if (myResult.x != 0.0) {
		myResult.x += float(worldPosInPixels.x > origin.x) * 10.0;
	}



	return myResult;
}




vec4 getLines(vec3 worldPosInPixels) {


	int i;
	int baseInd = 0;

	vec4 matResult = vec4(0.0);

	vec3 visMinInPixels = vec3(0.0);
	vec3 visMaxInPixels = vec3(0.0);
	vec3 matParams = vec3(0.0);
	vec3 p0 = vec3(0.0);
	vec3 p1 = vec3(0.0);
	vec3 tbnRad0 = vec3(0.0);
	vec3 tbnRad1 = vec3(0.0);
	vec3 tanVec = vec3(0.0);
	vec3 tanVecNoNorm = vec3(0.0);
	vec3 bitVec = vec3(0.0);
	vec3 norVec = vec3(0.0);
	
	float curDis = 0.0;
	
	vec4 dres = vec4(0.0);
	float curThickness = 0.0;
	
	vec3 perpVec = vec3(0.0);
	
	float lerpVal = 0.0;
	float bitOrNor = 0.0;
	float tanOrBN = 0.0;

	for (i = 0; i < numEntries; i++) {

		baseInd = i * paramsPerEntry;
		matParams = paramArr[baseInd + E_AP_MATPARAMS];


		if (matParams.x == E_ENT_PARAM_LINES) {

			visMinInPixels = paramArr[baseInd + E_AP_VISMININPIXELST];
			visMaxInPixels = paramArr[baseInd + E_AP_VISMAXINPIXELST];


			if (
				all( lessThanEqual(worldPosInPixels, visMaxInPixels) ) &&
				all( greaterThanEqual(worldPosInPixels, visMinInPixels) )
			) {

				p0 = paramArr[baseInd + E_AP_ORG];
				p1 = paramArr[baseInd + E_AP_ORG];
				
				
				tanVecNoNorm = paramArr[baseInd + E_AP_TAN];
				
				tanVec = normalize(tanVecNoNorm);
				bitVec = paramArr[baseInd + E_AP_BIT];
				norVec = paramArr[baseInd + E_AP_NOR];
				tbnRad0 = paramArr[baseInd + E_AP_RAD0];
				tbnRad1 = paramArr[baseInd + E_AP_RAD1];
				
				p0 -= tanVecNoNorm;
				p1 += tanVecNoNorm;
				

				dres = pointSegDistance(worldPosInPixels, p0, p1);
				curDis = distance(worldPosInPixels,dres.xyz);
				
				perpVec = normalize(worldPosInPixels.xyz-dres.xyz);
				
				bitOrNor = clamp(abs(dot(perpVec,norVec)),0.0,1.0);
				tanOrBN = clamp(abs(dot(perpVec,tanVec)),0.0,1.0);
				
				lerpVal = pow(clamp(dres.w,0.0,1.0),2.0);
				
				curThickness =
					
					
					mix(
						mix( tbnRad0.y, tbnRad0.z, bitOrNor ),
						mix( tbnRad1.y, tbnRad1.z, bitOrNor ),
						lerpVal
					);
					
					// mix(
					// 	mix(
					// 		mix( tbnRad0.y, tbnRad0.z, bitOrNor ),
					// 		mix( tbnRad1.y, tbnRad1.z, bitOrNor ),
					// 		lerpVal
					// 	),
					// 	mix(tbnRad0.x,tbnRad1.x,lerpVal),
					// 	lerpVal//abs(lerpVal-0.5)*2.0	
					// );
					
					

				if (curDis < curThickness) {
					
					matResult.x = 2.0+matParams.z;
					
					matResult.y = matParams.y;
					
					
					matResult.z = 1.0;
					matResult.w = 1.0;
				}
				
				

			}
		}
	}

	return matResult;
}

vec4 getGeom(vec3 worldPosInPixels, int iCurMat) {//, float terHeight) {

	float curMat = float(iCurMat);

	int i;
	int j;
	int k;

	int bestI = 0;
	int baseInd;

	//int n;
	//int nMax = 1;
	int bestInd[2];
	int tallestInd = 0;
	bestInd[0] = -1;
	bestInd[1] = -1;
	float bestHeight[2];
	bestHeight[0] = 0.0;
	bestHeight[1] = 0.0;

	float insetAmount = 0.0;
	float counter = 0.0;
	float m = 0.0;
	float resXY = 0.0;
	float res = 0.0;
	float resNoRef = 0.0;
	float resNoRefVisDis = 0.0;
	float resNoRefVisDisZ = 0.0;
	float resMin = 0.0;
	float resMax = 0.0;
	float visDis = 0.0;
	float visDisXY = 0.0;
	float visDisZ = 0.0;
	float tempf1 = 0.0;
	float tempf2 = 0.0;
	float tempf3 = 0.0;
	float curDis = 0.0;
	float curRad = 0.0;
	float curThe = 0.0;
	float curPhi = 0.0;
	float normalUID = 0.0;
	float thickness = 0.0;
	float wThickness = 0.0;
	float floorHeight = 0.0;
	float disCenterMinMax = 0.0;

	//float nearestJoint = invalid;
	float bestDis = invalid;
	float nextBestDis = invalid;
	float testDis = 0.0;



	float nearestJointXY = invalid;
	float bestDisXY = invalid;
	float nextBestDisXY = invalid;
	float testDisXY = 0.0;
	//float testHeight = 0.0;
	//float tallestHeight = 0.0;

	float finalMod = 0.0;
	float finalMat = TEX_NULL;

	float stairHeight;

	float stairVal = 0.0;

	float maxDisInPixels = 0.0;
	float disInPixels = 0.0;
	float sqrt3 = sqrt(3.0);
	float resXYInside = 0.0;
	float resInside = 0.0;
	float woodRes = 0.0;

	float divDis = 0.0625 * pixelsPerMeter;

	bool doProc = false;

	// bool isRoof[2];
	// isRoof[0] = false;
	// isRoof[1] = false;

	bool isInside = false;
	// bool isInside[2];
	// isInside[0] = false;
	// isInside[1] = false;

	// bool isTower[2];
	// isTower[0] = false;
	// isTower[1] = false;

	//bool isTower = false;


	vec2 topVals = vec2(0.0);

	//vec3 worldPosInPixelsOrig = worldPosInPixels;
	vec3 coefMin = vec3(0.0);
	vec3 coefMax = vec3(0.0);
	vec3 boundsMinInPixels = vec3(0.0);
	vec3 boundsMaxInPixels = vec3(0.0);
	vec3 visMinInPixels = vec3(0.0);
	vec3 visMaxInPixels = vec3(0.0);
	vec3 centerPoint = vec3(0.0);
	vec3 cornerDisInPixels = vec3(0.0);
	vec3 powerVals = vec3(0.0);
	vec3 powerVals1 = vec3(0.0);
	vec3 powerVals2 = vec3(0.0);
	vec3 thickVals = vec3(0.0);
	vec3 matParams = vec3(0.0);
	//vec3 coefficients = vec3(0.0);
	//vec3 squareVals = vec3(0.0);
	//vec3 minMaxMat1 = vec3(0.0);
	//vec3 minMaxMat2 = vec3(0.0);
	//vec3 dirFlags = vec3(0.0);

	vec3 newVisMinInPixels = vec3(0.0);
	vec3 newVisMaxInPixels = vec3(0.0);
	//vec3 innerDisInPixels = vec3(0.0);

	vec3 originInPixels = vec3(0.0);
	vec3 originInPixelsVoro = vec3(0.0);
	vec3 dis = vec3(0.0);
	vec3 absDis = vec3(0.0);
	vec3 disNorm = vec3(0.0);
	vec3 absDisNorm = vec3(0.0);
	vec3 absDisNormalized = vec3(0.0);
	vec3 newCornerDis = vec3(0.0);
	vec3 radInPixels = vec3(0.0);

	vec3 boundsMinCorner = vec3(0.0);
	vec3 boundsMaxCorner = vec3(0.0);
	//vec3 slack = vec3(0.0,0.0,0.0)*pixelsPerMeter; //vec3(0.125,0.125,0.0)*pixelsPerMeter;//vec3(0.0,0.0,0.0)*pixelsPerMeter; //

	vec3 radInPixelsTopUV = vec3(0.0);
	vec3 newCornerDisTopUV = vec3(0.0);
	vec3 originInPixelsTopUV = vec3(0.0);
	vec3 disTopUV = vec3(0.0);
	vec3 disNormTopUV = vec3(0.0);
	vec3 absDisNormTopUV = vec3(0.0);

	vec4 matResult = vec4(0.0); //x: normalID, y: material



	vec3 centerMin = vec3(0.0);
	vec3 centerMax = vec3(0.0);

	vec3 tempVec = vec3(0.0);
	vec3 tempVec2 = vec3(0.0);
	vec3 tempVec3 = vec3(0.0);
	vec3 orig = vec3(0.0);
	vec3 origVis = vec3(0.0);
	vec3 normLen = vec3(0.0);
	vec3 eqRes = vec3(0.0);
	vec3 eqResMax = vec3(0.0);
	vec3 oneVec = vec3(1.0);
	vec3 zeroVec = vec3(0.0);
	vec4 newUVW = vec4(0.0);

	vec4 archRes = vec4(0.0);
	vec3 brickCoords = vec3(0.0);
	float brickRes = 0.0;

	bvec3 bLessThanOrig;
	int nodeDir;
	bool isVert;
	bool isDivider = false;
	bool isInsideCorners = false;
	bool testRes = false;
	bool thickInside = false;
	bool bestVert = false;
	bool nextBestVert = false;

	bool tempb = false;
	bool tempb2 = false;

	//int visCount = 0;



	for (i = 0; i < numEntries; i++) {

		baseInd = i * paramsPerEntry;
		matParams = paramArr[baseInd + E_GP_MATPARAMS];

		if (matParams.x == curMat) {

			boundsMinInPixels = paramArr[baseInd + E_GP_BOUNDSMININPIXELST];
			boundsMaxInPixels = paramArr[baseInd + E_GP_BOUNDSMAXINPIXELST];
			visMinInPixels = paramArr[baseInd + E_GP_VISMININPIXELST] + 1.0;
			visMaxInPixels = paramArr[baseInd + E_GP_VISMAXINPIXELST];
			centerPoint = paramArr[baseInd + E_GP_CENTERPOINT];
			
			//thickVals = paramArr[baseInd+E_GP_THICKVALS];

			// if (thickVals.y != 0.0) {
			//  visMinInPixels.z = terHeight - thickVals.y;
			//  visMaxInPixels.z = terHeight + thickVals.y;

			//  boundsMinInPixels.z = visMinInPixels.z;
			//  boundsMaxInPixels.z = visMaxInPixels.z;
			// }


			if (
				all( lessThanEqual(worldPosInPixels, visMaxInPixels) ) && //+slack
				all( greaterThan(worldPosInPixels, visMinInPixels) ) //-slack
			) {


				//orig = (boundsMaxInPixels + boundsMinInPixels) / 2.0;
				testDisXY = distance(worldPosInPixels.xy,centerPoint.xy);
				
				radInPixels = (boundsMaxInPixels - boundsMinInPixels) / 2.0;
				isVert = radInPixels.x < radInPixels.y;

				// radInPixelsTopUV = (boundsMaxInPixels - boundsMinInPixels)*0.5;
				// newCornerDisTopUV.xy = vec2(min(radInPixelsTopUV.x,radInPixelsTopUV.y));
				// newCornerDisTopUV.z = min(radInPixelsTopUV.z,newCornerDisTopUV.x);
				// centerMin = boundsMinInPixels + newCornerDisTopUV;
				// centerMax = boundsMaxInPixels - newCornerDisTopUV;
				// originInPixelsTopUV = clamp(worldPosInPixels, centerMin, centerMax );
				// testDis = distance(worldPosInPixels,originInPixelsTopUV);



				//testHeight = boundsMaxInPixels.z - boundsMinInPixels.z;


				if (testDisXY < bestDisXY) {
					//nextBestDis = bestDis;
					//bestDis = testDis;

					nextBestVert = bestVert;
					bestVert = isVert;

					//bestHeight[1] = bestHeight[0];
					//bestHeight[0] = testHeight;

					bestInd[1] = bestInd[0];
					bestInd[0] = i;

					nextBestDisXY = bestDisXY;
					bestDisXY = testDisXY;
				}
				else {
					if (testDisXY < nextBestDisXY) {
						bestInd[1] = i;
						//bestHeight[1] = testHeight;
						nextBestVert = isVert;
						nextBestDisXY = testDisXY;
					}
				}


				// if (testHeight > tallestHeight) {
				//  tallestHeight = testHeight;
				//  tallestInd = i;
				// }


				//visCount++;

			}


		}

		//worldPosInPixels = worldPosInPixelsOrig;


	}


	if ( (bestDisXY == invalid) || (nextBestDisXY == invalid) ) {
		//nearestJoint = invalid;
		nearestJointXY = invalid;
	}
	else {


		nearestJointXY = abs(nextBestDisXY - bestDisXY);
		if (bestVert == nextBestVert) {
			nearestJointXY = invalid;
		}



	}

	//nMax = int(min(float(nMax),float(visCount)));



	//for (n = 0; n < nMax; n++) {}






	baseInd = bestInd[0] * paramsPerEntry; //[n]

	visMinInPixels = paramArr[baseInd + E_GP_VISMININPIXELST];
	visMaxInPixels = paramArr[baseInd + E_GP_VISMAXINPIXELST];




	// if (
	//  all( lessThanEqual(worldPosInPixels,visMaxInPixels) ) &&
	//  all( greaterThanEqual(worldPosInPixels,visMinInPixels) )
	// ) {}





	boundsMinInPixels = paramArr[baseInd + E_GP_BOUNDSMININPIXELST];
	boundsMaxInPixels = paramArr[baseInd + E_GP_BOUNDSMAXINPIXELST];
	cornerDisInPixels = paramArr[baseInd + E_GP_CORNERDISINPIXELS];
	powerVals1 = paramArr[baseInd + E_GP_POWERVALS];
	powerVals2 = paramArr[baseInd + E_GP_POWERVALS2];
	thickVals = paramArr[baseInd + E_GP_THICKVALS];
	matParams = paramArr[baseInd + E_GP_MATPARAMS];

	wThickness = thickVals.x;
	floorHeight = thickVals.y;

	tempVec = vec3(equal(visMinInPixels, boundsMinInPixels));
	tempVec2 = vec3(equal(visMaxInPixels, boundsMaxInPixels));

	newVisMinInPixels = visMinInPixels - tempVec * 9999.0;
	newVisMaxInPixels = visMaxInPixels + tempVec2 * 9999.0;


	orig = (boundsMaxInPixels + boundsMinInPixels) / 2.0;




	origVis = (newVisMaxInPixels + newVisMinInPixels) / 2.0;
	radInPixels = (boundsMaxInPixels - boundsMinInPixels) / 2.0;
	isVert = radInPixels.x < radInPixels.y;

	if (radInPixels.x < radInPixels.y) {
		nodeDir = 1;
	}
	else {
		if (radInPixels.x > radInPixels.y) {
			nodeDir = 0;
		}
		else {
			nodeDir = 2;
		}

	}

	thickness = min(min(radInPixels.x, radInPixels.y), radInPixels.z);


	//innerDisInPixels = radInPixels - cornerDisInPixels;





	
	radInPixelsTopUV = (boundsMaxInPixels - boundsMinInPixels) * 0.5;
	newCornerDisTopUV.xy = vec2(min(radInPixelsTopUV.x, radInPixelsTopUV.y));
	newCornerDisTopUV.z = min(radInPixelsTopUV.z, newCornerDisTopUV.x);
	centerMin = boundsMinInPixels + newCornerDisTopUV;
	centerMax = boundsMaxInPixels - newCornerDisTopUV;
	if (isVert) {
		tempf1 = clamp( (worldPosInPixels.y - centerMin.y) / (centerMax.y - centerMin.y), 0.0, 1.0);
	}
	else {
		tempf1 = clamp( (worldPosInPixels.x - centerMin.x) / (centerMax.x - centerMin.x), 0.0, 1.0);
	}
	powerVals = mix(powerVals1, powerVals2, tempf1);
	stairVal = 1.0-clamp(powerVals.z*2.0-0.5,0.0,1.0);

	
	
	
	
	boundsMinCorner = boundsMinInPixels + cornerDisInPixels;
	boundsMaxCorner = boundsMaxInPixels - cornerDisInPixels;

	tempVec = abs( abs(newVisMaxInPixels - origVis) - abs(worldPosInPixels - origVis) );
	visDis = 1.0 - clamp( min(min(tempVec.x, tempVec.y), tempVec.z) / thickness, 0.0, 1.0);
	visDisXY = 1.0 - clamp( min(tempVec.x, tempVec.y) / thickness, 0.0, 1.0);
	visDisZ = 1.0 - clamp( tempVec.z / thickness, 0.0, 1.0);


	originInPixelsTopUV = clamp(worldPosInPixels, centerMin, centerMax );
	disTopUV = worldPosInPixels - originInPixelsTopUV;
	disNormTopUV = (disTopUV / newCornerDisTopUV);
	absDisNormTopUV = abs( disNormTopUV );



	disCenterMinMax = distance(originInPixelsTopUV.xy, centerMin.xy); // /distance(centerMin.xy,centerMax.xy);



	originInPixels = clamp(worldPosInPixels, boundsMinCorner, boundsMaxCorner );
	originInPixelsVoro = clamp(voroPos, boundsMinCorner, boundsMaxCorner );

	bLessThanOrig = lessThanEqual( abs(worldPosInPixels - orig), abs(originInPixels - orig) );
	isInsideCorners = all(bLessThanOrig.xyz);





	dis = worldPosInPixels - originInPixels;
	absDis = abs(dis);
	disNorm = (dis / cornerDisInPixels);
	absDisNorm = abs( disNorm );
	absDisNormalized = normalize(absDisNorm);

	//nearestCenterPoint = originInPixels;





	// cornerdis must be less than thickness


	tempVec = cornerDisInPixels - thickness;
	thickInside = any(lessThanEqual(tempVec, zeroVec));
	tempVec = max(tempVec, oneVec);
	coefMin = tempVec;
	coefMax = cornerDisInPixels;










	curRad = length(disNorm);
	curPhi = atan(disNorm.y, disNorm.x);
	curThe = acos(disNorm.z / curRad);
	newUVW = vec4(curPhi / PIO2, 1.0 - curThe / PIO2, 0.0, 0.0);
	newUVW.x *= (cornerDisInPixels.x + cornerDisInPixels.y);
	newUVW.y *= (cornerDisInPixels.z) + (cornerDisInPixels.x + cornerDisInPixels.y) / 2.0;

	tempVec3 = worldPosInPixels - boundsMinInPixels;


	if ( all(bLessThanOrig.xy) ) {

		bestDis = -99999.0;
		for (i = 0; i < 4; i++) {
			testDis = dot(normalize(disNormTopUV.xy), dirVecs[i]);
			if (testDis > bestDis) {
				bestDis = testDis;
				topVals.xy = tempVec3.xy * dirMats[i];
			}
		}



		if (bLessThanOrig.z) {

			bestDis = -99999.0;
			for (i = 0; i < 6; i++) {
				testDis = dot(normalize(disNormTopUV), dirVecs2[i]);
				if (testDis > bestDis) {
					bestDis = testDis;
					bestI = i;
				}
			}

			if (bestI >= 4) {
				newUVW.xy = topVals;
			}
			else {
				if (bestI <= 1) {
					newUVW.xy = tempVec3.yz;
					//newUVW.y += uvScale.y/2.0;
				}
				else {
					newUVW.xy = tempVec3.xz;
					//newUVW.y += uvScale.y/2.0;
				}
			}


		}
		else {
			newUVW.xy = topVals;

			isDivider = (abs( abs(disTopUV.x) - abs(disTopUV.y) ) <= divDis) && (abs(disTopUV.x) + abs(disTopUV.y) > divDis * 2.0 ) ;

		}


	}
	else {



		if ( all(bLessThanOrig.yz) ) {
			newUVW.xy = tempVec3.yz;
		}
		else {
			if ( all(bLessThanOrig.xz) ) {
				newUVW.xy = tempVec3.xz;
			}
			else {

				if (bLessThanOrig.x) {
					newUVW.x = tempVec3.x;
				}
				if (bLessThanOrig.y) {
					newUVW.x = tempVec3.y;
				}
				if (bLessThanOrig.z) {
					newUVW.y = tempVec3.z;
				}

			}
		}



	}


	tempf1 = clamp(
						 min(
							 min(
								 abs(originInPixels.x - boundsMinInPixels.x),
								 abs(boundsMaxInPixels.x - originInPixels.x)
							 ),
							 min(
								 abs(originInPixels.y - boundsMinInPixels.y),
								 abs(boundsMaxInPixels.y - originInPixels.y)
							 )
						 ),
						 0.0,
						 thickness
					 );

	tempf2 = clamp(
						 min(
							 tempf1,
							 min(
								 abs(originInPixels.z - boundsMinInPixels.z),
								 abs(boundsMaxInPixels.z - originInPixels.z)
							 )
						 ),
						 0.0,
						 thickness
					 );
	resXYInside = 1.0 - tempf1 / thickness;
	resInside = 1.0 - tempf2 / thickness;


	if (thickInside && all(bLessThanOrig.xy) ) {
		resXY = resXYInside;
	}
	else {
		tempVec = absDis / coefMin;
		resMin = 1.0/pow(dot(pow(tempVec.xy, powerVals.xx), oneVec.xy), 1.0 / powerVals.x);
		tempVec = absDis / coefMax;
		resMax = 1.0/pow(dot(pow(tempVec.xy, powerVals.xx), oneVec.xy), 1.0 / powerVals.x);
		resXY = clamp(  ( 1.0 - resMin ) / ( resMax - resMin ), 0.0, 1.0  );

		resXY = resXY * (1.0 - resXYInside) + resXYInside;
	}

	if (thickInside && isInsideCorners) {
		res = resInside;
	}
	else {
		tempVec = absDis / coefMin;
		tempVec2.x = pow(dot(pow(tempVec.xy, powerVals.xx), oneVec.xy), 1.0 / powerVals.x);
		tempVec2.y = tempVec.z;
		resMin = 1.0/pow(dot(pow(tempVec2.xy, powerVals.yy), oneVec.xy), 1.0 / powerVals.y);

		tempVec = absDis / coefMax;
		tempVec2.x = pow(dot(pow(tempVec.xy, powerVals.xx), oneVec.xy), 1.0 / powerVals.x);
		tempVec2.y = tempVec.z;
		resMax = 1.0/pow(dot(pow(tempVec2.xy, powerVals.yy), oneVec.xy), 1.0 / powerVals.y);

		res = ( 1.0 - resMin ) / ( resMax - resMin );

		res = res * (1.0 - resInside) + resInside;

	}










	resNoRef = clamp(res, 0.0, 1.0);

	resNoRefVisDis = max(resNoRef, visDis);
	resNoRefVisDisZ = max(resNoRef, visDisZ);


	res = abs(resNoRef - 0.5) * 2.0;
	res = max(res, visDis);

	//resNoRef = max(resNoRef,visDis);

	testRes = ((1.0/resMin >= 1.0) || thickInside) && (1.0/resMax <= 1.0);



	tempVec3.xy = worldPosInPixels.xy - boundsMinCorner.xy;
	tempVec3.xy = abs(tempVec3.xy - (boundsMaxCorner.xy - boundsMinCorner.xy) / 2.0);
	tempVec3.z = worldPosInPixels.z - visMinInPixels.z;


	//newUVW.xy = intModFV(newUVW.xyz,uvScale).xy;
	//newUVW.xy += uvScale.xy * vec2(lessThan(newUVW.xy,zeroVec.xy));
	newUVW.z = resNoRef * thickness;
	newUVW.w = res * thickness;

	//isInside = testRes; //[n]
	//isRoof[n] = !bLessThanOrig.z;

	if ( testRes ) {
		normalUID = 1.0;
		finalMat = TEX_DIRT;
		finalMod = 0.0;
		isInside = true;
	}

	// todo: move this to main function
	if (finalMat == TEX_WOOD) {
		finalMod = getWoodGrain(normalUID, worldPosInPixels, 2.0 * pixelsPerMeter, woodRes, 4.0 );
	}

	matResult.x = normalUID;
	matResult.y = finalMat;
	matResult.z = float(isInside);//[0] || isInside[1]);
	matResult.w = finalMod;

	return matResult;

}






void main() {


	int i;
	int j;


	int iVolumePitch = int(volumePitch);

	//hasCobble = false;
	shingleMod = 0.0;
	globalFloat = 0.0;
	//nearestCenterPoint = vec3(0.0);


	voroId = 0.0;
	voroGrad = 0.0;
	voroPos = vec3(0.0);


	vec3 newCoords = vec3(0.0);
	j = int( volumePitch * volumePitch * TexCoord0.y );
	newCoords.x = TexCoord0.x;

	newCoords.z = float(j / iVolumePitch) / volumePitch;

	newCoords.y = (TexCoord0.y - newCoords.z) * volumePitch; //float(intMod(j,iVolumePitch))/volumePitch;

	vec3 worldPosInPixels = vec3(
		mix(worldMinBufInPixels.x, worldMaxBufInPixels.x, newCoords.x),
		mix(worldMinBufInPixels.y, worldMaxBufInPixels.y, newCoords.y),
		mix(worldMinBufInPixels.z, worldMaxBufInPixels.z, newCoords.z)
	);

	float randVal = randf(TexCoord0);
	float finalMod = 0.0;
	float finalMat = TEX_NULL;
	//float finalBlend = 1.0;
	float finalNormUID = 0.0;
	float finalInside = 0.0;
	float finalLayer = 0.0;
	float fj;
	float fi;

	int iMatCount = 0;

	vec4 finalRes = vec4(0.0);
	vec4 finalRes2 = vec4(0.0);
	matResultTer = vec4(0.0);
	vec4 matResultTree = vec4(0.0);
	vec4 matResultGeom = vec4(0.0);
	vec4 matResult = vec4(0.0);
	vec4 tempResult;



	


	// if (hasTerrain) {
	// 	getCobble(worldPosInPixels);
	// 	matResultTer = getTerrain(worldPosInPixels);//vec4(1.0,TEX_DIRT,1.0,1.0);//getTerrain(worldPosInPixels);
	// }






	if (hasGeom) {

		for (j = 0; j < E_ENT_PARAM_LINES; j++) {

			iMatCount = int(matCountArr[j]);

			if (iMatCount > 0) {
				tempResult = getGeom(worldPosInPixels, j);//, matResultTer.w-0.75*pixelsPerMeter );
				if ( (tempResult.z == 1.0) || (tempResult.y != TEX_NULL) ) {
					matResultGeom = tempResult;
				}
			}
		}
	}
	matResult = matResultGeom;

	
	if (hasLines) {
		matResult = getLines(worldPosInPixels);
	}







	// if ( (matResultTer.y != TEX_NULL) && (matResultGeom.z != 1.0) ) {
	// 	finalBlend = 0.5;
	// 	matResult = matResultTer;
	// }
	// else {
	//	matResult = matResultGeom;
	// }

	// if (hasTree) {
	// 	matResultTree = getTree(worldPosInPixels);
	// 	if (matResultTree.y != TEX_NULL) {
	// 		matResult = matResultTree;
	// 	}

	// }

	finalNormUID = matResult.x;
	finalMat = matResult.y;
	finalInside = matResult.z;
	finalMod = matResult.w;






	vec4 tex2 =  texture3D(Texture1, newCoords);
	if (tex2.a > 0.5) {
		finalMat = TEX_DIRT;

	}
	else {
		if (tex2.b > 0.3) {
			finalMat = TEX_NULL;
		}
	}



	if (finalMat == TEX_MORTAR) {
		finalMat = TEX_SAND;
		finalNormUID = 0.0;
	}

	if (finalMat == TEX_SAND || finalMat == TEX_MORTAR || finalMat == TEX_BRICK || finalMat == TEX_METAL) {
		finalMod = randVal;
	}

	if ( (finalMat >= TEX_SHINGLE) && (finalMat < TEX_PLASTER) ) {
		finalMod = clamp(shingleMod, 0.0, 1.0);
	}


	if (finalMat == TEX_DIRT) {
		fj = clamp((matResultTer.w - worldPosInPixels.z) / 512.0, 0.0, 3.0);
		finalMat = TEX_EARTH + floor(fj);
		finalMod = fj - floor(fj);
	}


	// if (hasTerrain) {
	// 		finalLayer = 0.0;
	// 		finalMat = TEX_DIRT;
	// 		finalNormUID = 1.0;
	// 		finalMod = 0.0;
	// }



	//TODO: ADD BACK IN FOR WATER
	if (finalMat == TEX_WATER) {
		finalLayer = 1.0;
		finalMat = TEX_WATER;
		finalNormUID = 254.0;
		finalMod = 0.0;
	}
	

	if (finalMat == TEX_GLASS) {
		finalLayer = 1.0;
		finalNormUID = 254.0;
		finalMod = 0.0;
	}



	finalLayer = min(finalLayer, totLayers - 1.0);

	finalRes.a = finalMat / 255.0;
	finalRes.r = finalLayer;
	finalRes.b = (finalMod * 127.0) / 255.0; //finalMod         0.0; // blend amount
	finalRes.g = finalNormUID / 255.0;

	//finalMod = abs(sin(worldPosInPixels.z/(1.0*pixelsPerMeter)));
	//finalMod = matResult.w;

	//finalRes2.b = (finalMod * 127.0) / 255.0; //finalMod


	gl_FragData[0] = finalRes;
	//gl_FragData[1] = finalRes2;

}

