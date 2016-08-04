#version 120


uniform sampler3D Texture0; //volume texture nearest
uniform sampler3D Texture1; //volume texture linear
uniform sampler2D Texture2; //terrain heightmap
uniform sampler2D Texture3; //terrainID // no longer used
uniform sampler3D Texture4; //ter tex




uniform	float totLayers;
uniform	float pixelsPerMeter;
uniform	float seaLevel;
uniform	vec4 worldSizeInPixels;
uniform float volumePitch;




uniform vec4 worldMinBufInPixels;
uniform vec4 worldMaxBufInPixels;

uniform vec4 blockMinBufInPixels;
uniform vec4 blockMaxBufInPixels;

//uniform float blockSizeInPixels;

uniform int numEntries;
uniform int paramsPerEntry;

uniform bool hasTree;
uniform bool hasGeom;
uniform bool hasTerrain;
uniform bool hasLines;


//uniform int voroCount;
uniform vec4 voroArr[27];

uniform vec3 paramArr[256];
uniform float matCountArr[16];

varying vec2 TexCoord0;

float smoothVal;
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



const int E_TP_VISMININPIXELST = 0;
const int E_TP_VISMAXINPIXELST = 1;
const int E_TP_P0 = 2;
const int E_TP_P1 = 3;
const int E_TP_P2 = 4;
const int E_TP_POWERVALS = 5;
const int E_TP_POWERVALS2 = 6;
const int E_TP_THICKVALS = 7;
const int E_TP_UNUSED = 8;
const int E_TP_MATPARAMS = 9; // must be last
const int E_TP_LENGTH = 10;


const float E_PT_OAK_TRUNK = 0.0;
const float E_PT_OAK_ROOTS = 1.0;
const float E_PT_OAK2_TRUNK = 2.0;
const float E_PT_OAK2_ROOTS = 3.0;
const float E_PT_BARE_OAK_TRUNK = 4.0;
const float E_PT_BARE_OAK_ROOTS = 5.0;
const float E_PT_LENGTH = 6.0;


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
const float TEX_SNOW =    47.0;


const float E_MAT_SUBPARAM_NONE =       0.0;
const float E_MAT_SUBPARAM_TUDOR =      1.0;
const float E_MAT_SUBPARAM_DOCK =       2.0;
const float E_MAT_SUBPARAM_BRICK =      3.0;
const float E_MAT_SUBPARAM_BRICK_ARCH = 4.0;
const float E_MAT_SUBPARAM_LENGTH =     5.0;

const float E_MAT_PARAM_FOUNDATION =    0.0;
const float E_MAT_PARAM_ROOF =        	1.0;
const float E_MAT_PARAM_BUILDING =      2.0;
const float E_MAT_PARAM_LANTERN =       3.0;
const float E_MAT_PARAM_DOORWAY =       4.0;
const float E_MAT_PARAM_DOOR =        	5.0;
const float E_MAT_PARAM_TREE =        	6.0; // TREES MUST BE LAST ENTRY
const float E_MAT_PARAM_LENGTH =      	7.0;




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

	if (length(dis) < 1.0) { //(dis.x+dis.y) length(dis) //max(dis.x,dis.y)

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




vec4 getArch(
	vec4 newUVW,
	float disFromTopInPixels,
	float archDisFromTopInMeters,
	float outerRadInMeters,
	float innerRadInMeters,
	float intervalSizeInMeters,
	float intervalOffset
) {
	vec4 myResult;

	float brickRes = 2.0;
	vec3 brickCoords = newUVW.xyz - vec3(0.0, 0.25, 0.0) * pixelsPerMeter;

	float t1 = getIntervalF(newUVW.x + intervalOffset*pixelsPerMeter, intervalSizeInMeters, intervalSizeInMeters);
	float t2 = disFromTopInPixels - (archDisFromTopInMeters + outerRadInMeters) * pixelsPerMeter; //getIntervalF(newUVW.y+outerRadInMeters*pixelsPerMeter,floorHeightInMeters,floorHeightInMeters);
	float t3 = 0.0;
	bool inArch = 
		(disFromTopInPixels > (archDisFromTopInMeters) * pixelsPerMeter) &&
		(disFromTopInPixels < (archDisFromTopInMeters+outerRadInMeters) * pixelsPerMeter);
	bool aboveArch = disFromTopInPixels <= (archDisFromTopInMeters) * pixelsPerMeter;


	if (aboveArch) {

	}
	else {
		if (inArch) {
			t3 = sqrt(t1 * t1 + t2 * t2);
		}
		else {
			t3 = sqrt(t1 * t1);
		}

		if (t3 > outerRadInMeters * pixelsPerMeter) {
			brickRes = 2.0; // outside of arch
		}
		else {
			if (t3 > innerRadInMeters * pixelsPerMeter) {
				brickRes = 1.0; // border of arch
			}
			else {
				brickRes = 0.0; // empty space inside of arch
			}
		}



		if (brickRes == 1.0) {
			if (inArch) {
				brickCoords = vec3(

					t3,//(sin(t1/(4.0*pixelsPerMeter)))*newUVW.x + (cos(t1/(4.0*pixelsPerMeter)))*newUVW.y,
					atan(t2, t1) * outerRadInMeters * pixelsPerMeter/2.0, //(cos(t1/(4.0*pixelsPerMeter)))*newUVW.x + (sin(t1/(4.0*pixelsPerMeter)))*newUVW.y,
					newUVW.z + 1.0*pixelsPerMeter
				);
			}
			else {
				brickCoords = vec3(
					sin(t1 / ((outerRadInMeters / 2.0) * pixelsPerMeter/2.0)) * outerRadInMeters * pixelsPerMeter,
					newUVW.y,//cos(t1/(1.0*pixelsPerMeter))*2.0*pixelsPerMeter,
					newUVW.z + 1.0*pixelsPerMeter
				);
			}
		}
	}




	myResult.w = brickRes;
	myResult.xyz = brickCoords;

	return myResult;

}

vec4 getBuilding(
	vec3 worldPosInPixels,
	vec4 newUVW,
	vec3 relPos,
	vec3 matParams,
	bvec3 bLessThanOrig,
	int nodeDir,
	float nearestJointXY,
	float resXY,
	float thickness,
	float disCenterMinMax,
	float visDisXY,
	float floorHeight,
	float hasSupport,
	float maxCornerRad
) {
	
	
	
	
	//newUVW.x += 1.0*pixelsPerMeter;

	bool isVert = (nodeDir == 1);
	bool isDock = (matParams.y == E_MAT_SUBPARAM_DOCK);
	bool notDock = !isDock;
	bool isTudor = (matParams.y == E_MAT_SUBPARAM_TUDOR)||isDock;
	bool isBrickRoom = (matParams.y == E_MAT_SUBPARAM_BRICK_ARCH) || (matParams.y == E_MAT_SUBPARAM_BRICK);

	float fIsTudor = float(isTudor);
	bool hasPillars = isTudor;
	bool hasBrick = isBrickRoom || isTudor;
	bool hasPlaster = isTudor;
	bool hasScaff = isTudor;
	bool hasArch = (matParams.y == E_MAT_SUBPARAM_BRICK_ARCH);
	bool hasStairs = true;


	// todo: fix this (sloppy)
	// if ((maxCornerRad > 4.0*pixelsPerMeter)&&(matParams.x == E_MAT_PARAM_BUILDING)) {
	// 	if (bLessThanOrig.x) {
	// 		newUVW.x *= 9.0/8.0;
	// 	}
	// 	else {
	// 		newUVW.x *= 0.75;
	// 		newUVW.x += 0.5*pixelsPerMeter;
	// 	}
	// }


	float floorHeightInPixels = floorHeight * pixelsPerMeter;

	float dockMod =  float(isDock)*4.0;



	float disFromBottomInPixels = worldPosInPixels.z - floor(worldPosInPixels.z / floorHeightInPixels) * floorHeightInPixels; //relPos.z;

	float wallThickness = (1.0 - fIsTudor * 0.4) * pixelsPerMeter; // + pow(( max(disFromBottomInPixels-3.0*pixelsPerMeter,0.0)/floorHeight)*0.1,2.0); //+0.5*float(isBasement)
	//

	float wallInsetInPixels = 0.25 * pixelsPerMeter * fIsTudor;
	float disFromInsideInPixels = newUVW.z;
	float disFromOutsideInPixels = (thickness - wallInsetInPixels ) - disFromInsideInPixels; //thickness - disFromInsideInPixels;
	float capDis = thickness - visDisXY * thickness;
	float disFromOutsideRef = 0.0;

	float plasterMod = 0.0;


	float horzBoardThickness = 0.5;

	float archOffset = 0.0;
	bool inArch = false;
	float brickMod = 0.0;
	float brickRes = 0.0;
	float insetAmount;
	vec3 brickCoords = vec3(0.0);

	float t1 = 0.0;
	float t2 = 0.0;
	float t3 = 0.0;

	float floorNumber = 2.0;
	bool bIsOuterWall = disFromOutsideInPixels < wallThickness;
	bool bIsCapWall = (capDis < wallThickness);
	float vertMod = 50.0 * float(isVert);
	float shingleDepth = 0.25 * pixelsPerMeter;
	//bool bIsOuterWallBoards =  (disFromOutsideInPixels < (0.5*pixelsPerMeter)) && (disFromOutsideInPixels > (0.25*pixelsPerMeter));
	//bool bIsShingle = (disFromOutsideInPixels < (shingleDepth));
	float notCorner = float(bLessThanOrig.x || bLessThanOrig.y);
	float isOuterWall = float(bIsOuterWall);
	bool isJoint = (nearestJointXY <= 0.1875 * pixelsPerMeter);
	bool isNearJoint = (nearestJointXY <= 2.0 * pixelsPerMeter);
	bool bIsFloor = false;
	float plasterDis = 0.0;
	float boardThickness = 0.25;
	float dirMod = 0.0;

	vec4 archRes = vec4(0.0);

	if ( (capDis < 1.0 * pixelsPerMeter) && bIsOuterWall ) {
		boardThickness = 1.0;
	}


	float divHeight = 4.0;


	vec4 myResult = vec4(0.0);
	myResult.y = TEX_WOOD;
	myResult.z = 1.0;

	float fVert = float(isVert);

	myResult.w = fVert;

	bool bIsOuterWallOrig = bIsOuterWall;

	if ((!bIsOuterWall) && bIsCapWall) {

		myResult.w = 1.0 - fVert;

		disFromOutsideInPixels = capDis - 0.0625 * pixelsPerMeter;



		bIsOuterWall = bIsCapWall;
		isOuterWall = float(bIsCapWall);

		if (isVert) {
			newUVW.x = relPos.x;
		}
		else {
			newUVW.x = relPos.y;
		}

		if (!bLessThanOrig.z) {
			newUVW.y = relPos.z;
		}

		newUVW.z = disFromOutsideInPixels;

		// myResult.y = TEX_STONE;
		// myResult.x = 1.0;

	}

	bool isVertBoard = false;
	bool isHorzBoard = getInterval(
											 newUVW.y - (divHeight + dockMod) * pixelsPerMeter ,
											 floorHeight,
											 horzBoardThickness * 2.0 * hasSupport
										 );

	if (hasScaff || isHorzBoard) {

		if (
			getInterval(
				newUVW.y - (horzBoardThickness * 0.5 + 0.25 + divHeight + dockMod )*pixelsPerMeter,
				floorHeight,
				0.5
			) && (!isBrickRoom)
			//&& (!bIsOuterWall)

		) {

			// floor boards
			if (isDock) {
				myResult.x = 6.0 + getBoard(newUVW.zx + vec2(0.0,0.5*pixelsPerMeter), 1.0, 4.0); // + vec2(0.0,0.5*pixelsPerMeter)
			}
			else {
				myResult.x = 6.0 + getBoard(newUVW.xz, 0.75, 3.0);
			}
		}
		else {

			isVertBoard = getInterval(
											newUVW.x,
											2.0,
											mix(boardThickness / pow(resXY * 0.7 + 0.3, 2.0), boardThickness, notCorner)
										);


			if ( isHorzBoard && isVertBoard) {

				// joists and rafters
				myResult.w = 1.0 - fVert;
				myResult.x = 4.0;
			}
			else {
				if ( isVertBoard && (!isNearJoint) ) {
					myResult.w = 2.0;
					myResult.x = 2.0 * isOuterWall;
				}

				if ( myResult.x == 0.0 ) {

					if (isHorzBoard) {
						// horizontal wall support beams



						if ( (isJoint || ( bIsOuterWall && (!isBrickRoom) ) ) ) {
							myResult.x = 3.0;
						}
					}
					else {


						if ( ( isJoint || (isDock&&(nearestJointXY < 1.0*pixelsPerMeter)) ) && bIsOuterWall ) {

							// is a joint welding
							myResult.x = 3.0;
							myResult.w = 2.0;
						}


						if (( getInterval(newUVW.y + (dockMod*0.5) * pixelsPerMeter, 4.0, horzBoardThickness*1.0) ) ) {
							myResult.x = 3.0 * isOuterWall;
							myResult.y = TEX_WOOD;
						}
						else {


							// diagonal beams

							//if (!getInterval(newUVW.x,8.0,4.0) && (notDock)) { // && (notCorner == 1.0)

							if (bLessThanOrig.z && notDock) {
								dirMod = (float(getInterval(newUVW.x, 8.0, 4.0)) - 0.5) * 2.0;

								if ( getInterval(newUVW.x + dirMod * newUVW.y * 0.5, 2.0, 0.25) && bIsOuterWall ) {
									myResult.x = 50.0;
									myResult.w = 2.0;
								}
							}

							//}


						}




					}

				}
			}
		}
	}



	// inner pillars / beams
	if ( hasPillars && notDock ) { //(!bIsOuterWallOrig) && ( notBasement || (isBasement&&(!bIsCapWall)) )
		if (resXY * thickness < 0.25 * pixelsPerMeter) {

			if ( getInterval(disCenterMinMax, 8.0, 0.25 ) ) {
				myResult.x = 5.0;
				myResult.w = 2.0;
			}

		}
	}

	if (myResult.x == 0.0) {
		myResult.y = TEX_NULL;

		if (isTudor && (!bIsCapWall)) {
			wallThickness = 0.5 * pixelsPerMeter;
			wallInsetInPixels = 0.3 * pixelsPerMeter;
			disFromInsideInPixels = newUVW.z;
			disFromOutsideInPixels = (thickness - wallInsetInPixels ) - disFromInsideInPixels; //thickness - disFromInsideInPixels;
			bIsOuterWall = disFromOutsideInPixels < wallThickness;
			bIsCapWall = (capDis < wallThickness);
		}


	}

	if (
		disFromOutsideInPixels < -0.0625 * pixelsPerMeter * float(myResult.x == 4.0)
	) {
		myResult.x = 0.0;
		myResult.y = TEX_NULL;
		myResult.z = 0.0;
	}

	bIsFloor = (disFromBottomInPixels < 1.0 * pixelsPerMeter);

	// if (hasStairs) {


	//  bIsFloor = (disFromBottomInPixels < (atan(relPos.y,relPos.x)/(2.0*3.14159))*floorHeight*pixelsPerMeter);
	// }


	// if (supportAmount < 0.5) { //

	//  if (disFromBottomInPixels > 2.0*pixelsPerMeter) {
	//    myResult.x = 0.0;
	//    myResult.y = TEX_NULL;
	//    myResult.z = 0.0;
	//    return myResult;
	//  }


	// }


	if ( bIsFloor && (!bIsOuterWall) ) {

		disFromOutsideInPixels = disFromBottomInPixels;
		newUVW.xyz = newUVW.xzy;
	}

	if ( (bIsOuterWall || bIsFloor) && (myResult.y == TEX_NULL) && hasBrick && notDock) {


		disFromOutsideInPixels = min(disFromOutsideInPixels, capDis);
		disFromOutsideRef = (1.0 - abs(clamp( (disFromOutsideInPixels / wallThickness), 0.0, 1.0) - 0.5) * 2.0) * wallThickness;

		if (disFromOutsideRef < 0.125 * pixelsPerMeter) {
			myResult.x = 0.0;
			myResult.y = TEX_NULL;
			//myResult.z = 0.0;
		}
		else {

			insetAmount = 0.0;

			if (hasArch) {
				if (bIsFloor) {
					brickRes = 2.0;
				}
				else {
					archRes = vec4(0.0);//getArch(newUVW, disFromBottomInPixels, floorHeight, 3.0, 2.25, 4.0, 0.0);
					brickRes = archRes.w;
					brickCoords = archRes.xyz;
				}
			}
			else  {
				brickRes = 2.0;
			}

			if (brickRes > 0.0) {

				//hasPlaster = brickRes != 1.0;

				if (brickRes == 2.0) { // inside
					insetAmount = 0.25;
					brickCoords = newUVW.xyz - vec3(0.0, 0.25, 0.0) * pixelsPerMeter;
				}

				brickMod = float(brickRes == 1.0) * 4.0;

				myResult.x = getBoardSpaced(
											 brickCoords + vec3(0.0, -0.0625 * pixelsPerMeter, 0.0),
											 vec3(1.0 + brickMod, 0.5, 1.0 + brickMod),
											 0.125
										 );
				myResult.x += 21.0;

				if ( (myResult.x != 21.0) ) {
					myResult.y = TEX_BRICK;
					plasterDis = 0.25;
				}
				else {
					plasterDis = 0.375;
					if ( disFromOutsideRef > (0.1875 + insetAmount)*pixelsPerMeter ) {
						myResult.y = TEX_MORTAR;

					}
				}

				// if ((matParams.y != E_MAT_SUBPARAM_TOP)&&(brickRes == 1.0)) {
				//  hasPlaster = true;
				// }

				plasterMod = texture2D(
					Texture2, pixelsPerMeter * 0.5 * (
						(worldPosInPixels.xy + worldPosInPixels.yz) / worldSizeInPixels.x	
					)
				).r;

				if ( (disFromOutsideRef < (plasterDis - float(abs(sin(plasterMod*8.0)) - 0.97)/0.06 + insetAmount)*pixelsPerMeter) ) {
					myResult.x = 0.0;
					myResult.y = TEX_PLASTER * float(hasPlaster);
				}
			}

		}

		if (bIsFloor && bIsOuterWall && (myResult.y == TEX_NULL) && (disFromOutsideInPixels > wallThickness * 0.5) ) {
			myResult.y = TEX_MORTAR;
		}



	}





	if ( ((disFromOutsideInPixels < wallThickness * 0.5) || (isDock)) && myResult.y == TEX_NULL) {
		myResult.z = 0.0;
	}

	myResult.x += vertMod * float(myResult.x != 0.0) * float( myResult.y != TEX_SHINGLE );

	return myResult;


}


vec4 getRoof(

	vec3 worldPosInPixels,
	vec4 newUVW,
	vec3 relPos,
	vec3 matParams,
	bvec3 bLessThanOrig,
	int nodeDir,
	float nearestJointXY,
	float resXY,
	float thickness,
	float disCenterMinMax,
	float visDisXY,
	float floorHeight,
	float maxCornerRad


	// vec3 worldPosInPixels,
	// vec4 newUVW,
	// bvec3 bLessThanOrig,
	// bool isVert,
	// float nearestJointXY,
	// float resXY,
	// float thickness,
	// float disCenterMinMax,
	// float visDisXY,
	// float floorHeight
) {

	bool isVert = (nodeDir == 1);

	float disFromInsideInPixels = newUVW.z;
	float disFromOutsideInPixels = thickness - disFromInsideInPixels;
	float disFromOutsideRef = 0.0;
	float floorHeightInPixels = floorHeight * pixelsPerMeter;
	float horzBoardThickness = 0.5;
	float wallThickness = (0.5) * pixelsPerMeter;
	bool bIsOuterWall = disFromOutsideInPixels < (wallThickness + 0.5 * pixelsPerMeter );
	float vertMod = 50.0 * float(isVert);
	float shingleDepth = 0.25 * pixelsPerMeter;
	bool bIsOuterWallBoards =  (disFromOutsideInPixels < (0.5 * pixelsPerMeter)) && (disFromOutsideInPixels > (0.25 * pixelsPerMeter));
	bool bIsShingle = (disFromOutsideInPixels < (shingleDepth));
	float notCorner = float(bLessThanOrig.x || bLessThanOrig.y);
	float isOuterWall = float(bIsOuterWall);
	bool isJoint = (nearestJointXY <= 0.1875 * pixelsPerMeter);
	float boardThickness = 0.25;

	float capDis = thickness - visDisXY * thickness;
	bool bIsCapWall = (capDis < wallThickness);

	float divHeight = 4.0;


	vec4 myResult = vec4(
										0.0,
										TEX_WOOD,
										1.0,
										float(isVert)
									);

	bool isVertBoard = getInterval(
											 newUVW.x,
											 2.0,
											 mix(boardThickness / pow(resXY * 0.7 + 0.3, 2.0), boardThickness, notCorner)
										 );
	bool isHorzBoard = getInterval(
											 newUVW.y - (divHeight) * pixelsPerMeter,
											 floorHeight,
											 horzBoardThickness * 2.0
										 );


	if ( (isJoint || isVertBoard) ) {
		myResult.w = 2.0;
		myResult.x = 2.0 * isOuterWall;
	}

	if ( (myResult.x == 0.0) ) {
		if (isHorzBoard) {
			// horizontal wall support beams

			if ( bIsOuterWall ) {
				myResult.x = 3.0;
			}
		}
	}

	// inner pillars / beams
	if (!bIsOuterWall) {
		if (resXY * thickness < 0.25 * pixelsPerMeter) {

			if ( getInterval(disCenterMinMax, 8.0, 0.25 ) ) {
				myResult.x = 5.0;
				myResult.w = 2.0;
			}
		}
	}

	if (myResult.x == 0.0) {
		myResult.y = TEX_NULL;
	}

	if (disFromOutsideInPixels < 0.0) {

		if (myResult.x == 4.0) {
			if (disFromOutsideInPixels < -0.0625 * pixelsPerMeter ) {
				myResult.x = 0.0;
				myResult.y = TEX_NULL;
				myResult.z = 0.0;
			}
		}
		else {
			myResult.x = 0.0;
			myResult.y = TEX_NULL;
			myResult.z = 0.0;
		}

	}





	if (bIsShingle) {
		////////////////////////////////////
		// SHINGLE MAT
		////////////////////////////////////

		myResult.xyz = getShingle(newUVW.xyz, 1.0 * pixelsPerMeter, disFromOutsideInPixels, shingleDepth );
		myResult.x += 16.0;
		myResult.z = float(myResult.y != TEX_NULL);
	}
	else {
		if (bIsOuterWallBoards) { // roof boards
			myResult.x = 11.0 + getBoard(newUVW.xy, 1.0, 2.0);
			myResult.y = TEX_WOOD;
		}
		else {
			if (bIsCapWall) {
				return getBuilding(
								 worldPosInPixels,
								 newUVW,
								 relPos,
								 matParams,
								 bLessThanOrig,
								 nodeDir,
								 nearestJointXY,
								 resXY,
								 thickness,
								 disCenterMinMax,
								 visDisXY,
								 floorHeight,
								 1.0,
								 maxCornerRad
							 );
			}
		}
	}
	if (disFromOutsideInPixels < 0.0) {
		myResult.x = 0.0;
		myResult.y = TEX_NULL;
	}



	if ( (disFromOutsideInPixels < wallThickness * 0.5) && myResult.y == TEX_NULL) {
		myResult.z = 0.0;
	}

	myResult.x += vertMod * float(myResult.x != 0.0) * float( myResult.y != TEX_SHINGLE );

	return myResult;

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

	// float isStone = float(finalRes < divAmount);

	// return vec4(
	//  3.0,// finalNormUID = matResult.x;
	//  mix(TEX_NULL,TEX_DEBUG,isStone),// finalMat = matResult.y;
	//  isStone,// finalInside = matResult.z;
	//  finalRes/divAmount// finalMod = matResult.w;
	// );

	return finalRes;

}


// return vec2
// x: distance from line sp0->sp1
// y: percentage between sp0->sp1 (0.0->1.0)

vec2 pointSegDistance(vec3 testPoint, vec3 sp0, vec3 sp1)
{
	vec3 v = sp1 - sp0;
	vec3 w = testPoint - sp0;

	float d0 = distance(testPoint, sp0);
	float d1 = distance(testPoint, sp1);
	float d2 = distance(sp0, sp1);

	float c1 = dot(w, v);
	if ( c1 <= 0 ) {
		return vec2(d0, 0.0);
	}

	float c2 = dot(v, v);
	if ( c2 <= c1 ) {
		return vec2(d1, 1.0);
	}

	float b = c1 / c2;
	vec3 testPoint2 = sp0 + b * v; // testPoint2 is the nearest point on the line
	return vec2(distance(testPoint, testPoint2), distance(testPoint2, sp0) / d2 );
}


void getCobble(vec3 worldPosInPixels) {//, float minSpacing, float maxSpacing) {

	//vec2 psRes = vec2(0.0);

	vec4 myResult = vec4(0.0);

	// vec3 newWP = worldPosInPixels + vec3(
	//  cos(worldPosInPixels.z/100.0),
	//  sin(worldPosInPixels.z/100.0),
	//  cos(worldPosInPixels.x/100.0)
	// )*0.25*pixelsPerMeter;

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
	
	
	vec2 roughPos = (worldPosInPixels.xy + worldPosInPixels.yz) / worldSizeInPixels.x;
	float roughVoro = abs(texture2D(Texture2, 256.0 * roughPos ).r);

	vec3 newWP = worldPosInPixels.xyz;
	newWP.xyz += clamp((roughVoro-0.5)*8.0,-1.0,1.0)*1.0*pixelsPerMeter;

	//vec3 modVec = vec3(2.0,2.0,1.0);

	//float wpz = abs(sin( (worldMaxBufInPixels.x+worldMaxBufInPixels.y+worldMaxBufInPixels.z)/(1.0*pixelsPerMeter) ));

	for (i = 0; i < 27; i++) { //voroCount
		curPos = voroArr[i];
		

		curVoroDis = distance(curPos.xyz, newWP);// *wpz;

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

	// gradVal = clamp(
	//  min(
	//    (pointSegDistance(worldPosInPixels, nextBestPos, bestPos ).y-0.5)*2.0,
	//    (pointSegDistance(worldPosInPixels, bestPos, nextBestPos ).y)*2.0
	//  ),
	//  0.0,
	//  1.0
	// );
	gradVal = (clamp(1.0 - (minDis1 * 2.0 / (minDis1 + minDis2)), 1.0 / 255.0, 1.0));




	// if (
	//  (gradVal > (minDis1+minDis2)/(minSpacing+bestRand*maxSpacing))
	// ) {
	//  myResult.y = TEX_STONE;
	// }

	//myResult.y = TEX_DEBUG;

	// float dv = clamp(distance(nearestCenterPoint.xy, bestPos.xy)/(3.0*pixelsPerMeter),0.0,1.0);



	//myResult.z = float(myResult.y != TEX_NULL);

	voroId = floor(bestRand * 120.0) + 1.0;
	voroGrad = gradVal;
	voroPos = bestPos;

	// finalNormUID = matResult.x;
	// finalMat = matResult.y;
	// finalInside = matResult.z;
	// finalMod = matResult.w;

	//return myResult;

}


// vec4 tex3DBiLinear( sampler3D textureSampler_i, vec3 texCoord_i )
// {
		
		
// 		vec2 texelSize = 1.0/terPitch.xy;
		
// 		vec3 newTC = floor(texCoord_i*terPitch)/terPitch;
		
	
//     vec4 p0q0 = texture3D(textureSampler_i, newTC + vec3( -texelSize.x, texelSize.y, 0.0));
//     vec4 p1q0 = texture3D(textureSampler_i, newTC + vec3( texelSize.x, -texelSize.y, 0.0));

//     vec4 p0q1 = texture3D(textureSampler_i, newTC + vec3( -texelSize.x,  texelSize.y, 0.0));
//     vec4 p1q1 = texture3D(textureSampler_i, newTC + vec3( texelSize.x , texelSize.y, 0.0));

//     float a = fract( newTC.x * terPitch.x ); // Get Interpolation factor for X direction.
// 					// Fraction near to valid data.

//     vec4 pInterp_q0 = mix( p0q0, p1q0, a ); // Interpolates top row in X direction.
//     vec4 pInterp_q1 = mix( p0q1, p1q1, a ); // Interpolates bottom row in X direction.

//     float b = fract( newTC.y * terPitch.y );// Get Interpolation factor for Y direction.
//     return mix( pInterp_q0, pInterp_q1, b ); // Interpolate in Y direction.
// }

vec4 getTerrain(vec3 worldPosInPixels) {

	vec4 matResult = vec4(0.0);

	float newMult = pixelsPerMeter/128.0;

	float finalMat = 0.0;
	float finalNormUID = 0.0;
	float finalMod = 0.0;

	float rockSize = distance(worldMinBufInPixels.xyz,worldMaxBufInPixels.xyz)/2.0;

	float baseRand = randf(worldPosInPixels.xy);

	float grassMod = float(worldPosInPixels.z >= (seaLevel) );

	float resMod = 0.25;//(32.0/pixelsPerMeter);

	float randv = baseRand;
	vec3 newBlockSizeInPixels = blockMaxBufInPixels.xyz - blockMinBufInPixels.xyz;
	vec3 voroCoords = (voroPos - blockMinBufInPixels.xyz) / newBlockSizeInPixels;
	vec4 texVoro = texture3D(Texture4, voroCoords);
	float randVoro = randf(voroCoords.xy);
	vec3 wCoords = (worldPosInPixels - blockMinBufInPixels.xyz) / newBlockSizeInPixels;
	vec4 texW = texture3D(Texture4, wCoords); //texture3D //tex3DBiLinear
	
	
	vec2 roughPos = (worldPosInPixels.xy + worldPosInPixels.yz) / worldSizeInPixels.x;
	vec2 roughVal = vec2(
										abs(texture2D(Texture2, 512.0 * roughPos+0.01*randVoro*voroGrad ).r),
										abs(texture2D(Texture2, 256.0 * roughPos+0.015*randVoro*voroGrad ).r)
									);
	
	
	float fIsSnow = 0.0;
	float snowRand = roughVal.x;
	
	vec3 wCoords2 = (worldPosInPixels +
									 vec3(
										 0.25,
										 0.25,
										 -mix(randv,snowRand,fIsSnow)
									 ) * pixelsPerMeter - blockMinBufInPixels.xyz) / newBlockSizeInPixels;
	vec4 texW2 = texture3D(Texture4, wCoords2);
	vec4 texW3 = texture3D(Texture4, 
		(worldPosInPixels +	vec3(0.5,0.5,-0.5) * pixelsPerMeter - blockMinBufInPixels.xyz) / newBlockSizeInPixels	
	);
	
	
	
	
	
	
	roughVal = -abs(roughVal - 0.5) * 2.0;

	//roughVal = mix(roughVal*roughVal*roughVal,roughVal,0.5);


	//roughVal.x;
	float hardVal = clamp((smoothVal-0.5)*4.0, 0.0, 1.0);
	
	//smoothVal = clamp(mix(-2.0,2.0,smoothVal),0.0,1.0);

	float tempRand = randf3(voroPos);
	float jutDis = clamp(
			( distance(worldPosInPixels.xyz,vec3(voroPos.xy,voroPos.z-rockSize)) ) / (2.0 * rockSize), //worldPosInPixels.z - (voroPos.z - rockSize)
			0.0,
			1.0
		);
	//float voroJut = 1.0-jutDis;
	
	float voroJut = mix(
		1.0 - jutDis,
		0.0,
		roughVal.y	
	);

	roughVal = 
			mix(
			roughVal * clamp( (1.0 - voroGrad), 0.0, 1.0),
			roughVal,
			randVoro * 0.25 + 0.75
		);
	
	
	roughVal *= resMod;
	voroJut *= resMod;
	
	//voroJut*=smoothVal;
	
	//roughVal = vec2(0.0);
	
	//resMod = 1.0;
	
	
	float multVal = @terThickness@; // 0.3
	float multVal2 = @terThickness2@; // 0.6
	

	float newTWA = pow(texW.a, multVal)*multVal2;
	float newTWA2 = pow(texW2.a, multVal)*multVal2;
	float newTWA3 = pow(texW3.a, multVal)*multVal2;
	float newMedian = @terMedian@; // 0.5
	float compScale = @terCompScale@; // 0.4

	float threshVal = 
		newMedian +
		(tempRand * 0.05 + 0.6 * voroJut)*compScale;
	
	
	float threshVal2 = 
		newMedian +
		(
			(tempRand * 0.01) -
			(roughVal.x*0.8 - ((1.0 - voroGrad) * 0.25 + roughVal.y) * 0.1)
		)*compScale;
	
	float threshVal3 = newMedian +
		(
		(voroJut*0.5) - //tempRand * 0.05 + 
		(roughVal.x * (0.4 + roughVal.y*0.2)) -
		smoothVal * 0.1
		)*compScale;
	
	float threshVal4 = newMedian +
		(-roughVal.x*0.4)*compScale;
		
	
	
	
	
	
	if (grassMod == 1.0) {
		
		if (fIsSnow == 1.0) {
			if (
				(newTWA2*@snowVal@*4.0 - threshVal2) > mix(-0.5,0.05,newMult)*compScale		// GRASS 
			) {
				finalNormUID = 2.0;
				finalMat = TEX_SNOW;
				finalMod = 1.0;
			}
		}
		else {
			if (
				(newTWA2 - threshVal2) > mix(-0.5,0.05,newMult)*compScale		// GRASS 
			) {
				finalNormUID = 2.0;
				finalMat = TEX_GRASS;
				finalMod = clamp((newTWA2 - threshVal2) * 10.0, 0.0, 1.0) * 0.25 + 0.5;
			}
		}
		
		
		
		if (
			(newTWA2 - threshVal2) > mix(-0.5,0.05,newMult)*compScale		// GRASS 
		) {
			finalNormUID = 2.0;
			finalMat = TEX_GRASS; // TEX_SNOW
			finalMod = 1.0;//clamp((newTWA2 - threshVal2) * 10.0, 0.0, 1.0) * 0.25 + 0.5;
		}
		
	}
	
	if (
		(newTWA3 - threshVal4) > (mix(
			mix(-0.5,0.12,newMult)
			,0.0,hardVal)*compScale ) ||
		(newTWA - threshVal4) > mix(-0.5,0.12,newMult)*compScale
		
		 		// SAND
	) {
		finalNormUID = 2.0;
		finalMat = TEX_DIRT;
		finalMod = 0.0;
	}

	

	// ROCKS
	if (
		( texVoro.a > 0.0 ) &&
		(
			( (newTWA - threshVal3) > mix(-0.2,0.0,newMult) )
			
			&&
			
			( voroGrad > (roughVal.y*0.1 + mix(0.2*newMult,-0.2,randVoro)*abs(jutDis-0.5)*2.0 ) ) //
			
		// 	// (voroGrad > mix(
		// 	// 		(roughVal.y*0.2 - smoothstep(0.9,0.99,newTWA)*0.1 ),
		// 	// 		(roughVal.y*0.1 + mix(0.2,0.0,randVoro) ),
		// 	// 		hardVal
		// 	// ))
			
			//
			
		)
		
		
	) {
		finalNormUID = voroId;
		finalMat = TEX_DIRT; //TEX_SNOW
		finalMod = voroGrad;
	}


	matResult.x = finalNormUID;
	matResult.y = finalMat;
	matResult.z = 0.0;
	matResult.w = finalMod;

	return matResult;


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


float roundVal(float v) {
	float floorV = floor(v);
	float f = v-floorV;
	if (f > 0.5) {
		return floorV+1.0;
	}
	else {
		return floorV;
	}
}

vec4 getTree(vec3 worldPosInPixels) {


	int i;
	int j;
	int k;

	int curInd = -1;

	int maxCount = 0;
	int baseInd = 0;


	float testDis = 0.0;
	float t;

	vec4 resPoint[2];
	resPoint[0] = vec4(0.0);
	resPoint[1] = vec4(0.0);

	vec3 visMinInPixels = vec3(0.0);
	vec3 visMaxInPixels = vec3(0.0);
	vec3 matParams = vec3(0.0);

	vec4 matResult = vec4(0.0);

	vec3 p0;
	vec3 p1;
	vec3 p2;

	vec2 dres = vec2(0.0);
	vec2 dres1 = vec2(0.0);
	vec2 dres2 = vec2(0.0);


	vec3 tempv = vec3(0.0);
	vec3 tempvNorm = vec3(0.0);

	vec3 roThetaPhi = vec3(0.0);
	vec3 roThetaPhi2 = vec3(0.0);


	vec3 bezTanP0;
	vec3 bezTanP1;

	vec4 tempResult = vec4(0.0);

	float tempDis = 0.0;
	float radNorm = 0.0;
	float radNormFloored = 0.0;

	int bestInd = 0;
	vec2 bestRes = vec2(invalid);
	vec2 resArr = vec2(invalid);
	vec2 resArrLeaf = vec2(invalid);
	vec3 thickVals = vec3(0.0);
	
	vec3 origVec = vec3(0.0);

	float curThickness = 0.0;
	float sphereRad = 0.0;
	float numDivs = 2.0;
	float numDivsGen = 0.0;
	
	float minDis = 999999.0;

	// p0: start point
	// p1: end point
	// p2: control point
	//      p2
	// p0        p1
	
	vec4 bestNode = vec4(invalid);

	float totCount = 0.0;
	float totThresh = 0.0;
	float threshVal = 0.0;

	float leafRad = 8.0;//0.5*pixelsPerMeter;

	vec4 maxv = vec4(invalid);

	vec3 newWP = vec3(0.0);
	vec3 totNorms = vec3(0.0);

	for (i = 0; i < numEntries; i++) {

		baseInd = i * paramsPerEntry;
		matParams = paramArr[baseInd + E_TP_MATPARAMS];
		

		if (matParams.x == E_MAT_PARAM_TREE) {

			visMinInPixels = paramArr[baseInd + E_TP_VISMININPIXELST];
			visMaxInPixels = paramArr[baseInd + E_TP_VISMAXINPIXELST];


			if (
				all( lessThanEqual(worldPosInPixels, visMaxInPixels) ) && //+slack
				all( greaterThanEqual(worldPosInPixels, visMinInPixels) ) //-slack
			) {

				p0 = paramArr[baseInd + E_TP_P0];
				p1 = paramArr[baseInd + E_TP_P1];
				p2 = paramArr[baseInd + E_TP_P2];
				thickVals = paramArr[baseInd + E_TP_THICKVALS];

				sphereRad = thickVals.z;

				dres = pointSegDistance(worldPosInPixels, p0, p1);
				//dres2 = pointSegDistance(worldPosInPixels,p0,p2);
				//dres = mix(dres2, dres1, mix(dres1.y,dres2.y,0.5) );

				//if (dres.x < bestRes.x) {

				t =  dres.y;
				bezTanP0 = mix(p0, p2, t);
				bezTanP1 = mix(p2, p1, t);
				resArr = pointSegDistance(worldPosInPixels, bezTanP0, bezTanP1);

				curThickness = mix(thickVals.x, thickVals.y, t) * (1.0 + 0.3*abs(sin(smoothVal*10.0)));

				if (
					resArr.x <curThickness
					//sin( (worldPosInPixels.x + worldPosInPixels.z + worldPosInPixels.y) / (0.125 * pixelsPerMeter) )
				) {

					if (
						(abs(resArr.x - curThickness) < 0.25 * pixelsPerMeter) &&
						(matResult.y != TEX_TREEWOOD)
					) {
						matResult.y = TEX_BARK;
					}
					else {
						matResult.y = TEX_TREEWOOD;
					}




					totCount = max( clamp(1.0 - (resArr.x / curThickness), 0.0, 1.0), totCount); //abs( sin(dres.x/(curThickness*0.25)) );


					//totCount += 1.0;

					// bestRes = dres;
					// bestInd = baseInd;
				}





				//roThetaPhi2 = += roThetaPhi;

				tempDis = distance(worldPosInPixels, p1);
				

				if ( (tempDis < sphereRad) ) {
					
					threshVal = pow(1.0-clamp(tempDis/sphereRad,0.0,1.0),@tt0PowValThresh@*8.0);
					totThresh += threshVal;
					maxv.w = sphereRad;
					maxv.xyz = p1;
					totNorms += maxv.xyz*threshVal;//threshVal*(worldPosInPixels - maxv.xyz);
					
					if (tempDis < minDis) {
						minDis = tempDis;
						bestNode = maxv;
					}
					
					
					if (matParams.y == E_PT_OAK2_TRUNK) {
						sphereRad = maxv.w;
						tempv = worldPosInPixels - maxv.xyz;
						tempvNorm = normalize(tempv);
						
						
						radNorm = length(tempv)/sphereRad;//sqrt();
						
						roThetaPhi.z = length(tempv); //sphereRad - 
						roThetaPhi.x = atan(tempvNorm.y, tempvNorm.x);
						roThetaPhi.y = acos(tempvNorm.z);
						
						k = 1;
						//for (k = 0; k < 2; k++) {
							radNormFloored = roundVal( (roThetaPhi.y)*@tt1NumDivsY@*8.0)/(tt1NumDivsY*8.0);						
							roThetaPhi2.x = roundVal( (roThetaPhi.x)*@tt1NumDivsX@*8.0*radNormFloored)/(tt1NumDivsX*8.0*radNormFloored);
							roThetaPhi2.y = roundVal( (roThetaPhi.y)*tt1NumDivsY*8.0)/(tt1NumDivsY*8.0);
							roThetaPhi2.z = roThetaPhi.z;
							
							resPoint[k].x = cos(roThetaPhi2.x)*sin(roThetaPhi2.y)*roThetaPhi2.z;
							resPoint[k].y = sin(roThetaPhi2.x)*sin(roThetaPhi2.y)*roThetaPhi2.z;
							resPoint[k].z = cos(roThetaPhi2.y)*roThetaPhi2.z - roThetaPhi.z*@tt1Falloff@;
							resPoint[k].w = (1.0-radNormFloored)*0.25*pixelsPerMeter;
						//}
						
						
						resArrLeaf = pointSegDistance(tempv, resPoint[1].xyz, resPoint[1].xyz); //
						
						
						curThickness = pixelsPerMeter*mix(
							@tt1MinRad@*16.0-8.0,
							@tt1MaxRad@*16.0,
							pow(1.0-radNorm,@tt1PowVal@*4.0)
						);
						
						if (
							(
								resArrLeaf.x <
								curThickness
							)
							&& (length(tempv) < sphereRad)
						) {
							matResult.y = TEX_LEAF;
							matResult.w = resArrLeaf.x/curThickness;
						}
					}
					
					if (matParams.y == E_PT_OAK_TRUNK) {
						// ROUND LEAF
						
						
						
						tempv = worldPosInPixels - maxv.xyz;
						
						if (length(tempv) < (@tt0MaxClamp@*8.0*pixelsPerMeter)) {
							roThetaPhi.z = sphereRad - length(tempv);
							roThetaPhi.x = atan(tempv.y, tempv.x);
							roThetaPhi.y = -0.35 * acos(tempv.z / length(tempv)); //randf(bestNode.xy)

							roThetaPhi.x *= @tt0ScaleParamX@*8.0;
							roThetaPhi.y *= @tt0ScaleParamY@*8.0;
							

							tempv = getShingle(
								threshVal*roThetaPhi * pixelsPerMeter * 8.0 / PI,
								1.0 * pixelsPerMeter,
								1.0*roThetaPhi.z,
								threshVal*8.0 * pixelsPerMeter * ( (0.95 - normalize(tempv).z) )
							);

							if ( (matResult.y == TEX_NULL) && (tempv.y != TEX_NULL) ) {
								matResult.y = TEX_LEAF;
								matResult.w = (1.0 - shingleMod);
							}
						}

						
					}	
					
					
					



				}

				//}
			}
		}
	}

	if (bestNode.z != invalid) {
		
		
		
	}
	
	// if (totThresh > @tt2MetaThresh@) {
	// 	//totNorms = totNorms/totThresh;
		
	// 	matResult.y = TEX_LEAF;
	// 	matResult.w = 1.0;
	// }




	if (matResult.y == TEX_TREEWOOD) {
		matResult.w = abs( sin(totCount * 8.0) );
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
	vec3 tempVec4 = vec3(0.0);
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




		if (

			(matParams.x == E_MAT_PARAM_BUILDING)
			//|| (matParams.x == E_MAT_PARAM_WALKWAY_TOP)

			//false

		) {

			matResult = getBuilding(
										worldPosInPixels,
										newUVW,
										tempVec3,
										matParams.xyz,
										bLessThanOrig,
										nodeDir,
										nearestJointXY,
										resXY,
										thickness,
										disCenterMinMax,
										visDisXY,
										floorHeight,
										1.0,
										max(cornerDisInPixels.x,cornerDisInPixels.y)
									);

			//tempVec3.xy = (worldPosInPixels.xy - boundsMinCorner.xy) / (boundsMaxCorner.xy - boundsMinCorner.xy);

			//if ( (tempVec3.x < 0.5) || (tempVec3.y < 0.5) || (tempVec3.z < 1.0*pixelsPerMeter) ) {
			isInside = bool(matResult.z);
			normalUID = matResult.x;
			finalMat = matResult.y;
			woodRes = matResult.w;
			//}


		}


		if (matParams.x == E_MAT_PARAM_ROOF) {

			//(matParams.x == E_MAT_PARAM_DOCK) ||




			matResult = getRoof(
										worldPosInPixels,
										newUVW,
										tempVec3,
										matParams.xyz,
										bLessThanOrig,
										nodeDir,
										nearestJointXY,
										resXY,
										thickness,
										disCenterMinMax,
										visDisXY,
										floorHeight,
										max(cornerDisInPixels.x,cornerDisInPixels.y)

										// worldPosInPixels,
										// newUVW,
										// bLessThanOrig,
										// isVert,
										// nearestJointXY,
										// resXY,
										// thickness,
										// disCenterMinMax,
										// visDisXY,
										// floorHeight
									);

			isInside = bool(matResult.z);
			normalUID = matResult.x;
			finalMat = matResult.y;
			woodRes = matResult.w;

			if (finalMat == TEX_SHINGLE) {
				finalMat += matParams.z;
			}

		}



		if (matParams.x == E_MAT_PARAM_FOUNDATION) {
			
			

			if (matParams.y == E_MAT_SUBPARAM_BRICK) {
				
				tempVec4.z = (visMaxInPixels.z-worldPosInPixels.z) + 1.0*pixelsPerMeter;
				
				tempf1 = floor (   (tempVec4.z - float(newUVW.z < (thickness-1.0*pixelsPerMeter))*pixelsPerMeter) / pixelsPerMeter) / floorHeight;

				
				if (tempf1 > stairVal) {
					
					if (
						
						true//( tempf1-stairVal < 0.3 )
						
					) {
						
						
						brickRes = 2.0;
						brickCoords = newUVW.xyz;
						if ((bLessThanOrig.x || bLessThanOrig.y)) {


							/*
							vec4 getArch(
							  vec4 newUVW,
							  float disFromTopInPixels,
							  float archDisFromTopInMeters,
							  float outerRadInMeters,
							  float innerRadInMeters,
							  float intervalSizeInMeters,
							  float intervalOffset
							)
							*/

							

							archRes = getArch(
													newUVW + vec4(-4.0 * pixelsPerMeter, 0.0, 0.0, 0.0),
													(tempVec4.z),
													floorHeight + 4.0,// + float(stairVal > 0.5) * 8.0,
													4.0,
													3.0,
													8.0,
													0.0
												);
							brickRes = archRes.w;
							brickCoords = archRes.xyz;

						}

						if (brickRes > 0.0) {

							insetAmount = float(brickRes == 2.0) * 0.25 * pixelsPerMeter;

							tempf3 = float(brickRes == 1.0) * 4.0;


							normalUID = getBoardSpaced(
														brickCoords + vec3(0.0, -0.6 * pixelsPerMeter, 0.0),
														vec3(2.0 + tempf3, 1.0, 2.0),
														0.125
													);


							if (stairVal == 1.0) {
								tempf2 = resNoRefVisDis;
							}
							else {

								tempVec4.z = (worldPosInPixels.z - visMinInPixels.z) - floorHeight * pixelsPerMeter - (1.0 * pixelsPerMeter + (pixelsPerMeter / 6.0));
								
								//
								//tempf1 = floor ( (tempVec4.z - float(newUVW.z < (thickness-1.0*pixelsPerMeter))*pixelsPerMeter) / pixelsPerMeter) / floorHeight;


								//
								
								//tempf1 = floor ( (tempVec4.z / (floorHeight * pixelsPerMeter)) * floorHeight ) / floorHeight;
								tempf2 = max(resNoRefVisDis, (stairVal - tempf1));
							}


							if (newUVW.z < thickness - insetAmount) {
								if (  (normalUID != 0.0) &&
											(
												( (nearestJointXY > divDis) && (!isDivider) ) ||
												( brickRes == 1.0 )
											)

									 ) { //
									finalMat = TEX_BRICK;
								}
								else {

									if (
										(tempf2 * thickness < thickness - (insetAmount - pixelsPerMeter / 6.0))

									) {
										finalMat = TEX_MORTAR;
									}
									else {
										finalMat = TEX_NULL;
									}

								}
							}
							
						}
						else {
							normalUID = 0.0;
							finalMod = 0.0;
							finalMat = TEX_NULL;
						}	
						
						isInside = tempf1-stairVal < 0.3;//finalMat != TEX_NULL; //[0]
						
					}

				}
				else {
					
					
					normalUID = 1.0;
					finalMod = 1.0;
					finalMat = TEX_NULL;
					isInside = true;
				}
			}
			else {
				
				// is wood
				
				
				
				tempVec4.z = (visMaxInPixels.z-worldPosInPixels.z) + (0.0)*pixelsPerMeter;
				
				tempf2 = (tempVec4.z - float(newUVW.z < (thickness-1.0*pixelsPerMeter))*pixelsPerMeter) / pixelsPerMeter;
				tempf1 = floor ( tempf2 ) / floorHeight;
				
				tempf2 /= floorHeight;
				
				isInside = tempf2-stairVal < 0.5;
				
				tempb2 = (thickness-newUVW.z) > (1.0*pixelsPerMeter);
				
				if (tempb2) {
					tempf1 = floor(stairVal*floorHeight)/floorHeight;
				}
				else {
					tempf1 = stairVal;
				}
				
				
				
				if (tempf2 > stairVal) {
					
					//if ((tempf2-stairVal) < 0.3) {
						
						//float(tempb2&&(stairVal != 0.0))*1.0*pixelsPerMeter + 
						
						tempf3 = (tempf1)*floorHeight*pixelsPerMeter;
						
						
						matResult = getBuilding(
													worldPosInPixels,
													newUVW + vec4( 0.0, tempf3, 0.0, 0.0),
													tempVec3 + vec3( 0.0, 0.0, tempf3),
													matParams.xyz,
													bLessThanOrig,
													nodeDir,
													nearestJointXY,
													resXY,
													thickness,
													disCenterMinMax,
													visDisXY,
													floorHeight,
													float ( (stairVal == 0.0) || (!tempb2) ),
								 					max(cornerDisInPixels.x,cornerDisInPixels.y)
													
												);
						//isInside = bool(matResult.z);
						normalUID = matResult.x;
						finalMat = matResult.y;
						woodRes = matResult.w;
						
					//}

				}
				else {
					
					
					normalUID = 1.0;
					finalMod = 1.0;
					finalMat = TEX_NULL;
					isInside = true;
				}
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			}
			
			
		}




		//resNoRefVisDis = max(resNoRef, visDisXY);
		tempb = (matParams.x == E_MAT_PARAM_DOOR);
		if ((matParams.x == E_MAT_PARAM_DOORWAY) || tempb) {

			//resNoRefVisDis
			if ( (resNoRefVisDisZ * thickness) > (thickness - wThickness) ) {
				tempf1 = float(worldPosInPixels.z - boundsMinCorner.z > 0.25 * pixelsPerMeter);
				finalMat = mix(
										 mix(TEX_WOOD, TEX_METAL, float(tempb) * matParams.z),
										 mix(TEX_BRICK, TEX_WOOD, matParams.z),
										 float(matParams.x == E_MAT_PARAM_DOORWAY)
									 );


				woodRes = mix(0.0 + float(isVert), 2.0, tempf1);
				normalUID = 24.0 + float(bLessThanOrig.z) + tempf1 + 4.0 * float(tempb);
				
			}
			else {

				if (tempb) {
					matResult = getSlats(newUVW, thickness, orig, worldPosInPixels, visMinInPixels, visMaxInPixels, isVert, matParams.z);
					normalUID = matResult.x;
					finalMat = matResult.y;
					woodRes = matResult.w;
				}
				else {
					finalMat = TEX_NULL;
				}

				

			}


			if (finalMat == TEX_BRICK) {
				normalUID = getBoardSpaced(newUVW.xyz, vec3(1.0, 0.5, 0.5), 0.125 );
				if ( normalUID != 0.0 ) {
					finalMat = TEX_BRICK;
				}
				else {
					finalMat = mix(TEX_NULL, TEX_MORTAR, float( resNoRef * thickness < (thickness - pixelsPerMeter / 32.0) ) );
				}
			}
			
			isInside = true;


		}
		
		
		
		

		if (matParams.x == E_MAT_PARAM_LANTERN) {

			if ( all(bLessThanOrig.xz) || all(bLessThanOrig.yz) ) {
				finalMat = TEX_GLASS;
			}
			else {
				finalMat = TEX_METAL;
				normalUID = 20.0;
			}
		}
		
		
		
		
		
		
		// if (matParams.x == E_MAT_PARAM_STAIRS) {


		// 	if (nodeDir == 2) {

		// 		tempVec3.xy = ((boundsMaxCorner.xy + boundsMinCorner.xy) / 2.0) - worldPosInPixels.xy;

		// 		tempf2 = (atan(tempVec3.x, tempVec3.y) * 1.0 + PI * 1.0 ) / (2.0 * PI);



		// 		// if (matParams.z == 0.0) {
		// 		//  tempf2 += 0.5;
		// 		// }

		// 		tempf2 += 0.5;

		// 		if (tempf2 > 1.0) {
		// 			tempf2 -= 1.0;
		// 		}



		// 		tempf1 = floor(( tempf2 * floorHeight * pixelsPerMeter ) / (1.0 * pixelsPerMeter)) * 1.0 * pixelsPerMeter;


		// 		isInside = (
		// 								 (tempVec3.z < tempf1 + 4.0 * pixelsPerMeter) &&
		// 								 (tempVec3.z > tempf1 - 4.0 * pixelsPerMeter)
		// 							 );

		// 		tempb = (distance(worldPosInPixels.xy, (boundsMaxCorner.xy + boundsMinCorner.xy) / 2.0 ) < 1.0 * pixelsPerMeter);

		// 		if (

		// 			(
		// 				(tempVec3.z < tempf1 + 0.0 * pixelsPerMeter) &&
		// 				(tempVec3.z > tempf1 - 1.0 * pixelsPerMeter)
		// 			) ||
		// 			tempb

		// 		) {
		// 			normalUID = (tempf2 * 8.0);
		// 			finalMat = TEX_WOOD;
		// 			finalMod = 1.0;
		// 			isInside = true;

		// 			if (mod(tempVec3.z, 1.0 * pixelsPerMeter) < 0.5 * pixelsPerMeter) {
		// 				finalMat = TEX_NULL;
		// 			}

		// 			if (tempb) {
		// 				normalUID = getBoardSpaced(newUVW.xyz, vec3(1.0, 0.5, 0.5), 0.125 );
		// 				if (  (normalUID != 0.0)  ) {
		// 					finalMat = TEX_BRICK;
		// 				}
		// 				else {
		// 					finalMat = mix(TEX_NULL, TEX_MORTAR, float( res * thickness < (thickness - pixelsPerMeter / 16.0) ) );
		// 				}
		// 			}
		// 		}


		// 	}
		// 	else {
		// 		tempVec3.xy = worldPosInPixels.xy - boundsMinCorner.xy;

		// 		if (nodeDir == 0) {
		// 			tempf1 = tempVec3.x;
		// 		}
		// 		else {
		// 			tempf1 = tempVec3.y;
		// 		}

		// 		tempf1 = floor(tempf1 / (1.0 * pixelsPerMeter)) * 1.0 * pixelsPerMeter;

		// 		if (tempVec3.z < 8.0 * pixelsPerMeter - tempf1) {
		// 			//normalUID = 1.0;
		// 			//finalMat = TEX_DIRT;
		// 			finalMod = 1.0;
		// 			isInside = true;


		// 			normalUID = getBoardSpaced(newUVW.xyz, vec3(1.0, 0.5, 1.0), 0.125 );
		// 			if (  (normalUID != 0.0) &&  (nearestJointXY > divDis) && (!isDivider)   ) {
		// 				finalMat = TEX_BRICK;
		// 			}
		// 			else {
		// 				finalMat = mix(TEX_NULL, TEX_MORTAR, float( res * thickness < (thickness - pixelsPerMeter / 8.0) ) );
		// 			}

		// 		}

		// 		if (abs(tempVec3.z - (8.0 * pixelsPerMeter - tempf1) ) < 4.0 * pixelsPerMeter) {
		// 			isInside = true;
		// 		}


		// 	}


		// }

		// if (matParams.x == E_MAT_PARAM_DOOR) {

		//  finalMat = TEX_WOOD;

		//  matResult = getSlats(newUVW, worldPosInPixels,visMinInPixels,visMaxInPixels, isVert);
		//  normalUID = matResult.x;
		//  finalMat = matResult.y;
		//  woodRes = matResult.w;

		//  // isInside[0] = true;

		//  // woodRes = mix(0.0 + float(isVert), 2.0, tempf1);
		//  // normalUID = 24.0 + float(bLessThanOrig.z) + tempf1;

		// }


	}

	// todo: move this to main function
	if (finalMat == TEX_WOOD) {
		finalMod = getWoodGrain(normalUID, worldPosInPixels, 2.0 * pixelsPerMeter, woodRes, 4.0 );
	}

	// if (finalMat == TEX_METAL) {
	//  finalMod = getWoodGrain(normalUID, worldPosInPixels, 2.0*pixelsPerMeter, 3.0, 2.0 );
	// }










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
	float finalBlend = 1.0;
	float finalNormUID = 0.0;
	float finalInside = 0.0;
	float finalLayer = 0.0;
	float fj;
	float fi;

	int iMatCount = 0;
	
	smoothVal = texture2D(Texture2, 512.0 * worldPosInPixels.xy/worldSizeInPixels.xy ).r;

	vec4 finalRes = vec4(0.0);
	vec4 finalRes2 = vec4(0.0);
	matResultTer = vec4(0.0);
	vec4 matResultTree = vec4(0.0);
	vec4 matResultGeom = vec4(0.0);
	vec4 matResult = vec4(0.0);
	vec4 tempResult;




	if (hasTerrain) {
		getCobble(worldPosInPixels);
		matResultTer = getTerrain(worldPosInPixels);
	}

	if (hasGeom) {

		for (j = 0; j < E_MAT_PARAM_TREE; j++) {

			iMatCount = int(matCountArr[j]);

			if (iMatCount > 0) {
				tempResult = getGeom(worldPosInPixels, j);//, matResultTer.w-0.75*pixelsPerMeter );
				if ( (tempResult.z == 1.0) || (tempResult.y != TEX_NULL) ) {
					matResultGeom = tempResult;
				}
			}
		}
	}



	if ( (matResultTer.y != TEX_NULL) && (matResultGeom.z != 1.0) ) {
		finalBlend = 0.75;
		matResult = matResultTer;
	}
	else {
		matResult = matResultGeom;
	}

	if (hasTree) {
		matResultTree = getTree(worldPosInPixels);
		if (matResultTree.y != TEX_NULL) {
			matResult = matResultTree;
		}

	}

	finalNormUID = matResult.x;
	finalMat = matResult.y;
	finalInside = matResult.z;
	finalMod = matResult.w;






	vec4 tex2 =  texture3D(Texture1, newCoords);
	if (tex2.a > 0.5) {
		finalMat = TEX_DIRT;

	}
	else {
		if (tex2.b > 0.5) {
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


	// if (finalMat == TEX_BRICK) {
	// 	finalMat = TEX_DIRT;
	// }
	
	//

	if (finalMat == TEX_DIRT) {
		fj = clamp(
			(
				abs(sin(worldPosInPixels.z / (4.0*pixelsPerMeter))) + 
				texture2D(Texture2, 256.0 * worldPosInPixels.xy/worldSizeInPixels.xy ).r*3.0
				+ matResultTer.w*2.0 
			),
			0.0,
			5.0
		);
		finalMat = TEX_EARTH + floor(fj);
		finalMod = fj - floor(fj);
	}

	//TODO: ADD BACK IN FOR WATER
	if (

	 (
	   (finalMat == TEX_NULL)
	   // || (finalMat == TEX_GRASS)
	 ) &&
	 (worldPosInPixels.z <= (seaLevel)) && //
	 (finalInside == 0.0)

	) {
	 finalLayer = 1.0;
	 finalMat = TEX_WATER;
	 finalNormUID = 254.0;
	 finalMod = 0.0;
	}
	
	// if (finalMat == TEX_GRASS) {
	//  finalLayer = 1.0;
	//  //finalMat = TEX_WATER;
	//  finalNormUID = 254.0;
	//  //finalMod = 0.0;
	// }
	
	
	// if ((finalMat == TEX_NULL)) {
		
	// 	finalLayer = 0.0;
	// 	finalMat = TEX_DIRT;
	// 	finalNormUID = 1.0;
	// 	finalMod = 0.0;
	// }


	if (finalMat == TEX_GLASS) {
		finalLayer = 1.0;
		finalNormUID = 254.0;
		finalMod = 0.0;
	}
	
	if (finalMat == TEX_PLASTER) {
		finalMod = abs(sin(smoothVal*5.0))*0.5;
	}

	/////////////////////////
	//blendAmount deprecated
	/////////////////////////

	//finalMod = voroGrad;

	finalLayer = min(finalLayer, totLayers - 1.0);

	finalRes.a = finalMat / 255.0;
	finalRes.r = finalLayer;
	finalRes.b = (finalMod * 127.0) / 255.0; //finalMod
	//0.75; // blend amount
	finalRes.g = finalNormUID / 255.0;

	//finalMod = abs(sin(worldPosInPixels.z/(1.0*pixelsPerMeter)));
	//finalMod = matResult.w;


	//finalRes2.b = (finalMod * 127.0) / 255.0; //finalMod


	gl_FragData[0] = finalRes;
	//gl_FragData[1] = finalRes2;

}

