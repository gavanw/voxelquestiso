
class GameWorld
{
public:


	int numProvinces;
	int seaLevel;
	int seaSlack;
	int pageCount;
	int mapSwapFlag;
	int visPageSizeInUnits;
	int blockSizeInHolders;

	int iBlockSize;
	//int diagrams[E_RENDER_LENGTH][E_STATE_LENGTH];
	int renderMethod;
	int iBufferSize;
	int maxThreads;
	int availThreads;
	int visPageSizeInPixels;
	int holderSizeInPages;

	int lightCount;

	int MIN_MIP;
	int MAX_MIP;
	int AVG_MIP;

	int blockMip;

	int hmChannel;
	int idChannel;
	int densityChannel;
	int blockChannel;
	
	int curLoadRadius;

	int stChannel;
	int btChannel;
	int pathChannel;
	int houseChannel;

	int *curDiagram;
	int *provinceGrid;
	int *provinceX;
	int *provinceY;

	bool procResultAccum;
	bool doDrawFBO;
	bool lastProcResult;
	bool mapLockOn;
	bool foundPath;

	float mapStep;
	float mapTrans;
	float newZoom;


	int dirFlags[4];
	int dirFlagsOp[4];
	int dirFlagsO[4];
	int dirFlagsOpO[4];
	int dirModX[6];
	int dirModY[6];
	int dirModZ[6];
	int opDir[4];

	//GameLight globalLight;
	GameLight *activeLights[MAX_EVAL_LIGHTS];

	int dirFlagClear;
	int visFlag;
	int visFlagO;

	int activeFBO;

	bool noiseGenerated;


	std::vector<coordAndIndex> roadCoords;

	std::vector<GamePageHolder *> holdersToRefresh;

	

	vector<int> ocThreads;

	
	FIVector4 lScreenCoords;
	FIVector4 cScreenCoords;
	//FIVector4 aoScreenCoords;
	FIVector4 worldSizeInPages;
	FIVector4 worldSizeInHolders;
	FIVector4 worldSizeInBlocks;

	FIVector4 geomMin;
	FIVector4 geomMax;

	FIVector4 camPagePos;
	FIVector4 camHolderPos;
	FIVector4 cutHolderPos;
	FIVector4 camBlockPos;
	FIVector4 camTerPos;
	FIVector4 iPixelWorldCoords;
	FIVector4 pagePos;
	FIVector4 unitPos;
	FIVector4 lastUnitPos;
	FIVector4 lastPagePos;
	
	FIVector4 tempVec1;
	FIVector4 tempVec2;
	FIVector4 tempVec3;
	
	FIVector4 blockPos[2];
	FIVector4 nodePos[2];
	FIVector4 nodePosInPixels[2];
	PathNode blockAndIndexPath[2];
	PathNode blockAndIndexSplitPath[2];
	FIVector4 lineSeg[2];
	PathHolder* finalPath;
	
	int nodeInd[2];
	//int finalInd;
	
	GameBlock* blockRef[2];
	
	

	FIVector4 minLRInPixels;
	FIVector4 maxLRInPixels;

	FIVector4 minLRInHolders;
	FIVector4 maxLRInHolders;

	FIVector4 minv;
	FIVector4 maxv;

	FIVector4 tempVec;
	FIVector4 unitPosMin;
	FIVector4 unitPosMax;
	FIVector4 unitPosCenter;
	//FIVector4 unitPosMinIS;
	//FIVector4 unitPosMaxIS;

	FIVector4 startBounds;
	FIVector4 endBounds;

	FIVector4 *fogPos;
	FIVector4 *cutPos;
	FIVector4 *lightPos;
	FIVector4 *globLightPos;
	FIVector4 lightPosBase;
	FIVector4 *cameraPos;

	FIVector4 *curBoxPos;
	FIVector4 tv0;
	FIVector4 tv1;
	FIVector4 tv2;
	FIVector4 tv3;
	FIVector4 tv4;
	FIVector4 tv5;

	//glm::quat myQuat;
	//glm::vec3 paramVec;
	//glm::vec3 spinVec;

	Singleton *singleton;

	GameBlock **blockData;

	FBOWrapper *curFBO;
	FBOWrapper *curFBO2;
	
	


	//Poco::ThreadPool threadpool;




	GameWorld()
	{

		// Notes
		// -----
		// Depth: 16 bits
		// Material: 16 bits
		// AO val: 8 bits, normal: 24 bits

	}


	void init(Singleton *_singleton)
	{

		//pushTrace("GameWorld init()");

		

		singleton = _singleton;
		
		curLoadRadius = singleton->minWInPages;

		int i;
		int j;
		
		//finalInd = -1;

		lightCount = 1;

		noiseGenerated = false;

		finalPath = NULL;

		blockSizeInHolders = singleton->blockSizeInHolders;

		dirFlagsO[0] = 1;
		dirFlagsO[1] = 2;
		dirFlagsO[2] = 4;
		dirFlagsO[3] = 8;

		dirFlagsOpO[0] = 2;
		dirFlagsOpO[1] = 1;
		dirFlagsOpO[2] = 8;
		dirFlagsOpO[3] = 4;

		dirFlags[0] = ~1;
		dirFlags[1] = ~2;
		dirFlags[2] = ~4;
		dirFlags[3] = ~8;

		dirFlagsOp[0] = ~2;
		dirFlagsOp[1] = ~1;
		dirFlagsOp[2] = ~8;
		dirFlagsOp[3] = ~4;

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

		dirFlagClear = ~15;
		visFlag = 16;
		visFlagO = ~16;

		foundPath = false;

		activeFBO = 0;
		mapLockOn = false;

		numProvinces = 32;
		provinceGrid = new int[numProvinces * numProvinces];
		provinceX = new int[numProvinces];
		provinceY = new int[numProvinces];

		mapSwapFlag = 0;
		mapStep = 0.0f;

		pageCount = 0;
		procResultAccum = false;
		lastProcResult = true;
		maxThreads = 7;
		availThreads = maxThreads;

		for (i = 0; i < maxThreads; i++)
		{
			ocThreads.push_back(-1);
		}

		hmChannel = 0;
		idChannel = 1;
		densityChannel = 2;
		blockChannel = 3;

		stChannel = 0;
		btChannel = 1;
		pathChannel = 2;
		houseChannel = 3;




		MIN_MIP = 0;
		MAX_MIP = 1;
		AVG_MIP = 2;


		doDrawFBO = false;

		// for (j = 0; j < E_RENDER_LENGTH; j++)
		// {
		// 	for (i = 0; i < E_STATE_LENGTH; i++)
		// 	{
		// 		diagrams[j][i] = E_STATE_WAIT;
		// 	}
		// }

		cutPos = &(singleton->dynObjects[E_OBJ_CUTAWAY]->pos);
		fogPos = &(singleton->dynObjects[E_OBJ_FOG]->pos);
		cameraPos = &(singleton->dynObjects[E_OBJ_CAMERA]->pos);

		renderMethod = (int)E_RENDER_VOL;

		worldSizeInPages.copyFrom( &(singleton->worldSizeInPages) );
		worldSizeInHolders.copyFrom( &(singleton->worldSizeInHolders) );
		worldSizeInBlocks.copyFrom( &(singleton->worldSizeInBlocks) );

		visPageSizeInPixels = singleton->visPageSizeInPixels;

		// diagrams[E_RENDER_VOL][E_STATE_INIT_END] = E_STATE_GENERATEVOLUME_LAUNCH;
		// diagrams[E_RENDER_VOL][E_STATE_GENERATEVOLUME_END] = E_STATE_LENGTH;
		// curDiagram = diagrams[renderMethod];

		holderSizeInPages = singleton->holderSizeInPages;
		visPageSizeInUnits = singleton->visPageSizeInUnits;

		iBlockSize = worldSizeInBlocks.getIX() * worldSizeInBlocks.getIY();



		blockData = new GameBlock*[iBlockSize];
		for (i = 0; i < iBlockSize; i++)
		{
			blockData[i] = NULL;
		}

		
		
		


		//popTrace();
	}


	
	
	// x, y, and z are measured in blocks
	GameBlock *getBlockAtCoords(int xInBlocks, int yInBlocks, bool createOnNull = false)
	{





		int newX = wrapCoord(xInBlocks, worldSizeInBlocks.getIX());
		int newY = wrapCoord(yInBlocks, worldSizeInBlocks.getIY());

		//cout << "xy " << newX << " " << newY << "\n";

		int ind =
			newY * worldSizeInBlocks.getIX() +
			newX;

		if (blockData[ind] == NULL) {
			if (createOnNull) {
				blockData[ind] = new GameBlock();
				blockData[ind]->init(singleton, ind, xInBlocks, yInBlocks, newX, newY);
			}
		}

		return blockData[ind];

	}

	// x, y, and z are measured in holders
	GamePageHolder *getHolderAtCoords(int x, int y, int z, bool createOnNull = false)
	{

		GamePageHolder **holderData;

		int newX = wrapCoord(x, worldSizeInHolders.getIX());
		int newY = wrapCoord(y, worldSizeInHolders.getIY());
		int newZ = z;

		int holderX = newX - intDiv(newX, blockSizeInHolders) * blockSizeInHolders;
		int holderY = newY - intDiv(newY, blockSizeInHolders) * blockSizeInHolders;
		int holderZ = newZ - intDiv(newZ, blockSizeInHolders) * blockSizeInHolders;

		int holderId = holderZ * blockSizeInHolders * blockSizeInHolders + holderY * blockSizeInHolders + holderX;


		GameBlock *curBlock = getBlockAtCoords(
														intDiv(x, blockSizeInHolders),
														intDiv(y, blockSizeInHolders),
														createOnNull
													);

		if (curBlock == NULL)
		{
			return NULL;
		}
		else
		{
			holderData = curBlock->holderData;


			if (holderData[holderId] == NULL)
			{
				if (createOnNull)
				{
					holderData[holderId] = new GamePageHolder();
					holderData[holderId]->init(singleton, curBlock->blockId, holderId, x, y, z); //, x, y, z
				}
			}

			return holderData[holderId];


		}



	}
	
	
	// x, y, and z are measured in terDataBufSize
	uint getTerDataAtCoords(int x, int y, int z)
	{

		int tdvpXY = singleton->terDataVisPitchXY;
		int tdvpZ = singleton->terDataVisPitchZ;

		int newX = wrapCoord(x, singleton->worldSizeInTerData.getIX());
		int newY = wrapCoord(y, singleton->worldSizeInTerData.getIY());
		int newZ = z;


		int holderX = newX - intDiv(newX, tdvpXY) * tdvpXY;
		int holderY = newY - intDiv(newY, tdvpXY) * tdvpXY;
		int holderZ = newZ - intDiv(newZ, tdvpZ) * tdvpZ;

		int holderId = holderZ * tdvpXY * tdvpXY + holderY * tdvpXY + holderX;


		GameBlock *curBlock = getBlockAtCoords(
														intDiv(x, tdvpXY),
														intDiv(y, tdvpXY),
														true
													);

		return curBlock->terData[holderId];


	}
	
	
	

	// assumed that holder exists when calling this
	GamePageHolder *getHolderAtId(intPair id)
	{

		if (blockData[id.v0] == NULL)
		{
			return NULL;
		}
		else
		{
			return blockData[id.v0]->holderData[id.v1];
		}
	}

	// assumed that block exists when calling this
	GameBlock *getBlockAtId(int id)
	{


		if ((id < 0) || (id >= iBlockSize))
		{
			doTraceND("BLOCK INDEX OUT OF RANGE");
			return NULL;
		}
		else
		{
			if (blockData[id] == NULL)
			{
				doTraceND("BLOCK DATA IS NULL");
				return NULL;
			}
			else
			{
				return blockData[id];
			}
		}



	}


	// assumed that page exists when calling this
	GamePage *getPageAtIndex(int ind)
	{
		//pushTrace("getPageAtIndex()");

		int newInd = ind;
		int x, y, z;
		GamePage *gp;

		z = newInd / (worldSizeInPages.getIX() * worldSizeInPages.getIY());
		newInd -= z * (worldSizeInPages.getIX() * worldSizeInPages.getIY());

		y = newInd / (worldSizeInPages.getIX());
		newInd -= y * (worldSizeInPages.getIX());

		x = newInd;

		gp = getPageAtCoords(x, y, z, false);

		//popTrace();

		return gp;

	}


	// x, y, and z are measured in pages
	GamePage *getPageAtCoords(int x, int y, int z, bool createOnNull = false)
	{

		//pushTrace("getPageAtCoords()");
		int hx, hy, hz;
		int px, py, pz;
		int gpInd;
		//int xmod = 0;
		//int ymod = 0;
		int newX = wrapCoord(x, worldSizeInPages.getIX());
		int newY = wrapCoord(y, worldSizeInPages.getIY());
		int newZ = z;
		int ind =
			newZ * worldSizeInPages.getIX() * worldSizeInPages.getIY() +
			newY * worldSizeInPages.getIX() +
			newX;

		GamePage *gp = NULL;

		px = newX % holderSizeInPages;
		py = newY % holderSizeInPages;
		pz = newZ % holderSizeInPages;




		GamePageHolder *gph = getHolderAtCoords(
														intDiv(x, holderSizeInPages),
														intDiv(y, holderSizeInPages),
														intDiv(z, holderSizeInPages),
														createOnNull
													);


		if ( gph )
		{



			gpInd = pz * holderSizeInPages * holderSizeInPages + py * holderSizeInPages + px;
			//gph->getPageIndex(px,py,pz);

			if (gpInd == -1)
			{
				// prob
				cout << "Invalid holder index\n";
			}
			else
			{
				gp = gph->pageData[gpInd];

				if (gp == NULL) {
					if (createOnNull) {

						gph->pageData[gpInd] = new GamePage();
						gp = gph->pageData[gpInd];
						gp->init(
							singleton,
							gph,
							ind,
							x, y, z,//newX, newY, newZ,
							px, py, pz
						);
					}
				}
			}

		}

		//popTrace();
		return gp;

	}



	bool checkBounds(int k, int km) {
		
		return ((k >= 0)&&(k<km));

	}


	void update()
	{
		
		bool procResult = false;
		

		//pushTrace("update()");

		singleton->updateLock = true;

		int i;

		float x;
		float y;
		float z;
		
		

		newZoom = max(1.0f, singleton->cameraZoom);

		bool doFinalDraw = false;
		
		singleton->testHuman->basePosition.copyFrom(&(singleton->dynObjects[E_OBJ_HUMAN]->pos));
		transformEnt(singleton->testHuman);

		mapTrans = 1.0f-smoothstep(1.0f/128.0f,1.0f/32.0f,singleton->cameraZoom);
		//1.0f - (singleton->cameraZoom * ((float)DEF_SCALE_FACTOR)) / 0.01f;
		if (mapTrans > 0.91)
		{
			mapTrans = 1.0;
		}
		if (mapTrans < 0.1)
		{
			mapTrans = 0.0;
		}
		
    bool changesMade = false;
    bool bufferInvalid = false;

		if (mapLockOn)
		{
			goto DO_RETURN_UPDATE;
		}

		if (singleton->mapInvalid)
		{


			goto DO_RETURN_UPDATE;
		}

		if (noiseGenerated)
		{

		}
		else
		{
			noiseGenerated = true;
			singleton->bindShader("NoiseShader");
			singleton->bindFBO("noiseFBO");
			singleton->drawFSQuad(1.0f);
			singleton->unbindFBO();
			singleton->unbindShader();
		}

		changesMade = singleton->changesMade;
		bufferInvalid = singleton->bufferInvalid;
		

		if (mapTrans < 1.0f)
		{

			if ( singleton->isZooming ) //
			{

			}
			else
			{
				procResult = procPages();
				
				procResultAccum = procResultAccum || procResult;
				
				if (singleton->skipFrames > 1) {
					if ( (singleton->frameCount % singleton->skipFrames) != 0) {
						doFinalDraw = true;
						goto FINAL_DRAW;
					}
				}
				
				
				procResultAccum = false;
				

				if ( (lastProcResult != procResultAccum)  ) // && (procResultAccum == false)
				{
					singleton->wsBufferInvalid = true;
				}
			}

			if (
				procResultAccum ||
				changesMade ||
				(singleton->charState == E_CHAR_STATE_RENDERED) ||
				(singleton->tiltChanged)
			)
			{
				actionOnHolders(E_HOLDER_ACTION_RENDER);
				combineHolders();

			}

		}

		if (
			procResultAccum ||
			changesMade ||
			bufferInvalid ||
			singleton->abDown || 
			//(singleton->charState == E_CHAR_STATE_SKEL) ||
			(singleton->charState == E_CHAR_STATE_RENDERED) ||
			(singleton->tiltChanged)
			
		)	{

			doFinalDraw = true;

			renderGeom();
			combineBuffers();
			renderWorldSpaceGPU();


		}




		////////////


		if (doFinalDraw || singleton->waterOn || (mapTrans > 0.0))
		{
			glClearColor(0.6f, 0.6f, 0.7f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			if ( mapTrans < 1.0 )
			{

				postProcess();

			}

			if ( mapTrans > 0.0 )
			{
				if (doFinalDraw) {
					singleton->createVTListTilt();
				}				
				drawMap();
			}

			

			glutSwapBuffers();
			glFlush();
		}



		////////////


		if (singleton->forceGetPD)
		{
			singleton->forceGetPD = false;
			getWorldSpaceBuffer();
		}

FINAL_DRAW:


DO_RETURN_UPDATE:

		if (
			(singleton->skipFrames <= 1) ||
			((singleton->frameCount % singleton->skipFrames) == 0)
		) {
			lastProcResult = procResultAccum;
		}
		
		if (procResult) {
			
		}
		else {
			curLoadRadius++;
			curLoadRadius = min(curLoadRadius,singleton->maxWInPages);
		}
		
		
		singleton->updateLock = false;
		//popTrace();


	}



	bool procPages()
	{



		int counter;
		int i, j, k;
		int res;


		int ii;
		int jj;
		int kk;

		int incVal;

		bool cmade = false;

		
		// if (singleton->autoScroll) {
		// 	camTerPos.copyFrom( &(singleton->cameraPosAdjusted) );
		// 	camPagePos.copyFrom( &(singleton->cameraPosAdjusted) );
		// 	camBlockPos.copyFrom( &(singleton->cameraPosAdjusted) );
		// }
		// else {
			camTerPos.copyFrom( cameraPos );
			camPagePos.copyFrom( cameraPos );
			camBlockPos.copyFrom( cameraPos );
		//}
		
		
		camTerPos.intDivXYZ(
			singleton->terDataVisPitchXY,
			singleton->terDataVisPitchXY,
			singleton->terDataVisPitchZ	
		);
		
		//camPagePos.setFZ(heightAtPoint);
		camPagePos.intDivXYZ(visPageSizeInPixels);
		camPagePos.addXYZ(1.0f,1.0f,1.0f);

		camHolderPos.copyFrom(&camPagePos);
		camHolderPos.intDivXYZ(singleton->holderSizeInPages);

		camHolderPos.addXYZ(1.0f,1.0f,1.0f);

		cutHolderPos.copyFrom(cutPos);
		cutHolderPos.intDivXYZ(singleton->holderSizeInPixels);
		
		

		
		camBlockPos.intDivXYZ(singleton->blockSizeInPixels);


		GamePageHolder* curHolder;
		GameBlock *curBlock;

		int m;
		//E_STATES nState;

		int loadRad = curLoadRadius; //singleton->maxWInPages;
		int loadRad2 = singleton->maxHInPages; //curLoadRadius; //
		
		if (singleton->changingGenVal) {
			loadRad2 = 1;
		}
		
		int changeCount = 0;

		int maxChangesInHolders = singleton->maxChangesInHolders;
		
		
		if (
			(singleton->hitGUI) ||
			(singleton->rbDown && singleton->bShift)
		) {
			
		}
		else {
			if (
				(singleton->abDown || singleton->isZooming)
			) {
				maxChangesInHolders = 1;
			}
		}


		// // check for threads to free
		// if (availThreads < maxThreads)
		// {
		// 	for (i = 0; i < ocThreads.size(); i++)
		// 	{
		// 		if ( ocThreads[i] == -1)
		// 		{
		// 			// already freed
		// 		}
		// 		else
		// 		{
		// 			if ( getPageAtIndex(ocThreads[i]) == NULL )
		// 			{
		// 				// page was destroyed, free thread

		// 				ocThreads[i] = -1;
		// 				availThreads++;
		// 			}
		// 			else
		// 			{
		// 				if (getPageAtIndex(ocThreads[i])->threadRunning)
		// 				{

		// 				}
		// 				else
		// 				{
		// 					ocThreads[i] = -1;
		// 					availThreads++;
		// 				}
		// 			}
		// 		}
		// 	}
		// }


		// if (availThreads == 0)
		// {
		// 	goto DO_RETURN_PP;
		// }

		

		

		// first fetch all the blocks to make sure they get created
		// don't remove this, necessary for overlapping geom
		
		int blockRad = 1;
		for (j = -blockRad; j <= blockRad; j++)
		{
			for (i = -blockRad; i <= blockRad; i++)
			{
				ii = i + camBlockPos.getIX();
				jj = j + camBlockPos.getIY();

				curBlock = getBlockAtCoords(ii, jj, true);

			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//////////////
		
		bool foundIt = false;
		int terVal = 0;
		
		int MAX_CAM_CAST = singleton->terDataVisPitchXY;
		for (i = 0; i < MAX_CAM_CAST; i++) {
			
			ii = camTerPos.getIX()-i;
			jj = camTerPos.getIY()-i;
			kk = camTerPos.getIZ()-i;
			
			if (
				(kk < 0)
			) {
				break;
			}
			
			if (kk >= singleton->terDataVisPitchZ) {
				
			}
			else {
				terVal = getTerDataAtCoords(ii,jj,kk);
			}
			
			if (terVal > 0) {
				foundIt = true;
				break;
			}
			
			
		}
		
		
		float ftPitchXY = singleton->terDataVisPitchXY;
		float ftPitchZ = singleton->terDataVisPitchZ;
		
		if (foundIt) {
			
			camHolderPos.setIXYZ(ii,jj,kk);
			camHolderPos.multXYZ(
				singleton->blockSizeInPixels/ftPitchXY,
				singleton->blockSizeInPixels/ftPitchXY,
				singleton->blockSizeInPixels/ftPitchZ
			);
			
			camHolderPos.multXYZ(1.0f/((float)(singleton->holderSizeInPixels)));
			
		}
		
		
		minLRInPixels.copyFrom(&camHolderPos);
		maxLRInPixels.copyFrom(&camHolderPos);
		minLRInPixels.addXYZ(-singleton->minWInPages, -singleton->minWInPages, -loadRad2);
		maxLRInPixels.addXYZ(singleton->minWInPages, singleton->minWInPages, loadRad2);
		
		minLRInPixels.addXYZ(-0.5f);
		maxLRInPixels.addXYZ(0.5f);
		
		minLRInPixels.multXYZ(singleton->holderSizeInPixels);
		maxLRInPixels.multXYZ(singleton->holderSizeInPixels);
		
		
		//////////////
		
		
		
		
		int tempVal = 0;

		int mink = camHolderPos.getIZ() - loadRad2;
		int maxk = camHolderPos.getIZ() + loadRad2;
		int minj = camHolderPos.getIY() - loadRad;
		int maxj = camHolderPos.getIY() + loadRad;
		int mini = camHolderPos.getIX() - loadRad;
		int maxi = camHolderPos.getIX() + loadRad;
		int curHeight = 0;

		minLRInHolders.setIXYZ(mini + 1, minj + 1, mink + 1);
		maxLRInHolders.setIXYZ(maxi - 1, maxj - 1, maxk - 1);

		int curMC;
		int n;
		int nMax;
		
		if (maxChangesInHolders == 1) {
			nMax = 1;
			curMC = maxChangesInHolders;
		}
		else {
			nMax = 2;
			curMC = maxChangesInHolders/2;
		}
		
		

		for (n = 0; n < nMax; n++) {
			
			if (n == 1) {
				curMC = maxChangesInHolders;
			}
			
			for (jj = maxj; jj >= minj; jj--) {
				
				if (curLoadRadius == singleton->minWInPages) {
					incVal = 1;
				}
				else {
					if ( (jj == minj) || (jj == maxj) ) {
						incVal = 1;
					}
					else {
						incVal = maxi - mini;
					}
				}
				
				for (ii = maxi; ii >= mini; ii -= incVal) {
					
					
					for (kk = maxk; kk >= mink; kk--) {
						if ( checkBounds(kk, worldSizeInHolders.getIZ()) ) {
							
							if (n == 0) {
								curHolder = getHolderAtCoords(ii, jj, kk, true);
							}
							else {
								curHolder = getHolderAtCoords(jj, ii, kk, true);
							}
							
							
							
							
							if (curHolder->childrenDirty) {
								
								tempVal = curHolder->passiveRefresh();
								changeCount += tempVal;
								
								if (tempVal > 0) {
									cmade = true;
								}
								
							}
							
							
							
							if (changeCount >= curMC)
							{
								
								if ((n == 0) && (maxChangesInHolders > 1)) {
									goto FINISH_CUR_LOOP_PP;
								}
								else {
									goto DO_RETURN_PP;
								}
								
							}
						}
					}
					
				}
			}
			
FINISH_CUR_LOOP_PP:
			;
			
		}
		
		
		


DO_RETURN_PP:

		//popTrace();
		return cmade;
	}

	bool addHolderToRefresh(GamePageHolder *toAdd)
	{
		int i;

		bool wasFound = false;

		if (toAdd == NULL)
		{
			return false;
		}

		for (i = 0; i < holdersToRefresh.size(); i++)
		{
			if (holdersToRefresh[i] == toAdd)
			{
				wasFound = true;
			}
		}

		if (wasFound)
		{
			return false;
		}
		else
		{
			holdersToRefresh.push_back(toAdd);
			return true;
		}
	}

	int getHoldersInGeom(GameGeom *gg)
	{

		int i;
		int j;
		int k;

		geomMin.copyFrom(gg->getVisMinInPixelsT());
		geomMin.intDivXYZ(singleton->holderSizeInPixels);

		geomMax.copyFrom(gg->getVisMaxInPixelsT());
		geomMax.intDivXYZ(singleton->holderSizeInPixels);

		GamePageHolder *gphMin = getHolderAtCoords(geomMin.getIX(), geomMin.getIY(), geomMin.getIZ(), true);
		GamePageHolder *gphMax = getHolderAtCoords(geomMax.getIX(), geomMax.getIY(), geomMax.getIZ(), true);

		//doTraceVecND("min: ", &(gphMin->offsetInHolders));
		//doTraceVecND("max: ", &(gphMax->offsetInHolders));

		int totCount = 0;

		bool wasAdded;


		for (i = gphMin->offsetInHolders.getIX(); i <= gphMax->offsetInHolders.getIX(); i++)
		{
			for (j = gphMin->offsetInHolders.getIY(); j <= gphMax->offsetInHolders.getIY(); j++)
			{
				for (k = gphMin->offsetInHolders.getIZ(); k <= gphMax->offsetInHolders.getIZ(); k++)
				{
					wasAdded = addHolderToRefresh(getHolderAtCoords(i, j, k, false));
					if (wasAdded)
					{
						totCount++;
					}

				}
			}
		}

		return totCount;

	}

	void refreshHoldersInList(bool doImmediate, bool clearEverything)
	{
		int i;

		for (i = 0; i < holdersToRefresh.size(); i++)
		{
			holdersToRefresh[i]->refreshChildren(doImmediate, clearEverything);
		}
	}


	void actionOnHolders(int action, bool instantRefresh = false, bool clearEverything = false)
	{

		//pushTrace("renderHolders()");

		int i, j, k, m;
		int res;
		int drawnPageCount = 0;
		int skippedPages = 0;
		intPair cid;
		int ppSize = singleton->gpuPool->orderedIds.size();
		GamePageHolder* gp;
		
		bool entPass = false;
		
		float zOffR = 0.0f;
		float zOffG = 0.0f;
		
		GameEnt* activeEnt = singleton->testHuman;
		GamePageHolder* gphEnt = activeEnt->gph;

		if (singleton->charState == E_CHAR_STATE_RENDERED) {
			
			
			
			
			if (  (gphEnt->childrenDirty)&&(singleton->entOn)  ) {
				
				// TOOD: this must be called before other pages or potential crash from lack of memory to alloc
				//transformEnt(singleton->testHuman);
				
				
				gphEnt->refreshGeom();
				gphEnt->refreshChildren(true);
				
				
			}
		}
		

		singleton->bindShader("BlitShader");

		for (k = 0; k < MAX_LAYERS*2; k++)
		{
			
			
			j = k % MAX_LAYERS;
			entPass = k >= MAX_LAYERS;

			if (entPass) {
				if (j == 0)
				{
					singleton->bindFBO("pages3FBO");
				}
				else
				{
					singleton->bindFBO("water3FBO");
				}
			}
			else {
				if (j == 0)
				{
					singleton->bindFBO("pages2FBO");
				}
				else
				{
					singleton->bindFBO("water2FBO");
				}
			}

			


			singleton->setShaderFloat("zOffset",0.0f);

			for (i = 0; i < ppSize; i++)
			{
				cid = singleton->gpuPool->orderedIds[i];

				if ( pairIsNeg(cid) )
				{

				}
				else
				{
					gp = getHolderAtId(cid);

					if (gp == NULL)
					{

					}
					else
					{

						switch (action)
						{
						case E_HOLDER_ACTION_RENDER:
							if (
								(cutHolderPos.getFX() - 1.0f < gp->offsetInHolders.getFX()) &&
								(cutHolderPos.getFY() - 1.0f < gp->offsetInHolders.getFY()) &&
								(cutHolderPos.getFZ() - 1.0f < gp->offsetInHolders.getFZ())


							)
							{

							}
							else
							{
								
								if ( ((j == 0) && gp->hasSolids) || ((j == 1) && gp->hasTrans) )
								{

									//cout << "drawHolder\n";

									//if ( gp->offsetInHolders.inBoundsXYZ(&minLRInHolders,&maxLRInHolders) ) {
									drawHolder(gp, j, 0.0f, 0.0f, 0.0f);
									//}

								}
								
								
								
							}
							break;
						case E_HOLDER_ACTION_RESET:
						
							gp->refreshChildren(instantRefresh, clearEverything);
						
							
							break;
						}


					}
				}
			}
			
			
			if (singleton->charState == E_CHAR_STATE_RENDERED) {
				
				
				if (entPass) {
					switch (action)
					{
					case E_HOLDER_ACTION_RENDER:
						
						singleton->setShaderFloat("zOffset",activeEnt->basePosition[2]);
						
						
						if ( ((j == 0) && gphEnt->hasSolids) || ((j == 1) && gphEnt->hasTrans) )
						{
							
							if (singleton->entOn) {
								drawHolder(
									gphEnt,
									j,
									activeEnt->basePosition[0],
									activeEnt->basePosition[1],
									activeEnt->basePosition[2]
								);
							}
							

						}
						
						
						break;
					case E_HOLDER_ACTION_RESET:
						if (singleton->entOn) {
							gphEnt->refreshChildren(true);							
						}
						break;
					}
					
					
				}
				
			}



			singleton->unbindFBO();
		}

		singleton->unbindShader();


		//doTrace( "POSSIBLE ERROR: " , i__s(glGetError()) , "\n" );

		//popTrace();
	}



	// todo: render with display list

	void drawHolder(
		GamePageHolder *gp,
		int curLayer,
		float xoff,
		float yoff,
		float zoff
	)
	{
		//pushTrace("drawHolder()");


		float dx = gp->offsetInHolders.getFX();
		float dy = gp->offsetInHolders.getFY();
		float dz = gp->offsetInHolders.getFZ();

		float pitchSrc = (float)((singleton->holderSizeInPixels * 2.0f));
		float pitchSrc2 = pitchSrc / 2.0f;

		float itilt = 1.0-singleton->tiltAmount;
		float tilt = singleton->tiltAmount;

		float dxmod = dx * pitchSrc2 + xoff - cameraPos->getFX();
		float dymod = dy * pitchSrc2 + yoff - cameraPos->getFY();
		float dzmod = dz * pitchSrc2 + zoff - cameraPos->getFZ();


		// float tilt = 1.0-singleton->tiltAmount;
		
		// float fx1 = (dxmod - dymod);
		// //float fy1 = (-(dxmod / 2.0f) + -(dymod / 2.0f) + dzmod) - pitchSrc2;
		// float fy1 = (-tilt*dxmod + -tilt*dymod + (1.0-tilt)*2.0f*dzmod);


		tempVec2.setFXYZ(dxmod,dymod,dzmod);
		singleton->worldToScreenBase(&tempVec1,&tempVec2);
		float fx1 = tempVec1.getFX();
		float fy1 = tempVec1.getFY();
		
		pitchSrc /= singleton->fHolderMod;
		pitchSrc2 /= singleton->fHolderMod;

		fy1 -= (0.5-tilt)*pitchSrc;

		fx1 -= pitchSrc2;
		fy1 -= pitchSrc2;
		float fx2 = fx1 + pitchSrc;
		float fy2 = fy1 + pitchSrc;




		// TODO: should be baseW/H?

		float sx = singleton->bufferDim.getFX();
		float sy = singleton->bufferDim.getFY();

		float myZoom = std::min(1.0f, singleton->cameraZoom);


		fx1 = fx1 * (myZoom) / sx;
		fy1 = fy1 * (myZoom) / sy;
		fx2 = fx2 * (myZoom) / sx;
		fy2 = fy2 * (myZoom) / sy;


		if (gp->gpuRes != NULL)
		{
			singleton->sampleFBODirect(gp->gpuRes->getFBOS(curLayer));


			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);


			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(fx1, fy1, 0.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(fx2, fy1, 0.0f);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(fx2, fy2, 0.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(fx1, fy2, 0.0f);

			glEnd();

			singleton->unsampleFBODirect(gp->gpuRes->getFBOS(curLayer));
		}




		//popTrace();

	}


	void combineHolders()
	{
		
		int i;
		
		
		bool entOff = false;
		
		
		if (entOff) {
			singleton->copyFBO("pages2FBO", "pagesFBO");
			singleton->copyFBO("water2FBO", "waterFBO");
		}
		else {
			singleton->bindShader("CombineShader");
			for (i = 0; i < 2; i++) {

				if (i == 0) {
					singleton->bindFBO("pagesFBO");
					singleton->sampleFBO("pages2FBO", 0);
					singleton->sampleFBO("pages3FBO", 2);
				}
				else {
					singleton->bindFBO("waterFBO");
					singleton->sampleFBO("water2FBO", 0);
					singleton->sampleFBO("water3FBO", 2);
				}
				

				singleton->drawFSQuad(1.0f);

				if (i == 0) {
					singleton->unsampleFBO("pages3FBO", 2);
					singleton->unsampleFBO("pages2FBO", 0);
				}
				else {
					singleton->unsampleFBO("water3FBO", 2);
					singleton->unsampleFBO("water2FBO", 0);
				}

				singleton->unbindFBO();
				
				
			}
			singleton->unbindShader();
		}
		
		
		
		
		
	}


	void combineBuffers()
	{

		singleton->bindShader("CombineShader");
		singleton->bindFBO("combineFBO");

		singleton->sampleFBO("pagesFBO", 0);
		singleton->sampleFBO("geomFBO", 2);

		singleton->drawFSQuad(1.0f);

		singleton->unsampleFBO("geomFBO", 2);
		singleton->unsampleFBO("pagesFBO", 0);

		singleton->unbindFBO();
		singleton->unbindShader();
	}




	void transformEnt(GameEnt* curEnt) {
		
		// GameEntNode* curNode = NULL;
		
		// curNode = curEnt->baseNode->getNode(E_BONE_L_UPPERARM);
		// curNode->rotThe = sin(singleton->curTime/1000.0f)*3.14159f * 0.25f;
		
		// curNode = curNode->getNode(E_BONE_L_LOWERARM);
		// curNode->rotThe = sin(singleton->curTime/1000.0f)*3.14159f * 0.25f;
		// curNode->rotPhi = sin(singleton->curTime/1000.0f)*3.14159f * 2.0f;
		
		curEnt->baseNode->doTransform(singleton);
	}


	void drawEnt(GameEnt* curEnt, bool drawAll) {
		
		
		float scale = 1.0f*((float)(singleton->pixelsPerMeter));
		
		
		glLineWidth(0);
		
		
		
		// tangents
		singleton->setShaderFloat("matVal", getPackedColor(255, 0, 0));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 0, drawAll);
		
		// bitangents
		singleton->setShaderFloat("matVal", getPackedColor(0, 255, 0));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 1, drawAll);
		
		// normals
		singleton->setShaderFloat("matVal", getPackedColor(0, 0, 255));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 2, drawAll);
		
		if (drawAll) {
			// nodes
			singleton->setShaderFloat("matVal", getPackedColor(254, 254, 254));
			drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 3, drawAll);
		}
		
		
		
	}


	void drawNodeEnt(
		GameEntNode* curNode,
		FIVector4* basePosition,
		float scale,
		int drawMode,
		bool drawAll
	) {
		
		// if (curNode == singleton->selectedNode) {
		// 	glLineWidth(3);
		// }
		// else {
		// 	glLineWidth(0);
		// }
		
		bool doProc = false;
		
		if (drawAll) {
			doProc = true;
		}
		else {
			if (curNode == singleton->selectedNode) {
				doProc = true;
			}
		}
		
		int i;
		
		
		if (doProc) {
			lineSeg[0].setFXYZRef(&(curNode->orgTrans[0]));
			lineSeg[0].multXYZ(  scale  );
			
			if (drawAll) {
				lineSeg[1].setFXYZRef(&(curNode->tbnTrans[drawMode%3]));
				lineSeg[1].multXYZ(  scale  );
			}
			else {
				lineSeg[1].setFXYZRef(&(curNode->tbnRotC[drawMode%3]));
				lineSeg[1].multXYZ(  (curNode->tbnRadInMeters0[drawMode%3]*scale*16.0f)  );
				lineSeg[1].multXYZ(&(curNode->tbnRadScale0));
				lineSeg[1].addXYZRef(&(lineSeg[0]));
			}
			
			
			lineSeg[0].addXYZRef(basePosition);
			lineSeg[1].addXYZRef(basePosition);
			
			
			
			switch(drawMode) {
				case 0: // tangents
				case 1: // bitangents
				case 2: // normals
					singleton->drawLine(&(lineSeg[0]),&(lineSeg[1]));
				break;
				case 3: // nodes
					singleton->drawCubeCentered(&(lineSeg[1]),0.0125f*scale);
				break;
				
			}
		}
		
		
		for (i = 0; i < curNode->children.size(); i++) {
			drawNodeEnt(curNode->children[i], basePosition, scale, drawMode, drawAll);
		}
		
	}














	void clearVisitedPaths(PathHolder* pathHolder) {
		while (pathHolder->visitedList.size() > 0) {
			blockData[
				pathHolder->visitedList.back().blockId
			]->buildingData[
				pathHolder->visitedList.back().index
			].visited = 0;
			pathHolder->visitedList.pop_back();
		}
	}

	
	
	void clearPathList(PathHolder* pathHolder) {
		pathHolder->pathList.clear();
	}
	
	float getIdealPathLength(PathNode* blockAndIndex) {
		return 		
			abs(blockAndIndex[0].x-blockAndIndex[1].x) +
			abs(blockAndIndex[0].y-blockAndIndex[1].y) +
			abs(blockAndIndex[0].z-blockAndIndex[1].z);
	}

	int findAIPathRBT(
		PathHolder* pathHolder,
		PathNode* blockAndIndex,
		float _pathSlack
	) {


		//int begInd, int endInd

		float pathSlack = _pathSlack;

		int i;
		//int rbInd = 0;
		PathNode curInd;

		int testX = 0;
		int testY = 0;
		int testZ = 0;
		
		int wrappedX;
		int wrappedY;
		int wrappedZ;

		int curX = 0;
		int curY = 0;
		int curZ = 0;
		
		float idealPathLength = getIdealPathLength(blockAndIndex);
		
		int bestBlockId;
		int bestX;
		int bestY;
		int bestZ;
		int bestInd = 0;

		int testInd = 0;
		int curDir = 0;
		

		int endZ = blockAndIndex[1].z;
		int endY = blockAndIndex[1].y;
		int endX = blockAndIndex[1].x;
		
		int terDataVisPitchXY = singleton->terDataVisPitchXY;
		
		int conType;
		
		int pathCost;
		int bestCost;
		int invalidCost = 1<<30;

		int maxPops;

		PathNode tempNode;

		
		
		
		int numPathSteps = 0;
		
		
		
		//cout << "\n\n\nSTART COORD " << blockAndIndex[0].x << " " << blockAndIndex[0].y << " " << blockAndIndex[0].z << "\n";
		//cout << "END COORD " << blockAndIndex[1].x << " " << blockAndIndex[1].y << " " << blockAndIndex[1].z << "\n";
		

		BuildingNode* curBuildingData;
		GameBlock* testBlock;

		while ( (pathHolder->pathList.size() > 0) ) { // && (numPathSteps < 10)
			
			numPathSteps++;
			bestInd = -1;
			bestCost = invalidCost;

			curInd = pathHolder->pathList.back();
			
			
			
			if (curInd == blockAndIndex[1]) {
				goto DONE_FINDING_PATH;
			}
			
			//cout << "curBlockId " << curInd.blockId << "\n";
			
			curBuildingData = &(blockData[curInd.blockId]->buildingData[curInd.index]); 
			curBuildingData->visited = 1;
			pathHolder->visitedList.push_back(curInd);
			
			
			if (pathHolder->pathList.size() > idealPathLength*pathSlack) {
				cout << "Exceeded Path Slack\n";
				return false;
			}
				
			// 	maxPops = pathHolder->pathList.size() / 2;
			// 	pathSlack *= 1.1f;
				
			// 	if (pathSlack > 5.0f) {
			// 		cout << "Exceeded max path length\n";
			// 		return false;
			// 	}
				
			// 	for (i = 0; i < maxPops; i++) {
					
			// 		if (i < maxPops/2) {
			// 			blockData[
			// 				pathHolder->pathList.back().blockId
			// 			]->buildingData[
			// 				pathHolder->pathList.back().index
			// 			].visited = 0;
			// 		}
					
					
			// 		pathHolder->pathList.pop_back();
			// 	}
				
			// 	goto SKIP_PATH;
			
			

			curZ = curInd.z;
			curY = curInd.y;
			curX = curInd.x;

			
			for (curDir = 0; curDir < 4; curDir++) {


				testX = curX + dirModX[curDir];
				testY = curY + dirModY[curDir];
				testZ = curZ + dirModZ[curDir] + curBuildingData->con[curDir].heightDelta;
				
				
				wrappedX = (wrapCoord(testX,terDataVisPitchXY*worldSizeInBlocks.getIX())%terDataVisPitchXY)+singleton->terDataBufAmount;
				wrappedY = (wrapCoord(testY,terDataVisPitchXY*worldSizeInBlocks.getIY())%terDataVisPitchXY)+singleton->terDataBufAmount;
				wrappedZ = testZ+singleton->terDataBufAmount;
				
				testBlock = getBlockAtCoords(
					intDiv(testX,terDataVisPitchXY),
					intDiv(testY,terDataVisPitchXY),
					true
				);
				
				
				if (testBlock != NULL) {
					testInd = testBlock->getNodeIndex(wrappedX, wrappedY, wrappedZ, 0);

					if (testInd >= 0) {

						conType = curBuildingData->con[curDir].conType;
						
						//cout << "conType " << conType << " visited " << testBlock->buildingData[testInd].visited << "\n";
						
						if (
							( testBlock->isTraversable[conType] ) &&
							( testBlock->buildingData[testInd].visited == 0 )
						) {
							
							
							pathCost = abs(testX-endX) + abs(testY-endY) + abs(testZ-endZ);

							//cout << "pathCost " << pathCost << " bestCost " << bestCost << "\n";

							if (pathCost < bestCost) {
								bestInd = testInd;
								bestBlockId = testBlock->blockId;
								bestCost = pathCost;
								bestX = testX;
								bestY = testY;
								bestZ = testZ;
							}
						}
					}
				}
				
				
			}


			
			if (bestInd == -1) { // dead end, back up
				pathHolder->pathList.pop_back();
				
				//cout << "pop_back\n";
				//cout << "new length: " << pathHolder->pathList.size() << "\n\n";
			} else {
				tempNode.index = bestInd;
				tempNode.blockId = bestBlockId;
				tempNode.x = bestX;
				tempNode.y = bestY;
				tempNode.z = bestZ;
				pathHolder->pathList.push_back(tempNode);
				
				//cout << bestInd << " " << bestBlockId << " " << bestX << " " << bestY << " " << bestZ << "\n\n";
				
			}

SKIP_PATH:
			;
			
			

		}
		
DONE_FINDING_PATH:
		;
		
		return pathHolder->pathList.size() > 0;

	}


	void drawPathLine(PathHolder* curPath, int r, int g, int b, float lw, float zoff) {
		// IMPORTANT: size is a uint, do not let underflow happen!
		int totSize = curPath->pathList.size();
		totSize -= 1;
		int i;
		
		glLineWidth(lw);
		
		singleton->setShaderFloat("matVal", getPackedColor(r,g,b));
		for (i = 0; i < totSize; i++) {
			blockData[curPath->pathList[i].blockId]->nodeIndexToWorldSpaceInPixels(curPath->pathList[i].index, &(lineSeg[0]));
			blockData[curPath->pathList[i+1].blockId]->nodeIndexToWorldSpaceInPixels(curPath->pathList[i+1].index, &(lineSeg[1]));
			lineSeg[0].addXYZ(0.0f,0.0f,zoff);
			lineSeg[1].addXYZ(0.0f,0.0f,zoff);
			singleton->drawLine(&(lineSeg[0]),&(lineSeg[1]));
		}
	}

	void drawAIPath(PathHolder* pathHolder, PathHolder* splitPathHolder) {
		
		
		
		
		int i;
		int curStep = singleton->currentStep;
		int curInd;
		int totSize;
		bool pathResult;
		bool doCont;
		
		float maxSlack = 8.0f;
		
		int numDivisions;
		int splitSize = 100;
		
		//int terDataBufPitchXY2 = singleton->terDataBufPitchXY*singleton->terDataBufPitchXY;
		//int endSegInd;
		
		// 0 - nothing
		// 1 - first marker placed
		// 2 - second marker placed
		// 3 - clear markers
		
		
		singleton->setShaderFloat("isWire", 0.0f);
		for (i = 0; i < curStep; i++) {
			
			blockPos[i].copyFrom(&(singleton->moveNodes[i]));
			blockPos[i].intDivXYZ(singleton->blockSizeInPixels);
			blockRef[i] = getBlockAtCoords(blockPos[i].getIX(), blockPos[i].getIY(), true);
			nodeInd[i] = blockRef[i]->findNearestNode(
				&(singleton->moveNodes[i]),
				&(nodePos[i]),
				&(nodePosInPixels[i])
			);
			blockAndIndexPath[i].index = nodeInd[i];
			blockAndIndexPath[i].blockId = blockRef[i]->blockId;
			blockAndIndexPath[i].x = nodePos[i].getIX();
			blockAndIndexPath[i].y = nodePos[i].getIY();
			blockAndIndexPath[i].z = nodePos[i].getIZ();
			
			singleton->setShaderFloat("matVal", getPackedColor(i*255, (1-i)*255, 0));
			singleton->drawCubeCentered(
				&(nodePosInPixels[i]),
				1.0f * singleton->pixelsPerMeter
			);
		}
		
		
		
		if (curStep == 2) {
			
			if (!foundPath) {
				
				finalPath = NULL;
				foundPath = true;
				
				if (
					//(blockRef[0] == blockRef[1]) &&
					(nodeInd[0] != -1) &&
					(nodeInd[1] != -1)
				) {
					
					clearVisitedPaths( pathHolder );
					clearPathList( pathHolder );
					clearVisitedPaths( splitPathHolder );
					clearPathList( splitPathHolder );
					
					
					pathHolder->pathList.push_back(blockAndIndexPath[0]);
					
					pathResult = findAIPathRBT(
						pathHolder,
						blockAndIndexPath,
						maxSlack
					);
					
					clearVisitedPaths( pathHolder );
					if (pathResult) {
						finalPath = pathHolder;
					}
					
					
					
					// if (pathResult) {	
					// 	numDivisions = pathHolder->pathList.size()/splitSize;
					// 	if (
					// 		(numDivisions >= 2) &&
					// 		(pathHolder->pathList.size() > getIdealPathLength(blockAndIndexPath)*1.5f)
					// 	) {
							
					// 		cout << "splitting path " << numDivisions << " times\n";
					// 		cout << "total path size is " << pathHolder->pathList.size() << "\n";
							
							
					// 		splitPathHolder->pathList.push_back(blockAndIndexPath[0]);
							
							
					// 		i = 0;
					// 		doCont = true;
					// 		while (doCont) {
					// 			blockAndIndexSplitPath[0] = pathHolder->pathList[i*splitSize];
								
								
					// 			cout << "split number " << i << "\n";
								
					// 			if ( (i+1)*splitSize >= pathHolder->pathList.size() ) {
					// 				blockAndIndexSplitPath[1] = pathHolder->pathList.back();
					// 				doCont = false;
					// 			}
					// 			else {
					// 				blockAndIndexSplitPath[1] = pathHolder->pathList[(i+1)*splitSize];
					// 			}
								
									
					// 			pathResult = findAIPathRBT(
					// 				splitPathHolder,
					// 				blockAndIndexSplitPath,
					// 				maxSlack
					// 			);
								
					// 			if (pathResult) {
									
					// 			}
					// 			else {
					// 				doCont = false;
					// 				cout << "Failed to find path at split #" << i << "\n";
					// 			}
								
					// 			i++;
								
					// 		}
							
					// 		finalPath = splitPathHolder;
							
					// 	}
						
					// }
					
				
					cout << "DONE FINDING PATH\n";
					
					//finalInd = blockRef[0]->findPath(nodeInd[0],nodeInd[1]);
					//doTraceND("finalInd ", i__s(finalInd), " nodeInd ", i__s(nodeInd[0]), " ", i__s(nodeInd[1]));
				}
				else {
					// doTraceND("Different Blocks");
				}
				
			}
			
		}
		else {
			foundPath = false;
			//finalInd = -1;
		}
		
		
		if ( (finalPath != NULL) && foundPath) {
			drawPathLine(pathHolder, 255, 255, 0, 2.0f, 0.0f);
			drawPathLine(splitPathHolder, 255, 0, 0, 2.0f, 4.0f*((float)singleton->pixelsPerMeter));
		}
		
		
		
		
	}

	void renderGeom()
	{
		//pushTrace("renderGeom()");

		int i;
		bool doProc;


		//glEnable(GL_DEPTH_TEST);

		singleton->bindShader("GeomShader");

		singleton->setShaderFloat("objectId",0.0);
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
		singleton->setShaderFloat("curTime", singleton->curTime);
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
		

		singleton->bindFBO("geomFBO");
		//singleton->sampleFBO("pagesFBO");


		glEnable(GL_DEPTH_TEST);
		//remember 2x radius

		

		// if (!(singleton->entOn)) {
		// 	if (singleton->bShift) {
		// 		singleton->setShaderFloat("isWire", 1.0);
		// 		singleton->setShaderFloat("matVal", getPackedColor(255,0,255));
				
		// 		singleton->drawBox(&minLRInPixels,&maxLRInPixels);
		// 	}
		// }
		
		
		singleton->setShaderFloat("isWire", 0.0);

		switch (singleton->mouseState)
		{

		case E_MOUSE_STATE_MOVE:

			if (singleton->gridOn == 1.0f)
			{
				// singleton->setShaderFloat("matVal", getPackedColor(255, 0, 255));
				// singleton->setShaderFloat("isWire", 1.0f);
				// singleton->drawBox(&minLRInPixels, &maxLRInPixels);
			}
			
			
			

			break;
		
		case E_MOUSE_STATE_BRUSH:
			singleton->setShaderFloat("matVal", getPackedColor(255, 0, 0));
			singleton->setShaderFloat("isWire", 1.0);
			singleton->drawCubeCentered(&lastUnitPos, ((int)singleton->curBrushRad) * (singleton->unitSizeInPixels)  );
			glClear(GL_DEPTH_BUFFER_BIT);
		break;
		// case E_MOUSE_STATE_OBJECTS:



			



		// 	break;
		case E_MOUSE_STATE_PICKING:
			// singleton->setShaderFloat("matVal", getPackedColor(0,255,0));
			// singleton->drawBoxUp(lastUnitPos, 0.25f*singleton->pixelsPerMeter, 0.25f*singleton->pixelsPerMeter, 2.0f*singleton->pixelsPerMeter);



			if (singleton->highlightedGeom == NULL)
			{

			}
			else
			{
				singleton->setShaderFloat("matVal", getPackedColor(254, 254, 254));
				singleton->setShaderFloat("isWire", 1.0);

				minv.setFXYZRef(singleton->highlightedGeom->getVisMinInPixelsT());
				maxv.setFXYZRef(singleton->highlightedGeom->getVisMaxInPixelsT());

				minv.addXYZ(-0.25 * singleton->pixelsPerMeter);
				maxv.addXYZ(0.25 * singleton->pixelsPerMeter);


				singleton->drawBox(&minv, &maxv);
			}

			if (singleton->selectedGeom == NULL)
			{

			}
			else
			{
				singleton->setShaderFloat("matVal", getPackedColor(255, 255, 0));
				singleton->setShaderFloat("isWire", 1.0);

				minv.setFXYZRef(singleton->selectedGeom->getVisMinInPixelsT());
				maxv.setFXYZRef(singleton->selectedGeom->getVisMaxInPixelsT());

				// minv.addXYZ(-0.25 * singleton->pixelsPerMeter);
				// maxv.addXYZ(0.25 * singleton->pixelsPerMeter);


				singleton->drawBox(&minv, &maxv);
			}


			break;

		}
		
		if (singleton->pathfindingOn) {
			drawAIPath( &(singleton->charPathHolder), &(singleton->splitPathHolder) );
		}
		
		if (singleton->bCtrl) {
			for (i = 1; i < singleton->dynObjects.size(); i++) {
				if (singleton->dynObjects[i]->doRender)
				{

					doProc = false;

					if (i >= E_OBJ_LIGHT0)
					{
						if (i - E_OBJ_LIGHT0 < singleton->numDynLights)
						{
							doProc = true;
						}
					}
					else
					{
						doProc = true;
					}

					if (doProc)
					{
						singleton->setShaderFloat("objectId",i);
						singleton->setShaderFloat("matVal", singleton->dynObjects[i]->colPacked);
						curBoxPos = &(singleton->dynObjects[i]->pos);
						singleton->drawCubeCentered(curBoxPos, singleton->dynObjects[i]->radius);


						if (i == singleton->activeObject)
						{
							//singleton->drawCrossHairs(singleton->dynObjects[i]->pos,4.0f);
						}
					}


				}
			}
		}

		singleton->setShaderFloat("objectId",0.0);

		if (singleton->charState == E_CHAR_STATE_RENDERED) { //E_CHAR_STATE_SKEL
			//transformEnt(singleton->testHuman);
			drawEnt(singleton->testHuman, false);
		}
		


		// for (i = 1; i < lightCount; i++) {
		//  singleton->setShaderFloat("matVal", activeLights[i]->colPacked);
		//  curBoxPos = &(activeLights[i]->pos);
		//  singleton->drawCubeCentered(curBoxPos,0.125f*singleton->pixelsPerMeter);
		// }



		glDisable(GL_DEPTH_TEST);



		//singleton->unsampleFBO("pagesFBO");
		singleton->unbindFBO();
		singleton->unbindShader();

		//glDisable(GL_DEPTH_TEST);

		//popTrace();

	}


	void modifyUnit(FIVector4 *fPixelWorldCoordsBase, E_BRUSH brushAction)
	{
		
		//pushTrace("modifyUnit()");

		int radius = ((int)singleton->curBrushRad);

		FIVector4 fPixelWorldCoords;
		fPixelWorldCoords.copyFrom(fPixelWorldCoordsBase);


		uint *vd_ptr;
		uint *vdl_ptr;

		GamePage *curPage;


		int ind2;
		int pageSizeMult = visPageSizeInUnits * (singleton->bufferMult);


		int i, j, k, m, n, o, p;

		int ii;
		int jj;
		int kk;

		int pixelPS = (singleton->unitSizeInPixels * singleton->visPageSizeInUnits);



		lastUnitPos.copyFrom(&fPixelWorldCoords);
		lastUnitPos.intDivXYZ(singleton->unitSizeInPixels);
		lastUnitPos.multXYZ(singleton->unitSizeInPixels);
		lastUnitPos.setFW(singleton->unitSizeInPixels);
		
		
		

		lastPagePos.copyFrom(&fPixelWorldCoords);
		lastPagePos.intDivXYZ(pixelPS);
		lastPagePos.multXYZ(pixelPS);
		lastPagePos.setFW(pixelPS);

		bool changes = false;

		int newRad = 2 + radius / visPageSizeInUnits;


		uint linV;
		uint nearV;

		uint linR;
		uint linG;
		uint linB;
		uint linA;

		uint nearR;
		uint nearG;
		uint nearB;
		uint nearA;

		bool isInside;
		
		
		
		
		


		pagePos.copyFrom(&fPixelWorldCoords);
		unitPos.copyFrom(&fPixelWorldCoords);

		pagePos.intDivXYZ( pixelPS );
		unitPos.intDivXYZ( singleton->unitSizeInPixels );


		unitPosMin.copyFrom(&unitPos);
		unitPosMax.copyFrom(&unitPos);
		unitPosMin.addXYZ((float)radius, -1.0f);
		unitPosMax.addXYZ((float)radius, 1.0f);

		unitPosCenter.copyFrom(&unitPosMin);
		unitPosCenter.addXYZRef(&unitPosMax);
		unitPosCenter.multXYZ(0.5f);
		
		
		float unitPosRad = (unitPosMax.getFX()-unitPosMin.getFX())*0.5f;
		float unitPosCurDis = 0.0f;
		
		FIVector4 blockPos;
		blockPos.copyFrom(&pagePos);
		blockPos.intDivXYZ(singleton->blockSizeInPages);
		GameBlock *curBlock = getBlockAtCoords(blockPos.getIX(),blockPos.getIY(),true);


		// unitPosMinIS.copyFrom(&unitPos);
		// unitPosMaxIS.copyFrom(&unitPos);
		// unitPosMinIS.addXYZ((float)radius+1, -1.0f);
		// unitPosMaxIS.addXYZ((float)radius-1, 1.0f);


		if (brushAction == E_BRUSH_MOVE)
		{
			//popTrace();
			return;
		}
		
		cout << "modifyUnit\n";

		if (singleton->isMacro) {
			
			curBlock->modifyTerrain(
				&fPixelWorldCoords,
				brushAction == E_BRUSH_SUB
			);
			
		}

		


		for (m = 0; m < 2; m++)
		{
			for (i = -newRad; i <= newRad; i++)
			{
				for (j = -newRad; j <= newRad; j++)
				{
					for (k = -newRad; k <= newRad; k++)
					{




						ii = i + pagePos.getIX();
						jj = j + pagePos.getIY();
						kk = k + pagePos.getIZ();
						
						

						if (
							checkBounds(kk,worldSizeInPages.getIZ())
							
						)
						{

							//

							curPage = getPageAtCoords(ii, jj, kk, true);


							if (true) {


								startBounds.maxXYZ(&unitPosMin, &(curPage->worldUnitMin));
								endBounds.minXYZ(&unitPosMax, &(curPage->worldUnitMax));




								




								if (
									(startBounds.getFX() > endBounds.getFX()) ||
									(startBounds.getFY() > endBounds.getFY()) ||
									(startBounds.getFZ() > endBounds.getFZ())
								)
								{

								}
								else
								{




									for (n = startBounds.getIX(); n < endBounds.getIX(); n++)
									{
										for (o = startBounds.getIY(); o < endBounds.getIY(); o++)
										{
											for (p = startBounds.getIZ(); p < endBounds.getIZ(); p++)
											{
												
												
												

												tempVec.setIXYZ(n, o, p);
												isInside = tempVec.inBoundsXYZ(&unitPosMin, &unitPosMax);

												unitPosCurDis = unitPosCenter.distance(&tempVec);

												//TODO: fix this to wrap
												if (
													tempVec.inBoundsXYZ(
														&(curPage->worldUnitMin),
														&(curPage->worldUnitMax)
													) &&
													(
														unitPosCurDis < unitPosRad
													)
												)
												{
													tempVec.addXYZRef( &(curPage->worldUnitMin), -1.0);

													ind2 = tempVec.getIZ() * pageSizeMult * pageSizeMult + tempVec.getIY() * pageSizeMult + tempVec.getIX();

													if (
														(ind2 < 0) ||
														(ind2 >= pageSizeMult * pageSizeMult * pageSizeMult)
													)	{
														// index out of range	
														cout << "index out of range\n";
													}
													else
													{

														if (m == 0)
														{

															
															
															if (singleton->isMacro) {
																
															}
															else {
																vd_ptr = curPage->getVolData();
																vdl_ptr = curPage->getVolDataLinear();

																linV = vdl_ptr[ind2];
																nearV = vd_ptr[ind2];

																linR = (linV) & 255;
																linG = (linV >> 8) & 255;
																linB = (linV >> 16) & 255; // used for subtraction
																linA = (linV >> 24) & 255; // used for addition

																nearR = (nearV) & 255;
																nearG = (nearV >> 8) & 255;
																nearB = (nearV >> 16) & 255;
																nearA = (nearV >> 24) & 255;


																if (p >= singleton->worldSizeInUnits.getFZ()) {

																	linA = 0;
																}
																else
																{

																	if (brushAction == E_BRUSH_SUB) {
																		if (isInside)
																		{
																			linA = 0;
																			//linB = 255;
																			
																			linB += 40;
																			if (linB > 255) {
																				linB = 255;
																			}
																			
																			// (tex2.b > 0.5)
																			// 1.0 = nothing
																			// 0.0 = solid
																			// linB = clampf(
																				
																			// 	(unitPosCurDis/unitPosRad - unitPosCurDis/(unitPosRad+1)),
																			// 	0.0f,
																			// 	1.0f
																			// )*255.0f;
																		}

																	}
																	else
																	{

																		if (isInside)
																		{
																			//linA = 255;
																			linA += 40;
																			if (linA > 255) {
																				linA = 255;
																			}
																			linB = 0;
																		}

																		nearA = 0;

																	}
																}

																vd_ptr[ind2] = (nearA << 24) | (nearB << 16) | (nearG << 8) | (nearR);
																vdl_ptr[ind2] = (linA << 24) | (linB << 16) | (linG << 8) | (linR);
																curPage->volDataModified = true;	
															}

															curPage->parentGPH->childrenDirty = true;
															curPage->isDirty = true;
															changes = true;
														}
														else
														{
															if (curPage->parentGPH->childrenDirty)
															{
																curPage->parentGPH->refreshChildren(true,true,true);
															}
														}

													}

												}


											}
										}
									}
								}
							}

						}




					}
				}
			}
		}
		
		if (changes)
		{
			singleton->changesMade = true;
			singleton->wsBufferInvalid = true;
		}



		//popTrace();

	}


	void renderWorldSpaceGPU()
	{
		singleton->bindShader("WorldSpaceShader");

		singleton->bindFBO("worldSpaceFBO");
		singleton->sampleFBO("pagesFBO", 0);
		singleton->sampleFBO("waterFBO", 2);
		singleton->sampleFBO("geomFBO", 4);

		//MUST BE CALLED AFTER FBO IS BOUND
		
		singleton->setShaderInt("iMax", 4);
		singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
		singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim) );
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);

		singleton->drawFSQuad(1.0f);

		
		singleton->unsampleFBO("geomFBO", 4);
		singleton->unsampleFBO("waterFBO", 2);
		singleton->unsampleFBO("pagesFBO", 0);


		singleton->unbindFBO();
		singleton->unbindShader();
		
		
	}

	void getWorldSpaceBuffer(int bufNum = 0)
	{

		if (singleton->autoScroll) {
			
		}
		else {
			singleton->getFBOWrapper("worldSpaceFBO", bufNum)->getPixels();
		}

		singleton->wsBufferInvalid = false;

	}

	float weighPath(float x1, float y1, float x2, float y2, float rad, bool doSet, bool isOcean)
	{

		int i;
		int iMax = (int)min(64.0f, rad * 4.0f);

		float fi;
		float fMax = (float)(iMax - 1);
		float lerp;

		float curX;
		float curY;


		float startVal = curFBO->getPixelAtWrapped((int)x1, (int)y1, hmChannel);
		float lastRes = startVal;
		float curRes;
		float curRes2;
		float tempRes;
		float tot = 0.0f;

		bool startsInWater = startVal <= seaLevel;

		for (i = 1; i < iMax; i++)
		{
			fi = (float)i;
			lerp = fi / fMax;
			curX = (1.0f - lerp) * x1 + (lerp) * x2;
			curY = (1.0f - lerp) * y1 + (lerp) * y2;
			curRes = curFBO->getPixelAtWrapped((int)curX, (int)curY, hmChannel);

			if (isOcean)
			{
				if (doSet)
				{

					if (curRes > seaLevel)
					{

						tempRes = abs(curRes - lastRes);
						tempRes = tempRes * tempRes * tempRes;
						//tempRes = 255-curRes;
					}
					else
					{
						tempRes = curRes;
					}


					//tempRes = abs(curRes-lastRes);
					//tempRes = tempRes*tempRes*tempRes;
					if ((curRes > seaLevel) != (lastRes > seaLevel))
					{
						tempRes += 100000.0f;
					}

					// if (startsInWater) {
					//  if (curRes > seaLevel) {
					//      tempRes += 1000000.0f;
					//  }
					// }

				}
				else
				{
					tempRes = 0.0;
					if (curRes > seaLevel)
					{
						tempRes = 1.0f;
					}
					else
					{
						tempRes = -1.0f;
					}
				}
			}
			else
			{
				tempRes = abs(curRes - lastRes) * 10.0 + curRes;
				//tempRes = tempRes;
				if (curRes <= seaLevel - 20.0f)
				{
					tempRes += 100000.0f;
				}
				if ((curRes > seaLevel) != (lastRes > seaLevel))
				{
					tempRes += 100000.0f;
				}
			}


			tot += tempRes;
			lastRes = curRes;

		}

		return tot;
	}

	float findBestPath(float x1, float y1, float x2, float y2, int generation, int roadIndex, bool doSet, bool isOcean)
	{
		int i;
		int j;

		coordAndIndex baseCoord;
		coordAndIndex bestCoord;
		coordAndIndex testCoord;

		float mpx = (x1 + x2) / 2.0;
		float mpy = (y1 + y2) / 2.0;
		float dis = quickDis(x1, y1, x2, y2);
		float rad = dis / 2.0;
		float mpxTemp;
		float mpyTemp;
		float delta;
		float bestDis;
		float curDis;
		float bestDelta = FLT_MAX;
		float bestX;
		float bestY;
		float genMod;

		int q;
		int p;

		int ibx;
		int iby;
		int ix2;
		int iy2;
		int tot1 = 0;
		int tot2 = 0;
		int iRad;
		int numTries = max((int)(rad), 20);

		if ( (rad < 2.0f) || (generation > 1024) )
		{
			// do manhattan distance

			if (doSet)
			{
				ibx = x1;
				iby = y1;
				ix2 = x2;
				iy2 = y2;


				while (ibx != ix2)
				{
					curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
					if (ibx < ix2)
					{
						ibx++;
					}
					else
					{
						ibx--;
					}
				}
				while (iby != iy2)
				{
					curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
					if (iby < iy2)
					{
						iby++;
					}
					else
					{
						iby--;
					}
				}

				curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
			}
			else
			{

			}

			return 0.0f;

		}



		genMod = 2.0f;

		// if (generation > 32) {
		//  return 0.0f;
		// }




		for (i = 0; i < numTries; i++)
		{
			mpxTemp = mpx + (fGenRand() * dis - rad) / genMod;
			mpyTemp = mpy + (fGenRand() * dis - rad) / genMod;

			delta = weighPath(x1, y1, mpxTemp, mpyTemp, rad / 2.0f, doSet, isOcean);
			delta += weighPath(mpxTemp, mpyTemp, x2, y2, rad / 2.0f, doSet, isOcean);

			if (delta < bestDelta)
			{
				bestDelta = delta;
				bestX = mpxTemp;
				bestY = mpyTemp;
			}

		}



		if (doSet)
		{



			if (generation < 8)
			{

				baseCoord.x = bestX;
				baseCoord.y = bestY;
				baseCoord.index = roadIndex;
				//roadCoords.push_back(baseCoord);

				bestDis = FLT_MAX;
				for (i = 0; i < roadCoords.size(); i++)
				{
					testCoord = roadCoords[i];


					if (baseCoord.index == testCoord.index)
					{

					}
					else
					{
						curDis = coordDis(&baseCoord, &testCoord);

						if (curDis < bestDis)
						{
							bestDis = curDis;
							bestCoord = roadCoords[i];
						}
					}


				}

				if (bestDis != FLT_MAX)
				{
					curDis = coordDis(&bestCoord, &baseCoord);

					if (curDis < min(400.0f, rad) )   //
					{
						baseCoord = bestCoord;
						baseCoord.index = roadIndex;
					}

					bestX = baseCoord.x;
					bestY = baseCoord.y;
				}

				roadCoords.push_back(baseCoord);
			}


			//curFBO2->setPixelAtWrapped((int)bestX, (int)bestY, pathChannel, 255);
			//curFBO2->setPixelAtWrapped((int)bestX, (int)bestY, breadCrumbChannel, 255);
			findBestPath(x1, y1, bestX, bestY, generation + 1, roadIndex, doSet, isOcean);
			findBestPath(bestX, bestY, x2, y2, generation + 1, roadIndex, doSet, isOcean);
		}

		return bestDelta;

	}

	void initMap()
	{
		mapLockOn = true;

		//pushTrace("initMap()");

		mapSwapFlag = 0;

		mapStep = 0.0f;



		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBO", 0);
		FBOWrapper *fbow2 = singleton->getFBOWrapper("cityFBO", 0);

		curFBO = fbow;
		curFBO2 = fbow2;

		

		FIVector4 startVec;
		FIVector4 endVec;
		FIVector4 midPointVec;

		int w = fbow2->width;
		int h = fbow2->height;


		//0:r
		//1:g
		//2:b
		//3:a




		int i;
		int j;
		int k;
		int m;
		int totSize = w * h;
		int *btStack = new int[totSize];
		int btStackInd = 0;
		int curInd;
		int curX;
		int curY;
		int destX;
		int destY;
		int lastDir;
		int curXRight;
		int curXLeft;
		int curYUp;
		int curYDown;
		int testX;
		int testY;
		int testInd;
		int basePix;
		int basePix2;
		int testPix;
		int testPix1;
		int testPix2;
		int testPix3;
		int testPix4;
		int count;
		int p1;
		int p2;



		// int alleyFlag = 32;
		// int streetFlag = 64;
		// int highwayFlag = 128;

		int startDir;
		int curDir;
		blockMip = intLogB2(singleton->blockSizeInLots);

		int cx1;
		int cy1;
		int cx2;
		int cy2;

		int histogram[256];

		float delta;
		float bestDelta;
		float nextBestDelta;

		int nextBestInd;
		int bestDir;
		int nextBestDir;

		int bestInd;
		int tempVal;

		int xind;
		int yind;
		int curHeight;

		bool isValid;
		bool notFound;
		bool touchesWater;
		bool doBreak;

		float mult;
		float tempDis;





		for (i = 0; i < 16; i++)
		{
			singleton->paramArrMap[i * 3 + 0] = fGenRand();
			singleton->paramArrMap[i * 3 + 1] = fGenRand();
			singleton->paramArrMap[i * 3 + 2] = fGenRand();
		}

		for (i = 0; i < 6; i++)
		{
			singleton->paramArrMap[i * 3 + 0] = i;
		}

		for (i = 0; i < 30; i++)
		{
			p1 = iGenRand(0, 5);
			p2 = iGenRand(0, 5);

			if (p1 != p2)
			{
				tempVal = singleton->paramArrMap[p1];
				singleton->paramArrMap[p1] = singleton->paramArrMap[p2];
				singleton->paramArrMap[p2] = tempVal;
			}
		}



		singleton->bindShader("Simplex2D");
		singleton->bindFBO("simplexFBO");
		singleton->setShaderFloat("curTime", fGenRand() * 100.0f); //singleton->curTime);
		singleton->drawFSQuad(1.0f);
		singleton->unbindFBO();
		singleton->unbindShader();

		singleton->bindShader("TerrainMix");
		singleton->bindFBO("hmFBOLinear");
		singleton->sampleFBO("simplexFBO", 0);
		singleton->setShaderTexture(1, singleton->imageHM0->tid);
		singleton->setShaderTexture(2, singleton->imageHM1->tid);
		singleton->setShaderArrayfVec3("paramArrMap", singleton->paramArrMap, 16 );
		singleton->setShaderFloat("mapSampScale", 1.0f); //singleton->mapSampScale
		singleton->drawFSQuad(1.0f);
		singleton->setShaderTexture(2, 0);
		singleton->setShaderTexture(1, 0);
		singleton->unsampleFBO("simplexFBO", 0);
		singleton->unbindFBO();
		singleton->unbindShader();

		singleton->copyFBO("hmFBOLinear", "hmFBO");


		fbow->getPixels(true);
		fbow->setAllPixels(densityChannel, 255);
		fbow->setAllPixels(idChannel, 0);
		fbow->setAllPixels(blockChannel, 0);


		// determine sea level

		for (i = 0; i < 256; i++)
		{
			histogram[i] = 0;
		}
		
		int minSL = 0;
		int maxSL = 0;
		int curSL = 0;
		int avgSL = 0;
		
		for (i = 0; i < totSize; i++)
		{
			curSL = fbow->getPixelAtIndex(i, hmChannel);
			
			if (curSL < minSL) {
				minSL = curSL;
			}
			if (curSL > maxSL) {
				maxSL = curSL;
			}
			
			histogram[curSL]++;
		}

		int totFilled = 0;
		i = 0;
		while (totFilled < (totSize * 40) / 100 )
		{
			totFilled += histogram[i];
			i++;
		}
		
		avgSL = (minSL*3+maxSL*1)/4;


		seaLevel = i+20; //avgSL;//
		seaSlack = seaLevel - 1;
		cout << "Sea Level: " << seaLevel << "\n";



		cout << "start place cities\n";

		for (i = 1; i < numProvinces; i++)
		{

			isValid = false;

			do
			{

				xind = (int)(fGenRand() * fbow->width);
				yind = (int)(fGenRand() * fbow->height);

				tempVec1.setFXYZ(xind, yind, 0.0f);

				notFound = false;
				for (j = 1; j < i; j++)
				{
					tempVec2.setFXYZ(provinceX[j], provinceY[j], 0.0f);
					tempDis = tempVec2.wrapDistance(&tempVec1, w, false);

					if (tempDis < 200.0f * singleton->mapSampScale)
					{
						notFound = true;
					}

				}

				if (notFound)
				{

				}
				else
				{
					if (fbow->getPixelAtC(xind, yind, idChannel) == 0)
					{
						curHeight = fbow->getPixelAtC(xind, yind, hmChannel);

						if (
							(curHeight > seaLevel)
						)
						{

							provinceX[i] = xind;
							provinceY[i] = yind;
							fbow->setPixelAtC(xind, yind, idChannel, i);
							fbow->setPixelAtC(xind, yind, densityChannel, 0);
							isValid = true;

						}
					}
				}



			}
			while (!isValid);

		}

		cout << "end place cities\n";


		cout << "start grow provinces\n";

		fbow->cpuToGPU();

		singleton->copyFBO("hmFBO", "swapFBO0");
		singleton->bindShader("MapBorderShader");
		mapStep = 0.0f;
		for (i = 0; i < 1024; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->setShaderFloat("seaSlack", ((float)seaSlack) / 255.0 );
			singleton->setShaderFloat("mapStep", mapStep);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();


			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();


		singleton->bindShader("MapBorderShader");
		mapStep = 1.0f;
		for (i = 0; i < 256; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->setShaderFloat("seaSlack", ((float)seaSlack) / 255.0 );
			singleton->setShaderFloat("mapStep", -mapStep);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();


			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();


		singleton->copyFBO("swapFBO0", "hmFBO");


		fbow->getPixels();
		fbow->updateMips();

		cout << "end grow provinces\n";


		cout << "start find neighboring cities\n";

		for (i = 0; i < numProvinces * numProvinces; i++)
		{
			provinceGrid[i] = 0;
		}

		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			basePix = fbow->getPixelAtIndex(curInd, idChannel);

			testPix = fbow->getPixelAtIndex(fbow->getIndex(curX + 1, curY), idChannel);
			testPix2 = fbow->getPixelAtIndex(fbow->getIndex(curX, curY + 1), idChannel);


			if (basePix != 0)
			{
				if (testPix != 0)
				{
					if (basePix != testPix)
					{

						provinceGrid[basePix * numProvinces + testPix] = 1;
						provinceGrid[basePix + testPix * numProvinces] = 1;

					}
				}
				if (testPix2 != 0)
				{
					if (basePix != testPix2)
					{
						provinceGrid[basePix * numProvinces + testPix2] = 1;
						provinceGrid[basePix + testPix2 * numProvinces] = 1;
					}
				}
			}


		}

		cout << "end find neighboring cities\n";




		// 1 - x+
		// 2 - x-
		// 4 - y+
		// 8 - y-


		cout << "start find city blocks\n";


		fbow2->getPixels(true);
		fbow2->setAllPixels(btChannel, 15);
		fbow2->setAllPixels(stChannel, 0);
		fbow2->setAllPixels(pathChannel, 0);
		fbow2->setAllPixels(houseChannel, 0);


		int blockMod = singleton->blockSizeInLots;
		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			basePix = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP);
			testPix = fbow->getMipVal(curX, curY, blockMip, densityChannel, AVG_MIP);

			testPix1 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, -1, 0);
			testPix2 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 1, 0);
			testPix3 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 0, -1);
			testPix4 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 0, 1);



			if (testPix1 != testPix2 || testPix3 != testPix4 || testPix > 120 )
			{
				fbow->setPixelAtIndex(curInd, blockChannel, 0);
			}
			else
			{
				fbow->setPixelAtIndex(curInd, blockChannel, basePix);
			}

		}

		fbow->cpuToGPU();
		singleton->copyFBO("hmFBO", "hmFBOLinear");

		cout << "end find city blocks\n";


		cout << "start add in city roads\n";
		//add in city roads

		for (i = 0; i < numProvinces; i++)
		{
			// recursive backtrack
			btStack[0] = fbow2->getIndex(provinceX[i], provinceY[i]);
			btStackInd = 0;

			while (btStackInd > -1)
			{

				curInd = btStack[btStackInd];
				curY = curInd / w;
				curX = curInd - curY * w;

				fbow2->orPixelAtIndex(curInd, btChannel, visFlag);

				startDir = 0;
				count = 0;
				notFound = true;
				bestDelta = FLT_MAX;


				testPix2 = fbow->getPixelAtIndex(curInd, blockChannel);

				//testPix2 = fbow->getMipVal(curX,curY,blockMip,densityChannel,AVG_MIP);
				//testPix3 = fbow->getMipVal(curX,curY,blockMip,idChannel,MIN_MIP);
				//testPix4 = fbow->getMipVal(curX,curY,blockMip,idChannel,MAX_MIP);


				if ( testPix2 != 0 )
				{
					do
					{
						curDir = (startDir + count) % 4;

						testX = curX + dirModX[curDir];
						testY = curY + dirModY[curDir];
						testInd = fbow2->getIndex(testX, testY);
						testPix = fbow2->getPixelAtIndex(testInd, btChannel);
						testPix3 = fbow->getPixelAtIndex(testInd, blockChannel);

						if ( (testPix & visFlag) == 0 && (testPix3 != 0))
						{
							//not visited, proceed
							notFound = false;


							delta = abs(
												fbow->getPixelAtIndex(curInd, hmChannel) -
												fbow->getPixelAtIndex(testInd, hmChannel)
											);

							if (delta < bestDelta)
							{
								bestDelta = delta;
								bestDir = curDir;
								bestInd = testInd;
							}

						}

						count++;
					}
					while (count < 4); //notFound &&
				}

				if (notFound)
				{
					btStackInd--;
				}
				else
				{

					// join the two and remove walls
					fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
					fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);

					btStackInd++;
					btStack[btStackInd] = bestInd;
				}

			}
		}

		cout << "end add in city roads\n";



		// clear visited
		for (k = 0; k < totSize; k++)
		{
			testPix = fbow2->getPixelAtIndex(k, btChannel);
			if ( (testPix & visFlag) == 0)
			{
				//not visited
				for (i = 0; i < 4; i++)
				{
					fbow2->andPixelAtIndex(k, btChannel, dirFlags[i]);
				}
			}
			else
			{
				//visited
			}

			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}



		cout << "start link close cities\n";

		// link close cities

		for (i = 1; i < numProvinces - 1; i++)
		{
			for (j = i + 1; j < numProvinces; j++)
			{

				curInd = i + j * numProvinces;

				if (provinceGrid[curInd] == 1)
				{
					p1 = i;
					p2 = j;



					tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
					tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

					tempVec2.wrapDistance(&tempVec1, w);
					tempVec3.copyFrom(&tempVec1);

					findBestPath(
						tempVec2.getFX(),
						tempVec2.getFY(),
						tempVec3.getFX(),
						tempVec3.getFY(),
						0,
						curInd,
						true,
						false
					);

				}

			}
		}



		cout << "end link close cities\n";



		floatAndIndex *oceanRes = new floatAndIndex[numProvinces * numProvinces];

		for (i = 0; i < numProvinces * numProvinces; i++)
		{
			oceanRes[i].value = FLT_MAX;
			oceanRes[i].index1 = 0;
			oceanRes[i].index2 = 0;
		}

		cout << "start find biggest ocean gaps\n";


		for (k = 0; k < 2; k++)
		{

			cout << "iteration: " << k << "\n";

			count = 0;

			if (k == 0)
			{
				for (i = 1; i < numProvinces - 1; i++)
				{
					for (j = i + 1; j < numProvinces; j++)
					{
						curInd = i + j * numProvinces;
						if (provinceGrid[curInd] != 1)
						{
							p1 = i;
							p2 = j;



							tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
							tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

							tempVec2.wrapDistance(&tempVec1, w);
							tempVec3.copyFrom(&tempVec1);


							oceanRes[count].value = findBestPath(
																				tempVec2.getFX(),
																				tempVec2.getFY(),
																				tempVec3.getFX(),
																				tempVec3.getFY(),
																				0,
																				curInd,
																				false,
																				true
																			);
							oceanRes[count].index1 = i;
							oceanRes[count].index2 = j;

							count++;

						}

					}
				}
			}
			else
			{
				bubbleSortF(oceanRes, numProvinces * numProvinces);


				for (i = 0; i < 30; i++)
				{

					p1 = oceanRes[i].index1;
					p2 = oceanRes[i].index2;

					curInd = p1 + p2 * numProvinces;

					tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
					tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

					tempVec2.wrapDistance(&tempVec1, w);
					tempVec3.copyFrom(&tempVec1);

					findBestPath(
						tempVec2.getFX(),
						tempVec2.getFY(),
						tempVec3.getFX(),
						tempVec3.getFY(),
						0,
						curInd,
						true,
						true
					);
				}

			}


		}



		cout << "end find biggest ocean gaps\n";








		mapSwapFlag = 0;
		mapStep = 0.0f;

		fbow2->cpuToGPU();
		singleton->copyFBO("cityFBO", "swapFBO0");
		singleton->bindShader("DilateShader");
		for (i = 0; i < 2; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->sampleFBO("hmFBO", 1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 1.0);
			singleton->setShaderFloat("doDilate", 1.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("hmFBO", 1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();

			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();
		singleton->copyFBO("swapFBO0", "cityFBO");
		fbow2->getPixels();
		//fbow2->updateMips();






		//bool notCovered = true;
		int id = 1;
		int totCount;
		int fillColor;
		bool incId;

		cout << "start road regions\n";

		for (i = 0; i < totSize; i++)
		{

			if (fbow2->getPixelAtIndex(i, pathChannel) == 0)
			{



				for (j = 0; j < 2; j++)
				{
					btStack[0] = i;
					btStackInd = 0;
					totCount = 0;

					if (j == 0)
					{
						fillColor = id;
					}
					else
					{
						fillColor = 255;
					}


					while (btStackInd > -1)
					{

						curInd = btStack[btStackInd];
						curY = curInd / w;
						curX = curInd - curY * w;

						if (j == 0)
						{
							fbow2->orPixelAtIndex(curInd, btChannel, visFlag);
						}
						else
						{
							fbow2->andPixelAtIndex(curInd, btChannel, visFlagO );
						}


						fbow2->setPixelAtIndex(curInd, pathChannel, fillColor );


						count = 0;
						notFound = true;



						do
						{
							curDir = count;

							testX = curX + dirModX[curDir];
							testY = curY + dirModY[curDir];
							testInd = fbow2->getIndex(testX, testY);
							testPix = fbow2->getPixelAtIndex(testInd, btChannel);
							testPix2 = fbow2->getPixelAtIndex(testInd, pathChannel);


							if (j == 0)
							{
								if ( ( (testPix & visFlag) == 0 ) && (testPix2 == 0))
								{
									notFound = false;
									totCount++;

								}
							}
							else
							{
								if ( ( (testPix & visFlag) > 0) && (testPix2 == id))
								{
									notFound = false;
									totCount++;
								}
							}




							count++;
						}
						while (notFound && count < 4);

						if (notFound)
						{
							btStackInd--;
						}
						else
						{

							// join the two and remove walls
							//fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
							//fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);


							btStackInd++;
							btStack[btStackInd] = testInd;
						}

					}

					incId = false;

					if (j == 0)
					{
						if (totCount < 1000)
						{
							//cout << "Too Small\n";
						}
						else
						{
							incId = true;
							j++;
						}
					}
					else
					{
						incId = true;
					}

					if (incId)
					{
						//cout << "Id: " << id << "\n";
						id++;
						if (id > 254)
						{
							id = 1;
						}
					}
				}




			}

		}


		cout << "end road regions\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}

		fbow2->cpuToGPU();


		mapSwapFlag = 0;
		mapStep = 0.0f;
		singleton->copyFBO("cityFBO", "swapFBO0");



		singleton->bindShader("SkeletonShader");
		for (k = 0; k < 19; k++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			//singleton->sampleFBO("hmFBO",1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 0.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			//singleton->unsampleFBO("hmFBO",1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();
			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;

		}
		singleton->unbindShader();


		singleton->bindShader("RoadShader");
		for (k = 0; k < 1; k++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			//singleton->sampleFBO("hmFBO",1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 0.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			//singleton->unsampleFBO("hmFBO",1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();
			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;

		}
		singleton->unbindShader();


		singleton->copyFBO("swapFBO0", "cityFBO");
		fbow2->getPixels();







		// generate streets

		int *streetFlagsV = new int[w]; //runs vertical
		int *streetFlagsH = new int[h]; //runs horizontal

		for (i = 0; i < w; i++)
		{
			streetFlagsV[i] = 0;
		}
		for (i = 0; i < h; i++)
		{
			streetFlagsH[i] = 0;
		}

		// 1 - x+
		// 2 - x-
		// 4 - y+
		// 8 - y-

		for (i = 0; i < w; i += singleton->blockSizeInLots )
		{

			curInd = i - 1;

			while (curInd < 0)
			{
				curInd += w;
			}

			streetFlagsV[curInd] |= 1;
			streetFlagsV[i] |= 2;
		}
		for (i = 0; i < h; i += singleton->blockSizeInLots )
		{

			curInd = i - 1;

			while (curInd < 0)
			{
				curInd += h;
			}

			streetFlagsH[curInd] |= 4;
			streetFlagsH[i] |= 8;
		}












		//add in main streets
		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			testPix = fbow->getPixelAtIndex(curInd, blockChannel);

			if (testPix != 0)
			{
				fbow2->orPixelAtIndex(curInd, btChannel, streetFlagsH[curY] | streetFlagsV[curX]);
				fbow2->orPixelAtIndex(curInd, stChannel, streetFlagsH[curY] | streetFlagsV[curX]); //stChannel
			}


		}


		// for (k = 0; k < totSize; k++) {

		//  // int stChannel;
		//  // int btChannel;
		//  // int pathChannel;
		//  // int houseChannel;

		//  testPix = fbow2->getPixelAtIndex(k, stChannel);
		//  fbow2->orPixelAtIndex(k, btChannel, testPix );

		//  testPix = fbow2->getPixelAtIndex(k, pathChannel);
		//  fbow2->orPixelAtIndex(k, btChannel, testPix );
		// }


		/*
		for (i = 0; i < numProvinces-1; i++) {
		    for (j = i + 1; j < numProvinces; j++) {
		        if (provinceGrid[i + j*numProvinces] == 1) {

		            k = fbow->numMips-1;

		            cx1 = provinceX[i];
		            cy1 = provinceY[i];
		            cx2 = provinceX[j];
		            cy2 = provinceY[j];

		            while (getMipInd(cx1,cy1,k) == getMipInd(cx2,cy2,k)) {
		                k--;
		            }

		        }
		    }
		}



		// remove any road that touches water or is out of town

		int cityLevel = 0;
		for (k = 0; k < totSize; k++) {
		    curInd = k;
		    curY = curInd/w;
		    curX = curInd-curY*w;

		    touchesWater = false;

		    for (j = -1; j <= 1; j++) {
		        for (i = -1; i <= 1; i++) {
		            testX = curX + i;
		            testY = curY + j;
		            testInd = fbow->getIndex(testX,testY);
		            testPix = fbow->getPixelAtIndex(testInd, hmChannel);


		            if (testPix < seaLevel + 10) {
		                touchesWater = true;
		                break;
		            }

		        }
		        if (touchesWater) {
		            break;
		        }
		    }

		    testPix2 = fbow->getPixelAtIndex(curInd, densityChannel);


		    if (touchesWater) { // || (testPix2 > 120)
		        fbow2->andPixelAtIndex(curInd, btChannel, dirFlagClear);
		        fbow2->andPixelAtIndex(curInd, stChannel, dirFlagClear);

		        //TODO: repair all broken (half) edges
		    }
		    // if (testPix2 > 80) {
		    //  fbow2->andPixelAtIndex(curInd, stChannel, dirFlagClear);
		    // }


		}



		// fix half streets

		for (k = 0; k < totSize; k++) {
		    curInd = k;
		    curY = curInd/w;
		    curX = curInd-curY*w;

		    basePix = fbow2->getPixelAtIndex(curInd, btChannel);
		    basePix2 = fbow2->getPixelAtIndex(curInd, stChannel);

		    for (i = 0; i < 4; i++) {



		        curDir = i;

		        testX = curX + dirModX[curDir];
		        testY = curY + dirModY[curDir];
		        testInd = fbow2->getIndex(testX,testY);
		        testPix = fbow2->getPixelAtIndex(testInd, btChannel);
		        testPix2 = fbow2->getPixelAtIndex(testInd, stChannel);


		        if ( (basePix & dirFlagsO[curDir]) != (testPix & dirFlagsOpO[curDir]) ) {
		            fbow2->orPixelAtIndex(curInd, btChannel, dirFlagsO[curDir]);
		            fbow2->orPixelAtIndex(testInd, btChannel, dirFlagsOpO[curDir]);
		        }

		        if ( (basePix2 & dirFlagsO[curDir]) != (testPix2 & dirFlagsOpO[curDir]) ) {
		            fbow2->orPixelAtIndex(curInd, stChannel, dirFlagsO[curDir]);
		            fbow2->orPixelAtIndex(testInd, stChannel, dirFlagsOpO[curDir]);
		        }

		    }

		}

		*/


















		// ?????




		cout << "start filling houses\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}

		fbow->updateMips();




		int wb = worldSizeInBlocks.getIX();
		int hb = worldSizeInBlocks.getIY();
		int blockInd;

		for (i = 0; i < wb; i++)
		{
			for (j = 0; j < hb; j++)
			{
				blockInd = i + j * wb;

				testPix = fbow->getMipAtIndex(blockInd, blockMip, blockChannel, MIN_MIP);

				if (testPix != 0)
				{



					id = 1;

					for (k = i * blockMod; k < (i + 1)*blockMod; k++)
					{
						for (m = j * blockMod; m < (j + 1)*blockMod; m++)
						{
							curInd = k + m * w;
							curX = k;
							curY = m;


							testPix = fbow2->getPixelAtIndex(curInd, btChannel);

							if (testPix & visFlag)
							{

							}
							else
							{
								btStack[0] = curInd;
								btStackInd = 0;
								totCount = 0;


								while ( (btStackInd > -1) && (totCount < 3) )
								{

									curInd = btStack[btStackInd];
									curY = curInd / w;
									curX = curInd - curY * w;

									fbow2->orPixelAtIndex(curInd, btChannel, visFlag);
									fbow2->setPixelAtIndex(curInd, houseChannel, id );


									count = 0;
									notFound = true;

									testPix2 = fbow2->getPixelAtIndex(curInd, btChannel);
									//testPix3 = fbow2->getPixelAtIndex(curInd, stChannel);
									testPix4 = fbow2->getPixelAtIndex(curInd, pathChannel);

									do
									{
										curDir = count;

										testX = curX + dirModX[curDir];
										testY = curY + dirModY[curDir];

										testInd = fbow2->getIndex(testX, testY);

										testPix = fbow2->getPixelAtIndex(testInd, btChannel);

										if (
											( (testPix & visFlag) == 0 ) &&
											( (testPix2 & dirFlagsO[curDir]) == 0) &&
											//( (testPix3 & dirFlagsO[curDir]) == 0) &&
											( (testPix4 & dirFlagsO[curDir]) == 0)
										)
										{
											notFound = false;
											totCount++;

										}


										count++;
									}
									while (notFound && count < 4);

									if (notFound)
									{
										btStackInd--;
									}
									else
									{

										// join the two and remove walls
										//fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
										//fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);


										btStackInd++;
										btStack[btStackInd] = testInd;
									}

								}

								id++;
								if (id > 254)
								{
									id = 1;
								}




							}


						}
					}

				}

			}
		}


		cout << "end filling houses\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}



		// ?????










		fbow2->cpuToGPU();

		delete[] btStack;
		delete[] streetFlagsH;
		delete[] streetFlagsV;
		delete[] oceanRes;

		//////////



		singleton->mapInvalid = false;

		singleton->setCameraToElevation();

		cout << "DONE WITH MAP\n";

		mapLockOn = false;

		//popTrace();
	}


	void drawMap()
	{


		//pushTrace("drawMap()");

		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBOLinear", 0);

		
		//singleton->setCameraToElevationBase();


		singleton->bindShader("TopoShader");
		
		singleton->bindFBO("resultFBO0");
		
		singleton->sampleFBO("palFBO", 0);
		singleton->sampleFBO("hmFBO", 1); //Linear
		singleton->sampleFBO("cityFBO", 2);
		singleton->sampleFBO("backFaceMapFBO",3);
		singleton->sampleFBO("frontFaceMapFBO",4);

		
		singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
		singleton->setShaderfVec4("mapFreqs", &(singleton->mapFreqs) );
		singleton->setShaderfVec4("mapAmps", &(singleton->mapAmps) );
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderFloat("mapTrans", mapTrans);
		singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
		singleton->setShaderFloat("curTime", singleton->curTime);
		singleton->setShaderVec2("mapDimInPixels", fbow->width, fbow->height);
		singleton->setShaderfVec3("worldSizeInPixels", &(singleton->worldSizeInPixels) );

		// singleton->drawQuadBounds(
		// 	-singleton->worldSizeInPixels.getFX() / 2.0f,// + cameraPos->getFX(),
		// 	-singleton->worldSizeInPixels.getFY() / 2.0f,// + cameraPos->getFY(),
		// 	singleton->worldSizeInPixels.getFX() / 2.0f,// + cameraPos->getFX(),
		// 	singleton->worldSizeInPixels.getFY() / 2.0f,// + cameraPos->getFY(),
		// 	0.0f//cameraPos->getFZ()//singleton->getHeightAtPixelPos(cameraPos->getFX(), cameraPos->getFY()) //0.0f// + cameraPos->getFZ()
		// );

		
		singleton->drawFSQuad(1.0f);

		
		singleton->unsampleFBO("frontFaceMapFBO",4);
		singleton->unsampleFBO("backFaceMapFBO",3);
		singleton->unsampleFBO("cityFBO", 2);
		singleton->unsampleFBO("hmFBO", 1);
		singleton->unsampleFBO("palFBO", 0);
		
		
		singleton->unbindFBO();
		
		singleton->unbindShader();

		
		//singleton->drawFBO("resultFBO", 0, newZoom, 1 - activeFBO);
		
		glEnable(GL_BLEND);
		singleton->drawFBO("resultFBO0",0,1.0f);
		glDisable(GL_BLEND);


		//popTrace();
	}

	void doBlur(string fboName)
	{
		int i;
		mapSwapFlag = 0;
		
		singleton->bindShader("BlurShader");
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderFloat("numBlurPixelsPerSide", 4.0); // value of 4 is a 9x9 kernel (4*2+1)
		singleton->setShaderFloat("sigma", 4.0);
		
		for (i = 0; i < 2; i++)
		{
			
			singleton->bindFBO(fboName, mapSwapFlag);
			singleton->sampleFBO(fboName, 0, mapSwapFlag);
			
			if (i == 0) { // horizontal
				singleton->setShaderFloat("blurSize", 1.0f/(singleton->currentFBOResolutionX));
				singleton->setShaderVec2("blurMultiplyVec", 1.0f, 0.0f);
			}
			else { // vertical
				singleton->setShaderFloat("blurSize", 1.0f/(singleton->currentFBOResolutionY));
				singleton->setShaderVec2("blurMultiplyVec", 0.0f, 1.0f);
			}

			
			singleton->drawFSQuad(1.0f);
			
			singleton->unsampleFBO(fboName, 0, mapSwapFlag);
			singleton->unbindFBO();
			

			mapSwapFlag = 1 - mapSwapFlag;

		}
		
		
		singleton->unbindShader();
		
	}

	void updateLights()
	{

		int i;
		int j;
		int k;

		int flag = 1;

		GameLight *tempLight;



		int ii;
		int jj;

		int blockRad = 1;

		lightCount = singleton->numDynLights;
		GameLight *curLight;
		GameBlock *curBlock;

		//activeLights[0] = &globalLight;

		if (singleton->targetTimeOfDay <= 0.5)
		{
			for (j = -blockRad; j <= blockRad; j++)
			{
				for (i = -blockRad; i <= blockRad; i++)
				{
					ii = i + camBlockPos.getIX();
					jj = j + camBlockPos.getIY();

					curBlock = getBlockAtCoords(ii, jj, true);


					for (k = 0; k < curBlock->gameLights.size(); k++)
					{
						curLight = curBlock->gameLights[k];

						// TODO: cache screen coords

						singleton->worldToScreen(&lScreenCoords, &(curLight->pos), true);

						curLight->screenDistance = lScreenCoords.length();

						if ( (curLight->screenDistance < 2.0f ) && (curLight->isOn) )
						{

							// if (lightCount == singleton->numLights) {

							// }

							activeLights[lightCount] = curBlock->gameLights[k];
							lightCount++;
						}

						if (lightCount >= MAX_EVAL_LIGHTS)
						{
							goto UPDATE_LIGHTS_END;
						}

					}
				}
			}

UPDATE_LIGHTS_END:

			for (i = singleton->numDynLights + 1; (i <= lightCount) && flag; i++)
			{
				flag = 0;
				for (j = singleton->numDynLights; j < (lightCount - 1); j++)
				{
					if (activeLights[j + 1]->screenDistance < activeLights[j]->screenDistance) // ascending order simply changes to <
					{
						tempLight = activeLights[j];
						activeLights[j] = activeLights[j + 1];
						activeLights[j + 1] = tempLight;
						flag = 1;
					}
				}
			}

			lightCount = min(lightCount, MAX_LIGHTS);
		}



	}

	void postProcess()
	{

		

		int i;
		int iMin;

		int k;
		int baseInd;

		GameLight *curLight;

		//pushTrace("postProcess()");

		// NOTE: ALWAYS UNSAMPLE IN REVERSE ORDER!!!




		//globalLight.initFrom( singleton->dynObjects[E_OBJ_LIGHT0] );
		//activeLights[0] = &globalLight;

		for (i = 0; i < singleton->numDynLights; i++)
		{
			activeLights[i] = singleton->dynObjects[E_OBJ_LIGHT0 + i]->getLight();
		}


		for (k = 0; k < lightCount; k++)
		{
			baseInd = k * FLOATS_PER_LIGHT;

			// lightPosBase.copyFrom(&(singleton->dynObjects[E_OBJ_LIGHT0 + k]->pos));
			// lightPosBase.addXYZ(
			//  sin(singleton->curTime/1300.0)*4.0f*singleton->pixelsPerMeter,
			//  sin(singleton->curTime/700.0)*4.0f*singleton->pixelsPerMeter,
			//  sin(singleton->curTime/1100.0)*4.0f*singleton->pixelsPerMeter
			// );
			// lightPos = &lightPosBase;

			curLight = activeLights[k];

			lightPos = &(curLight->pos);

			// if (k == 0) {
			//  globLightPos = lightPos;
			// }
			// if (k == 1) {
			//  lightPos->setFXYZ(
			//      cameraPos->getFX()-(globLightPos->getFX() - cameraPos->getFX()),
			//      cameraPos->getFY()-(globLightPos->getFY() - cameraPos->getFY()),
			//      globLightPos->getFZ()
			//  );
			// }

			singleton->worldToScreen(&lScreenCoords, lightPos);

			singleton->lightArr[baseInd + 0] = lightPos->getFX();
			singleton->lightArr[baseInd + 1] = lightPos->getFY();
			singleton->lightArr[baseInd + 2] = lightPos->getFZ();

			// light radius
			if (k == 0)
			{
				// global light
				singleton->lightArr[baseInd + 3] = 4096.0f * singleton->pixelsPerMeter;
			}
			else
			{
				// if (k == 1) {
				//  singleton->lightArr[baseInd + 3] = 4096.0f*singleton->pixelsPerMeter;
				// }
				// else {
				// other lights
				singleton->lightArr[baseInd + 3] = 16.0f * singleton->pixelsPerMeter;
				//}

			}

			singleton->lightArr[baseInd + 4] = lScreenCoords.getFX();
			singleton->lightArr[baseInd + 5] = lScreenCoords.getFY();
			singleton->lightArr[baseInd + 6] = 0.0f;
			singleton->lightArr[baseInd + 7] = 0.0f;


			// light color

			singleton->lightArr[baseInd + 8] = curLight->color.getFX(); // light red
			singleton->lightArr[baseInd + 9] = curLight->color.getFY(); // light green
			singleton->lightArr[baseInd + 10] = curLight->color.getFZ(); // light blue

			switch (k)
			{
			case 0:
				singleton->lightArr[baseInd + 11] = 1.0f; // light intensity (unused?)
				singleton->lightArr[baseInd + 12] = 0.0f; // light colorization (0-1)
				singleton->lightArr[baseInd + 13] = 0.0f; // light flooding (colorizes regardless of shadows) (0-1)
				break;
			default:
				singleton->lightArr[baseInd + 11] = 1.0f;
				singleton->lightArr[baseInd + 12] = 1.0f;
				singleton->lightArr[baseInd + 13] = 0.0f;
				break;

			}


		}

		if ( mapTrans < 1.0 )
		{




			activeFBO = 0;


			if (singleton->waterOn)	{


				singleton->bindShader("WaveHeightShader");
				singleton->bindFBO("waveFBO");
				singleton->sampleFBO("worldSpaceFBO", 4);
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("waveSpacing", singleton->pixelsPerMeter * 2.0f);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->drawFSQuad(1.0f);
				
				
				singleton->unsampleFBO("worldSpaceFBO", 4);
				singleton->unbindFBO();
				singleton->unbindShader();

				iMin = 0;

				singleton->bindShader("WaterShaderCombine");
				singleton->bindFBO("combineFBOWithWater");
				singleton->sampleFBO("combineFBO", 0);
				singleton->sampleFBO("waterFBO", 2);
				singleton->sampleFBO("waveFBO", 4);
				singleton->sampleFBO("worldSpaceFBO", 5);
				
				//singleton->setShaderFloat("maxWaveHeight", singleton->pixelsPerMeter * 2.0f);
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
				singleton->drawFSQuad(1.0f);
				
				singleton->unsampleFBO("worldSpaceFBO", 5);
				singleton->unsampleFBO("waveFBO", 4);
				singleton->unsampleFBO("waterFBO", 2);
				singleton->unsampleFBO("combineFBO", 0);
				singleton->unbindFBO();
				singleton->unbindShader();
				
				
				
				// copy waves to new world space fbo
				
				singleton->bindShader("WorldSpaceShader");
				singleton->bindFBO("worldSpaceWavesFBO");
				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->setShaderInt("iMax", 1);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim) );
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("combineFBOWithWater", 0);
				singleton->unbindFBO();
				singleton->unbindShader();
				
				
				
				
			}
			else
			{
				singleton->copyFBO("worldSpaceFBO", "worldSpaceWavesFBO", 3);
				singleton->copyFBO2("combineFBO", "combineFBOWithWater");

				iMin = 1;
			}





			singleton->bindShader("PreLightingShader");

			for (i = iMin; i < 2; i++)
			{
				if (i == 0)
				{
					singleton->bindFBO("swapFBOLinHalf0");
					singleton->sampleFBO("combineFBO", 0);
				}
				else
				{
					
					singleton->bindFBO("resultFBO", activeFBO);
					singleton->sampleFBO("combineFBOWithWater", 0);
				}

				singleton->sampleFBO("palFBO", 2);
				
				
				
				if ((i==1)&&(singleton->waterOn)) {
					singleton->setShaderTexture(3, singleton->getFBOWrapper("worldSpaceWavesFBO",0)->color_tex);
				}
				else {
					//worldSpaceFBO
					singleton->setShaderTexture(3, singleton->getFBOWrapper("worldSpaceFBO",0)->color_tex);
				}
				
				
				
				
				//worldSpaceFBO
				//singleton->setShaderTexture(4, singleton->getFBOWrapper("worldSpaceBlurFBO0",0)->color_tex);
				
				
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				
				singleton->setShaderInt("gridOn", (int)(singleton->gridOn));
				singleton->setShaderInt("testOn", (int)(singleton->testOn));
				
				singleton->setShaderInt("solidPass",i);
				
				singleton->setShaderFloat("holderMod",singleton->holderMod);
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderInt("iNumSteps", singleton->iNumSteps);


				singleton->setShaderArrayfVec4("lightArr", singleton->lightArr, (FLOATS_PER_LIGHT * lightCount) / 4);
				
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderFloat("blockSizeInMeters", singleton->blockSizeInMeters);
				singleton->setShaderFloat("lightCount", lightCount);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->drawFSQuad(1.0f);

				//singleton->setShaderTexture(4,0);
				singleton->setShaderTexture(3,0);
				singleton->unsampleFBO("palFBO", 2);

				if (i == 0)
				{
					singleton->unsampleFBO("combineFBO", 0);
				}
				else
				{
					singleton->unsampleFBO("combineFBOWithWater", 0);
				}

				singleton->unbindFBO();
			}

			singleton->unbindShader();

			activeFBO = 1 - activeFBO;


			if (singleton->waterOn)
			{
				doBlur("swapFBOLinHalf");
				singleton->bindShader("WaterShader");
				singleton->bindFBO("resultFBO", activeFBO);
				singleton->sampleFBO("combineFBO", 0);
				singleton->sampleFBO("combineFBOWithWater", 2);
				singleton->sampleFBO("resultFBO", 4, activeFBO);
				singleton->sampleFBO("swapFBOLinHalf0", 5);
				singleton->sampleFBO("noiseFBO", 6);
				singleton->sampleFBO("waveFBO", 7);
				singleton->sampleFBO("worldSpaceFBO", 8);
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
				singleton->drawFSQuad(1.0f);
				
				singleton->unsampleFBO("worldSpaceFBO", 8);
				singleton->unsampleFBO("waveFBO", 7);
				singleton->unsampleFBO("noiseFBO", 6);
				singleton->unsampleFBO("swapFBOLinHalf0", 5);
				singleton->unsampleFBO("resultFBO", 4, activeFBO);
				singleton->unsampleFBO("waterFBO", 2);
				singleton->unsampleFBO("combineFBO", 0);
				singleton->unbindFBO();
				singleton->unbindShader();

				activeFBO = 1 - activeFBO;
			}


			if (singleton->radiosityOn || singleton->fogOn)
			{

				if (activeFBO == 0)
				{
					singleton->copyFBO("resultFBO0", "swapFBOBLin0");
				}
				else
				{
					singleton->copyFBO("resultFBO1", "swapFBOBLin0");
				}


				doBlur("swapFBOBLin");
			}



			if (singleton->radiosityOn)
			{

				singleton->bindShader("RadiosityShader");

				singleton->bindFBO("swapFBOLinHalf0");
				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->sampleFBO("swapFBOBLin0", 2);
				singleton->sampleFBO("worldSpaceWavesFBO", 4);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec3("lightPosWS", lightPos);
				singleton->setShaderInt("iNumSteps", singleton->iNumSteps);
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("worldSpaceWavesFBO", 4);
				singleton->unsampleFBO("swapFBOBLin0", 2);
				singleton->unsampleFBO("combineFBOWithWater", 0);
				singleton->unbindFBO();
				singleton->unbindShader();


				doBlur("swapFBOLinHalf");

				singleton->bindShader("RadiosityCombineShader");
				singleton->bindFBO("resultFBO", activeFBO);
				singleton->sampleFBO("resultFBO", 0, activeFBO);
				singleton->sampleFBO("swapFBOLinHalf0", 1);
				singleton->sampleFBO("combineFBOWithWater", 2);
				singleton->setShaderInt("testOn", (int)(singleton->testOn));
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("combineFBOWithWater", 2);
				singleton->unsampleFBO("swapFBOLinHalf0", 1);
				singleton->unsampleFBO("resultFBO", 0, activeFBO);
				singleton->unbindFBO();
				singleton->unbindShader();

				activeFBO = 1 - activeFBO;


			}

			if (singleton->fogOn == 1.0f)
			{
				mapSwapFlag = 0;

				singleton->bindShader("FogShader");



				singleton->bindFBO("resultFBO", activeFBO);

				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->sampleFBO("resultFBO", 2, activeFBO);
				singleton->sampleFBO("swapFBOBLin0", 3);
				singleton->sampleFBO("worldSpaceFBO", 4);

				// todo: replace with worldSpaceWavesFBO
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec4("fogPos", fogPos);

				singleton->drawFSQuad(1.0f);

				singleton->unsampleFBO("worldSpaceFBO", 4);
				singleton->unsampleFBO("swapFBOBLin0", 3);
				singleton->unsampleFBO("resultFBO", 2, activeFBO);
				singleton->unsampleFBO("combineFBOWithWater", 0);

				singleton->unbindFBO();
				singleton->unbindShader();


				activeFBO = 1 - activeFBO;

			}

			//singleton->drawFBO("swapFBOBLin0", 0, newZoom);
			
			
			//singleton->drawFBO("frontFaceFBO", 0, 1.0f);

			

			// if (singleton->testOn) {
			// 	doBlur("resultFBO");
			// }

			if (singleton->guiOn) {
				if (singleton->mainGUI->isReady) {
					singleton->mainGUI->renderGUI(newZoom, 1 - activeFBO);
				}
				
			}
			else {
				singleton->drawFBO("resultFBO", 0, newZoom, 1 - activeFBO);
			}
			






			// singleton->bindShader("CopyShader");
			// singleton->setShaderTexture(0,singleton->testPat->tid);
			// singleton->drawFSQuad(0.25f);
			// singleton->setShaderTexture(0,0);
			// singleton->unbindShader();





		}


		//popTrace();


	}

	~GameWorld()
	{

		//threadpool.stopAll();

		int i;
		int j;

	}


};

