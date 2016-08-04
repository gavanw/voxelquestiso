class GameBlock
{
public:



	Singleton *singleton;

	int blockId;
	int blockSizeInHolders;
	int blockSizeInLots;
	int localGeomCounter;
	int lightCounter;
	int terDataBufAmount;

	bool forceUpdate;

	float trilin[8];

	int terDataVisPitchXY;
	float fTerDataVisPitchXY;
	int terDataBufPitchXY;
	int terDataBufPitchScaledXY;

	int terDataVisPitchZ;
	float fTerDataVisPitchZ;
	int terDataBufPitchZ;
	int terDataBufPitchScaledZ;

	
	int terDataTexScale;
	int terDataVisSize;
	int terDataBufSize;
	int blockSizeInPixels;
	int iHolderSize;
	int maxFloors;
	float fBlockSizeInPixels;

	int dirModX[6];
	int dirModY[6];
	int dirModZ[6];
	int opDir[6];
	
	float pixelsPerMeter;
	float floorHeightInMeters;
	
	float floorHeight;
	float roofHeight;

	bool isBuilding[E_CT_LENGTH];
	bool isRoad[E_CT_LENGTH];
	bool isRoom[E_CT_LENGTH];
	bool isBase[E_CT_LENGTH];
	bool isTraversable[E_CT_LENGTH];
	int ctClasses[E_CT_LENGTH];
	int layerHash[E_CT_LENGTH];

	FIVector4 anchorPoint;
	FIVector4 moveMinInPixels;
	FIVector4 moveMaxInPixels;
	
	FIVector4 p1;
	FIVector4 p2;
	FIVector4 newP1;
	FIVector4 newP2;
	FIVector4 rad;
	FIVector4 visInsetFromMin;
	FIVector4 visInsetFromMax;
	FIVector4 cornerRad;
	FIVector4 thickVals;
	FIVector4 powerVals;
	FIVector4 powerVals2;
	FIVector4 matParams;
	FIVector4 centerPoint;
	FIVector4 lightVec;
	FIVector4 offsetInBlocks;
	FIVector4 offsetInBlocksWrapped;
	FIVector4 origin;
	FIVector4 blockMinBufInPixels;
	FIVector4 blockMaxBufInPixels;
	
	FIVector4 tempVec;
	FIVector4 tempVec2;
	FIVector4 tempVec3;
	FIVector4 tempVec4;
	FIVector4 tempVecB;
	FIVector4 tempVecB2;
	FIVector4 tempVecB3;

	std::vector<GameGeom *> gameGeom;
	std::vector<GameLight *> gameLights;
	//std::vector<GameEnt *> gameEnts; // only one instance per block

	//GamePlant oakTree2;
	//GamePlant oakTree;
	//GamePlant bareTree;
	GameWorld *gw;
	GamePageHolder **holderData;

	BuildingNode *buildingData;
	MapNode *mapData;
	uint *terData;

	BuildingCon *curCon;


	GameBlock() {
		terData = NULL;
		buildingData = NULL;
	}

	void init(Singleton *_singleton, int _blockId, int _x, int _y, int _xw, int _yw) {


		dirModX[0] = 1;
		dirModX[1] = -1;
		dirModX[2] = 0;
		dirModX[3] = 0;
		dirModX[4] = 0;
		dirModX[5] = 0;

		dirModY[0] = 0;
		dirModY[1] = 0;
		dirModY[2] = 1;
		dirModY[3] = -1;
		dirModY[4] = 0;
		dirModY[5] = 0;

		dirModZ[0] = 0;
		dirModZ[1] = 0;
		dirModZ[2] = 0;
		dirModZ[3] = 0;
		dirModZ[4] = 1;
		dirModZ[5] = -1;

		opDir[0] = 1;
		opDir[1] = 0;
		opDir[2] = 3;
		opDir[3] = 2;
		opDir[4] = 5;
		opDir[5] = 4;

		forceUpdate = false;

		singleton = _singleton;
		blockId = _blockId;
		offsetInBlocks.setIXYZ(_x, _y, 0);
		offsetInBlocksWrapped.setIXYZ(_xw, _yw, 0);

		localGeomCounter = 0;
		lightCounter = 0;

		origin.setFXYZ(0.0f, 0.0f, 0.0f);




		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int q;
		
		int tempInt;
		int incVal;
		
		int minRot = 0;
		int maxRot = 0;


		for (i = 0; i < E_CT_LENGTH; i++) {
			isTraversable[i] = false;
			isRoom[i] = false;
			isBase[i] = false;
			isBuilding[i] = false;
			isRoad[i] = false;
			ctClasses[i] = E_CTC_NOTHING;
			layerHash[i] = 0;
		}
		
		
		layerHash[E_CT_FOUNDATION] = 2;
		
		layerHash[E_CT_LANTERN] = 3;
		layerHash[E_CT_WINDOWFRAME] = 1;
		layerHash[E_CT_WINDOW] = 1;
		layerHash[E_CT_DOORWAY] = 1;
		layerHash[E_CT_DOOR] = 1;
		
		
		
		isTraversable[E_CT_ROAD] = true;
		isTraversable[E_CT_CONNECTED] = true;
		
		isRoad[E_CT_ROAD] = true;
		
		isBuilding[E_CT_ROOM_BRICK] = true;
		isBuilding[E_CT_ROOM_TUDOR] = true;
		isBuilding[E_CT_WALKWAY] = true;
		isBuilding[E_CT_ROOF] = true;

		isRoom[E_CT_ROOM_BRICK] = true;
		isRoom[E_CT_ROOM_TUDOR] = true;
		isRoom[E_CT_WALKWAY] = true;

		isBase[E_CT_ROOM_BRICK] = true;
		isBase[E_CT_ROAD] = true;
		
		
		ctClasses[E_CT_NULL] = E_CTC_NOTHING;
		ctClasses[E_CT_CONNECTED] = E_CTC_NOTHING;
		ctClasses[E_CT_ROAD] = E_CTC_ROAD;
		ctClasses[E_CT_ROOF] = E_CTC_ROOF;
		ctClasses[E_CT_WALKWAY_TOP] = E_CTC_ROOM;
		ctClasses[E_CT_ROOM_BRICK] = E_CTC_ROOM;
		ctClasses[E_CT_ROOM_TUDOR] = E_CTC_ROOM;
		ctClasses[E_CT_WALKWAY] = E_CTC_ROOM;
		ctClasses[E_CT_STAIRS] = E_CTC_STAIRS;
		ctClasses[E_CT_LENGTH] = E_CTC_NOTHING;

		int nMax;

		int curAlign = 0;

		float x1;
		float y1;
		float z1;

		float x2;
		float y2;
		float z2;


		float hingeDis = 0.0f;

		//float z;

		float zmax;


		int curDir = 0; // 0:x, 1:y, 2:z

		int roofType = 0;

		maxFloors = 3;

		terDataTexScale = singleton->terDataTexScale;

		blockSizeInHolders = singleton->blockSizeInHolders;
		blockSizeInLots = singleton->blockSizeInLots;

		blockSizeInPixels = singleton->blockSizeInPixels;
		fBlockSizeInPixels = (float)blockSizeInPixels;

		pixelsPerMeter = singleton->pixelsPerMeter;


		float uvSizeInMeters = 1.0;
		float uvSizeInPixels = uvSizeInMeters * pixelsPerMeter; // 64

		float offsetPerFloor = 0.25;
		float floorOffset;

		bool notFound;
		bool foundA;
		bool foundB;
		bool foundC;
		
		bool isInside;
		bool isWingBeg;
		bool isWingEnd;
		bool isWingBeg2;
		bool isWingEnd2;
		
		
		float wingMult;
		float newWingMult;
		float nDir;

		float hm = 0.0f;

		float cr1;
		float cr2;
		float cr3;
		float cr4;

		float doorMod = 0.0f;

		gw = singleton->gw;

		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBO", 0);
		FBOWrapper *fbow2 = singleton->getFBOWrapper("cityFBO", 0);

		int maxLoop;
		int lotX;
		int lotY;
		int lotZ;


		float xmod1;
		float ymod1;
		float zmod1;

		float xmod2;
		float ymod2;
		float zmod2;


		int curLev = 0;
		int kt = 0;
		int kmax = 0;
		int kmin = 0;
		int kstep = 0;

		int testX;
		int testY;


		int baseI = 0;
		int baseJ = 0;


		int res;
		int res2;
		int res3;

		unsigned int nodeFlags = 0;

		int counter;

		int houseColor = 0;
		int lotSizeO2 = singleton->pixelsPerLot / 2;

		int XP = 0;
		int XN = 1;
		int YP = 2;
		int YN = 3;
		int curChannel = 0;

		int ktemp = 0;
		int curId = 0;
		int curBT = 0;
		int curBT2 = 0;
		int curBT3 = 0;
		int curHeight = 0;

		int wingDir;

		floorHeightInMeters = singleton->floorHeightInMeters;
		float roofHeightInMeters;// = singleton->roofHeightInMeters;
		float wallRadInMeters;
		float flushRadInMeters;
		float fi;
		float fj;
		float fk;

		float tempf;
		float pv1;
		float pv2;
		float pv3;
		float pv4;

		float perc1;
		float perc2;
		float baseOffset = 0.0f;
		float holderSizeInPixels = singleton->holderSizeInPixels;

		bool doProc = false;
		bool isVert;
		bool isDif;

		int curInd = 0;
		int testInd = 0;
		int testInd2 = 0;
		int testInd3 = 0;
		int testVal;
		int testVal2;
		int conType;
		int testConType;
		int seaLev;

		int curType;
		uint uiSimp;
		float fSimp;

		int newCount = 0;
		int io, jo, ko;
		
		float doorThickness = 0.0625f;
		float lanternOffset = 0.1875f;
		float doorInset = 0.0f;
		float doorScale = 0.625f;
		
		int iNodeDivsPerLot = singleton->iNodeDivsPerLot;

		iHolderSize = blockSizeInHolders * blockSizeInHolders * blockSizeInHolders;
		holderData = new GamePageHolder*[iHolderSize];
		for (i = 0; i < iHolderSize; i++) {
			holderData[i] = NULL;
		}


		terDataBufAmount = singleton->terDataBufAmount;
		terDataVisSize = singleton->terDataVisSize;
		terDataBufSize = singleton->terDataBufSize;

		terDataVisPitchXY = singleton->terDataVisPitchXY;
		fTerDataVisPitchXY = singleton->terDataVisPitchXY;
		terDataBufPitchXY = singleton->terDataBufPitchXY;
		terDataBufPitchScaledXY = singleton->terDataBufPitchScaledXY;

		terDataVisPitchZ = singleton->terDataVisPitchZ;
		fTerDataVisPitchZ = singleton->terDataVisPitchZ;
		terDataBufPitchZ = singleton->terDataBufPitchZ;
		terDataBufPitchScaledZ = singleton->terDataBufPitchScaledZ;

		
		seaLev = singleton->getSLNormalized()*fTerDataVisPitchZ + terDataBufAmount;

		float fTerDataBufAmount = (float)(singleton->terDataBufAmount);
		float bmodXY = fTerDataBufAmount / (fTerDataVisPitchXY);
		float bmodZ = fTerDataBufAmount / (fTerDataVisPitchZ);

		blockMinBufInPixels.copyFrom(&(offsetInBlocks));
		blockMinBufInPixels.addXYZ(-bmodXY, -bmodXY, -bmodZ);
		blockMinBufInPixels.multXYZ(fBlockSizeInPixels);


		blockMaxBufInPixels.copyFrom(&(offsetInBlocks));
		blockMaxBufInPixels.addXYZ(1.0f + bmodXY, 1.0f + bmodXY, 1.0f + bmodZ);
		blockMaxBufInPixels.multXYZ(fBlockSizeInPixels);


		



		terData = new uint[terDataBufSize];
		buildingData = new BuildingNode[terDataBufSize];

		for (i = 0; i < terDataBufSize; i++) {
			terData[i] = 0;

			buildingData[i].id = -1;
			buildingData[i].visited = 0;
			buildingData[i].mazeIndex = -1;
			buildingData[i].nearTerrain = false;
			buildingData[i].nearAir = false;

			for (j = 0; j < TOT_NODE_VALS; j++) {
				curCon = &(buildingData[i].con[j]);
				curCon->conType = E_CT_NULL;
				curCon->nodeFlags = 0;
				curCon->heightDelta = 0;
				curCon->wingMult = 1.0f;
				curCon->wallRadInMeters = singleton->wallRadInMeters;
			}


		}

		// Create Map Data


		
		// iBuildingNodesPerSideM1 = blockSizeInLots*iNodeDivsPerLot;
		// fBuildingNodesPerSideM1 = (float)iBuildingNodesPerSideM1;
		// iBuildingNodesPerSide = iBuildingNodesPerSideM1 + 1;
		int iMapBufSize = terDataBufPitchXY * terDataBufPitchXY;

		mapData = new MapNode[iMapBufSize];

		for (i = 0; i < iMapBufSize; i++) {
			mapData[i].id = 0;
			for (j = 0; j < TOT_MAP_DIRS; j++) {
				mapData[i].connectionProps[j] = E_CT_NULL;
			}
		}




		// Create Ter Data

		p = 1;
		for (i = 0; i < terDataBufPitchXY; i++) {
			fi = (float)((i / p) * p);
			for (j = 0; j < terDataBufPitchXY; j++) {
				fj = (float)((j / p) * p);
				for (k = 0; k < terDataBufPitchZ; k++) {
					fk = (float)k;


					curInd = getNodeIndex(i, j, k, 0);

					// fSimp = simplexScaledNoise(
					//  4.0f, //octaves
					//  2.0f, //persistence (amount added in each successive generation)
					//  1.0f/32.0f, //scale (frequency)
					//  0.0f, // lo bound
					//  1.0f, // hi bound
					//  fi + offsetInBlocks.getFX()*((float)terDataVisPitchXY) - 1.0f,
					//  fj + offsetInBlocks.getFY()*((float)terDataVisPitchXY) - 1.0f,
					//  fk + offsetInBlocks.getFZ()*((float)terDataVisPitchZ) - 1.0f
					// );
					// uiSimp = clampfZO(fSimp)*255.0f;


					tempVec.setFXYZ(
						fi + offsetInBlocks.getFX()*fTerDataVisPitchXY - fTerDataBufAmount,
						fj + offsetInBlocks.getFY()*fTerDataVisPitchXY - fTerDataBufAmount,
						fk + offsetInBlocks.getFZ()*fTerDataVisPitchZ - fTerDataBufAmount
					);
					tempVec.multXYZ(
						fBlockSizeInPixels / fTerDataVisPitchXY,
						fBlockSizeInPixels / fTerDataVisPitchXY,
						fBlockSizeInPixels / fTerDataVisPitchZ	
					);

					tempf = singleton->getHeightAtPixelPos(tempVec.getFX(), tempVec.getFY());

					if ( tempVec.getFZ() < tempf) {//tempVec.getFZ() < singleton->getSLInPixels() + 4.0*pixelsPerMeter ) {//
						uiSimp = 255;
					} else {
						uiSimp = 0;
					}



					// if ((i+j+k)%2 == 0) {
					//  uiSimp = 255;
					// }
					// else {
					//  uiSimp = 0;
					// }

					terData[curInd] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;
				}
			}
		}






		// Get Ter Data Height

		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {

				testInd2 = -1;
				for (k = 0; k < terDataBufPitchZ; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					if (terData[curInd] != 0) {
						singleton->rbHeightStack[curInd] = 0;
					} else {

						if (testInd2 == -1) {
							testInd2 = k;
						}

						testInd = getNodeIndex(i, j, k - 1, 0);

						if (testInd > -1) {
							singleton->rbHeightStack[curInd] = singleton->rbHeightStack[testInd] + 1;
						} else {
							singleton->rbHeightStack[curInd] = 0;
						}
					}
				}

				

				mapData[getMapNodeIndex(i, j, 0)].terHeight = testInd2;
				mapData[getMapNodeIndex(i, j, 0)].adjustedHeight = testInd2;
			}
		}


		












		// Layout Map Roads

		for (i = -1; i <= blockSizeInLots; i++) {
			for (j = -1; j <= blockSizeInLots; j++) {


				for (m = 0; m < 2; m++) {

					switch (m) {
					case 0:
						//curChannel = gw->stChannel;
						curChannel = gw->pathChannel;
						break;
					case 1:
						curChannel = gw->btChannel;
						break;
					}

					//one lot = one map pixel
					lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
					lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;
					res = fbow2->getPixelAtWrapped(lotX, lotY, curChannel);


					// if (
					// 	singleton->getHeightAtPixelPos(lotX*singleton->pixelsPerLot,lotY*singleton->pixelsPerLot) <=
					// 	singleton->getSLInPixels()  + 1.0f * pixelsPerMeter
					// ) {
					// 	curType = E_CT_DOCK;
					// }
					// else {
						curType = E_CT_ROAD;
					//}




					// roads
					for (k = 0; k < TOT_MAP_DIRS; k++) {

						if ( (res & gw->dirFlagsO[k]) > 0) { // has road

							baseI = i * iNodeDivsPerLot + terDataBufAmount;
							baseJ = j * iNodeDivsPerLot + terDataBufAmount;

							for (m = 0; m < iNodeDivsPerLot; m++) {
								switch (k) {
								case 0: // x+
									connectMapNodes(baseI + iNodeDivsPerLot, baseJ + m, baseI + iNodeDivsPerLot, baseJ + m + 1, curType, -1, 0);
									break;
								case 1: // x-
									connectMapNodes(baseI, baseJ + m, baseI, baseJ + m + 1, curType, -1, 0);
									break;
								case 2: // y+
									connectMapNodes(baseI + m, baseJ + iNodeDivsPerLot, baseI + m + 1, baseJ + iNodeDivsPerLot, curType, -1, 0);
									break;
								case 3: // y-
									connectMapNodes(baseI + m, baseJ, baseI + m + 1, baseJ, curType, -1, 0);
									break;

								}
							}

						}
					}
				}


			}
		}

		// houses

		for (i = 0; i < blockSizeInLots; i++) {
			for (j = 0; j < blockSizeInLots; j++) {

				lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
				lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;


				res = fbow2->getPixelAtWrapped(lotX, lotY, gw->houseChannel);
				res3 = fbow2->getPixelAtWrapped(lotX, lotY, gw->btChannel);

				if (res != 0) {
					for (k = 0; k < TOT_MAP_DIRS; k++) {

						res2 = fbow2->getPixelAtWrapped(lotX + dirModX[k], lotY + dirModY[k], gw->houseChannel);

						if ( (res == res2)  && ( touchesMap(i,j,E_CT_ROAD,0) == 0 ) ) { // house id matches, there is a house in that direction




							baseI = i * iNodeDivsPerLot + terDataBufAmount + iNodeDivsPerLot / 2;
							baseJ = j * iNodeDivsPerLot + terDataBufAmount + iNodeDivsPerLot / 2;

							for (m = 0; m < iNodeDivsPerLot / 2; m++) {

								
								switch (k) {
								case 0: // x+
									connectMapNodes(baseI + m, baseJ, baseI + m + 1, baseJ, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 1: // x-
									connectMapNodes(baseI - (m + 1), baseJ, baseI - m, baseJ, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 2: // y+
									connectMapNodes(baseI, baseJ + m, baseI, baseJ + m + 1, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 3: // y-
									connectMapNodes(baseI, baseJ - (m + 1), baseI, baseJ - m, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;

								}


							}


						}
					}
				}

			}
		}



		// connect wings

		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				if ( touchesMap(i, j, E_CT_NULL, 0) == 4 ) {

					notFound = true;
					for (k = 0; (k < 4) && notFound; k++) {

						isVert = k >= 2;

						testX = i + dirModX[k];
						testY = j + dirModY[k];

						if ( touchesMap(testX, testY, E_CT_MAINHALL, 0) >= 1 ) {

							if (
								(touches2Map(i, j, E_CT_WING, 0) == 0)
								
								// TODO: must ensure any random number
								// is persistent across the world with iSeedRand2
								
							) {

								if (true) {

									testInd = getMapNodeIndex(testX, testY, 0);

									if (testInd > -1) {
										testInd2 = mapData[testInd].id;
									} else {
										testInd2 = 0;
									}

									connectMapNodes(i, j, testX, testY, E_CT_WING, testInd2, 0 );

									testX = i + dirModX[ gw->opDir[k] ];
									testY = j + dirModY[ gw->opDir[k] ];

									if (touchesMap(testX, testY, E_CT_ROAD, 0) >= 1) {
										connectMapNodes(i, j, testX, testY, E_CT_ROAD, -1, 0);

										

									}
									
									notFound = false;
								}

							}
						}
					}
				}
			}
		}
		
		
		tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
		
		
		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				testInd = getMapNodeIndex(i, j, 0);
				tempVec.setFXYZ(i*2.132f,j*4.10523f,15.23523f);

				mapData[testInd].houseHeight = iGetRandSeeded(&tempVec,&tempVec2, 0, 1);
			}
		}
		
		
		
		
		
		
		
		
		if (singleton->treesOn) {
			for (i = terDataBufAmount*2; i < terDataBufPitchXY-terDataBufAmount*2; i++) {
				for (j = terDataBufAmount*2; j < terDataBufPitchXY-terDataBufAmount*2; j++) {
					if ( (touchesWithinRadMap(i,j,E_CT_TREE, 3, 0) == 0) && (touches2Map(i,j,E_CT_NULL,0) == 16) ) {

						lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
						lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;

						x1 = lotX + (i*blockSizeInPixels)/terDataBufPitchXY;
						y1 = lotY + (j*blockSizeInPixels)/terDataBufPitchXY;

						testInd = getMapNodeIndex(i, j, 0);
						
						tempVec.setFXYZ(i,j,15.0);

						if (
							
							//singleton->getHeightAtPixelPos(x1,y1) >
							//singleton->getSLInPixels() + 2.0f * pixelsPerMeter
							
							( ((float)(mapData[testInd].terHeight))/fTerDataVisPitchZ ) >
							(singleton->getSLNormalized() + 1.0f/255.0f)
							
						) {
							
							
							
							if ( iGetRandSeeded(&tempVec,&tempVec2, 0, 100) > 20 ) {
								mapData[testInd].connectionProps[0] = E_CT_TREE;
							}
						}

						
					}
				}
			}
		}




		// even out adjusted heights for terrain to be within one unit of eachother

		counter = 0;
		
		int newSeaLev = seaLev+1;
		
		do {

			notFound = false;

			for (i = 0; i < terDataBufPitchXY; i++) {
				for (j = 0; j < terDataBufPitchXY; j++) {

					curInd = getMapNodeIndex(i, j, 0);
					
					if (curInd > -1) {
						m = mapData[curInd].adjustedHeight;

						p = 0;

						for (k = 0; k < TOT_MAP_DIRS; k++) {
							testX = i + dirModX[k];// * q;
							testY = j + dirModY[k];// * q;
							testInd = getMapNodeIndex(testX, testY, 0);

							if (testInd > -1) {
								p = max(p, mapData[testInd].adjustedHeight);
							}
						}

						if (p - m > 1) {
							mapData[curInd].adjustedHeight = p - 1;
							notFound = true;
						}
						
						if ( newSeaLev > mapData[curInd].adjustedHeight) {
							mapData[curInd].adjustedHeight = max(mapData[curInd].adjustedHeight, newSeaLev);
							notFound = true;
						}
					}
					


				}
			}

			counter++;

		} while (notFound && (counter < 16));
















		



		


		// building layout

		for (n = 0; n < E_BG_LENGTH; n++) {

			if (n == E_BG_DOORS) {
				incVal = 1;
			}
			else {
				incVal = 2;
			}

			for (ktemp = 0; ktemp < terDataBufPitchZ; ktemp++) {

				if (n == E_BG_FILL_TERRAIN) {
					k = (terDataBufPitchZ - 1) - ktemp;
				}
				else {
					k = ktemp;
				}


				fk = (float)k;
				for (j = 0; j < terDataBufPitchXY; j++) {
					fj = (float)j;
					for (i = 0; i < terDataBufPitchXY; i++) {
						fi = (float)i;

						curInd = getNodeIndex(i, j, k, 0);




						if (curInd > -1) {

							for (m = 0; m < 6; m += incVal) {



								conType = buildingData[curInd].con[m].conType;
								nodeFlags = 0;

								switch (n) {

								case E_BG_ROADS_AND_BUILDINGS:




									if (m < 4) {
										testInd = getMapNodeIndex(i, j, 0);
										testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);

										if (
											(testInd > -1) &&
											(testInd2 > -1)
										) {

											curBT = mapData[testInd].connectionProps[m];
											//curBT2 = mapData[testInd2].connectionProps[m];

											testVal = mapData[testInd].adjustedHeight;
											testVal2 = mapData[testInd2].adjustedHeight;


											/*
											int _x1,
											int _y1,
											int _z1,
											int _x2,
											int _y2,
											int _z2,
											int ct,
											int id = -1,
											int _heightDelta = 0,
											int _direction = 0,
											float _wallRadInMeters = -1.0f
											*/


											switch (curBT) {
												case E_CT_ROAD:
												case E_CT_MAINHALL:
												case E_CT_WING:
													
													
													if (
														testVal == (k+1)
													) {
														connectNodes(
															i,
															j,
															k,
															i + dirModX[m],
															j + dirModY[m],
															k + dirModZ[m],

															E_CT_FOUNDATION,
															-1,
															testVal2 - testVal, // heightDelta,
															0,
															singleton->wallRadInMeters + 1.0f
														);
													}												
												break;
											}

											switch (curBT) {
											case E_CT_ROAD:

												if (
													testVal == k
												) {
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_ROAD,
														-1,
														testVal2 - testVal // heightDelta
													);
												}

												break;


											case E_CT_TREE:

												if (
													testVal == k
												) {
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_TREE,
														-1,
														0 // heightDelta
													);
												}

												break;


											


											/*
											int _x1,
											int _y1,
											int _z1,
											int _x2,
											int _y2,
											int _z2,
											
											int ct,
											int id = -1,
											int _heightDelta = 0,
											int _direction = 0,
											float _wallRadInMeters = -1.0f,
											unsigned int _nodeFlags = 0
											*/


												
											case E_CT_MAINHALL:
											case E_CT_WING:
												if (
													// max(
													// 	mapData[testInd].adjustedHeight,
													// 	mapData[testInd2].adjustedHeight
													// )
													// == k
													
													(
														(k >= mapData[testInd].adjustedHeight) &&
														(k <= mapData[testInd].adjustedHeight + mapData[testInd].houseHeight)
													)
													||
													(
														(k >= mapData[testInd2].adjustedHeight) &&
														(k <= mapData[testInd2].adjustedHeight)
													)
												) {

													tempf = -1.0f;
												
													// if (
													// 	((mapData[testInd].adjustedHeight + mapData[testInd].houseHeight - k) == 0) &&
													// 	(mapData[testInd].houseHeight == 1)
													// ) {
													// 	tempf = singleton->wallRadInMeters + 1.0;
													// }

													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_ROOM_TUDOR,
														mapData[testInd].id,
														0,
														0,
														tempf
													);


												}
												break;
											}


										}


									}


									break;

								// case E_BG_STAIRS: // add stairs
								// 	if (m == 4) {

								// 		// only put stairs in placed building segments
								// 		if (conType > E_CT_CONNECTED) {
								// 			foundA = false;
								// 			testInd = -1;

								// 			// find best direction for stairs
								// 			for (p = 0; p < 4; p++) {
								// 				if (buildingData[curInd].con[p].conType == conType) {
								// 					foundA = true;
								// 					if (p % 2 == 0) {
								// 						if (testInd == -1) {
								// 							testInd = p;
								// 						} else {

								// 						}

								// 					}
								// 					break;
								// 				}
								// 			}

								// 			if (foundA) { // make stairs straight
								// 				if (testInd > -1) {
								// 					connectNodes(
								// 						i,
								// 						j,
								// 						k,
								// 						i + dirModX[testInd],
								// 						j + dirModY[testInd],
								// 						k + dirModZ[testInd],

								// 						E_CT_STAIRS,

								// 						
								// 					);
								// 				}

								// 			} else { // is tower, make winding stairs
								// 				connectNodes(
								// 					i,
								// 					j,
								// 					k,
								// 					i + dirModX[m],
								// 					j + dirModY[m],
								// 					k + dirModZ[m],

								// 					E_CT_STAIRS,

								// 					
								// 				);
								// 			}
								// 		}

								// 	}
								// 	break;


								// case E_BG_REMOVE_REDUNDANT_Z_SEGMENTS:
								
									

								// 	if (m == 4) {
										
								// 		doProc = false;
										
								// 		if ( ctClasses[conType] == E_CTC_ROAD ) {
								// 			if ( touchesPlanarClass(i,j,k+1,E_CTC_ROAD, 0) ) {
								// 				doProc = true;
								// 			}
								// 		}
										
								// 		if (touchesRoomOnLevel(i, j, k)) {
								// 			doProc = true;
								// 		}
										
								// 		if (doProc) {
								// 			connectNodes(
								// 				i,
								// 				j,
								// 				k,
								// 				i,
								// 				j,
								// 				k + 1,

								// 				E_CT_CONNECTED
								// 			);
								// 		}
										
								// 	}


								// 	break;


								case E_BG_ROOFS:





									//if (m < 4) {

									roofType = E_CT_NULL;


									if (conType == E_CT_ROOM_TUDOR) {
										roofType = E_CT_ROOF;
										
									}
									if (conType == E_CT_WALKWAY) {
										roofType = E_CT_WALKWAY_TOP;
									}




									if (roofType != E_CT_NULL) {

										testInd = getNodeIndex(i, j, k + 1, 0);

										if (testInd > -1) {
											testConType = buildingData[testInd].con[m].conType;
											if (testConType <= E_CT_CONNECTED) {


												if (m == 4) {
													foundA = !( touchesRoomOnLevel(i, j, k + 1) );
												} else {
													foundA = true;
												}

												if (foundA) {
													connectNodes(
														i,
														j,
														k + 1,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m] + 1,

														roofType,

														buildingData[curInd].id,
														
														0,
														0,
														singleton->wallRadInMeters + 0.5f

													);
												}
											}
										}
									}
									//}



									break;

								// case E_BG_BASEMENTS:



								// 	// if (isRoom[conType] && (conType != E_CT_ROOM_BRICK)) {


								// 	// 	if ( !hasRoomBelow(i, j, k, m) ) { //hasTerrainBelow(i,j,k,m,false) ) {
								// 	// 		connectNodes(
								// 	// 			i,
								// 	// 			j,
								// 	// 			k - 1,
								// 	// 			i + dirModX[m],
								// 	// 			j + dirModY[m],
								// 	// 			k + dirModZ[m] - 1,

								// 	// 			E_CT_ROOM_BRICK
								// 	// 		);
								// 	// 	}


								// 	// }
								
									
								// 	if (
								// 		(ctClasses[conType] == E_CTC_ROAD)
								// 		 || (ctClasses[conType] == E_CTC_ROOM)
								// 	) {


										

								// 		if ( !hasRoomBelow(i, j, k, m) ) { //hasTerrainBelow(i,j,k,m,false) ) {
								// 			connectNodes(
								// 				i,
								// 				j,
								// 				k - 1,
								// 				i + dirModX[m],
								// 				j + dirModY[m],
								// 				k + dirModZ[m] - 1,

								// 				E_CT_FOUNDATION,
								// 				-1,
								// 				buildingData[curInd].con[m].heightDelta,
								// 				0,
								// 				singleton->wallRadInMeters - 1.0f
								// 			);
								// 		}


								// 	}
								


								// 	break;

								case E_BG_WING_TIPS:
									if (m < 4) {


										


										testInd = getMapNodeIndex(i, j, 0);
										testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);
										testInd3 = getMapNodeIndex(i - dirModX[m], j - dirModY[m], 0);

										tempf = 1.0f;
										foundA = false;
										foundB = false;

										if (
											(testInd > -1) && (testInd2 > -1) && (testInd3 > -1)
										) {

											curBT = mapData[testInd].connectionProps[m];
											curBT2 = mapData[testInd2].connectionProps[m];
											curBT3 = mapData[testInd3].connectionProps[m];
											
											
											
											
											// if ( (curBT == E_CT_WING) && (curBT2 == E_CT_ROAD) ) {
											// 	tempf = 0.75f;
											// }
											// if ( (curBT == E_CT_ROAD) && (curBT2 == E_CT_WING) ) {
											// 	tempf = 1.25f;
											// }
											
											if ( (curBT == E_CT_WING) && (curBT2 == E_CT_ROAD) ) {
												foundB = true;
											}
											if ( (curBT == E_CT_ROAD) && (curBT2 == E_CT_WING) ) {
												foundB = true;
											}
											
											if ( (curBT == E_CT_WING) && (curBT3 == E_CT_ROAD) ) {
												foundA = true;
											}
											if ( (curBT == E_CT_ROAD) && (curBT3 == E_CT_WING) ) {
												foundA = true;
											}
											
											
											if (foundA || foundB) {
												if (isBuilding[conType]) {
													//tempf = 0.75f;
												}
												else {//if (isRoad[conType]) {
													//tempf = 1.25f;
												}
											}
											
											
											// if (tempf != 1.0f) {
											// 	foundA = (touchesPlanarClass(i, j, k, ctClasses[conType], 0) == 1);
											// 	foundB = (touchesPlanarClass(i + dirModX[m], j + dirModY[m], k, ctClasses[conType], 0) == 1);
											// }
											
										}
										
										
										for (q = 0; q < MAX_NODE_VALS; q++) {
											
											if (q != layerHash[E_CT_FOUNDATION]) {
												applyWingValues(
													i,
													j,
													k,
													i + dirModX[m],
													j + dirModY[m],
													k + dirModZ[m],
													q,
													foundA,
													foundB,
													tempf
													
												);
											}
											
											
										}
										

										
									}
									break;
								
								case E_BG_DOORS:
								
								
									if (m < 4) {
										
										
										isWingBeg = (buildingData[curInd].con[m].nodeFlags & BC_FLAG_WING_BEG)>0;
										isWingEnd = (buildingData[curInd].con[m].nodeFlags & BC_FLAG_WING_END)>0;
										
										//if ( (m%2) == 0 ) {}
										
										
										
										
										if (
											(ctClasses[conType] == E_CTC_ROOM) &&
											(isWingEnd)
										) {
											
											curBT = E_CT_WINDOWFRAME;
											
											testInd = getNodeIndex(i + dirModX[m], j + dirModY[m], k, 0);
											if (testInd > -1) {
												if (
													ctClasses[buildingData[testInd].con[m].conType] == E_CTC_ROAD	
												) {
													curBT = E_CT_DOORWAY;
												}
											}
											
											
											if ( (m%2) == 0 ) {
												curDir = 1;
											}
											else {
												curDir = -1;
											}
											
											connectNodes(
												i,
												j,
												k,
												i + dirModX[m],
												j + dirModY[m],
												k + dirModZ[m],
												curBT,
												-1,
												0,
												curDir

											);
											
											
											
											if ( (curDir==1) ) { // 
												
												if (curBT == E_CT_DOORWAY) {
													
												}
												else {
													nodeFlags |= BC_FLAG_INSIDE;
												}
												
												/*
												void connectNodes(
													int _x1,
													int _y1,
													int _z1,
													int _x2,
													int _y2,
													int _z2,
													
													int ct,
													int id = -1,
													
													int _heightDelta = 0,
													int _direction = 0,
													
													float _wallRadInMeters = -1.0f,
													unsigned int _nodeFlags = 0
												)
												*/
												
												connectNodes(
													i,
													j,
													k,
													i + dirModX[m],
													j + dirModY[m],
													k + dirModZ[m],
													
													E_CT_LANTERN,
													-1,
													
													0,
													curDir,
													
													-1.0f,
													nodeFlags

												);
											}
											
											
											
										}
										
										
										
										
										
										
										
										
										
										if (conType <= E_CT_CONNECTED) {
											
											doProc = true;
											
											for (q = 0; q < 4; q++) {
												if (
													
													(
														( (q%2) == 1 ) &&
														( (buildingData[curInd].con[q].nodeFlags&BC_FLAG_WING_BEG) > 0)
													)
												) {
													doProc = false;
												}
											}
											
											
											if (doProc) {
												if (touchesPlanarClass(i, j, k, E_CTC_ROOM, 0) > 0) {
													
													if ( (m%2) == 0 ) {
														curDir = 1;
													}
													else {
														curDir = -1;
													}
													
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],
														E_CT_WINDOWFRAME,
														-1,
														0,
														curDir

													);
													
													if (curDir == 1) {
														nodeFlags |= BC_FLAG_INSIDE;
														connectNodes(
															i,
															j,
															k,
															i + dirModX[m],
															j + dirModY[m],
															k + dirModZ[m],
															
															E_CT_LANTERN,
															-1,
															
															0,
															curDir,
															
															-1.0f,
															nodeFlags

														);
													}
													
													
												}
											}
											
											
											
											
											
										}
										
									}
									
									break;
									
									
									
									
								case E_BG_FILL_TERRAIN:
									if (terData[curInd] == 0) {

										testInd = getNodeIndex(i, j, k + 1, 0);

										if (testInd > -1) {
											testVal = terData[testInd];
											if (touchesBaseOnLevel(i, j, k+1, 2) || (testVal != 0)) {
												uiSimp = 255;
												terData[curInd] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;
											}
										}
										
									}
									break;
									
								}

							}
						}
					}
				}
			}
		}
		
		
		
		
		if (singleton->cavesOn) {
			makeMazeUG();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		int minRad = -1;
		int minRadZ = -1;
		// if (pixelsPerMeter <= 32) {
		// 	minRad = -2;
		// }
		// if (pixelsPerMeter <= 64) {
		// 	minRadZ = -2;
		// }
		
		
		bool nearAir = false;
		
		for (k = 0; k < terDataBufPitchZ; k++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				for (i = 0; i < terDataBufPitchXY; i++) {

					curInd = getNodeIndex(i, j, k, 0);

					

					if (curInd > -1) {
						nearAir = false;
						
						
						
						for (ko = minRadZ; ko <= 1; ko++) {
							for (jo = minRad; jo <= 1; jo++) {
								for (io = minRad; io <= 1; io++) {
									testInd = getNodeIndex(i + io, j + jo, k + ko, 0);

									if (testInd > -1) {
										if (terData[testInd] == 0) {
											buildingData[curInd].nearAir = true;
											nearAir = true;
										}
										else {
											buildingData[curInd].nearTerrain = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}



		// geometry generation
		
		lotX = blockSizeInPixels * offsetInBlocks.getIX();
		lotY = blockSizeInPixels * offsetInBlocks.getIY();
		lotZ = 0;

		for (k = 0; k <= terDataBufPitchZ; k++) {

			for (i = 0; i < terDataBufPitchXY; i++) {

				for (j = 0; j < terDataBufPitchXY; j++) {
					
					

					curInd = getNodeIndex(i, j, k, terDataBufAmount); //terDataBufAmount

					

					if (curInd > -1) {
						for (q = 0; q < TOT_NODE_VALS; q += 2) {

							m = q % MAX_NODE_DIRS;

							curDir = m / 2;

							conType = buildingData[curInd].con[q].conType;

							if (conType != E_CT_NULL) {

								
								

								xmod1 = 0.0f;
								ymod1 = 0.0f;
								zmod1 = 0.0f;
								xmod2 = dirModX[m];
								ymod2 = dirModY[m];
								zmod2 = buildingData[curInd].con[q].heightDelta;

								if (conType == E_CT_FOUNDATION) {
									zmod1 -= 1.0f;
									zmod2 -= 1.0f;
									
									testInd = getMapNodeIndex(i, j, 0);
									testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);
									
									if ( (testInd > -1) && (testInd2 > -1) ) {
										if (
											mapData[testInd].adjustedHeight == mapData[testInd2].adjustedHeight
										) {
											zmod2 += 1.0;
										}
									}
									
									
								}
								
								
								
								isInside = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_INSIDE) > 0;
								isWingBeg = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_WING_BEG) > 0;
								isWingEnd = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_WING_END) > 0;
								wingMult = buildingData[curInd].con[q].wingMult;
								newWingMult = (wingMult - 1.0f);
								nDir = buildingData[curInd].con[q].direction;
								
								
								
								// todo: fix this!
								wallRadInMeters = buildingData[curInd].con[q].wallRadInMeters;
								flushRadInMeters = wallRadInMeters;
								for (n = 0; n < 4; n++) {
									
									if (
										ctClasses[buildingData[curInd].con[ n ].conType] == E_CTC_ROOM
									) {
										flushRadInMeters = max(
											flushRadInMeters,
											buildingData[curInd].con[ n ].wallRadInMeters
										);
									}
									
									
								}
									
								
								
								
								for (n = 0; n < 2; n++) {
									if (n == 0) {
										
									}
									else {
										
										
										
										if (curDir == E_DIR_X) {
											if (isWingBeg) {
												xmod1 -= newWingMult;
											}
											if (isWingEnd) {
												xmod2 += newWingMult;
											}
										}
										if (curDir == E_DIR_Y) {
											if (isWingBeg) {
												ymod1 -= newWingMult;
											}
											if (isWingEnd) {
												ymod2 += newWingMult;
											}
										}
										
										
										if (
											(conType == E_CT_DOORWAY) ||
											(conType == E_CT_WINDOWFRAME) ||
											(conType == E_CT_LANTERN)
										) {
											
											
											if (isWingBeg||isWingEnd) {
												
													if (curDir == E_DIR_X) {
														if (isWingBeg) {
															xmod2 = xmod1;
														}
														if (isWingEnd) {
															xmod1 = xmod2;
														}
														
													}
													if (curDir == E_DIR_Y) {
														if (isWingBeg) {
															ymod2 = ymod1;
														}
														if (isWingEnd) {
															ymod1 = ymod2;
														}
														
													}
													
													if (nDir == 1.0f) {
														tempf = -1.0f;
													}
													else {
														tempf = 1.0f;
													}
													
													if (conType == E_CT_LANTERN) {
														
														if (isInside) {
															tempf *= 2.0f;	
														}
														else {
															tempf *= -2.0f;	
														}
														
														
													}
													
													
													
													xmod1 += tempf*doorThickness*dirModX[m]*0.5f;
													ymod1 += tempf*doorThickness*dirModY[m]*0.5f;
													xmod2 += tempf*doorThickness*dirModX[m]*0.5f;
													ymod2 += tempf*doorThickness*dirModY[m]*0.5f;
													
													
													
													if (conType == E_CT_LANTERN) {
														
															if (isInside) {
																zmod1 += 0.125f;
																zmod2 += 0.125f;
															}
															else {
																xmod1 += lanternOffset*dirModY[m];
																ymod1 += lanternOffset*dirModX[m];
																xmod2 += lanternOffset*dirModY[m];
																ymod2 += lanternOffset*dirModX[m];
															}
														
															
													}
													else {
														xmod1 -= doorThickness*dirModX[m]*0.5f;
														ymod1 -= doorThickness*dirModY[m]*0.5f;
														xmod2 += doorThickness*dirModX[m]*0.5f;
														ymod2 += doorThickness*dirModY[m]*0.5f;
													}
													
													
												}
												else {
													if (nDir == 1.0f) {
														tempf = (flushRadInMeters*pixelsPerMeter)/(fBlockSizeInPixels / fTerDataVisPitchXY);
													}
													else {
														tempf = 1.0f-(flushRadInMeters*pixelsPerMeter)/(fBlockSizeInPixels / fTerDataVisPitchXY);
													}
													
													xmod1 = tempf*dirModX[m];
													ymod1 = tempf*dirModY[m];
													xmod2 = xmod1;
													ymod2 = ymod1;
													
													if (conType == E_CT_LANTERN) {
														if (nDir == 1.0f) {
															tempf = -1.0f;
														}
														else {
															tempf = 1.0f;
														}
														
														if (isInside) {
															tempf *= 2.0f;	
														}
														else {
															tempf *= -2.0f;	
														}
														
														xmod1 += tempf*doorThickness*dirModX[m]*0.5f;
														ymod1 += tempf*doorThickness*dirModY[m]*0.5f;
														xmod2 += tempf*doorThickness*dirModX[m]*0.5f;
														ymod2 += tempf*doorThickness*dirModY[m]*0.5f;
														
														
													}
													else {
														if (nDir == 1.0f) {
															xmod1 -= doorThickness*dirModX[m];
															ymod1 -= doorThickness*dirModY[m];
														}
														else {
															xmod2 += doorThickness*dirModX[m];
															ymod2 += doorThickness*dirModY[m];
														}
													}
													
													
												}
											
										}
										
										
									}
										
									x1 = lotX + ( ((float)(i - terDataBufAmount) + xmod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									y1 = lotY + ( ((float)(j - terDataBufAmount) + ymod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									z1 = lotZ + ( ((float)(k - terDataBufAmount) + zmod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ;

									x2 = lotX + ( ((float)(i - terDataBufAmount) + xmod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									y2 = lotY + ( ((float)(j - terDataBufAmount) + ymod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									z2 = lotZ + ( ((float)(k - terDataBufAmount) + zmod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ;
									
									if (n == 0) {
										centerPoint.setFXYZ(
											(x1+x2)*0.5f,
											(y1+y2)*0.5f,
											(z1+z2)*0.5f
										);
									}
									
									
								}
								

							
								

								p1.setFXYZ(x1, y1, z1);
								p2.setFXYZ(x2, y2, z2);


								


								switch (conType) {
								case E_CT_NULL:
								case E_CT_CONNECTED:
								case E_CT_ROAD:
									nMax = 0;
									break;
								case E_CT_DOORWAY:
								case E_CT_WINDOWFRAME:
									nMax = 3;
									break;
								default:
									nMax = 1;
									break;

								}


								// todo: fix this
								if (ctClasses[conType] == E_CTC_ROOM) {
									roofHeightInMeters = singleton->wallRadInMeters;
								}
								else {
									roofHeightInMeters = wallRadInMeters;
									
								}



								

								for (n = 0; n < nMax; n++) {
									
									curBT = conType;
									rad.setFXYZ(
										wallRadInMeters * pixelsPerMeter,
										wallRadInMeters * pixelsPerMeter,
										(floorHeightInMeters * 0.5f + roofHeightInMeters)*pixelsPerMeter
									);
									cornerRad.setFXYZ(
										wallRadInMeters * pixelsPerMeter,
										wallRadInMeters * pixelsPerMeter,
										roofHeightInMeters * pixelsPerMeter
									);
									powerVals.setFXYZ(2.0f, 1.0f, 0.0f);
									powerVals2.setFXYZ(2.0f, 1.0f, 0.0f);
									
									
									switch (buildingData[curInd].con[q].heightDelta) {
										case -1:
											powerVals.setFZ(1.0f);
											powerVals2.setFZ(0.0f);
										break;
										
										case 0:
											powerVals.setFZ(0.0f);
											powerVals2.setFZ(0.0f);
											
										break;
										
										case 1:
											powerVals.setFZ(0.0f);
											powerVals2.setFZ(1.0f);
											
										break;
										default:
											cout << "invalid height delta of " << buildingData[curInd].con[q].heightDelta << "\n";
										break;
									}
									
									
									
									
									thickVals.setFXYZ(0.0f, floorHeightInMeters, 0.0f);
									baseOffset = 0.0f;
									curAlign = E_ALIGN_MIDDLE;
									minRot = 0;
									maxRot = 0;
									anchorPoint.setFXYZRef(&centerPoint);

									switch (conType) {
										
										case E_CT_NULL:
												
											break;
										
										
										case E_CT_TREE:
											baseOffset = 0.0f;
											matParams.setFXYZ(E_MAT_PARAM_TREE, 0.0, 0.0f);

											visInsetFromMin.setFXYZ(0.0f,0.0f,0.0f);
											visInsetFromMax.setFXYZ(0.0f,0.0f,0.0f);
											
											tempVec4.setFXYZRef(&p1);
											tempVec4.addXYZ(0.0f,0.0f,2.0f*pixelsPerMeter);

											tempVec.setIXYZ(i,j,k);
											tempVec.multXYZ(102.33,305.44,609.121);
											tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
											tempInt = iGetRandSeeded(&tempVec,&tempVec2,0,E_PT_LENGTH/2 - 1);
											
											
											
											singleton->gamePlants[tempInt]->init(
												singleton,
												&(GamePlant::allPlantRules[tempInt*2+1]),
												&(GamePlant::allPlantRules[tempInt*2]),
												&origin
											);
											matParams.setFY(tempInt*2+1);
											addPlantNodes(singleton->gamePlants[tempInt]->rootsNode, &tempVec4, 1.0f);
											matParams.setFY(tempInt*2);
											addPlantNodes(singleton->gamePlants[tempInt]->trunkNode, &tempVec4, 1.0f);
											
											
											
											// if (tempf > 0.66) {
											// 	bareTree.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_BARE_OAK_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_BARE_OAK_TRUNK]),
											// 		&origin
											// 	);
											// 	matParams.setFY()
											// 	addPlantNodes(bareTree.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(bareTree.trunkNode, &tempVec4, 1.0f);
											// }
											// else if (tempf > 0.33) {
											// 	oakTree2.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_OAK2_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_OAK2_TRUNK]),
											// 		&origin
											// 	);

											// 	addPlantNodes(oakTree2.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(oakTree2.trunkNode, &tempVec4, 1.0f);
											// }
											// else {
											// 	oakTree.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_OAK_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_OAK_TRUNK]),
											// 		&origin
											// 	);

											// 	addPlantNodes(oakTree.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(oakTree.trunkNode, &tempVec4, 1.0f);
											// }

											
											
											goto SKIP_ADD_GEOM;
											
										break;
										
										
										case E_CT_LANTERN:
										

											matParams.setFXYZ(E_MAT_PARAM_LANTERN, 0.0, 0.0f);

											curAlign = E_ALIGN_MIDDLE;

											// floorHeight = 0.5f;
											// roofHeight = 0.25f;
											// baseOffset = 0.0f;
											rad.setFXYZ(
												(0.25f)*pixelsPerMeter,
												(0.25f)*pixelsPerMeter,
												(0.5f)*pixelsPerMeter
											);
											cornerRad.setFXYZ(
												(0.0625f)*pixelsPerMeter,
												(0.0625f)*pixelsPerMeter,
												(0.25f)*pixelsPerMeter
											);
											thickVals.setFX(0.25f*pixelsPerMeter);											

											visInsetFromMin.setFXYZ(0.0f,0.0f,cornerRad.getFZ() - 0.0625*pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f,0.0f,0.0f);

											powerVals.setFXYZ(2.0f, 1.0f, 0.0f);
											powerVals2.setFXYZRef(&powerVals);

											curBT = E_CT_LANTERN;




											
										break;
										
										case E_CT_DOORWAY:
										case E_CT_WINDOWFRAME:
										
											if (conType == E_CT_DOORWAY) {
												tempf = 0.0f;
											}
											else {
												tempf = 1.0f;
											}
										
											if (n == 0) {
												matParams.setFXYZ(E_MAT_PARAM_DOORWAY, 0.0f, tempf);
												doorMod = 0.0f;

											}
											else {
												matParams.setFXYZ(E_MAT_PARAM_DOOR, 0.0f, tempf);
												doorMod = 0.25f;
											}
											
											curAlign = E_ALIGN_BOTTOM;
											baseOffset = -(rad.getFZ() - (cornerRad.getFZ()+(0.25+doorMod)*pixelsPerMeter) ) + tempf*2.0f*pixelsPerMeter;
											

											
											floorHeight = 2.0f-doorMod;
											roofHeight = 1.5f-doorMod;
											
											rad.setFXYZ(
												(1.5f - doorMod)*pixelsPerMeter,
												(1.5f - doorMod)*pixelsPerMeter,
												(floorHeight*0.5f + roofHeight + tempf*0.5f)*pixelsPerMeter
											);
											cornerRad.setFXYZ(
												(1.5f - doorMod)*pixelsPerMeter,
												(1.5f - doorMod)*pixelsPerMeter,
												roofHeight*pixelsPerMeter
											);
											thickVals.setFX(0.25f*pixelsPerMeter);	
										
											doorInset = doorMod*pixelsPerMeter*1.25f;
											
											
											anchorPoint.copyFrom(&p1);
											anchorPoint.addXYZRef(&p2);
											anchorPoint.multXYZ(0.5f);
											
											hingeDis = p1.distance(&p2)*0.5f;
											
											switch (n) {
												case 0:
												
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOORWAY;
													}
													else {
														curBT = E_CT_WINDOWFRAME;
													}
												
													cr1 = 0.0f;
													cr2 = 0.0f;
												break;
												
												case 1:
												
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOOR;
													}
													else {
														curBT = E_CT_WINDOW;
													}
												
													
													cr1 = 0.0f;
													cr2 = 1.0f;
													
													if (curDir == E_DIR_Y) {
														anchorPoint.addXYZ(-(rad.getFX()+hingeDis),0.0f,0.0f);
													}
													else {
														anchorPoint.addXYZ(0.0f,-(rad.getFY()+hingeDis),0.0f);
													}
													
													
													if (
														((curDir == E_DIR_Y)&&(nDir==1)) ||
														((curDir == E_DIR_X)&&(nDir==-1))
													) { //(m == 1) || (m == 2) ) {
														minRot = 0;
														maxRot = 1;
													}
													else {
														minRot = -1;
														maxRot = 0;
													}
													
												
													
												break;
												
												case 2:
													
													
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOOR;
													}
													else {
														curBT = E_CT_WINDOW;
													}
													
													cr1 = 1.0f;
													cr2 = 0.0f;
													
													if (curDir == E_DIR_Y) {
														anchorPoint.addXYZ(rad.getFX()+hingeDis,0.0f,0.0f);
													}
													else {
														anchorPoint.addXYZ(0.0f,rad.getFY()+hingeDis,0.0f);
													}
													

													if (
														((curDir == E_DIR_X)&&(nDir==1)) ||
														((curDir == E_DIR_Y)&&(nDir==-1))
													) { //(m == 0) || (m == 3) ) {
														minRot = 0;
														maxRot = 1;
													}
													else {
														minRot = -1;
														maxRot = 0;
													}
													
													
												break;
											}
											
											if (curDir == E_DIR_X) {
												visInsetFromMin.setFXYZ(cornerRad.getFX()+doorInset, cr1*rad.getFY(), cornerRad.getFZ());
												visInsetFromMax.setFXYZ(cornerRad.getFX()+doorInset, cr2*rad.getFY(), 0.0f);
											}
											else {
												visInsetFromMin.setFXYZ(cr1*rad.getFX(), cornerRad.getFY()+doorInset, cornerRad.getFZ());
												visInsetFromMax.setFXYZ(cr2*rad.getFX(), cornerRad.getFY()+doorInset, 0.0f);
											}

											
											
											powerVals.setFX(2.0f);
											powerVals.setFY(2.0f);
											powerVals2.setFX(2.0f);
											powerVals2.setFY(2.0f);
											
											
										
											
											
											
										
											break;
											
										case E_CT_FOUNDATION:

											//testInd = getMapNodeIndex(i, j, 0);
											//testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);

											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											
											
											baseOffset = 0.0f;// -(floorHeightInMeters)*pixelsPerMeter;
											rad.addXYZ(
												0.0f,
												0.0f,
												(floorHeightInMeters+1.0f)*pixelsPerMeter
											);

											
											if (
												singleton->getHeightAtPixelPos(p1.getFX(), p1.getFY()) <=
												singleton->getSLInPixels()  + 2.0f * pixelsPerMeter
											) {
												rad.addXYZ(
													0.0f,
													0.0f,
													(2.0f)*pixelsPerMeter
												);
												matParams.setFXYZ(E_MAT_PARAM_FOUNDATION, E_MAT_SUBPARAM_DOCK, 0.0f);
											}
											else {
												matParams.setFXYZ(E_MAT_PARAM_FOUNDATION, E_MAT_SUBPARAM_BRICK, 0.0f);
											}

											

											

											break;
										case E_CT_ROOM_BRICK:
											matParams.setFXYZ(E_MAT_PARAM_BUILDING, E_MAT_SUBPARAM_BRICK, 0.0f);
											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											break;
										case E_CT_ROOM_TUDOR:

											//rad.addXYZ(-0.5f*pixelsPerMeter,-0.5f*pixelsPerMeter,0.0f);
											//cornerRad.addXYZ(-0.5f*pixelsPerMeter);

											matParams.setFXYZ(E_MAT_PARAM_BUILDING, E_MAT_SUBPARAM_TUDOR, 0.0f);
											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											break;

										// case E_CT_WALKWAY:

										// 	matParams.setFXYZ(E_MAT_PARAM_WALKWAY, E_MAT_SUBPARAM_BRICK_ARCH, 0.0f);
										// 	visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 	visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);

										// 	break;

										// case E_CT_WALKWAY_TOP:
										// 	matParams.setFXYZ(E_MAT_PARAM_WALKWAY_TOP, E_MAT_SUBPARAM_BRICK_ARCH, 0.0f);
										// 	visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 	visInsetFromMax.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + (floorHeightInMeters * 0.75))*pixelsPerMeter);

										// 	break;

										case E_CT_ROOF:
											baseOffset = -floorHeightInMeters * pixelsPerMeter;
											matParams.setFXYZ(E_MAT_PARAM_ROOF, E_MAT_SUBPARAM_TUDOR, buildingData[curInd].id);

											if (curDir == E_DIR_Z) {
												visInsetFromMin.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + floorHeightInMeters * 2.0f)*pixelsPerMeter);
											} else {
												visInsetFromMin.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + floorHeightInMeters)*pixelsPerMeter);
											}
											visInsetFromMax.setFXYZ(0.0f, 0.0f, 0.0f);
											break;

										// case E_CT_STAIRS:

										// 	switch (curDir) {
										// 	case E_DIR_X:
										// 		rad.multXYZ(0.5f, 0.5f, 1.0f);
										// 		cornerRad.multXYZ(0.5f, 0.5f, 1.0f);

										// 		if ((k % 2) == 0) {
										// 			visInsetFromMin.setFXYZ(cornerRad.getFX(), rad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(cornerRad.getFX(), 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 		} else {
										// 			visInsetFromMin.setFXYZ(cornerRad.getFX(), 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(cornerRad.getFX(), rad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		}
										// 		break;

										// 	case E_DIR_Y:
										// 		rad.multXYZ(0.5f, 0.5f, 1.0f);
										// 		cornerRad.multXYZ(0.5f, 0.5f, 1.0f);

										// 		if ((k % 2) == 0) {
										// 			visInsetFromMin.setFXYZ(rad.getFX(), cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(0.0f, cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		} else {
										// 			visInsetFromMin.setFXYZ(0.0f, cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(rad.getFX(), cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		}

										// 		break;

										// 	case E_DIR_Z:
										// 		rad.multXYZ(0.75f, 0.75f, 1.0f);
										// 		cornerRad.multXYZ(0.75f, 0.75f, 1.0f);
										// 		visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 		visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);

										// 		break;
										// 	}

										// 	matParams.setFXYZ(E_MAT_PARAM_STAIRS, E_MAT_SUBPARAM_NONE, (float)(k % 2));
										// 	baseOffset = 1.0f * pixelsPerMeter;

										// 	break;

										
									}

									if (curDir != E_DIR_Z) {
										

										switch (conType) {
										case E_CT_ROAD:
										case E_CT_ROOF:
										case E_CT_ROOM_TUDOR:
										case E_CT_ROOM_BRICK:

											// }

											if (curDir == E_DIR_X) {
												if (isWingBeg) {
													visInsetFromMin.setFX(cornerRad.getFX());
												}
												if (isWingEnd) {
													visInsetFromMax.setFX(cornerRad.getFX());
												}
											}
											if (curDir == E_DIR_Y) {
												if (isWingBeg) {
													visInsetFromMin.setFY(cornerRad.getFY());
												}
												if (isWingEnd) {
													visInsetFromMax.setFY(cornerRad.getFY());
												}
											}


											break;
										}
									}


									addNewGeom(
										curBT,
										curAlign,
										baseOffset,
										&p1,
										&p2,
										&rad,
										&cornerRad,
										&visInsetFromMin,
										&visInsetFromMax,
										&powerVals,
										&powerVals2,
										&thickVals,
										&matParams,
										&centerPoint,
										&anchorPoint,
										minRot,
										maxRot
									);
									
SKIP_ADD_GEOM:
									
									;

								}

							}
						}


					}


				}
			}
		}



	}
	
	
	
	
	
	int getNodeIndexClamped(int _x, int _y, int _z) {

	
			int x = clamp(_x,0,terDataBufPitchXY-1);
			int y = clamp(_y,0,terDataBufPitchXY-1);
			int z = clamp(_z,0,terDataBufPitchZ-1);
		
			return x + y * terDataBufPitchXY + z * terDataBufPitchXY * terDataBufPitchXY;
		
	}

	int getNodeIndex(int x, int y, int z, int bufAmount) {

		if (
			(x < bufAmount) ||
			(y < bufAmount) ||
			(z < bufAmount) ||
			(x >= terDataBufPitchXY - bufAmount) ||
			(y >= terDataBufPitchXY - bufAmount) ||
			(z >= terDataBufPitchZ - bufAmount)
		) {
			return -1;
		} else {
			return x + y * terDataBufPitchXY + z * terDataBufPitchXY * terDataBufPitchXY;
		}
	}

	int touchesPlanarBN(int x, int y, int z, int buildingType, int bufAmount) {
		int i;
		int tot = 0;
		int ind;

		ind = getNodeIndex(x, y, z, bufAmount);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (buildingData[ind].con[i].conType == buildingType) {
					tot++;
				}
			}
		}

		return tot;
	}
	int touchesPlanarClass(int x, int y, int z, int classType, int bufAmount) {
		int i;
		int tot = 0;
		int ind;

		ind = getNodeIndex(x, y, z, bufAmount);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (ctClasses[buildingData[ind].con[i].conType] == classType) {
					tot++;
				}
			}
		}

		return tot;
	}
	
	bool isLCorner(int x, int y, int z, int classType, bool includeSingle) {
		int i;
		int tot = 0;
		int ind;
		

		ind = getNodeIndex(x, y, z, 0);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if ( ctClasses[buildingData[ind].con[i].conType] == classType) {
					tot++;
				}
			}
			
			if ((tot == 1)&&includeSingle) {
				return true;
			}
			
			if (tot == 2) {
				tot = 0;
				for (i = 0; i < 2; i++) {
					if (ctClasses[buildingData[ind].con[i].conType] == classType) {
						tot++;
					}
				}
				
				if (tot == 1) {
					return true;
				}
				
			}
			
		}
		
		

		return false;
	}
	

	void applyWingValues(
		int _x1, int _y1, int _z1,
		int _x2, int _y2, int _z2,
		int cnum,
		bool isWingBeg,
		bool isWingEnd,
		float multiplier
	) {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-
		// 4: z+
		// 5: z-

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;
		int z1 = _z1;
		int z2 = _z2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}
		if (z1 > z2) {
			std::swap(z1, z2);
		}

		int baseDir = 0;

		int ind1 = getNodeIndex(x1, y1, z1, 0);
		int ind2 = getNodeIndex(x2, y2, z2, 0);
		
		int finalInd1;
		int finalInd2;
		
		uint tempFlags;

		if ((ind1 < 0) || (ind2 < 0)) {
			// invalid connection
		} else {

			if ((x1 == x2) && (y1 == y2)) {
				// up/down connection
				baseDir = 4;
			} else {
				if (x1 == x2) {
					// north/south connection
					baseDir = 2;
				}
				if (y1 == y2) {
					// east/west connection
					baseDir = 0;
				}
			}

			finalInd1 = baseDir + cnum * MAX_NODE_DIRS;
			finalInd2 = baseDir + 1 + cnum * MAX_NODE_DIRS;
			
			
			
			// WAS DOING: MAKE SURE TO SET FLAGS EXPLICITLY, NO OR "|" operator
			
			
			tempFlags = 0;
			if (isWingBeg) {
				tempFlags |= BC_FLAG_WING_BEG;
			}
			if (isWingEnd) {
				tempFlags |= BC_FLAG_WING_END;
			}
			
			buildingData[ind1].con[finalInd1].nodeFlags &= ~(BC_FLAG_WING_BEG|BC_FLAG_WING_END);
			buildingData[ind2].con[finalInd2].nodeFlags &= ~(BC_FLAG_WING_BEG|BC_FLAG_WING_END);
			
			buildingData[ind1].con[finalInd1].nodeFlags |= tempFlags;
			buildingData[ind1].con[finalInd1].wingMult = multiplier;

			tempFlags = 0;
			if (isWingEnd) {
				tempFlags |= BC_FLAG_WING_BEG;
			}
			if (isWingBeg) {
				tempFlags |= BC_FLAG_WING_END;
			}

			buildingData[ind2].con[finalInd2].nodeFlags |= tempFlags;
			//buildingData[ind2].con[finalInd2].wingMult = 2.0f-multiplier;
			
			

		}
	}
	
	
	void addPlantNodes(GamePlantNode* curPlantNode, FIVector4* orig, float scale ) {
		int i;

		float begThickness;
		float endThickness;

		if (curPlantNode->parent == NULL) {

		}
		else {

			if (curPlantNode->parent->parent == NULL) {
				tempVec.setFXYZ(0.0f,0.0f,0.0f); //Ref(&(curPlantNode->parent->begPoint));

				begThickness = curPlantNode->midThickness;
				endThickness = curPlantNode->midThickness;

			}
			else {
				tempVec.setFXYZRef(&(curPlantNode->parent->begPoint));
				tempVec.addXYZRef(&(curPlantNode->parent->endPoint));
				tempVec.multXYZ(0.5f);

				begThickness = curPlantNode->parent->midThickness;
				endThickness = curPlantNode->midThickness;
			}


			// if (curPlantNode->numChildren == 0) {
			// 	endThickness = 0.5f*singleton->pixelsPerMeter;
			// }

			
			
			tempVec2.setFXYZRef(&(curPlantNode->begPoint));
			tempVec2.addXYZRef(&(curPlantNode->endPoint));
			tempVec2.multXYZ(0.5f);
			
			tempVec3.setFXYZRef(&(curPlantNode->begPoint));

			tempVec.multXYZ(scale);
			tempVec2.multXYZ(scale);
			tempVec3.multXYZ(scale);

			tempVec.addXYZRef(orig);
			tempVec2.addXYZRef(orig);
			tempVec3.addXYZRef(orig);

			gameGeom.push_back(new GameGeom());
			gameGeom.back()->initTree(
				
				E_CT_TREE,
				localGeomCounter,
				singleton->geomCounter,
								
				&tempVec,
				&tempVec2,
				&tempVec3,

				begThickness*scale,//curPlantNode->begThickness,
				endThickness*scale,//curPlantNode->endThickness,	
				curPlantNode->sphereRad*scale,			
										
				&matParams
			);
			singleton->geomCounter++;
			localGeomCounter++;
		}

		

		for (i = 0; i < curPlantNode->numChildren; i++) {
			addPlantNodes( &(curPlantNode->children[i]), orig, scale);
		}
	}
	
	void addNewGeom(
		int _curBT,
		int _curAlign,
		float _baseOffset,
		FIVector4* _p1,
		FIVector4* _p2,
		FIVector4* _rad,
		FIVector4* _cornerRad,
		FIVector4* _visInsetFromMin,
		FIVector4* _visInsetFromMax,
		FIVector4* _powerVals,
		FIVector4* _powerVals2,
		FIVector4* _thickVals,
		FIVector4* _matParams,
		FIVector4* _centerPoint,
		FIVector4* _anchorPoint,
		int _minRot,
		int _maxRot
		
	) {
		
		
		
		
		
		gameGeom.push_back(new GameGeom());
		gameGeom.back()->initBounds(
			_curBT,
			localGeomCounter,
			singleton->geomCounter,
			_curAlign,
			_baseOffset,
			_p1,
			_p2,
			_rad,
			_cornerRad,
			_visInsetFromMin,
			_visInsetFromMax,
			_powerVals,
			_powerVals2,
			_thickVals,
			_matParams,
			_centerPoint,
			_anchorPoint,
			_minRot,
			_maxRot
		);
		
		if (_curBT == E_CT_LANTERN) {
			lightVec.setFXYZ(1.0f,0.5f,0.1f);
			gameLights.push_back(new GameLight());
			gameLights.back()->init(
				lightCounter,
				singleton->lightCounter,
				_p1,
				&lightVec
			);
			singleton->lightCounter++;
			lightCounter++;
			gameGeom.back()->light = gameLights.back();
		}
		
		
		
		singleton->geomCounter++;
		localGeomCounter++;
	}
	

	void connectNodes(
		int _x1,
		int _y1,
		int _z1,
		int _x2,
		int _y2,
		int _z2,
		
		int ct,
		int id = -1,
		int _heightDelta = 0,
		int _direction = 0,
		float _wallRadInMeters = -1.0f,
		unsigned int _nodeFlags = 0
	) {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-
		// 4: z+
		// 5: z-

		float wallRad = _wallRadInMeters;
		if (wallRad == -1.0f) {
			wallRad = singleton->wallRadInMeters;
		}

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;
		int z1 = _z1;
		int z2 = _z2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}
		if (z1 > z2) {
			std::swap(z1, z2);
		}

		int ind1 = getNodeIndex(x1, y1, z1, 0);
		int ind2 = getNodeIndex(x2, y2, z2+_heightDelta, 0);
		int baseDir = 0;
		
		int resInd1;
		int resInd2;
		
		int cnum = layerHash[ct];

		if ((ind1 < 0) || (ind2 < 0)) {
			// invalid connection
		} else {

			if (id >= 0) {
				buildingData[ind1].id = id;
				buildingData[ind2].id = id;
			}


			if ((x1 == x2) && (y1 == y2)) {
				// up/down connection
				baseDir = 4;
			} else {
				if (x1 == x2) {
					// north/south connection
					baseDir = 2;
				}
				if (y1 == y2) {
					// east/west connection
					baseDir = 0;
				}
			}

			

			resInd1 = baseDir + cnum * MAX_NODE_DIRS;
			resInd2 = baseDir + 1 + cnum * MAX_NODE_DIRS;

			buildingData[ind1].con[resInd1].conType = ct;
			buildingData[ind2].con[resInd2].conType = ct;
			buildingData[ind1].con[resInd1].heightDelta = _heightDelta;
			buildingData[ind2].con[resInd2].heightDelta = -_heightDelta;
			buildingData[ind1].con[resInd1].direction = _direction;
			buildingData[ind2].con[resInd2].direction = -_direction;
			
			buildingData[ind1].con[resInd1].nodeFlags |= _nodeFlags;
			buildingData[ind2].con[resInd2].nodeFlags |= _nodeFlags;
			
			buildingData[ind1].con[resInd1].wallRadInMeters = wallRad;
			buildingData[ind2].con[resInd2].wallRadInMeters = wallRad;
			
			
		}
	}


	int getMapNodeIndex(int x, int y, int bufAmount) {

		if (
			(x < bufAmount) ||
			(y < bufAmount) ||
			(x >= terDataBufPitchXY - bufAmount) ||
			(y >= terDataBufPitchXY - bufAmount)
		) {
			return -1;
		} else {
			return x + y * terDataBufPitchXY;
		}

	}




	int touchesMap(int x, int y, int buildingType, int bufAmount) {
		int i;
		int tot = 0;

		int ind;

		ind = getMapNodeIndex(x, y, bufAmount);
		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (mapData[ind].connectionProps[i] == buildingType) {
					tot++;
				}
			}
		}

		return tot;
	}


	int touchesWithinRadMap(int x, int y, int buildingType, int rad, int bufAmount) {
		int i;
		int j;
		
		int tot = 0;
		int testX;
		int testY;
		

		for (i = -rad; i <= rad; i++) {
			for (j = -rad; j <= rad; j++) {
				testX = x + i;
				testY = y + j;

				tot += touchesMap(testX, testY, buildingType, bufAmount);
			}
		}

		return tot;

	}

	int touches2Map(int x, int y, int buildingType, int bufAmount) {
		int i;
		int tot = 0;
		int testX;
		int testY;

		for (i = 0; i < 4; i++) {

			testX = x + dirModX[i];
			testY = y + dirModY[i];

			tot += touchesMap(testX, testY, buildingType, bufAmount);

		}

		return tot;

	}

	void connectMapNodes(int _x1, int _y1, int _x2, int _y2, int buildingType, int id, int bufAmount) {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;

		int boff = 0;

		int i;

		int ind1;
		int ind2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}

		int n[2];


		n[0] = getMapNodeIndex(x1, y1, bufAmount);
		n[1] = getMapNodeIndex(x2, y2, bufAmount);

		if (
			(n[0] < 0) ||
			(n[1] < 0)
		) {
			
		} else {

			if (id >= 0) {
				mapData[n[0]].id = id;
				mapData[n[1]].id = id;
			}

			if (x1 == x2) { // is vertical
				boff = 2;
			} else {
				boff = 0;
			}

			for (i = 0; i < 2; i++) {
				mapData[n[i]].connectionProps[i + boff] = buildingType;
			}

		}


	}


	int getAdjustedHeightInHolders(int xInHolders, int yInHolders) {

		float holderSizeInPixels = singleton->holderSizeInPixels;

		tempVec.setFXYZ(xInHolders*holderSizeInPixels, yInHolders*holderSizeInPixels, 0.0f);

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		tempVec.addXYZ(0.5f);


		
		int ind = getMapNodeIndex(tempVec.getIX(), tempVec.getIY(), 0);
		int res = 0;
		float fres = 0.0f;

		if (ind > -1) {
			fres = ((float)(mapData[ind].terHeight))/fTerDataVisPitchZ; //adjustedHeight
			
			res = fres*singleton->worldSizeInHolders.getFZ();
			
		} else {
			res = 0;
		}
		
		return res;

	}



	float fIsNearTerrain(
		FIVector4 *worldMinVisInPixels
	) {

		int ind;
		int ind2;
		
		int i;
		int j;
		int k;
		
		tempVec.copyFrom(worldMinVisInPixels);

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		for (i = 0; i <= 1; i++) {
			for (j = 0; j <= 1; j++) {
				for (k = 0; k <= 1; k++) {
					ind = getNodeIndexClamped(
						tempVec.getIX() + i,
						tempVec.getIY() + j,
						tempVec.getIZ() + k
					);
					ind2 = k*4 + j*2 + i;
					if (terData[ind] > 0) {
						trilin[ind2] = 1.0f;
					}
					else {
						trilin[ind2] = 0.0f;
					}
				}
				
			}
		}
		
		// 0 1
		// 2 3
		
		// 4 5
		// 6 7

		float lerpX = tempVec.getFX() - tempVec.getIX();
		float lerpY = tempVec.getFY() - tempVec.getIY();
		float lerpZ = tempVec.getFZ() - tempVec.getIZ();
		float ilerpX = 1.0f - lerpX;
		float ilerpY = 1.0f - lerpY;
		float ilerpZ = 1.0f - lerpZ;
		
		trilin[0] = trilin[0]*ilerpX + trilin[1]*lerpX;
		trilin[2] = trilin[2]*ilerpX + trilin[3]*lerpX;
		trilin[4] = trilin[4]*ilerpX + trilin[5]*lerpX;
		trilin[6] = trilin[6]*ilerpX + trilin[7]*lerpX;
		
		trilin[0] = trilin[0]*ilerpY + trilin[2]*lerpY;
		trilin[4] = trilin[4]*ilerpY + trilin[6]*lerpY;
		
		trilin[0] = trilin[0]*ilerpZ + trilin[4]*lerpZ;

		return trilin[0];
	}



	void refreshHoldersInArea(
		FIVector4 *worldPos
	) {


		int ind;
		int curInd;
		int testInd;
		int i;
		int j;
		int k;
		
		int holderSizeInPixels = singleton->holderSizeInPixels;
	
		float bsih = blockSizeInHolders;
	
		tempVec.copyFrom(worldPos);
		tempVec.intDivXYZ(holderSizeInPixels);
		
		
		doTraceVecND("refreshHoldersInArea", &tempVec);
		
		
		int rad = 2;
		
		for (i = -rad; i <= rad; i++) {
			for (j = -rad; j <= rad; j++) {
				for (k = -rad; k <= rad; k++) {
					
					
					
					gw->getHolderAtCoords(
						tempVec.getIX()+i,
						tempVec.getIY()+j,
						tempVec.getIZ()+k,
						true
					)->refreshChildren(true,true,true);
				}
			}
		}
		


	}


	void modifyTerrain(
		FIVector4 *worldPos,
		bool doSub
	) {

		int ind;
		int curInd;
		int testInd;
		int i;
		int j;
		int k;
		int n;
		
		int io;
		int jo;
		int ko;
		
		uint newValue = 255;
		if (doSub) {
			newValue = 0;
		}
		
		
		tempVec.copyFrom(worldPos);
		

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		//tempVec.addXYZ(0.5f);
		
		
		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		
		float xm = tempVec.getFX() - tempVec.getIX();
		float ym = tempVec.getFY() - tempVec.getIY();
		float zm = tempVec.getFZ() - tempVec.getIZ();
		
		
		if ((xm >= ym) && (xm >= zm)) {
			n = 0;
		}
		if ((ym >= xm) && (ym >= zm)) {
			n = 1;
		}
		if ((zm >= xm) && (zm >= ym)) {
			n = 2;
		}
		
		
		int counterMod = 1;
		
		if (doSub) {
			counterMod = -1;
		}
		
		int counterK = 0;
		while (true) {
			
			
			
			switch(n) {
				case 0:
					i = tempVec.getIX()+counterK*counterMod;
					j = tempVec.getIY();
					k = tempVec.getIZ();
				break;
				case 1:
					i = tempVec.getIX();
					j = tempVec.getIY()+counterK*counterMod;
					k = tempVec.getIZ();
				break;
				case 2:
					i = tempVec.getIX();
					j = tempVec.getIY();
					k = tempVec.getIZ()+counterK*counterMod;
				break;
			}
			
			
			ind = getNodeIndex(i, j, k, 0);
			if (ind > -1) {
				if ( (!doSub) && (terData[ind] == 0) ) {
					// found a place to add
					goto FOUND_ADD_SUB;
				}
				
				if ( (doSub) && (terData[ind] != 0) ) {
					// found a place to sub
					goto FOUND_ADD_SUB;
				}
			}
			else {				
				return;
			}
			
			
			
			counterK++;
		}
		
		
		FOUND_ADD_SUB:
		
		
		
		
		terData[ind] = (newValue << 24) | (newValue << 16) | (newValue << 8) | newValue;

		
		
		
		int rad2 = 3;
		int rad = 2;
		
		
		
		for (i = -rad2; i <= rad2; i++) {
			for (j = -rad2; j <= rad2; j++) {
				for (k = -rad2; k <= rad2; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					if (curInd > -1) {
						buildingData[curInd].nearAir = false;
						buildingData[curInd].nearTerrain = false;
					}
					
				}
			}
		}
		
		for (i = -rad2; i <= rad2; i++) {
			for (j = -rad2; j <= rad2; j++) {
				for (k = -rad2; k <= rad2; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					

					if (curInd > -1) {
						
						for (ko = -rad; ko <= rad; ko++) {
							for (jo = -rad; jo <= rad; jo++) {
								for (io = -rad; io <= rad; io++) {
									testInd = getNodeIndex(i + io, j + jo, k + ko, 0);

									if (testInd > -1) {
										if (terData[testInd] == 0) {
											buildingData[curInd].nearAir = true;
										}
										else {
											buildingData[curInd].nearTerrain = true;
										}
									}
								}
							}
						}
					}
					
				}
			}
		}
		
		forceUpdate = true;

		//copyTerToTexture(true);
		
		//refreshHoldersInArea(worldPos);

	}


	int isNearTerrain(FIVector4 *worldPosInPix) {

		int ind;
		
		int i;
		int j;
		int k;
		
		tempVec.copyFrom(worldPosInPix);
		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		tempVec.addXYZ(0.5f);

		bool nearT = false;
		bool nearA = false;

		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		ind = getNodeIndex(i, j, k, 0);
		if (ind > -1) {
			nearT = buildingData[ind].nearTerrain;
			nearA = buildingData[ind].nearAir;
		}

		if (nearT) {
			if (nearA) {
				return E_TER_GROUNDLEVEL;
			}
			else {
				return E_TER_UNDERGROUND;
			}
		}
		
		return E_TER_AIR;

	}
	
	
	int findNearestNode(FIVector4* worldPositionInPixelsIn, FIVector4* posInNodesOut, FIVector4* posInPixelsOut ) {

		int i;
		int j;
		int k;
		int m;
		int curInd;
		int offset;
		int bestInd = -1;
		
		float zBias = floorHeightInMeters*pixelsPerMeter*0.5f;

		bool notFound = true;
		
		
		tempVec.copyFrom(worldPositionInPixelsIn);
		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			zBias
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		
		
		for (m = 0; m < 3; m++) {
			switch (m) {
				case 0:
					offset = 0;
				break;
				case 1:
					offset = -1;
				break;
				case 2:
					offset = 1;
				break;
			}
			
			curInd = getNodeIndex(i,j,k+offset,0);
			
			if (curInd > -1) {
				if (touchesPlanarClass(i,j,k+offset,E_CTC_ROAD,0)) {
					bestInd = curInd;
					break;
				}
			}
		}
		
		
		
		
		if (bestInd > -1) {
			posInNodesOut->setIXYZ(
				i + offsetInBlocks.getIX()*terDataVisPitchXY - terDataBufAmount,
				j + offsetInBlocks.getIY()*terDataVisPitchXY - terDataBufAmount,
				k + offset - terDataBufAmount
			);
			nodeIndexToWorldSpaceInPixels(bestInd,posInPixelsOut);
		}
		
		
		return bestInd;

	}
	
	void nodeIndexToWorldSpaceInPixels(int ind, FIVector4* posInPixelsOut ) {


		int k = ind / (terDataBufPitchXY * terDataBufPitchXY);
		int j = (ind - k * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
		int i = ind - (k * terDataBufPitchXY * terDataBufPitchXY + j * terDataBufPitchXY);
				
		posInPixelsOut->setFXYZ(
			blockSizeInPixels * offsetInBlocks.getIX() + ( ((float)(i - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY,
			blockSizeInPixels * offsetInBlocks.getIY() + ( ((float)(j - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY,
			0 + ( ((float)(k - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ
		);

	}
	
	
	

	bool hasTerrainBelow(int i, int j, int k, int conDir, bool bothEnds) {
		bool foundA = false;
		bool foundB = false;

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int testInd2 = getNodeIndex(i + dirModX[conDir], j + dirModY[conDir], k + dirModZ[conDir] - 1, 0);


		if (conDir < 4) {
			if (testInd > -1) {
				if (terData[testInd] != 0) {
					foundA = true;
				}
			}

			if (testInd2 > -1) {
				if (terData[testInd2] != 0) {
					foundB = true;
				}
			}

		} else {
			if (testInd > -1) {
				if (
					(terData[testInd] != 0)
				) {
					foundA = true;
					foundB = true;
				}
			}
		}

		if (bothEnds) {
			return foundA && foundB;
		} else {
			return foundA || foundB;
		}
	}

	bool hasRoomBelow(int i, int j, int k, int conDir) {

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int p;

		if (testInd > -1) {
			if (isRoom[buildingData[testInd].con[conDir].conType]) {
				return true;
			}

			if (conDir >= 4) {
				for (p = 0; p < 4; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool isSupportedBelow(int i, int j, int k, int conDir, bool bothEnds) {

		bool foundA = false;
		bool foundB = false;

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int testInd2 = getNodeIndex(i + dirModX[conDir], j + dirModY[conDir], k + dirModZ[conDir] - 1, 0);

		int p;

		if (conDir < 4) {
			if (testInd > -1) {
				if (terData[testInd] != 0) {
					foundA = true;
				}

				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						foundA = true;
					}
				}

			}

			if (testInd2 > -1) {
				if (terData[testInd2] != 0) {
					foundB = true;
				}

				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd2].con[p].conType]) {
						foundB = true;
					}
				}

			}

		} else {
			if (testInd > -1) {
				if (
					(terData[testInd] != 0)
				) {
					foundA = true;
					foundB = true;
				}



				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						foundA = true;
						foundB = true;
					}
				}


			}
		}

		if (bothEnds) {
			return foundA && foundB;
		} else {
			return foundA || foundB;
		}


	}


	bool touchesRoomOnLevel(int i, int j, int k) {

		int testInd = getNodeIndex(i, j, k, 0);
		int p;

		if (testInd > -1) {
			for (p = 0; p < 4; p++) {
				if (isRoom[buildingData[testInd].con[p].conType]) {
					return true;
				}
			}
		}

		return false;
	}

	bool touchesBaseOnLevel(int i, int j, int k, int layer) {

		int testInd;
		int p;
		int m;
		int conType;

		//for (m = 0; m < 2; m++) {}
		
		m = 0;
		
		testInd = getNodeIndex(i, j, k+m, 0);
		if (testInd > -1) {
			for (p = 0; p < 4; p++) {
				conType = buildingData[testInd].con[p+layer*MAX_NODE_DIRS].conType;
				
				if (conType == E_CT_FOUNDATION) {
					return true;
				}
				
				
				// if (m == 0) {
				// 	if (
				// 		isBase[conType]
				// 		&& (!isRoad[conType])
				// 	) {
				// 		return true;
				// 	}
				// }
				// else {
				// 	if (isRoad[conType]) {
				// 		return true;
				// 	}
				// }
				
				
			}
		}

		
		
		
		return false;
	}



	bool buildingAbove(int x, int y, int z) {

		int newInd = getNodeIndex(x, y, z, 0);
		int i;
		int testConType;

		if (newInd > -1) {
			for (i = 0; i < 5; i++) { // skip downwards direction
				testConType = buildingData[newInd].con[i].conType;
				if (isRoom[testConType]) {
					return true;
				}
			}
		}

		return false;
	}

	int copyTerToTexture() {

		int resIndex = singleton->requestTerIndex(blockId);

		int i;
		int j;
		int k;
		int indSource;
		int indDest;

		uint uiSimp;

		uint *finalTex;

		if (singleton->terTextures[resIndex].alreadyBound && (!forceUpdate)) {
			
		} else {
			
			forceUpdate = false;

			doTraceND("copyTerToTexture resIndex: ", i__s(resIndex));

			singleton->terTextures[resIndex].alreadyBound = true;


			// if (terDataTexScale == 1) {
			// 	finalTex = terData;
			// } else {
				
			// }
			
			tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
			
			
			for (k = 0; k < terDataBufPitchScaledZ; k++) {
				for (j = 0; j < terDataBufPitchScaledXY; j++) {
					for (i = 0; i < terDataBufPitchScaledXY; i++) {
						indDest = k * terDataBufPitchScaledXY * terDataBufPitchScaledXY + j * terDataBufPitchScaledXY + i;
						indSource =
							(k / terDataTexScale) * terDataBufPitchXY * terDataBufPitchXY +
							(j / terDataTexScale) * terDataBufPitchXY +
							(i / terDataTexScale);
							
						if (terData[indSource] == 0) {
							uiSimp = 0;
						}
						else {
							if (buildingData[indSource].nearAir) {
								
								// TODO: rand num should be hashed based on location
								
								
								
								
								
								if (
									(i >= terDataBufPitchScaledXY-terDataBufAmount*4) ||
									(i <= terDataBufAmount*4) ||
									(j >= terDataBufPitchScaledXY-terDataBufAmount*4) ||
									(j <= terDataBufAmount*4)
								) {
									uiSimp = 255; // make sure block borders match up
								}
								else {
									
									tempVec.setIXYZ(
										i + offsetInBlocks.getIX()*terDataVisPitchXY - terDataBufAmount,
										j + offsetInBlocks.getIY()*terDataVisPitchXY - terDataBufAmount,
										k + offsetInBlocks.getIZ()*terDataVisPitchZ - terDataBufAmount
									);
									
									uiSimp = iGetRandSeeded(&tempVec,&tempVec2,200,255);
								}
								
							}
							else {
								uiSimp = 255;
							}
						}

						singleton->terDataScaled[indDest] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;//terData[indSource];
					}
				}
			}

			finalTex = singleton->terDataScaled;
			
			
			

			glBindTexture(GL_TEXTURE_3D, singleton->terTextures[resIndex].texId);

			glTexSubImage3D(
				GL_TEXTURE_3D,
				0,

				0,
				0,
				0,

				terDataBufPitchScaledXY,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledZ,

				GL_RGBA,
				GL_UNSIGNED_BYTE,

				finalTex

			);
			glBindTexture(GL_TEXTURE_3D, 0);
		}

		return resIndex;

	}




		void makeMazeUG() {

			//cout << "q\n";

			int i;
			int rbInd = 0;
			int curInd = 0;
			int startDir = 0;
			int count = 0;

			int testX = 0;
			int testY = 0;
			int testZ = 0;

			int curX = 0;
			int curY = 0;
			int curZ = 0;
			
			int ind1;
			int ind2;

			int testInd = 0;
			int bestInd = 0;
			int bestDir = 0;
			int curDir = 0;
			int blockOffset = offsetInBlocks.getIX() + offsetInBlocks.getIY();

			int ct;

			bool isOddX, isOddY, isOddZ;
			bool doProc;

			int divSize = 4;
			int tunnelCount = 0;

			rbInd = 0;
			


			//ind1 = getMapNodeIndex(terDataBufSize/2,terDataBufSize/2, 0);
			
			singleton->rbStack[0] = getNodeIndex(
																terDataBufPitchXY/2,
																terDataBufPitchXY/2,
																terDataBufPitchZ/2,
																0
															);
			
			




			while (rbInd > -1) {



				curInd = singleton->rbStack[rbInd];
				buildingData[curInd].visited = 1;
				buildingData[curInd].mazeIndex = rbInd;

				curZ = curInd / (terDataBufPitchXY * terDataBufPitchXY);
				curY = (curInd - curZ * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
				curX = curInd - (curZ * terDataBufPitchXY * terDataBufPitchXY + curY * terDataBufPitchXY);

				startDir = rbInd * 37 + blockOffset;
				count = 0;

				isOddX = ((curX + terDataBufAmount) % divSize) != 0;
				isOddY = ((curY + terDataBufAmount) % divSize) != 0;
				isOddZ = ((curZ + terDataBufAmount) % divSize) != 0;

				do {

					curDir = (startDir + count) % 6;

					testX = curX + dirModX[curDir];
					testY = curY + dirModY[curDir];
					testZ = curZ + dirModZ[curDir];

					testInd = getNodeIndex(testX, testY, testZ, 0);



					if (testInd >= 0) {
						
						//cout << "b\n";

						if ( true ) { // terData[testInd] != 0
							if ( buildingData[testInd].visited == 0 ) {

								

								doProc = false;

								if (isOddX) {
									if (curDir <= 1) {
										doProc = true;
									}
								}
								else {
									if (isOddY) {
										if ((curDir == 2) || (curDir == 3)) {
											doProc = true;
										}
									}
									else {
										if (isOddZ) {
											if (curDir >= 4) {
												doProc = true;
											}
										}
										else {
											doProc = true;
										}
									}
								}
								if (doProc) {
									//not visited, proceed

									

									bestDir = curDir;
									bestInd = testInd;
									goto DONE_SEARCHING;
								}



							}
						}


					}



					count++;


				} while (count < 6);

	DONE_SEARCHING:

				if (count >= 6) { // dead end, back up
					rbInd--;
				} else {

					//ct = E_CT_CONNECTED;//iGenRand(E_CT_ROAD,E_CT_ROOM_TUDOR);
					//connectNodes( curX, curY, curZ, testX, testY, testZ, E_CT_CONNECTED);
					
					//cout << "a\n";
					
					ind1 = getNodeIndex(curX,curY,curZ, 0);
					ind2 = getNodeIndex(testX,testY,testZ, 0);
					
					if (ind1 > -1) {
						terData[ind1] = 0;
					}
					if (ind2 > -1) {
						terData[ind2] = 0;
					}

					rbInd++;

					


					singleton->rbStack[rbInd] = bestInd;
					
					
					tunnelCount++;
					
					if (tunnelCount >= terDataBufSize/16) {
						return;
					}
					
				}



			}

		}





// 	int findPath(int begInd, int endInd) {

// 		int i;
// 		int rbInd = 0;
// 		int curInd = 0;

// 		int testX = 0;
// 		int testY = 0;
// 		int testZ = 0;

// 		int curX = 0;
// 		int curY = 0;
// 		int curZ = 0;

// 		int testInd = 0;
// 		int bestInd = 0;
// 		int bestDir = 0;
// 		int curDir = 0;
// 		int blockOffset = offsetInBlocks.getIX() + offsetInBlocks.getIY();

// 		int endZ = endInd / (terDataBufPitchXY * terDataBufPitchXY);
// 		int endY = (endInd - endZ * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
// 		int endX = endInd - (endZ * terDataBufPitchXY * terDataBufPitchXY + endY * terDataBufPitchXY);
		
// 		int conType;
		
// 		int pathCost;
// 		int bestCost;
// 		int invalidCost = terDataBufPitchXY*terDataBufPitchXY*terDataBufPitchXY + 1;

// 		rbInd = 0;
// 		singleton->rbStack[0] = begInd;
		
// 		for (i = 0; i < terDataBufSize; i++) {
// 			buildingData[i].visited = 0;
// 		}


// 		while (rbInd > -1) {
			

// 			curInd = singleton->rbStack[rbInd];
			
// 			if (curInd == endInd) {
// 				goto DONE_FINDING_PATH;
// 			}
			
// 			buildingData[curInd].visited = 1;

// 			curZ = curInd / (terDataBufPitchXY * terDataBufPitchXY);
// 			curY = (curInd - curZ * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
// 			curX = curInd - (curZ * terDataBufPitchXY * terDataBufPitchXY + curY * terDataBufPitchXY);


// 			bestInd = -1;
// 			bestCost = invalidCost;

			
// 			for (curDir = 0; curDir < 4; curDir++) {


// 				testX = curX + dirModX[curDir];
// 				testY = curY + dirModY[curDir];
// 				testZ = curZ + dirModZ[curDir] + buildingData[curInd].con[curDir].heightDelta;
// 				testInd = getNodeIndex(testX, testY, testZ, terDataBufAmount);

// 				if (testInd >= 0) {

// 					conType = buildingData[curInd].con[curDir].conType;
					
// 					if (
// 						( isTraversable[conType] ) &&
// 						( buildingData[testInd].visited == 0 )
// 					) {
// 						pathCost = abs(testX-endX) + abs(testY-endY) + abs(testZ-endZ);

// 						if (pathCost < bestCost) {
// 							bestCost = pathCost;
// 							bestDir = curDir;
// 							bestInd = testInd;
// 						}
// 					}
// 				}

// 			}

// 			if (bestInd == -1) { // dead end, back up
// 				rbInd--;
// 			} else {
// 				rbInd++;
// 				singleton->rbStack[rbInd] = bestInd;
				
// 			}

			

// 		}
		
// DONE_FINDING_PATH:
		
// 		return rbInd;

// 	}



	


// 	void makeMaze(bool underground) {

// 		int i;
// 		int rbInd = 0;
// 		int curInd = 0;
// 		int startDir = 0;
// 		int count = 0;

// 		int testX = 0;
// 		int testY = 0;
// 		int testZ = 0;

// 		int curX = 0;
// 		int curY = 0;
// 		int curZ = 0;
		
// 		int ind1;
// 		int ind2;

// 		int testInd = 0;
// 		int bestInd = 0;
// 		int bestDir = 0;
// 		int curDir = 0;
// 		int blockOffset = offsetInBlocks.getIX() + offsetInBlocks.getIY();

// 		int ct;

// 		bool isOddX, isOddY, isOddZ;
// 		bool doProc;

// 		int divSize = 4;

// 		rbInd = 0;


// 		if (underground) {
			
// 			ind1 = getMapNodeIndex(terDataBufSize/2,terDataBufSize/2, 0);
			
// 			singleton->rbStack[0] = getNodeIndex(
// 																terDataBufSize/2,
// 																terDataBufSize/2,
// 																mapData[ind1].terHeight/2,
// 																0
// 															);
			
			
			
			
// 		} else {

// 			for (i = 0; i < terDataBufSize; i++) {
// 				testInd = getNodeIndex(terDataBufAmount + divSize, terDataBufAmount + divSize, i, 0);
// 				if (testInd > -1) {
// 					if (singleton->rbHeightStack[testInd] > 0) {
// 						break;
// 					}
// 				}
// 			}

// 			singleton->rbStack[0] = testInd; // start maze at ground level
// 		}




// 		while (rbInd > -1) {



// 			curInd = singleton->rbStack[rbInd];
// 			buildingData[curInd].visited = 1;
// 			buildingData[curInd].mazeIndex = rbInd;

// 			curZ = curInd / (terDataBufPitchXY * terDataBufPitchXY);
// 			curY = (curInd - curZ * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
// 			curX = curInd - (curZ * terDataBufPitchXY * terDataBufPitchXY + curY * terDataBufPitchXY);

// 			startDir = rbInd * 37 + blockOffset;
// 			count = 0;

// 			isOddX = ((curX + terDataBufAmount) % divSize) != 0;
// 			isOddY = ((curY + terDataBufAmount) % divSize) != 0;
// 			isOddZ = ((curZ + terDataBufAmount) % divSize) != 0;

// 			do {

// 				curDir = (startDir + count) % 6;

// 				testX = curX + dirModX[curDir];
// 				testY = curY + dirModY[curDir];
// 				testZ = curZ + dirModZ[curDir];

// 				testInd = getNodeIndex(testX, testY, testZ, terDataBufAmount);


// 				if (testInd >= 0) {

// 					if (
// 						(underground && (terData[testInd] != 0)) ||
// 						((!underground) && (terData[testInd] == 0))
// 					) {
// 						if ( buildingData[testInd].visited == 0 ) {


// 							doProc = false;

// 							if (isOddX) {
// 								if (curDir <= 1) {
// 									doProc = true;
// 								}
// 							}

// 							if (isOddY) {
// 								if ((curDir == 2) || (curDir == 3)) {
// 									doProc = true;
// 								}
// 							}
							
// 							if (isOddZ) {
// 								if (curDir >= 4) {
// 									doProc = true;
// 								}
// 							}

// 							// if ( (!isOddY) && (!isOddX) ) {
// 							// 	doProc = true;
// 							// }

// 							// if (curDir >= 4) {
// 							// 	doProc = true;
// 							// }

// 							// if (!underground) {
// 							// 	doProc = doProc && (
// 							// 						 singleton->rbHeightStack[curInd] <=

// 							// 						 // maxFloors

// 							// 						 max(
// 							// 							 iSeedRand2(curX, curY, 1, maxFloors),
// 							// 							 iSeedRand2(testX, testY, 1, maxFloors)
// 							// 						 )
// 							// 					 );
// 							// }



// 							if (doProc) {
// 								//not visited, proceed

// 								cout << "c\n";

// 								bestDir = curDir;
// 								bestInd = testInd;
// 								goto DONE_SEARCHING;
// 							}



// 						}
// 					}


// 				}



// 				count++;


// 			} while (count < 6);

// DONE_SEARCHING:

// 			if (count >= 6) { // dead end, back up
// 				rbInd--;
// 			} else {

// 				//ct = E_CT_CONNECTED;//iGenRand(E_CT_ROAD,E_CT_ROOM_TUDOR);
// 				//connectNodes( curX, curY, curZ, testX, testY, testZ, E_CT_CONNECTED);
				
// 				cout << "a\n";
				
// 				ind1 = getNodeIndex(curX,curY,curZ, 0);
// 				ind2 = getNodeIndex(testX,testY,testZ, 0);
				
// 				if (ind1 > -1) {
// 					terData[ind1] = 0;
// 				}
// 				if (ind2 > -1) {
// 					terData[ind2] = 0;
// 				}

// 				rbInd++;



// 				singleton->rbStack[rbInd] = bestInd;
// 			}



// 		}

// 	}

};
