
class Singleton
{
public:
	
	struct UIQuad
	{
		fBoundingBox hitBounds;
		CharStruct* cs;
		int fontId;
	};
	
	struct UICont {
		UIComponent* uiComp;
		UIQuad bg;
		std::vector<UIQuad> charVec;
		//bool locked;
	};
	
	struct JSONStruct {
		JSONValue* jv;
	};
	struct UICStruct {
		UIComponent* uic;
		int nodeId;
	};
	
	struct CompareStruct {
	    bool operator()(const string& first, const string& second) {
	        return first.compare(second) < 0;//first.size() < second.size();
	    }
	};

	CompareStruct compareStruct;
	
	
	typedef map<string, UICStruct>::iterator itUICStruct;
	
	

	E_OBJ activeObject;
	E_OBJ tempObj;
	int mouseState;
	//E_GRASS_STATE grassState;
	eProgramState programState;
	eProgramAction progActionsDown[E_PS_SIZE * 256];
	eProgramAction progActionsUp[E_PS_SIZE * 256];

	float scrollDiv;
	
	float masterVolume;
	float ambientVolume;
	float guiVolume;
	float musicVolume;
	float fxVolume;

	bool isInteractiveGeom[E_CT_LENGTH];

	bool pathfindingOn;
	bool isMacro;
	bool entOn;
	bool autoScroll;
	bool cavesOn;
	bool bakeParamsOn;
	bool dragging;
	bool mouseMoved;
	bool changingGenVal;
	bool readyForRestart;
	bool forceRestart;
	bool hitGUI;
	bool guiLock;
	bool guiDirty;
	bool guiOn;
	bool mirrorOn;
	bool applyToChildren;
	
	bool bShiftOld;
	bool bCtrlOld;
	bool bCtrl;
	bool bShift;
	
	bool tiltChanged;
	bool testOn;
	bool emptyVDNotReady;
	bool radiosityOn;
	bool updateLock;
	bool isFullScreen;
	bool changesMade;
	bool mapInvalid;
	bool bufferInvalid;
	bool wsBufferInvalid;
	bool forceGetPD;
	bool mouseLeftDown;
	bool mouseRightDown;
	bool pboSupported;
	bool notQuit;
	bool timerNotSet;
	bool lbDown;
	bool abDown; // lb, rb, or mb is down
	bool rbDown;
	bool mbDown;
	bool isZooming;
	bool isPanning;
	bool isBare;
	bool showMap;
	bool traceOn;
	bool waterOn;
	bool treesOn;
	bool firstRun;
	bool rotOn;
	
	int maxLayerOver;
	
	int holderMod;
	float fHolderMod;
	int holderResolution;
	
	//int pageResolution;
	
	int visPageSizeInUnits;
	int bufferedPageSizeInUnits;
	int unitSizeInPixels;
	int holdersPerLot;
	int pixelsPerLot;
	
	
	int pixelsPerMeter;
	int visPageSizeInPixels;
	int holderSizeInPixels;
	
	

	int currentStep;
	int maxLayers;
	int maxChangesInPages;
	int maxChangesInHolders;
	int baseW;
	int baseH;
	int scaleFactor;
	

	int numDynLights;
	int iNumSteps;


	int curEntId;
	int metersPerLot;
	int extraRad;
	int defaultWinW;
	int defaultWinH;
	int guiWinW;
	int guiWinH;
	int shadersAreLoaded;
	int readyToRecompile;
	int lastPosX;
	int lastPosY;
	int frameCount;
	int maxHInPages;
	int maxWInPages;
	int minWInPages;
	int screenWidth;
	int screenHeight;
	int mouseMovingSize;
	int mouseMovingLoc;
	int mouseMovingStepsBack;
	int mouseCount;
	int lastMouseX;
	int lastMouseY;
	int voroSize;
	int geomCounter;
	int lightCounter;

	int charState;
	int skipFrames;
	
	float msPerFrame;
	
	int metersPerNodeXY;
	int terDataVisPitchXY;
	int terDataBufPitchXY;
	int terDataBufPitchScaledXY;
	
	int metersPerNodeZ;
	int terDataVisPitchZ;
	int terDataBufPitchZ;
	int terDataBufPitchScaledZ;
	
	
	int terDataBufAmount;
	int terDataVisSize;
	int terDataBufSize;

	int terDataTexScale;
	int terDataBufSizeScaled;
	uint *terDataScaled;

	int iNodeDivsPerLot;
	int selGeomListInd;
	int holderSizeInPages;
	uint volGenFBOX;
	uint palWidth;
	uint palHeight;
	uint blockShift;

	float fogOn;
	float gridOn;
	float mapSampScale;
	float curBrushRad;

	float timeOfDay;
	float targetTimeOfDay;

	float gridSizeInPixels;

	float origWinW;
	float origWinH;

	float guiX;
	float guiY;

	
	
	float tiltAmount;
	float currentFBOResolutionX;
	float currentFBOResolutionY;
	float mouseX;
	float mouseY;
	float mouseXUp;
	float mouseYUp;
	float cameraZoom;
	float targetZoom;
	float curTime;
	float lastTime;
	float myDelta;
	float mdTime;
	float muTime;
	float bufferMult;
	float holderSizeMB;
	float bestNodeDis;

	float *paramArr;
	float *voroArr;
	float *matCountArr;
	float *paramArrMap;
	int *geomIdArr;
	
	double curMS;
	
	GameEntNode* bestNode;
	GameEntNode* selectedNode;
	GameEntNode* lastSelNode;
	GameEntNode* activeNode;

	FIVector4 cameraPosAdjusted;
	FIVector4 baseScrollPos;
	FIVector4 worldSizeInPixels;
	FIVector4 mouseUpPD;
	FIVector4 mouseDownPD;
	FIVector4 mouseMovePD;
	FIVector4 geomPD;
	
	FIVector4 tempVec1;
	FIVector4 tempVec2;
	FIVector4 tempVec3;


	FIVector4 worldSizeInTerData;
	FIVector4 worldSizeInUnits;
	FIVector4 worldSizeInPages;
	FIVector4 worldSizeInLots;
	FIVector4 worldSizeInMeters;
	FIVector4 worldSizeInHolders;
	FIVector4 worldSizeInBlocks;
	
	FIVector4 moveNodes[2];
	
	FIVector4 voroVecArr[125];
	floatAndIndex indexArr[125];
	
	FIVector4 mouseStart;
	FIVector4 mouseEnd;

	FIVector4 mapFreqs;
	FIVector4 mapAmps;


	FIVector4 *mouseMoving;
	FIVector4 mouseVel;

	FIVector4 bufferDim;
	FIVector4 bufferDimTarg;
	FIVector4 bufferDimHalf;
	FIVector4 bufferModDim;
	FIVector4 origin;
	FIVector4 lastModXYZ;
	FIVector4 panMod;
	FIVector4 dMod;
	FIVector4 modXYZ;
	
	std::vector<UICont*> guiLayers[MAX_UI_LAYERS];
	
	// std::vector<FIVector4> rotStack;
	// std::vector<FIVector4> transStack;
	std::vector<RotationInfo> rotMatStack;
	std::vector<DynObject *> dynObjects;
	std::vector<GameGeom *> selGeomList;
	PathHolder charPathHolder;
	PathHolder splitPathHolder;


	float floorHeightInMeters;
	float roofHeightInMeters;
	float wallRadInMeters;



	int metersPerHolder;
	int metersPerPage;
	int unitsPerMeter;
	int blockSizeInLots;
	int blockSizeInMeters;
	int blockSizeInHolders;
	int blockSizeInPages;
	int blockSizeInPixels;

	Image *imageHM0;
	Image *imageHM1;
	Image *cloudImage;

	GameGeom *highlightedGeom;
	GameGeom *selectedGeom;
	GameGeom *curGeom;
	
	GamePlant* gamePlants[E_PT_LENGTH/2];

	Shader *curShaderPtr;
	string curShader;
	string allText;
	string stringBuf;
	string curCallback;
	string cbDataStrings[10];
	
	string guiSaveLoc;

	PoolManager* gpuPool;
	PoolManager* entityPool;
	//PoolPageManager* gpuPagePool;
	//PoolPageManager* entityPagePool;
	
	vector<string> shaderStrings;
	//vector<string> fboStrings;
	vector<string> shaderTextureIds;
	map<string, Shader*> shaderMap;
	map<string, UICStruct> compMap;
	
	map<string, FBOSet> fboMap;
	FBOSet vgFBOArr[MAX_VG_FBOS];

	//string curVGString;
	//string smallVGString;

	GLuint volId;
	GLuint volIdLinear;
	GLuint volIdEmpty;
	GLuint volIdEmptyLinear;

	GLuint volGenId;
	//GLuint terrainId;
	GLuint volTris;
	GLuint sliceTris;
	//GLuint grassTris[MAX_GRASS_LEV];
	uint *lookup2to3;
	//uint* volData;
	//uint* volDataLinear;

	unsigned char *resultImage;

	charArr nullBuffer;
	charArr lastImageBuffer;
	charArr lastJSONBuffer;
	charArr lastJSONBufferGUI;

	
	JSONValue *rootObjJS;
	JSONValue *guiRootJS;

	#ifdef USE_POCO
	WebSocketServer *myWS;
	#endif 
	Timer myTimer;
	Timer scrollTimer;
	//Timer fpsTimer;
	GameWorld *gw;

	float lightArr[MAX_LIGHTS * 16];
	int numLights;


	bool multiLights;

	int *rbStack;
	int *rbHeightStack;


	TerTexture terTextures[MAX_TER_TEX];

	//FTGLPixmapFont* myFont;

	GameEnt* testHuman;

	
	GameGUI* mainGUI;
	
	FontWrapper* fontWrappers[EFW_LENGTH];
	
	GameMusic* music[EML_LENGTH];
	map<string, GameSound> soundMap;
	
	map<string, StyleSheet> styleSheetMap;
	map<string, JSONStruct> internalJSON;

	Singleton()
	{
		
		fboMap.clear();
		shaderMap.clear();
		soundMap.clear();
		styleSheetMap.clear();
		
		
		
		mainGUI = NULL;
		volTris = NULL;
		sliceTris = NULL;
		gw = NULL;
		#ifdef USE_POCO
		myWS = NULL;
		#endif
	}


	void init(
		int _defaultWinW,
		int _defaultWinH,
		int _scaleFactor
		#ifdef USE_POCO
		,WebSocketServer *_myWS
		#endif
		
	) {

		pushTrace("Singleton init");
		int i;
		int j;
		
		internalJSON["shaderParams"].jv = NULL;
		
		for (i = 0; i < EML_LENGTH; i++) {
			music[i] = new GameMusic();
			music[i]->init("..\\data\\music\\"+musicStrings[i]+".ogg");
			music[i]->setLoop(true);
		}
		
		
		for (i = 0; i < E_CT_LENGTH; i++) {
			isInteractiveGeom[i] = false;
		}
		
		isInteractiveGeom[E_CT_WINDOW] = true;
		isInteractiveGeom[E_CT_DOOR] = true;
		isInteractiveGeom[E_CT_LANTERN] = true;
		
		pathfindingOn = false;
		isMacro = false;
		entOn = false;
		autoScroll = false;
		cavesOn = false;
		bakeParamsOn = true;
		dragging = false;
		mouseMoved = false;
		forceRestart = false;
		changingGenVal = false;
		readyForRestart = false;
		hitGUI = false;
		guiLock = false;
		guiDirty = true;
		
		
		activeNode = NULL;
		selectedNode = NULL;
		lastSelNode = NULL;
		
		curEntId = 0;
		charState = E_CHAR_STATE_RENDERED;
		
		rootObjJS = NULL;
		guiRootJS = NULL;
		highlightedGeom = NULL;
		selectedGeom = NULL;
		rbStack = NULL;
		rbHeightStack = NULL;

		multiLights = false;
		numDynLights = E_OBJ_LENGTH - E_OBJ_LIGHT0;
		updateMultiLights();

		maxLayerOver = -1;

		iNumSteps = 64;
		currentStep = 0;

		srand(time(NULL));

		timeOfDay = 1.0f;
		targetTimeOfDay = 1.0f;
		
		guiSaveLoc = "..\\cdat\\saves\\save0\\compMap.txt";

		//invItems = loadBMP("..\\data\\invitems.bmp");
		imageHM0 = loadBMP("..\\data\\hm0.bmp");
		imageHM1 = loadBMP("..\\data\\hm1.bmp");
		cloudImage = loadBMP("..\\data\\clouds.bmp");

		//invItems->getTextureId(GL_NEAREST);
		imageHM0->getTextureId(GL_NEAREST);
		imageHM1->getTextureId(GL_NEAREST);
		cloudImage->getTextureId(GL_LINEAR);

		selGeomListInd = 0;

		mapSampScale = 0.5f;
		curMS = 0.0;
		//renderCount = 1.0;
		int newPitch = (imageHM0->width) * mapSampScale; //*2;

		numLights = MAX_LIGHTS;//min(MAX_LIGHTS,E_OBJ_LENGTH-E_OBJ_LIGHT0);


		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////


		initStyleSheet();

		
		masterVolume = 0.0f;
		ambientVolume = 0.0f;
		guiVolume = 0.0f;
		musicVolume = 0.0f;
		fxVolume = 0.0f;

		applyToChildren = false;
		mirrorOn = true;
		guiOn = false;
		bCtrlOld = false;
		bShiftOld = false;
		bCtrl = false;
		bShift = false;
		tiltChanged = false;
		emptyVDNotReady = true;
		firstRun = true;
		waterOn = true;
		treesOn = true;
		rotOn = false;

		maxLayers = MAX_LAYERS;

		// Resolution Dependent

		volGenFBOX = 128; // MAX OF 128, DO NOT CHANGE THIS VALUE

		
		
		
		
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		
				
		// IMPORTANT: Maximum height must be less than 2^16, max world pitch must be less than 2^32
		
		// todo:
		
		// realtime cutaway based on green cube position
		// character editor load from json
		// floating trees
		// stacked lots?
		
		
		
		// qqqqqq
		
		// WAS DOING:
		// undo destruction
		
		// adjust camera for better loading, ray cast from cam pos to find nearest
		// chunk to load
		// flood fill from there until it hits blank chunk and stop
		
		
		
		int bufferDiv = 2;
		int curProfile;
		
		scrollDiv = 2.0;
		
		msPerFrame = 8.0;
		
		
		//curProfile = E_PP_ENTITY;
		curProfile = 999;//E_PP_SCROLLING;

		switch (curProfile) {
			
			case E_PP_TILTING:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;
				
				

				pixelsPerMeter = 64;
				metersPerPage = 8;
				metersPerHolder = 8;
				holderMod = 8;
			break;
			
			
			case E_PP_FAST_LOWRES:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8; 
				
				maxHInPages = 1;
				maxWInPages = 2;
				minWInPages = 1;
				
				

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 4;
			
			case E_PP_SCROLLING:
				skipFrames = 1;
				maxChangesInPages = 8;
				maxChangesInHolders = 2; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;
				
				

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 4;
			break;
			case E_PP_ENTITY:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 4; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 4;
			break;
			
			case E_PP_TERRAIN_MODIFICATION:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 3;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 8;
				holderMod = 4;
			break;
			case E_PP_FAST_MODIFICATION:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 3;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 8;
			break;
			case E_PP_HIGHQUALITY:
				skipFrames = 1;
				maxChangesInPages = 4;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 2;
			break;
			default:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8;
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 4;
			break;
		}
		
		

		
		

		
		// This var determines how high the z val can go,
		// but also increases load times for each block
		
		metersPerLot = 64; // adjust this to make lots bigger
		
		metersPerNodeXY = 16;
		metersPerNodeZ = 8;
		blockSizeInLots = 4;
		unitsPerMeter = 4; // ONE UNIT == ONE METER
		

		worldSizeInLots.setIXYZ(newPitch, newPitch, blockSizeInLots);
		worldSizeInMeters.copyIntMult(&worldSizeInLots, metersPerLot);
		blockSizeInMeters = blockSizeInLots * metersPerLot;
		holderSizeInPages = metersPerHolder / metersPerPage;
		holdersPerLot = metersPerLot / metersPerHolder;
		visPageSizeInUnits = metersPerPage * unitsPerMeter;
		bufferMult = 1.25f;
		bufferedPageSizeInUnits = visPageSizeInUnits * bufferMult;
		worldSizeInHolders.copyIntMult(&worldSizeInLots, holdersPerLot);
		blockSizeInHolders = blockSizeInLots * holdersPerLot;
		blockSizeInPages = blockSizeInHolders * holderSizeInPages;
		worldSizeInBlocks.copyIntDiv(&worldSizeInHolders, blockSizeInHolders);
		worldSizeInPages.copyIntMult(&worldSizeInHolders, holderSizeInPages);
		worldSizeInUnits.copyIntMult(&worldSizeInPages, visPageSizeInUnits);
		
		
		

		pixelsPerLot = pixelsPerMeter * metersPerLot;
		unitSizeInPixels = pixelsPerMeter / unitsPerMeter;
		blockSizeInPixels = pixelsPerMeter * blockSizeInMeters;
		worldSizeInPixels.copyIntMult(&worldSizeInMeters, pixelsPerMeter);
		
		visPageSizeInPixels = pixelsPerMeter * metersPerPage;
		holderSizeInPixels = pixelsPerMeter * metersPerHolder;
		
		
		// pageResolution = visPageSizeInPixels;//512; // height of one page in pixels
		
		
		fHolderMod = (float)holderMod;
		holderResolution = holderSizeInPixels/holderMod;
		
		
		
		
		
		
		
		
		
		
		terDataTexScale = 1;
		//if (pixelsPerMeter >= 128) {
			terDataTexScale = 2;
		//}
		
		terDataVisPitchXY = blockSizeInMeters / metersPerNodeXY;
		iNodeDivsPerLot = terDataVisPitchXY / blockSizeInLots;
		terDataBufAmount = iNodeDivsPerLot; // pad with one extra lot
		
		floorHeightInMeters = (float)metersPerNodeZ;
		roofHeightInMeters = ((float)metersPerNodeXY)/4.0f;
		wallRadInMeters = ((float)metersPerNodeXY)/4.0f;
		
		
		terDataBufPitchXY = terDataVisPitchXY + terDataBufAmount * 2;
		terDataBufPitchScaledXY = terDataBufPitchXY * terDataTexScale;
		
		terDataVisPitchZ = blockSizeInMeters / metersPerNodeZ;
		terDataBufPitchZ = terDataVisPitchZ + terDataBufAmount * 2;
		terDataBufPitchScaledZ = terDataBufPitchZ * terDataTexScale;

		terDataVisSize = terDataVisPitchXY * terDataVisPitchXY * terDataVisPitchZ;
		terDataBufSize = terDataBufPitchXY * terDataBufPitchXY * terDataBufPitchZ;
		terDataBufSizeScaled = terDataBufPitchScaledXY * terDataBufPitchScaledXY * terDataBufPitchScaledZ;


		terDataScaled = new uint[terDataBufSizeScaled];
		rbStack = new int[terDataBufSize];
		rbHeightStack = new int[terDataBufSize];


		worldSizeInTerData.setIXYZ(
			worldSizeInBlocks.getIX()*terDataVisPitchXY,
			worldSizeInBlocks.getIY()*terDataVisPitchXY,
			worldSizeInBlocks.getIZ()*terDataVisPitchZ
		);
		


		
		tiltAmount = 0.5f;


		
		blockShift = intLogB2(blockSizeInHolders * blockSizeInHolders * blockSizeInHolders);
		holderSizeMB = ( ((float)MAX_LAYERS) * 2.0f * 4.0f * (float)(holderResolution * holderResolution)) / (1024.0f * 1024.0f);








		cout << "\n\n\n\n\n\n";



		// cout << "terDataBufPitchXY: " << terDataBufPitchXY << "\n";
		// cout << "terDataBufPitchZ: " << terDataBufPitchXY << "\n";
		// cout << "terDataVisPitchXY: " << terDataBufPitchXY << "\n";
		// cout << "terDataVisPitchZ: " << terDataBufPitchXY << "\n";
		
		
		cout << "blockSizeInHolders: " << blockSizeInHolders << "\n";
		cout << "blockSizeInPixels: " << blockSizeInPixels << "\n";
		cout << "terDataBufPitchScaledXY " << terDataBufPitchScaledXY << "\n";
		cout << "maxChangesInHolders: " << maxChangesInHolders << "\n";
		cout << "volGenFBOX: " << volGenFBOX << "\n";
		cout << "volGenFBOY: " << volGenFBOX *volGenFBOX << "\n";
		cout << "visPageSizeInPixels: " << visPageSizeInPixels << "\n";
		cout << "holderSizeInPixels: " << holderSizeInPixels << "\n";
		cout << "bufferMult: " << bufferMult << "\n";
		cout << "metersPerLot: " << metersPerLot << "\n";
		cout << "pixelsPerMeter: " << pixelsPerMeter << "\n";
		cout << "unitsPerMeter: " << unitsPerMeter << "\n";
		cout << "blockSizeInLots: " << blockSizeInLots << "\n";
		cout << "pixelsPerUnit: " << unitSizeInPixels << "\n";
		cout << "unitsPerLot: " << metersPerLot*unitsPerMeter << "\n";
		cout << "pixelsPerLot: " << pixelsPerLot << "\n";
		cout << "holderSizeInPages: " << holderSizeInPages << "\n";
		cout << "holdersPerLot: " << holdersPerLot << "\n";
		cout << "visPageSizeInUnits: " << visPageSizeInUnits << "\n";
		cout << "unitSizeInPixels: " << unitSizeInPixels << "\n";


		doTraceVecND("worldSizeInBlocks: ", &worldSizeInBlocks);
		doTraceVecND("worldSizeInLots: ", &worldSizeInLots);
		doTraceVecND("worldSizeInHolders: ", &worldSizeInHolders);
		doTraceVecND("worldSizeInPages: ", &worldSizeInPages);
		doTraceVecND("worldSizeInTerData: ", &worldSizeInTerData);

		GLint glQuery;
		glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &glQuery);
		cout << "MAX_UNIFORMS: " << glQuery << "\n";

		cout << "\n\n\n\n\n\n";


		voroSize = 32;
		mapFreqs.setFXYZW(1.0f, 16.0f, 32.0f, 64.0f);
		mapAmps.setFXYZW(1.0f, 8.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f); //0.0f, 0.0f, 0.0f);//


		gridSizeInPixels = pixelsPerMeter;



		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		radiosityOn = true;
		testOn = false;
		updateLock = false;
		traceOn = false;
		gridOn = 0.0f;
		fogOn = 1.0f;
		geomCounter = 0;
		lightCounter = 0;



		int ccr = 0;
		int ccg = 0;
		int ccb = 0;

		doTraceVecND("worldSizeInPixels: ", &worldSizeInPixels);






		glGenTextures(1, &volId);
		glGenTextures(1, &volIdLinear);
		glGenTextures(1, &volIdEmpty);
		glGenTextures(1, &volIdEmptyLinear);

		int curFilter;

		for (i = 0; i < MAX_TER_TEX; i++)
		{

			terTextures[i].usedByBlockId = -1;
			terTextures[i].alreadyBound = false;


			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, 0);

			glGenTextures(1, &(terTextures[i].texId));
			glBindTexture(GL_TEXTURE_3D, terTextures[i].texId);
			glTexImage3D(
				GL_TEXTURE_3D,
				0,
				GL_RGBA,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledZ,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				0
			);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_3D, 0);

			TOT_GPU_MEM_USAGE += ((float)(terDataBufSizeScaled * 4)) / (1024.0f * 1024.0f);
		}



		for (i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				glBindTexture(GL_TEXTURE_3D, volId);
				break;
			case 1:
				glBindTexture(GL_TEXTURE_3D, volIdEmpty);
				break;
			case 2:
				glBindTexture(GL_TEXTURE_3D, volIdLinear);
				break;
			case 3:
				glBindTexture(GL_TEXTURE_3D, volIdEmptyLinear);
				break;
			}
			if (i < 2)
			{
				curFilter = GL_NEAREST;
			}
			else
			{
				curFilter = GL_LINEAR;
			}

			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, bufferedPageSizeInUnits, bufferedPageSizeInUnits, bufferedPageSizeInUnits, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, curFilter);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, curFilter);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_3D, 0);
		}


		geomIdArr = new int[1024];
		paramArr = new float[4096];
		voroArr = new float[27 * 4];
		matCountArr = new float[256];
		paramArrMap = new float[4096];




		showMap = true;



		lastImageBuffer.data = NULL;
		lastImageBuffer.size = 0;

		lastJSONBuffer.data = NULL;
		lastJSONBuffer.size = 0;
		
		lastJSONBufferGUI.data = NULL;
		lastJSONBufferGUI.size = 0;
		

		nullBuffer.data = new char[1];
		nullBuffer.data[0] = '\0';
		nullBuffer.size = 0;



		palWidth = 256;
		palHeight = 256;

		resultImage = new unsigned char[palWidth * palHeight * 4];

		mouseMovingSize = 100;
		mouseMovingLoc = 0;
		mouseCount = 0;
		mouseMovingStepsBack = 20;
		mouseMoving = new FIVector4[mouseMovingSize];

		#ifdef USE_POCO
		myWS = _myWS;
		#endif
		

		

		isZooming = false;
		isPanning = false;
		isBare = true;




		defaultWinW = _defaultWinW / _scaleFactor;
		defaultWinH = _defaultWinH / _scaleFactor;
		scaleFactor = _scaleFactor;
		
		guiWinW = _defaultWinW / UI_SCALE_FACTOR;
		guiWinH = _defaultWinH / UI_SCALE_FACTOR;

		origWinW = _defaultWinW;
		origWinH = _defaultWinH;

		curBrushRad = 4.0f;

		mouseState = E_MOUSE_STATE_MOVE;








		wsBufferInvalid = true;

		bufferDim.setIXY(defaultWinW, defaultWinH);
		bufferDimTarg.setIXY(defaultWinW, defaultWinH);
		
		bufferDimHalf.setIXY(defaultWinW / 2, defaultWinH / 2);
		bufferModDim.copyIntMult(&bufferDim,holderMod);

		myTimer.start();
		//fpsTimer.start();

		//grassState = E_GRASS_STATE_OFF;

		activeObject = E_OBJ_CAMERA;

		extraRad = 0;
		lastTime = 0.0;







		mbDown = false;
		lbDown = false;
		rbDown = false;
		abDown = false;



		isFullScreen = false;
		shadersAreLoaded = 0;
		readyToRecompile = 0;

		programState = E_PS_IN_GAME;


		for (i = 0; i < E_OBJ_LENGTH; i++)
		{
			dynObjects.push_back(new DynObject());
		}

		dynObjects[E_OBJ_CAMERA]->init(0, 0, worldSizeInPixels.getIZ() / 2, 0, 0, 0, false, false, NULL, 4.0f );

		for (i = E_OBJ_LIGHT0; i < E_OBJ_LENGTH; i++)
		{

			j = i - E_OBJ_LIGHT0;

			switch (j)
			{
			case 0:
				ccr = 255;
				ccg = 255;
				ccb = 255;
				break;

			case 1:
				ccr = 255;
				ccg = 0;
				ccb = 0;

				break;

			case 2:
				ccr = 255;
				ccg = 128;
				ccb = 0;

				break;

			case 3:
				ccr = 0;
				ccg = 255;
				ccb = 0;

				break;

			case 4:
				ccr = 0;
				ccg = 128;
				ccb = 255;

				break;
			case 5:
				ccr = 128;
				ccg = 0;
				ccb = 255;

				break;
			}

			dynObjects[i]->init(4096*4 + i * 256, 4096*4 + i * 256, 4096*4, ccr, ccg, ccb,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );



		}

		dynObjects[E_OBJ_FOG]->init(-1024*2, -1024*2, -1024/2,   0, 0, 255,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		dynObjects[E_OBJ_CUTAWAY]->init(4096*4 - 256, 4096*4 - 256 + 2048, 4096*4,   0, 255, 0,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		dynObjects[E_OBJ_HUMAN]->init(0, 1024/2, 0,   0, 255, 255,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );

		// dynObjects[E_OBJ_P0]->init(512-256,1024-256,2048,   128,0,0,    true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		// dynObjects[E_OBJ_P1]->init(512,1024,2048,      255,0,0,  true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		// dynObjects[E_OBJ_P2]->init(1024,512,2048,      0,255,255,  true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );


		cameraZoom = 1.0f;
		targetZoom = 1.0f;

		mouseX = 0.0f;
		mouseY = 0.0f;
		mouseXUp = 0.0f;
		mouseYUp = 0.0f;






		//// GL WIDGET START ////

		frameCount = 0;
		changesMade = false;
		forceGetPD = false;
		bufferInvalid = false;
		mapInvalid = true;
		notQuit = true;
		timerNotSet = true;
		screenWidth = defaultWinW;
		screenHeight = defaultWinH;
		mouseLeftDown = mouseRightDown = false;
		mouseX = mouseY = 0;
		myDelta = 0.0f;



		//gm = new GameMap();
		orthographicProjection();
		//// GL WIDGET END ////



		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // 4-byte pixel alignment
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		//glEnable(GL_BLEND);

		
		
		
		shaderStrings.push_back("GUIShader");
		shaderStrings.push_back("RoadShader");
		shaderStrings.push_back("SkeletonShader");
		shaderStrings.push_back("DilateShader");
		shaderStrings.push_back("TerrainMix");
		shaderStrings.push_back("Simplex2D");
		shaderStrings.push_back("TopoShader");
		shaderStrings.push_back("TCShader");
		shaderStrings.push_back("TCShader2");
		shaderStrings.push_back("WaveHeightShader");
		shaderStrings.push_back("WaterShader");
		shaderStrings.push_back("WaterShaderCombine");
		shaderStrings.push_back("CopyShader");
		shaderStrings.push_back("CopyShader2");
		shaderStrings.push_back("NoiseShader");
		shaderStrings.push_back("MapBorderShader");
		shaderStrings.push_back("WorldSpaceShader");
		shaderStrings.push_back("BlitShader");
		shaderStrings.push_back("BlitParentShader");
		shaderStrings.push_back("PreLightingShader");
		shaderStrings.push_back("BlurShader");
		shaderStrings.push_back("HBlurShader");
		shaderStrings.push_back("VBlurShader");
		shaderStrings.push_back("DownScaleShader");
		shaderStrings.push_back("RadiosityShader");
		shaderStrings.push_back("RadiosityCombineShader");
		shaderStrings.push_back("FogShader");
		shaderStrings.push_back("GeomShader");
		shaderStrings.push_back("CombineShader");
		shaderStrings.push_back("GenerateVolume");
		shaderStrings.push_back("GenerateVolumeEnt");
		shaderStrings.push_back("RenderVolume");


		std::sort(shaderStrings.begin(), shaderStrings.end(), compareStruct);
		stringBuf.reserve(shaderStrings.size()*256);


		shaderTextureIds.push_back("Texture0");
		shaderTextureIds.push_back("Texture1");
		shaderTextureIds.push_back("Texture2");
		shaderTextureIds.push_back("Texture3");
		shaderTextureIds.push_back("Texture4");
		shaderTextureIds.push_back("Texture5");
		shaderTextureIds.push_back("Texture6");
		shaderTextureIds.push_back("Texture7");
		shaderTextureIds.push_back("Texture8");
		shaderTextureIds.push_back("Texture9");
		shaderTextureIds.push_back("Texture10");
		shaderTextureIds.push_back("Texture11");
		shaderTextureIds.push_back("Texture12");
		shaderTextureIds.push_back("Texture13");
		shaderTextureIds.push_back("Texture14");
		shaderTextureIds.push_back("Texture15");

		//setupLookups();

		for (i = 0; i < shaderStrings.size(); i++)
		{
			shaderMap.insert(  pair<string, Shader*>(shaderStrings[i], new Shader(this))  );
		}
		doShaderRefresh(false);
		
		int faceDim = 256;
		
		
		for (i = 0; i < MAX_VG_FBOS; i++) {
			vgFBOArr[i].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		}
		
		
		
		
		
		
		/* (
				int _numBufs,
				int _width,
				int _height,
				int _bytesPerChannel,
				bool _hasDepth,
				int filterEnum = GL_NEAREST,
				int clampEnum = GL_CLAMP_TO_EDGE,
				bool isMultisample = false
		)*/
		
		
		
		
		//GL_LINEAR
		fboMap["worldSpaceFBO"].init(4, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["worldSpaceWavesFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		
		//fboMap["worldSpaceBlurFBO0"].init(1, bufferDim.getIX()/2, bufferDim.getIY()/2, 4, false, GL_LINEAR);
		//fboMap["worldSpaceBlurFBO1"].init(1, bufferDim.getIX()/2, bufferDim.getIY()/2, 4, false, GL_LINEAR);
		
		fboMap["frontFaceFBO"].init(1, faceDim, faceDim, 4, false, GL_NEAREST);
		fboMap["backFaceFBO"].init(1, faceDim, faceDim, 4, false, GL_NEAREST);
		fboMap["frontFaceMapFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["backFaceMapFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["palFBO"].init(1, palWidth, palHeight, 1, false, GL_LINEAR);
		
		fboMap["pagesFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["waterFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["pages2FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["water2FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["pages3FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["water3FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["geomFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, true);
		fboMap["combineFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["combineFBOWithWater"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		
		fboMap["noiseFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["guiFBO"].init(1, guiWinW, guiWinH, 1, false, GL_LINEAR);
		fboMap["resultFBO0"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST);
		fboMap["resultFBO1"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST);
		//fboMap["volGenFBO0"].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		//fboMap["volGenFBO1"].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		fboMap["waveFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOLin0"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOLin1"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOBLin0"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOBLin1"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOLinHalf0"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOLinHalf1"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["cityFBO"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["hmFBO"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["hmFBOLinear"].init(1, newPitch, newPitch, 1, false, GL_LINEAR, GL_REPEAT);
		fboMap["simplexFBO"].init(1, newPitch, newPitch, 1, false, GL_LINEAR, GL_REPEAT);
		fboMap["swapFBO0"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["swapFBO1"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);


		
		createVTListTilt();



		fontWrappers[EFW_ICONS] = new FontWrapper();
		fontWrappers[EFW_ICONS]->init(this, "icons", true, 2.0f, 0.0f);
		
		fontWrappers[EFW_TEXT] = new FontWrapper();
		fontWrappers[EFW_TEXT]->init(this, "arial_regular_24", false, 1.0f);

		mainGUI = new GameGUI();
		mainGUI->init(this);


		loadAllData();

		GamePlant::initAllPlants(this);
		for (i = 0; i < E_PT_LENGTH/2; i++) {
			gamePlants[i] = new GamePlant();
		}


		gw = new GameWorld();
		
		gpuPool = new PoolManager();
		entityPool = new PoolManager();
		//gpuPagePool = new PoolPageManager();
		//entityPagePool = new PoolPageManager();
		
		
		gpuPool->init(this,false,false,holderResolution,holderResolution);
		entityPool->init(this,true,false,holderResolution,holderResolution);
		
		
		
		testHuman = new GameEnt();
		testHuman->init(this);
		
		gw->init(this);
		gw->initMap();
			
		
		music[EML_BIRDSONG0]->play();
		music[EML_CRICKETS0]->play();
		music[EML_OCEANWAVES0]->play();
		
		
		loadGUI();
		loadGUIValues();
		
		if (bakeParamsOn) {
			doShaderRefresh(true);
		}
		

		doTraceND("GW DONE");


		popTrace();



	}
	
	void prepSound(string soundName) {
		if (soundMap.find( soundName ) == soundMap.end()) {
			soundMap.insert( pair<string, GameSound>(soundName, GameSound()) );
			soundMap[soundName].init("..\\data\\sounds\\"+soundName+".wav");
		}
	}

	void playSoundPosAndPitch(
		string soundName,
		FIVector4* listenerPos,
		FIVector4* soundPos,
		float variance=0.0f,
		float volume=1.0f
	) {
		
		
		FIVector4 res;
		
		prepSound(soundName);
		
		res.setFXYZRef(soundPos);
		res.addXYZRef(listenerPos,-1.0f);
		
		soundMap[soundName].setPitch(
			(fGenRand()-0.5f)*2.0*variance + 1.0f
		);
		
		soundMap[soundName].setPositionAndMinDis(
			res.getFX(),
			res.getFY(),
			res.getFZ(),
			32.0f*pixelsPerMeter
		);
		soundMap[soundName].play(volume*fxVolume*masterVolume);
	}

	void playSound(string soundName, float volume=1.0f) {
		prepSound(soundName);
		soundMap[soundName].play(volume);
	}

	void playSoundEvent(const char* eventName, bool suppress = false) {
		
		if (suppress) {
			return;
		}
		
		string tempString;
		float volume;
		
		if (mainGUI != NULL) {
			if (mainGUI->isReady) {
				tempString = mainGUI->jvSounds->Child(eventName)->Child("name")->string_value;
				volume = mainGUI->jvSounds->Child(eventName)->Child("vol")->number_value;
				
				if (tempString.size() > 0) {
					playSound( tempString, masterVolume*volume*guiVolume );
				}
			}
		}
		
		
		
		
		
		
	}

	void dispatchEvent(
		int button,
		int state,
		float x,
		float y,
		UIComponent* comp,
		bool automated = false,
		bool preventRefresh = false
	) {
		
		changingGenVal = false;
		
		// if (guiLock) {
		// 	return;
		// }
		
		int i;
		int cbDataCount;
		JSONValue* cbData = NULL;
		
		bool doSPUpdate = false;
		bool mouseUpEvent = false;
		
		float curValue = comp->getValue();
		
		switch (comp->guiClass) {
			case E_GT_SLIDER:
			case E_GT_BUTTON:
			case E_GT_RADIO:
			
				switch(button) {
					case GLUT_NO_BUTTON:
					
						
						
						switch(state) {
							case GLUT_OVER:
								playSoundEvent("mouseOver",automated);
							break;
							case GLUT_OUT:
								playSoundEvent("mouseOut",automated);
							break;
							case GLUT_CHANGING:
								
								doSPUpdate = true;
							break;
						}
						
					break;
					case GLUT_LEFT_BUTTON:
						if (state == GLUT_DOWN) {
							playSoundEvent("mouseDown",automated);
						}
						else {
							playSoundEvent("mouseUp",automated);
							doSPUpdate = true;
							mouseUpEvent = true;
						}
					break;
					
				}
			
				
			break;	
		}
		
		
		if (comp->uid.compare("$options.sound.masterVolume") == 0) {
			masterVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.ambientVolume") == 0) {
			ambientVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.guiVolume") == 0) {
			guiVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.musicVolume") == 0) {
			musicVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.fxVolume") == 0) {
			fxVolume = curValue;
		}
		else if (comp->uid.compare("$charEdit.entOn") == 0) {
			entOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.pathfindingOn") == 0) {
			pathfindingOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.mirrorOn") == 0) {
			mirrorOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.applyToChildren") == 0) {
			applyToChildren = curValue != 0.0f;
		}
		
		
		if (comp->jvNodeNoTemplate != NULL) {
			if (comp->jvNodeNoTemplate->HasChild("callback")) {
				curCallback = comp->jvNodeNoTemplate->Child("callback")->string_value;
				
				if (comp->jvNodeNoTemplate->HasChild("callbackData")) {
					
					cbData = comp->jvNodeNoTemplate->Child("callbackData");
				
					// cbDataCount = cbData->CountChildren();
					// for (i = 0; i < cbDataCount; i++) {
					// 	cbDataStrings[i] = cbData->Child(i)->string_value;
					// }
				
				}
				
				if (doSPUpdate) {
					if (curCallback.compare("updateShaderParam") == 0) {
						
						if (cbData != NULL) {
							cbDataStrings[0] = cbData->Child("shaderName")->string_value;
							cbDataStrings[1] = cbData->Child("paramName")->string_value;
							
							
							
							shaderMap[cbDataStrings[0]]->paramMap[cbDataStrings[1]] = curValue;
							
							if (
								(cbDataStrings[0].compare("GenerateVolume") == 0)	||
								(cbDataStrings[0].compare("RenderVolume") == 0)
							) {
								
								if (preventRefresh) {
									
								}
								else {
									if (mouseUpEvent) {
										forceRestart = true;
										readyForRestart = true;
									}
									else {
										changingGenVal = true;
										if (mouseMoved) {
											
											readyForRestart = true;
										}
									}
								}
								
								
								
							}
							
							
						}
					}
				}
				
				
			}
		}
		
		
		if (mouseMoved) {
			mouseMoved = false;
		}
	}

	StyleSheet* getNewStyleSheet(string ssName) {
		styleSheetMap[ssName].init();
		return &(styleSheetMap[ssName]);
	}

	void initStyleSheet() {
		
		
		StyleSheet* mainSS = getNewStyleSheet("defaultSS");
		StyleSheetState* curState = &(mainSS->compStates[E_COMP_UP]);
		
		
		
		curState->setVal(E_SS_BGCOL0_R, 0.2f, 0.15f, 0.1f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.1f, 0.075f, 0.05f, 0.5f);
		curState->setVal(E_SS_FGCOL0_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_FGCOL1_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_TGCOL0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_TGCOL1_R, 1.0f, 0.25f, 0.0f, 0.5f);
		curState->setVal(E_SS_BGCOLTEXT0_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_BGCOLTEXT1_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.8f, 0.7f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 1.0f, 1.0f, 0.5f);

		curState->props[E_SS_PADDING] = 4.0f;
		curState->props[E_SS_BORDER] = 1.0f;
		curState->props[E_SS_MARGIN] = 4.0f;
		curState->props[E_SS_CORNERRAD] = 4.0f;
		curState->props[E_SS_ROUNDNESS] = 1.0f;

		mainSS->compStates[E_COMP_OVER].copyFrom(& (mainSS->compStates[E_COMP_UP]) );
		mainSS->compStates[E_COMP_DOWN].copyFrom(& (mainSS->compStates[E_COMP_UP]) );

		
		
		curState = &(mainSS->compStates[E_COMP_OVER]);
		
		
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->props[E_SS_BDCOL_A] = 1.0f;
		
		curState->setVal(E_SS_BGCOL0_R, 0.1f, 0.075f, 0.05f, 1.0);
		curState->setVal(E_SS_BGCOL1_R, 0.05f, 0.025f, 0.0125f, 0.5);
		
		
		
		curState = &(mainSS->compStates[E_COMP_DOWN]);
		
		
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.8f, 0.7f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->props[E_SS_BDCOL_A] = 1.0f;
		curState->props[E_SS_BORDER] = 2.0f;

		curState->setVal(E_SS_BGCOL0_R, 0.05f, 0.025f, 0.0125f, 0.5f);	
		curState->setVal(E_SS_BGCOL1_R, 0.1f, 0.075f, 0.05f, 1.0f);	
		
		
		
		StyleSheet* tooltipSS = getNewStyleSheet("tooltipSS");
		tooltipSS->copyFrom(mainSS);
		
		curState = &(tooltipSS->compStates[E_COMP_UP]);
		curState->setVal(E_SS_BGCOL0_R, 0.0f, 0.0f, 0.0f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.0f, 0.0f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 0.75f, 0.0f, 1.0f);
		tooltipSS->compStates[E_COMP_OVER].copyFrom(& (tooltipSS->compStates[E_COMP_UP]) );
		tooltipSS->compStates[E_COMP_DOWN].copyFrom(& (tooltipSS->compStates[E_COMP_UP]) );

		curState = &(tooltipSS->compStates[E_COMP_OVER]);
		curState = &(tooltipSS->compStates[E_COMP_DOWN]);
		
		
		
		
		StyleSheet* headerSS = getNewStyleSheet("headerSS");
		headerSS->copyFrom(mainSS);
		
		curState = &(headerSS->compStates[E_COMP_UP]);
		curState->setVal(E_SS_BGCOL0_R, 0.0f, 0.2f, 0.5f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.0f, 0.4f, 0.8f, 0.5f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 0.75f, 0.0f, 1.0f);
		headerSS->compStates[E_COMP_OVER].copyFrom(& (headerSS->compStates[E_COMP_UP]) );
		headerSS->compStates[E_COMP_DOWN].copyFrom(& (headerSS->compStates[E_COMP_UP]) );

		curState = &(headerSS->compStates[E_COMP_OVER]);
		curState = &(headerSS->compStates[E_COMP_DOWN]);
		
		
		
	}

	int requestTerIndex(int requestingBlockId)
	{


		int i;

		bool foundFree = false;

		float bestDis;
		float testDis;
		int bestInd = 0;

		GameBlock *curBlock;

		// find if blockId already in use
		for (i = 0; i < MAX_TER_TEX; i++)
		{
			if (terTextures[i].usedByBlockId == requestingBlockId)
			{
				return i;
			}
		}

		// find if any blockIds not in use
		for (i = 0; i < MAX_TER_TEX; i++)
		{
			if (terTextures[i].usedByBlockId == -1)
			{
				bestInd = i;
				foundFree = true;
				break;
			}
		}

		if (foundFree)
		{

		}
		else
		{

			// find furthest blockId
			for (i = 0; i < MAX_TER_TEX; i++)
			{

				curBlock = gw->getBlockAtId(terTextures[i].usedByBlockId);
				testDis = curBlock->offsetInBlocks.distance(&(gw->camBlockPos));

				if (i == 0)
				{
					bestInd = 0;
					bestDis = testDis;
				}
				else
				{
					if (testDis > bestDis)
					{
						bestDis = testDis;
						bestInd = i;
					}
				}

			}

		}

		terTextures[bestInd].usedByBlockId = requestingBlockId;
		terTextures[bestInd].alreadyBound = false;
		return bestInd;


	}


	static void qNormalizeAngle(int &angle)
	{
		while (angle < 0)
		{
			angle += 360 * 16;
		}
		while (angle > 360 * 16)
		{
			angle -= 360 * 16;
		}
	}


	void perspectiveProjection()
	{
		float aspect = 1.0;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-aspect, +aspect, -1.0, +1.0, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
	}

	void orthographicProjection()
	{

		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

	}





	////// END GLWIDGET ////








	









	~Singleton()
	{
		if (gw)
		{
			delete gw;
		}
	}



	


	void setProgAction(eProgramState ps, unsigned char kc, eProgramAction pa, bool isDown)
	{

		if (isDown)
		{
			progActionsDown[ps * 256 + kc] = pa;
		}
		else
		{
			progActionsUp[ps * 256 + kc] = pa;
		}
	}

	void setProgActionAll(unsigned char kc, eProgramAction pa, bool isDown)
	{
		int i;

		for (i = 0; i < E_PS_SIZE; i++)
		{
			setProgAction((eProgramState)i, kc, pa, isDown);
		}

	}


	// void createGrassList(int index) {


	//  int i;
	//  int j;

	//  float fi;
	//  float fj;


	//  int spacing = 1;
	//  float multiplier = 1.0f;

	//  switch (index) {
	//    case 0:
	//      spacing = 8;
	//      multiplier = 1.0f;
	//    break;

	//    case 1:
	//      spacing = 4;
	//      multiplier = 2.0f;
	//    break;

	//    case 2:
	//      spacing = 2;
	//      multiplier = 4.0f;
	//    break;

	//    case 3:
	//      spacing = 2;
	//      multiplier = 8.0f;
	//    break;
	//  }


	//  int iMax = DEF_WIN_W/spacing;//bufferDim.getIX()/spacing;
	//  int jMax = DEF_WIN_H/spacing;//bufferDim.getIY()/spacing;

	//  float fiMax = (float)iMax;
	//  float fjMax = (float)jMax;

	//  grassTris[index] = glGenLists(1);


	//  glNewList(grassTris[index], GL_COMPILE);

	//  //glBegin(GL_TRIANGLES);
	//  glBegin(GL_QUADS);

	//  //glNormal3f(0, 0, 1);



	//  for (j = jMax-1; j >= 0; j -= 1) {
	//    fj = ((float)(j*2-jMax) + 1.0f)*multiplier/fjMax;
	//    for (i = 0; i < iMax; i += 1) {
	//      fi = ((float)(i*2-iMax) + 1.0f)*multiplier/fiMax;

	//      glMultiTexCoord4f( GL_TEXTURE0, fi, fj, 0.2f, -1.0);
	//      glVertex3f(fi,fj,0.0);


	//      glMultiTexCoord4f( GL_TEXTURE0, fi, fj, 0.0f, 0.0);
	//      glVertex3f(fi,fj,0.0f);


	//      glMultiTexCoord4f( GL_TEXTURE0, fi, fj, 0.2f, 1.0);
	//      glVertex3f(fi,fj,0.0f);


	//      glMultiTexCoord4f( GL_TEXTURE0, fi, fj, 1.0f, 0.0);
	//      glVertex3f(fi,fj,0.0f);


	//    }



	//  }

	//  glEnd();

	//  glEndList();

	// }

	void drawCrossHairs(FIVector4 originVec, float radius)
	{
		FIVector4 minV;
		FIVector4 maxV;

		float xm;
		float ym;
		float zm;

		float maxRad = 4096.0f;

		int i;
		for (i = 0; i < 3; i++)
		{

			switch (i)
			{
			case 0:
				xm = maxRad;
				ym = radius;
				zm = radius;
				break;
			case 1:
				xm = radius;
				ym = maxRad;
				zm = radius;
				break;
			case 2:
				xm = radius;
				ym = radius;
				zm = maxRad;
				break;
			}

			minV.setFXYZ(
				originVec.getFX() - xm,
				originVec.getFY() - ym,
				originVec.getFZ() - zm
			);

			maxV.setFXYZ(
				originVec.getFX() + xm,
				originVec.getFY() + ym,
				originVec.getFZ() + zm
			);

			drawBox(&minV, &maxV);
		}


	}

	void drawLine(FIVector4 *p0, FIVector4 *p1)
	{
		

		glBegin(GL_LINES);
		glMultiTexCoord3f(GL_TEXTURE0, 0.0f, 0.0f, 0.0f);
		glVertex3f(p0->getFX(), p0->getFY(), p0->getFZ());
		glMultiTexCoord3f(GL_TEXTURE0, 0.0f, 0.0f, 1.0f);
		glVertex3f(p1->getFX(), p1->getFY(), p1->getFZ());
		glEnd();
	}


	void drawCubeCentered(FIVector4 *originVec, float radius)
	{
		FIVector4 minV;
		FIVector4 maxV;

		minV.setFXYZ(
			originVec->getFX() - radius,
			originVec->getFY() - radius,
			originVec->getFZ() - radius
		);

		maxV.setFXYZ(
			originVec->getFX() + radius,
			originVec->getFY() + radius,
			originVec->getFZ() + radius
		);

		drawBox(&minV, &maxV);
	}

	void drawBoxUp(FIVector4 originVec, float radiusX, float radiusY, float diamZ)
	{
		FIVector4 minV;
		FIVector4 maxV;

		minV.setFXYZ(
			originVec.getFX() - radiusX,
			originVec.getFY() - radiusY,
			originVec.getFZ()
		);

		maxV.setFXYZ(
			originVec.getFX() + radiusX,
			originVec.getFY() + radiusY,
			originVec.getFZ() + diamZ
		);

		drawBox(&minV, &maxV);
	}


	void drawBox(FIVector4 *minVec, FIVector4 *maxVec, int faceFlag=2)
	{


		float minX = minVec->getFX();
		float minY = minVec->getFY();
		float minZ = minVec->getFZ();

		float maxX = maxVec->getFX();
		float maxY = maxVec->getFY();
		float maxZ = maxVec->getFZ();


		bool drawFront = false;
		bool drawBack = false;
		
		switch(faceFlag) {
			case 0:
				drawBack = true;
			break;
			case 1:
				drawFront = true;
			break;
			case 2:
				drawBack = true;
				drawFront = true;
			break;
		}

		glBegin(GL_QUADS);


		if (drawFront) {
			// front
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			// right
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			// top
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
		}
		
		
		if (drawBack) {
			// back
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
			// left
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			// bottom
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
		}
		
		
		
		
		



		glEnd();
	}



	void createVTListTilt()
	{

		int i;
		int j;

		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		//volTris = glGenLists(1);

		float halfTilt = tiltAmount/2.0f;
		
		float halfTiltUp = 0.5f + halfTilt;
		float halfTiltDn = 0.5f - halfTilt;

		float texMin = 0.0f;
		float texMax = 1.0f;

		float fx1 = -1.0f;
		float fy2 = -1.0f;
		float fx2 = 1.0f;
		float fy1 = 1.0f;

		float centerX = (fx1 + fx2) / 2.0f;
		//float centerY = (fy1 + fy2) / 2.0f;

		float fy25 = fy1 * halfTiltUp + fy2 * halfTiltDn;
		float fy75 = fy1 * halfTiltDn + fy2 * halfTiltUp;

		float coordsX[8];
		float coordsY[8];

		coordsX[0] = centerX;
		coordsY[0] = fy1 * tiltAmount + fy2 * (1.0-tiltAmount);//centerY; // back face center

		coordsX[1] = centerX;
		coordsY[1] = fy1;

		coordsX[2] = fx2;
		coordsY[2] = fy25;

		coordsX[3] = fx2;
		coordsY[3] = fy75;

		coordsX[4] = centerX;
		coordsY[4] = fy2;

		coordsX[5] = fx1;
		coordsY[5] = fy75;

		coordsX[6] = fx1;
		coordsY[6] = fy25;

		coordsX[7] = coordsX[1];
		coordsY[7] = coordsY[1];

		float backfaceX[8];
		float backfaceY[8];
		float backfaceZ[8];



		backfaceX[0] = texMin;
		backfaceY[0] = texMin;
		backfaceZ[0] = texMin;
		backfaceX[1] = texMin;
		backfaceY[1] = texMin;
		backfaceZ[1] = texMax;
		backfaceX[2] = texMax;
		backfaceY[2] = texMin;
		backfaceZ[2] = texMax;
		backfaceX[3] = texMax;
		backfaceY[3] = texMin;
		backfaceZ[3] = texMin;
		backfaceX[4] = texMax;
		backfaceY[4] = texMax;
		backfaceZ[4] = texMin;
		backfaceX[5] = texMin;
		backfaceY[5] = texMax;
		backfaceZ[5] = texMin;
		backfaceX[6] = texMin;
		backfaceY[6] = texMax;
		backfaceZ[6] = texMax;
		backfaceX[7] = backfaceX[1];
		backfaceY[7] = backfaceY[1];
		backfaceZ[7] = backfaceZ[1];


		//glNewList(volTris, GL_COMPILE);
		
		
		// string s = floatToHex(64.33f);
		// float tempv = hexToFloat(s.c_str());
		// cout << "\n\n\nfloatToHex: " << s << "\n";
		// cout << "\n\n\nhexToFloat: " << tempv << "\n";
		
		

		for (j = 0; j < 2; j++) {
			
			bindShader("TCShader");
			
			if (j == 0) {
				bindFBO("frontFaceFBO");
			}
			else {
				coordsY[0] = fy2 * tiltAmount + fy1 * (1.0-tiltAmount);
				bindFBO("backFaceFBO");
			}
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0, 0, 1);
			for (i = 0; i < 8; i++)
			{

				if (j == 0) { // front faces
					if (i == 0)
					{
						glMultiTexCoord3f( GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);
					}
				}
				else { // back faces
					glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);
				}
				

				glVertex3f(coordsX[i], coordsY[i], 0.0f);
			}
			glEnd();
			
			
			
			unbindFBO();
			unbindShader();
			
		}
		
		
		
		tempVec1.setFXYZ(
			cameraPos->getFX() - worldSizeInPixels.getFX() / 2.0f,
			cameraPos->getFY() - worldSizeInPixels.getFY() / 2.0f,
			0.0f
		);
		tempVec2.setFXYZ(
			cameraPos->getFX() + worldSizeInPixels.getFX() / 2.0f,
			cameraPos->getFY() + worldSizeInPixels.getFY() / 2.0f,
			worldSizeInPixels.getFZ()*1.0f // TODO: SHOULD BE NO MULTIPLER HERE
		);
		
		for (j = 0; j < 2; j++) {
			
			bindShader("TCShader2");
			
			if (j == 0) {
				bindFBO("backFaceMapFBO");
			}
			else {
				bindFBO("frontFaceMapFBO");
			}
			
			setShaderFloat("fHolderMod", fHolderMod);
			setShaderFloat("tiltAmount", tiltAmount);
			setShaderFloat("cameraZoom", cameraZoom);
			setShaderfVec2("bufferDim", &(bufferDim));
			setShaderfVec3("cameraPos", cameraPos);
			
			drawBox(&tempVec1,&tempVec2,j);

			unbindFBO();
			unbindShader();
			
		}
		
		

		


		//glEndList();
	}

	void createVTList()
	{

		volTris = glGenLists(1);


		float texMin = 0.0f;
		float texMax = 1.0f;

		float fx1 = -1.0f;
		float fy2 = -1.0f;
		float fx2 = 1.0f;
		float fy1 = 1.0f;

		float centerX = (fx1 + fx2) / 2.0f;
		float centerY = (fy1 + fy2) / 2.0f;

		float fy25 = fy1 * 0.75f + fy2 * 0.25f;
		float fy75 = fy1 * 0.25f + fy2 * 0.75f;

		float coordsX[8];
		float coordsY[8];

		coordsX[0] = centerX;
		coordsY[0] = centerY;

		coordsX[1] = centerX;
		coordsY[1] = fy1;

		coordsX[2] = fx2;
		coordsY[2] = fy25;

		coordsX[3] = fx2;
		coordsY[3] = fy75;

		coordsX[4] = centerX;
		coordsY[4] = fy2;

		coordsX[5] = fx1;
		coordsY[5] = fy75;

		coordsX[6] = fx1;
		coordsY[6] = fy25;

		coordsX[7] = coordsX[1];
		coordsY[7] = coordsY[1];

		float backfaceX[8];
		float backfaceY[8];
		float backfaceZ[8];



		backfaceX[0] = texMin;
		backfaceY[0] = texMin;
		backfaceZ[0] = texMin;
		backfaceX[1] = texMin;
		backfaceY[1] = texMin;
		backfaceZ[1] = texMax;
		backfaceX[2] = texMax;
		backfaceY[2] = texMin;
		backfaceZ[2] = texMax;
		backfaceX[3] = texMax;
		backfaceY[3] = texMin;
		backfaceZ[3] = texMin;
		backfaceX[4] = texMax;
		backfaceY[4] = texMax;
		backfaceZ[4] = texMin;
		backfaceX[5] = texMin;
		backfaceY[5] = texMax;
		backfaceZ[5] = texMin;
		backfaceX[6] = texMin;
		backfaceY[6] = texMax;
		backfaceZ[6] = texMax;
		backfaceX[7] = backfaceX[1];
		backfaceY[7] = backfaceY[1];
		backfaceZ[7] = backfaceZ[1];


		glNewList(volTris, GL_COMPILE);

		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, 1);

		int i;

		for (i = 0; i < 8; i++)
		{

			//glColor4f(backfaceX[i], backfaceY[i], backfaceZ[i], 1.0f);

			glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);

			if (i == 0)
			{
				//glColor4f((backfaceX[i]+1.0f)/2.0f, (backfaceY[i]+1.0f)/2.0f, (backfaceZ[i]+1.0f)/2.0f, 1.0f);
				glMultiTexCoord3f( GL_TEXTURE1, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				glMultiTexCoord3f( GL_TEXTURE1, backfaceX[i], backfaceY[i], backfaceZ[i]);
			}

			glVertex3f(coordsX[i], coordsY[i], 0.0f);
		}

		glEnd();


		glEndList();
	}



	void doShaderRefresh(bool doBake)
	{

		LAST_COMPILE_ERROR = false;

		readyToRecompile = 0;

		int i;
		int j;
		
		Shader* curShader;


		for (i = 0; i < shaderStrings.size(); i++) {
			shaderMap[ shaderStrings[i] ]->init( "../src/glsl/" + shaderStrings[i] + ".c", doBake);
		}
		shadersAreLoaded = 1;
		readyToRecompile = 1;
		
		if (LAST_COMPILE_ERROR) {
			
		}
		else {
			
			// load saved data (if exists)
			// merge saved data with existing data (if exists)
			// save merged data to saved data
			
			
			stringBuf = "{\n\t\"params\":[\n";
			
			
			
			for (i = 0; i < shaderStrings.size(); i++) {
				curShader = shaderMap[ shaderStrings[i] ];
				
				std::sort(curShader->paramVec.begin(), curShader->paramVec.end(), compareStruct);
				
				for (j = 0; j < curShader->paramVec.size(); j++) {
					stringBuf.append("\t\t{");
					stringBuf.append("\"shaderName\":\""+shaderStrings[i]+"\",");
					stringBuf.append("\"paramName\":\""+curShader->paramVec[j]+"\",");
					stringBuf.append("\"uid\":\"$shaderParams."+shaderStrings[i]+"."+curShader->paramVec[j]+"\"");
					stringBuf.append("},\n");
				}
			}
			
			stringBuf[stringBuf.size()-2] = ' ';
			
			
			stringBuf.append("\t]\n}\n\n");
			
			// this should automatically clear the key
			// and deallocate existing entries
			//internalJSON.insertValue("shaderParams", JSON::Parse(stringBuf.c_str()));
			
			processJSONFromString(
				&stringBuf,
				&(internalJSON["shaderParams"].jv)
			);
			
			// cout << "stringBuf:\n\n";
			// cout << stringBuf;
			
			
		}
		

	}





	void setMatrices(int w, int h)
	{

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

	}

	void setWH(int w, int h)
	{

		baseW = w;
		baseH = h;
	}

	void sampleFBODirect(FBOSet *fbos, int offset = 0)
	{
		int i;
		if (shadersAreLoaded)
		{
			for (i = 0; i < fbos->numBufs; i++)
			{
				setShaderTexture(i + offset, fbos->fbos[i].color_tex);
			}
		}
	}

	void unsampleFBODirect(FBOSet *fbos, int offset = 0)
	{
		int i;
		if (shadersAreLoaded)
		{
			for (i = fbos->numBufs - 1; i >= 0; i--)
			{
				setShaderTexture(i + offset, 0);
			}
		}
	}



	void bindFBODirect(FBOSet *fbos, int doClear = 1)
	{
		setMatrices(fbos->width, fbos->height);
		fbos->bind(doClear);
		currentFBOResolutionX = fbos->width;
		currentFBOResolutionY = fbos->height;
	}

	////




	void sampleFBO(string fboName, int offset = 0, int swapFlag = -1)
	{
		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "0"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "1"]);
			}

		}

		if (fbos)
		{
			sampleFBODirect(fbos, offset);
		}
		else
		{
			doTrace("sampleFBO: Invalid FBO Name");
		}


	}

	void unsampleFBO(string fboName, int offset = 0, int swapFlag = -1)
	{

		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "0"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "1"]);
			}

		}

		if (fbos)
		{
			unsampleFBODirect(fbos, offset);
		}
		else
		{
			doTrace("unsampleFBO: Invalid FBO Name");
		}

	}

	FBOSet *getFBOSet (string fboName)
	{
		return &(fboMap[fboName]);
	}

	FBOWrapper *getFBOWrapper (string fboName, int offset)
	{
		FBOSet *fbos = &(fboMap[fboName]);
		return fbos->getFBOWrapper(offset);
	}

	
	
	void copyFBO(string src, string dest, int num = 0)
	{
		bindShader("CopyShader");
		bindFBO(dest);
		//sampleFBO(src, 0);
		setShaderTexture(0, getFBOWrapper(src,num)->color_tex);
		drawFSQuad(1.0f);
		unsampleFBO(src, 0);
		unbindFBO();
		unbindShader();
	}

	void copyFBO2(string src, string dest)
	{
		bindShader("CopyShader2");
		bindFBO(dest);
		sampleFBO(src, 0);
		drawFSQuad(1.0f);
		unsampleFBO(src, 0);
		unbindFBO();
		unbindShader();
	}

	void bindFBO(string fboName, int swapFlag = -1)
	{

		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "1"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "0"]);
			}

		}

		if (fbos)
		{
			bindFBODirect(fbos);
		}
		else
		{
			doTrace("bindFBO: Invalid FBO Name");
		}


	}

	void unbindFBO()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		setMatrices(baseW, baseH);

	}



	void bindShader(string shaderName)
	{
		
		int i;
		int totSize;

		if (shadersAreLoaded)
		{
			curShader = shaderName;
			curShaderPtr = shaderMap[curShader];
			curShaderPtr->bind();
			
			totSize = curShaderPtr->paramVec.size();
			
			if (bakeParamsOn) {
				
			}
			else {
				for (i = 0; i < totSize; i++) {
					setShaderFloat(
						curShaderPtr->paramVec[i],
						curShaderPtr->paramMap[curShaderPtr->paramVec[i]]
					);
				}
			}
			
		}

	}

	void unbindShader()
	{
		if (shadersAreLoaded)
		{
			curShaderPtr->unbind();
		}
	}

	void setShaderArrayfVec3(string paramName, float *x, int count)
	{
		curShaderPtr->setShaderArrayfVec3(paramName, x, count);
	}
	void setShaderArrayfVec4(string paramName, float *x, int count)
	{
		curShaderPtr->setShaderArrayfVec4(paramName, x, count);
	}

	void setShaderArray(string paramName, float *x, int count)
	{
		curShaderPtr->setShaderArray(paramName, x, count);
	}
	void setShaderFloat(string paramName, float x)
	{
		curShaderPtr->setShaderFloat(paramName, x);
	}
	void setShaderInt(string paramName, int x)
	{
		curShaderPtr->setShaderInt(paramName, x);
	}
	void setShaderfVec2(string paramName, FIVector4 *v)
	{
		curShaderPtr->setShaderfVec2(paramName, v);
	}
	void setShaderVec2(string paramName, float x, float y)
	{
		curShaderPtr->setShaderVec2(paramName, x, y);
	}
	void setShaderVec3(string paramName, float x, float y, float z)
	{
		curShaderPtr->setShaderVec3(paramName, x, y, z);
	}
	void setShaderfVec3(string paramName, FIVector4 *v)
	{
		curShaderPtr->setShaderfVec3(paramName, v);
	}

	void setShaderVec4(string paramName, float x, float y, float z, float w)
	{
		curShaderPtr->setShaderVec4(paramName, x, y, z, w);
	}
	void setShaderfVec4(string paramName, FIVector4 *v)
	{
		curShaderPtr->setShaderfVec4(paramName, v);
	}



	void setShaderFloatUB(string paramName, float x)
	{
		curShaderPtr->setShaderFloatUB(paramName, x);
	}
	void setShaderfVec4UB(string paramName, FIVector4 *v)
	{
		curShaderPtr->setShaderfVec4UB(paramName, v);
	}



	void updateUniformBlock(int ubIndex, int ubDataSize = -1)
	{
		curShaderPtr->updateUniformBlock(ubIndex, ubDataSize);
	}
	void invalidateUniformBlock(int ubIndex)
	{
		curShaderPtr->invalidateUniformBlock(ubIndex);
	}
	void beginUniformBlock(int ubIndex)
	{
		curShaderPtr->beginUniformBlock(ubIndex);
	}
	bool wasUpdatedUniformBlock(int ubIndex)
	{

		return curShaderPtr->wasUpdatedUniformBlock(ubIndex);

	}

	void setShaderTexture(int multitexNumber, uint texId)
	{
		if (shadersAreLoaded)
		{
			glActiveTexture(GL_TEXTURE0 + multitexNumber);
			glBindTexture(GL_TEXTURE_2D, texId);
			curShaderPtr->setShaderInt(shaderTextureIds[multitexNumber] , multitexNumber);
		}
	}

	void setShaderTexture3D(int multitexNumber, uint texId)
	{
		if (shadersAreLoaded)
		{
			glActiveTexture(GL_TEXTURE0 + multitexNumber);
			glBindTexture(GL_TEXTURE_3D, texId);
			curShaderPtr->setShaderInt(shaderTextureIds[multitexNumber], multitexNumber);
		}
	}


	bool shiftDown()
	{
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_SHIFT);
	}

	bool ctrlDown()
	{
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_CTRL);
	}

	bool altDown()
	{
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_ALT);
	}


	void drawQuadBounds(float fx1, float fy1, float fx2, float fy2, float fz)
	{
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx1, fy1, fz);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fx2, fy1, fz);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx2, fy2, fz);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(fx1, fy2, fz);

		glEnd();
	}

	void drawFSQuad(float zoom)
	{
		drawFSQuadOffset(0.0f, 0.0f, zoom);
	}

	void drawFSQuadOffset(float xOff, float yOff, float zoom)
	{
		float fx1 = (xOff - 1.0f) * zoom;
		float fy1 = (yOff - 1.0f) * zoom;
		float fx2 = (xOff + 1.0f) * zoom;
		float fy2 = (yOff + 1.0f) * zoom;

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
	}

	void drawFBO(string fboName, int ind, float zoom, int swapFlag = -1)
	{
		if (swapFlag == -1)
		{
			drawFBOOffset(fboName, ind, 0.0f, 0.0f, zoom);
		}
		else
		{
			if (swapFlag == 0)
			{
				drawFBOOffset(fboName + "1", ind, 0.0f, 0.0f, zoom);
			}
			else
			{
				drawFBOOffset(fboName + "0", ind, 0.0f, 0.0f, zoom);
			}

		}
	}

	void drawFBOOffsetDirect(FBOSet *fbos, int ind, float xOff, float yOff, float zoom)
	{

		glBindTexture(GL_TEXTURE_2D, fbos->fbos[ind].color_tex);
		//glClearColor(0.2,0.2,0.2,0.0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawFSQuadOffset(xOff, yOff, zoom);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void drawFBOOffset(string fboName, int ind, float xOff, float yOff, float zoom)
	{
		FBOSet *fbos = &(fboMap[fboName]);

		if (fbos)
		{
			drawFBOOffsetDirect(fbos, ind, xOff, yOff, zoom);
		}
		else
		{
			doTrace("drawFBOOffsetDirect: Invalid FBO Name");
		}

	}
	
	
	float getTerHeightScaled(float val)
	{
		return mixf(0.125f,0.875f,val)*worldSizeInPixels.getFZ();
		
	}


	float getSLNormalized()
	{
		return (((float)gw->seaLevel) / 255.0f);
	}
	float getSLInPixels()
	{
		return getSLNormalized()*worldSizeInPixels.getFZ() + 2.5f*pixelsPerMeter;
	}

	float getHeightAtPixelPos(float x, float y, bool dd = false)
	{
		FBOWrapper *fbow;
		float xc;
		float yc;

		int channel = 0;

		float testHeight;
		
		float v0;
		float v1;
		float v2;
		float v3;
		
		if (mapInvalid)
		{

			cout << "mapInvalid\n";
			return 0.0f;

		}
		else
		{
			FBOWrapper *fbow = getFBOWrapper("hmFBO", 0);

			xc = (x / worldSizeInPixels.getFX()) * ((float)fbow->width);
			yc = (y / worldSizeInPixels.getFY()) * ((float)fbow->height);

			v0 = fbow->getPixelAtLinear((xc * mapFreqs.getFX()), (yc * mapFreqs.getFX()), channel);
			v1 = fbow->getPixelAtLinear((xc * mapFreqs.getFY()), (yc * mapFreqs.getFY()), channel);
			v2 = fbow->getPixelAtLinear((xc * mapFreqs.getFZ()), (yc * mapFreqs.getFZ()), channel);
			v3 = fbow->getPixelAtLinear((xc * mapFreqs.getFW()), (yc * mapFreqs.getFW()), channel);


			if (dd) {
				//cout << "hmvals: " << v0 << ", " << v1 << ", " << v2 << ", " << v3 << "\n";
			}
			

			testHeight = 
				  v0 * mapAmps.getFX()
				+ v1 * mapAmps.getFY()
				+ v2 * mapAmps.getFZ()
				+ v3 * mapAmps.getFW()
				
				- v1 * mapAmps.getFY()*0.5f
				- v2 * mapAmps.getFZ()*0.5f
				- v3 * mapAmps.getFW()*0.5f
				
			;
			
			if (dd) {
				//cout << "testHeight " << testHeight << "\n";
			}

			testHeight = clampf(testHeight,0.0f,1.0f);

			return getTerHeightScaled(testHeight);



		}



	}
	
	void syncObjects(FIVector4* bp) {
		int i;
		
		for (i = 1; i < E_OBJ_LENGTH; i++)
		{

			if (dynObjects[i]->isRelative)
			{
				dynObjects[i]->pos.copyFrom(bp);
				dynObjects[i]->pos.addXYZRef( &(dynObjects[i]->posRel) );
			}

		}
	}

	void moveCamera(FIVector4 *pModXYZ)
	{
		
		int i;
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		
		gw->curLoadRadius = minWInPages;
		
		// cout << "curHeight: " <<
		// 	getHeightAtPixelPos(cameraPos->getFX(), cameraPos->getFY(), true)/worldSizeInPixels.getFZ() << "\n";
		
		
		wsBufferInvalid = true;

		cameraPos->addXYZRef(pModXYZ);


		pModXYZ->setFZ(0.0f);

		if (cameraPos->getFX() > worldSizeInPixels.getFX() / 2.0)
		{
			cameraPos->setFX( cameraPos->getFX() - worldSizeInPixels.getFX() );
		}
		if (cameraPos->getFX() < -worldSizeInPixels.getFX() / 2.0)
		{
			cameraPos->setFX( cameraPos->getFX() + worldSizeInPixels.getFX() );
		}
		if (cameraPos->getFY() > worldSizeInPixels.getFY() / 2.0)
		{
			cameraPos->setFY( cameraPos->getFY() - worldSizeInPixels.getFY() );
		}
		if (cameraPos->getFY() < -worldSizeInPixels.getFY() / 2.0)
		{
			cameraPos->setFY( cameraPos->getFY() + worldSizeInPixels.getFY() );
		}



		syncObjects(cameraPos);

		isPanning = true;
	}
	
	GameEntNode* getMirroredNode(GameEntNode* curNode) {
		if ((curNode->nodeName < E_BONE_C_BEG)&&mirrorOn) {
			if (curNode->nodeName <= E_BONE_L_END) {
				return testHuman->baseNode->getNode(
					curNode->nodeName+(E_BONE_R_BEG-E_BONE_L_BEG)
				);
			}
			else {
				return testHuman->baseNode->getNode(
					curNode->nodeName-(E_BONE_R_BEG-E_BONE_L_BEG)
				);
			}
		}
		else {
			return NULL;
		}
		
	}



	void applyNodeChanges(GameEntNode* _curNode, float dx, float dy) {
		
		GameEntNode* curNode = _curNode;
		
		int i;
		int j;
		int k;
		
		float xm = 0.0f;
		float ym = 0.0f;
		float zm = 0.0f;
		
		float dirMod = 1.0f;
		
		if (
			(curNode->nodeName < E_BONE_C_BEG) &&
			(mirrorOn)
		) {
			j = 2;
		}
		else {
			j = 1;
		}
		
		for (i = 0; i < j; i++) {
			
			
			if (i == 1) {
				curNode = getMirroredNode(curNode);
				
				dirMod = -1.0f;
			}
			
			
			if (abDown) {
				makeDirty();
			}
			
			xm = dx/50.0f;
			ym = dy/50.0f;
			
			if (shiftDown()) { // || altDown()
								
				if (lbDown) {
					curNode->tbnRadScale0.addXYZ(0.0f,xm,ym);
				}
				if (rbDown) {
					curNode->tbnRadScale1.addXYZ(0.0f,xm,ym);
				}
				if (mbDown) {
					curNode->boneLengthScale += ym;
				}
			}
			else {
				
				if (lbDown) {
					curNode->rotThe += dirMod*ym;
				}
				if (rbDown) {
					curNode->rotRho += dirMod*ym;
				}
				if (mbDown) {
					curNode->rotPhi += dirMod*ym;
				}
				
				
			}
			
			if (applyToChildren) {
				for (k = 0; k < curNode->children.size(); k++) {
					applyNodeChanges(curNode->children[k], dx, dy);
				}
			}
			
			
		}
			
		
	}

	void moveObject(float dx, float dy, float zoom)
	{

		int i;
		int j;
		
		
		
		GameEntNode* curNode;

		float tilt = tiltAmount;
		float itilt = (1.0-tiltAmount);

		modXYZ.setFXYZ(0.0f,0.0f,0.0f);

		float dxZoom = dx * fHolderMod / zoom;
		float dyZoom = dy * fHolderMod / zoom;

		

		//float grassWidth;
		//float grassHeight;

		bool doDefault = false;
		
		
		
		
		float tileWidth = 1.0;
		float tileHeight = itilt;

		



		if (abDown)
		{
			// if (rbDown || (shiftDown() ) )
			// {
			// 	modXYZ.setFZ(  dyZoom );
			// 	modXYZ.setFX( -(0.0f + dxZoom / 2.0f) );
			// 	modXYZ.setFY( -(0.0f - dxZoom / 2.0f) );

			// }
			// else
			// {
			// 	modXYZ.setFX( -(dyZoom + dxZoom / 2.0f) );
			// 	modXYZ.setFY( -(dyZoom - dxZoom / 2.0f) );
			// }
			
			
			// screen to world
			
			if (rbDown || (shiftDown() ) )
			{
				modXYZ.setFZ(  dyZoom*1.0/tilt );
				modXYZ.setFX( -(0.0f + dxZoom) );
				modXYZ.setFY( -(0.0f - dxZoom) );

			}
			else
			{
				
				//iX = (((ScreenX) / tileWidth) - ((ScreenY) / tileHeight));
				//iY = (((ScreenX) / tileWidth) + ((ScreenY) / tileHeight));
				
				
				modXYZ.setFX( -(dyZoom*1.0/itilt + 1.0*dxZoom) );
				modXYZ.setFY( -(dyZoom*1.0/itilt - 1.0*dxZoom) );
				
			}
			

			lastModXYZ.addXYZRef(&modXYZ);




		}
		
		
		if (
			(entOn) && 
			(activeNode != NULL)
		) {
				
			applyNodeChanges(activeNode, dx, dy);
			
		}
		else {
			if (shiftDown())
			{
				
				
				if ((mouseState == E_MOUSE_STATE_BRUSH)&&lbDown)
				{
					curBrushRad -= modXYZ.getFZ() / 50.0f;

					if (curBrushRad < 0.0f)
					{
						curBrushRad = 0.0f;
					}
				}
				else
				{
					
					if (rbDown) {
						tiltAmount -=  modXYZ.getFZ()*zoom / 500.0f;
						
						tiltAmount = clampf(tiltAmount, 0.125f, 0.75f);
						
						tiltChanged = true;
						changesMade = true;
					}
					
				}

			}
			else
			{
				if (mouseState == E_MOUSE_STATE_BRUSH)
				{
					doDefault = true;
				}
				else
				{

					if (activeObject == E_OBJ_CAMERA)
					{
						doDefault = true;
					}
					else
					{
						dynObjects[activeObject]->posRel.addXYZRef(&modXYZ, -1.0f);
						dynObjects[activeObject]->pos.addXYZRef(&modXYZ, -1.0f);
					}
				}

				if (doDefault)
				{
					moveCamera(&modXYZ);
				}
				


			}
		}
		


		






	}

	void updateMultiLights()
	{
		if (multiLights)
		{
			numDynLights = E_OBJ_LENGTH - E_OBJ_LIGHT0;
		}
		else
		{
			numDynLights = 1;
		}
	}

	void toggleFullScreen()
	{
		isFullScreen = !isFullScreen;
		if (isFullScreen)
		{
			glutFullScreen();
		}
		else
		{
			glutPositionWindow(250, 50);
		}
	}




	/*
	GLUT_KEY_F1   F1 function key
	GLUT_KEY_F2   F2 function key
	GLUT_KEY_F3   F3 function key
	GLUT_KEY_F4   F4 function key
	GLUT_KEY_F5   F5 function key
	GLUT_KEY_F6   F6 function key
	GLUT_KEY_F7   F7 function key
	GLUT_KEY_F8   F8 function key
	GLUT_KEY_F9   F9 function key
	GLUT_KEY_F10    F10 function key
	GLUT_KEY_F11    F11 function key
	GLUT_KEY_F12    F12 function key
	GLUT_KEY_LEFT   Left function key
	GLUT_KEY_RIGHT    Right function key
	GLUT_KEY_UP   Up function key
	GLUT_KEY_DOWN   Down function key
	GLUT_KEY_PAGE_UP  Page Up function key
	GLUT_KEY_PAGE_DOWN  Page Down function key
	GLUT_KEY_HOME   Home function key
	GLUT_KEY_END    End function key
	GLUT_KEY_INSERT   Insert function key
	*/



	void restartGen(bool instantRefresh, bool clearEverything) {
		
		
	
		gw->curLoadRadius = minWInPages;
		gw->actionOnHolders(E_HOLDER_ACTION_RESET, instantRefresh, clearEverything);
		bufferInvalid = true;
		changesMade = true;
		
		
	}

	void setObjToElevationBase(FIVector4* obj) {
		
		obj->setFZ(
			getHeightAtPixelPos(obj->getFX(), obj->getFY())
		);

	}

	void setCameraToElevationBase() {
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		setObjToElevationBase(cameraPos);
	}

	void setCameraToElevation()
	{
		setCameraToElevationBase();
		
		bufferInvalid = true;
		changesMade = true;
		wsBufferInvalid = true;
	}


	void processSpecialKeys(int key, int _x, int _y)
	{

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		switch (key)
		{
		case GLUT_KEY_F1 :

			break;
		case GLUT_KEY_F2 :

			break;
		case GLUT_KEY_F3 :

			break;
		}
	}
	
	
	void updateCS() {
		if (
			(bCtrl != bCtrlOld) ||
			(bShift != bShiftOld)
		) {
			forceGetPD = true;
			wsBufferInvalid = true;
			bufferInvalid = true;
			changesMade = true;
		}
		bCtrlOld = bCtrl;
		bShiftOld = bShift;
	}
	
	void processKey(unsigned char key, int _x, int _y, bool isPressed)
	{

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;
	}
	void keyboardUp(unsigned char key, int _x, int _y)
	{

		GameEntNode* curNode;
		
		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		int holderCount;

		changesMade = false;

		
		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();


		if (key == 17) {
			glutLeaveMainLoop();
		}

		switch (key) {

		case 's':
				isMacro = !isMacro;
				
				//mirrorOn = !mirrorOn;
				cout << "isMacro: " << isMacro << "\n";
			break;


		// case '9':
		// 	saveAllData();
		// 	cout << "data saved\n";
		// break;
		
		case 19: //ctrl-s
			saveGUIValues();
			//cout << "Use s key in web editor to save\n";
			break;

		case 15: //ctrl-o
			//loadAllData();
			loadGUIValues();

			break;

		case '[':
			iNumSteps /= 2;
			if (iNumSteps < 16)
			{
				iNumSteps = 16;
			}
			doTraceND("iNumSteps: ", i__s(iNumSteps));
			bufferInvalid = true;
			break;
		case ']':
			iNumSteps *= 2;
			if (iNumSteps > 256)
			{
				iNumSteps = 256;
			}
			doTraceND("iNumSteps: ", i__s(iNumSteps));
			bufferInvalid = true;
			break;


		case 'e':
			setCameraToElevation();
			break;
			
		case 'q':
			// charState++;
			// if (charState > E_CHAR_STATE_RENDERED) {
			// 	charState = 0;
			// }
		
			autoScroll = !autoScroll;
			
			if (autoScroll) {
				scrollTimer.start();
				baseScrollPos.copyFrom(&(dynObjects[E_OBJ_CAMERA]->pos));
			}
			
			
			break;

		case 'w':
			resetActiveNode();
		break;
		case 'W':
			changesMade = true;
			maxWInPages++;
			break;
		case 'Q':
			changesMade = true;
			maxWInPages--;
			if (maxWInPages < 1)
			{
				maxWInPages = 1;
			}
			break;

		case 27: // esc
			std::exit(0);
			break;

		case 'b':
		
			bakeParamsOn = !bakeParamsOn;
			cout << "bakeParamsOn: " << bakeParamsOn << "\n";
			doShaderRefresh(bakeParamsOn);
			
			
			
		
			//radiosityOn = !radiosityOn;
			break;


		case 'R':
		
			//loadGUIValues(false);
			doShaderRefresh(bakeParamsOn);
			loadGUI();
			loadGUIValues();
			bufferInvalid = true;
		break;
		case 'r':
			doShaderRefresh(bakeParamsOn);
			
			bufferInvalid = true;

			cout << "Shaders Refreshed\n";
			
			break;
			
		case 'j':
			doShaderRefresh(bakeParamsOn);
			bufferInvalid = true;			
			mapInvalid = true;
			gw->initMap();
		break;

		case 'G':
			gridOn = 1.0 - gridOn;
			cout << "Grid On: " << gridOn << "\n";
			bufferInvalid = true;
			changesMade = true;
			break;


		case 'g':
		
			mouseState++;

			if (mouseState == E_MOUSE_STATE_LENGTH)
			{
				mouseState = 0;
			}
			
			cout << mouseStateStrings[mouseState] << "\n";

			bufferInvalid = true;
			changesMade = true;
			wsBufferInvalid = true;
			forceGetPD = true;
		
			
		break;
		
		case 'l':

			multiLights = !multiLights;
			updateMultiLights();


			bufferInvalid = true;
			changesMade = true;
			forceGetPD = true;

			break;


		case 'p':
			//cout << "curZoom " << cameraZoom << "\n";
			toggleFullScreen();
			break;

		case 'd':
			targetTimeOfDay = 1.0f-targetTimeOfDay;
			// targetTimeOfDay += 0.5;
			
			// if (targetTimeOfDay > 1.0) {
			// 	targetTimeOfDay = 0.0;
			// }
			
			break;

		case 'h':
			waterOn = !waterOn;

			if (MAX_LAYERS == 1)
			{
				waterOn = false;
			}


			bufferInvalid = true;
			changesMade = true;

			cout << "waterOn " << waterOn << "\n";
			break;

		case 't':

			// tiltAmount += 0.25f;
			
			// if (tiltAmount > 0.75f) {
			// 	tiltAmount = 0.25f;
			// }
			
			// createVTListTilt();
			
			// cout << "tiltAmount: " << tiltAmount << "\n";
			
			// restartGen(false, true);


			testOn = !testOn;

			//testOn = !testOn;
			//cout << "testOn " << testOn << "\n";

			//treesOn = !treesOn;
			//traceOn = true;
			break;
		case 'o':
			rotOn = !rotOn;
			break;

		case '\t':
		
			if (guiOn) {
				playSoundEvent("hideGUI");
			}
		
			if (!guiOn) {
				
				// todo: in the future don't reload the gui every time
				// just for testing right now
				// if (mainGUI->isLoaded) {
				// 
				// }
				// else {
				// 	loadGUI()
				// }
				
			}
			guiOn = !guiOn;
			
			if (guiOn) {
				playSoundEvent("showGUI");
			}
			
			bufferInvalid = true;
			break;

		case ' ':
			selGeomListInd++;
			if (selGeomListInd >= selGeomList.size()) {
				selGeomListInd = 0;
			}
			if (selGeomList.size() > 0) {
				selectedGeom = selGeomList[selGeomListInd];
			}
			
		break;

		case 'c':
			doShaderRefresh(bakeParamsOn);
			restartGen(false, true);
			break;
		

		case 'f':
			fogOn = 1.0 - fogOn;
			bufferInvalid = true;
			changesMade = true;
			cout << "fog on " << fogOn << "\n";
			break;

		case 'm':

			tiltAmount = 0.5f;
			targetZoom = 1.0f; 
			runReport();
			

			break;

		
		case 'A':
			changesMade = true;
			maxHInPages++;
			break;
		case 'Z':
			changesMade = true;
			maxHInPages--;
			if (maxHInPages < 1)
			{
				maxHInPages = 1;
			}
			break;

		case 'a':
			// selectedNode->material += 1.0f;
			// curNode = getMirroredNode(selectedNode);
			// if (curNode != NULL) {
			// 	curNode->material += 1.0f;
			// }
			// makeDirty();
		break;
		case 'z':
			// selectedNode->material -= 1.0f;
			// curNode = getMirroredNode(selectedNode);
			// if (curNode != NULL) {
			// 	curNode->material -= 1.0f;
			// }
			// makeDirty();
			
		break;

		case 'v':
			if (selectedGeom == NULL)
			{

			}
			else
			{
				selectedGeom->visible = !(selectedGeom->visible);

				holderCount = gw->getHoldersInGeom(selectedGeom);
				gw->refreshHoldersInList(true, true); //holderCount <= 12
				gw->holdersToRefresh.clear();

				bufferInvalid = true;
				changesMade = true;



			}
			break;



		default:

			break;
		}


	}
	void keyboardDown(unsigned char key, int _x, int _y)
	{
		
		
		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;
	}

	void runReport() {
		
		mainGUI->runReport();
		cout << "zoom " << cameraZoom << "\n";
		cout << "lightCount: " << gw->lightCount << "\n";
		cout << "TOT GPU MEM USED (MB): " << TOT_GPU_MEM_USAGE << "\n";
		cout << "HolderSize (MB): " << holderSizeMB << "\n";
		cout << "Num GPU Holders: " << gpuPool->holderPoolItems.size() << "\n";
		cout << "GPU Pooled MB Used: " << ((float)gpuPool->holderPoolItems.size())*holderSizeMB << "\n";
	}

	void getPixData(FIVector4 *toVector, int _xv, int _yv, int bufNum = 0, bool forceGet = false)
	{

		FBOWrapper *fbow;
		int newX;
		int newY;
		
		float xv = _xv;
		float yv = _yv;


		if (wsBufferInvalid || forceGet)
		{
			gw->getWorldSpaceBuffer(bufNum);
		}

		
		//xv = (xv - bufferDimHalf.getFX());
		//yv = (yv - bufferDimHalf.getFY());

		if (cameraZoom > 1.0)
		{
			newX = bufferDimHalf.getFX() + (xv - bufferDimHalf.getFX())/cameraZoom;
			newY = bufferDimHalf.getFY() + (yv - bufferDimHalf.getFY())/cameraZoom;
		}
		else
		{
			newX = clamp(xv, 0, bufferDim.getIX() - 1);
			newY = clamp(yv, 0, bufferDim.getIY() - 1);
		}



		fbow = getFBOWrapper("worldSpaceFBO", bufNum);
		fbow->getPixelAtF(toVector, newX, (bufferDim.getIY() - 1) - newY);
	}

	GameGeom *findNearestGeom(
		FIVector4 *testPoint,
		bool createList = false,
		bool onlyInteractive = false
	)
	{
		GameBlock *curBlock;

		int i;
		int j;
		int k;
		int ii;
		int jj;
		
		int curInd = 0;
		float bestDis;
		float curDis;
		
		bool doProc = false;
		
		if (createList) {
			selGeomList.clear();
			selGeomListInd = 0;
		}

		bestDis = 99999.0f;
		GameGeom *resGeom = NULL;

		for (j = -1; j <= 1; j++)
		{
			for (i = -1; i <= 1; i++)
			{
				ii = i + gw->camBlockPos.getIX();
				jj = j + gw->camBlockPos.getIY();

				curBlock = gw->getBlockAtCoords(ii, jj, false);

				if (curBlock == NULL)
				{

				}
				else
				{
					for (k = 0; k < curBlock->gameGeom.size(); k++)
					{
						if (
							testPoint->inBoundsXYZSlack(
								curBlock->gameGeom[k]->getVisMinInPixelsT(),
								curBlock->gameGeom[k]->getVisMaxInPixelsT(),
								0.0625*pixelsPerMeter
							)
						)
						{
							
							if (createList) {
								selGeomList.push_back(curBlock->gameGeom[k]);
								curInd++;
							}
							
							curDis = 
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFX()-testPoint->getFX()) +
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFY()-testPoint->getFY()) +
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFZ()-testPoint->getFZ());
							
							//curBlock->gameGeom[k]->getVisMinInPixelsT()->distance(testPoint) +
							//curBlock->gameGeom[k]->getVisMaxInPixelsT()->distance(testPoint);

							if (curBlock->gameGeom[k]->visible) {
								
							}
							else {
								curDis *= 16.0f;
							}

							if (onlyInteractive) {
								doProc = isInteractiveGeom[curBlock->gameGeom[k]->buildingType];
							}
							else {
								doProc = true;
							}

							if (
								(curDis < bestDis) &&
								doProc
							)
							{
								bestDis = curDis;
								resGeom = curBlock->gameGeom[k];
								selGeomListInd = curInd-1;
							}

						}
					}
				}
			}
		}

		return resGeom;
	}


	void mouseMove(int _x, int _y)
	{

		mouseMoved = true;

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		int dx = x - lastPosX;
		int dy = y - lastPosY;

		guiX = _x/UI_SCALE_FACTOR;
		guiY = _y/UI_SCALE_FACTOR;

		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();

		lastMouseX = x;
		lastMouseY = y;

		
		

		mouseXUp = x;
		mouseYUp = y;

		

		
		if (tiltChanged) {
			tiltChanged = false;
			createVTListTilt();
			readyForRestart = true;
			//restartGen(false, false);
		}

		if (abDown)
		{
			moveObject((float)dx, (float)dy, cameraZoom);
		}
		else
		{

			getPixData(&mouseMovePD, x, y);


			

			// if (
			// 	mouseState != E_MOUSE_STATE_MOVE
			// )	{

				gw->modifyUnit(&mouseMovePD, E_BRUSH_MOVE);
			//}
			
			


			//////////////

			if (entOn) {
				updateNearestEntNode(false, &mouseMovePD);
			}
			else {
				activeNode = NULL;
				setSelNode(NULL);
			}
			

			highlightedGeom = findNearestGeom(&mouseMovePD);
			


			//////////////


		}

		lastPosX = x;
		lastPosY = y;

		if ( (x >= 0) && (y >= 0) && (x < baseW) && (y < baseH) )
		{
			bufferInvalid = true;

			if (abDown)
			{
				changesMade = true;
			}
		}
	}


	void makeDirty() {
		testHuman->gph->childrenDirty = true;
	}

	void setSelNode(GameEntNode* newNode) {
		
		selectedNode = newNode;
		if (selectedNode != lastSelNode) {
			makeDirty();
		}
		lastSelNode = newNode;
		
	}



	void worldToScreenBase(FIVector4 *sc, FIVector4 *wc, bool doDiv = true ) {
		/*
		Screen -> Isometric space equations
		iX = (((ScreenX) / tileWidth) - ((ScreenY) / tileHeight));
		iY = (((ScreenX) / tileWidth) + ((ScreenY) / tileHeight));

		Isometric -> Screen space equations
		ScreenX = (iX + iY) * tileWidth / 2;
		ScreenY = (iY - iX) * tileHeight / 2;

		Assuming the isometric coordinating system goes as this: http://i.imgur.com/aUM4g.png

		*/
		
		float tilt = tiltAmount;
		float itilt = 1.0-tiltAmount;
		
		// float x1 = (wc->getFX() - wc->getFY())/2.0;
		// float y1 = (-wc->getFX() + -wc->getFY() + wc->getFZ());
		
				
		float x1 = (wc->getFX() - wc->getFY());
		//float y1 = (-(wc->getFX() / 2.0f) + -(wc->getFY() / 2.0f) + wc->getFZ());
		float y1 = (-itilt*wc->getFX() + -itilt*wc->getFY() + (tilt)*2.0f*wc->getFZ());
		
		if (doDiv) {
			x1 /= fHolderMod;
			y1 /= fHolderMod;
		}
		
		
		sc->setFX(x1);
		sc->setFY(y1);
	}



	void worldToScreen(FIVector4 *sc, FIVector4 *wc, bool centerIsOrigin = false)
	{
		
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		dMod.copyFrom(wc);
		dMod.addXYZRef(cameraPos, -1.0);
		
		worldToScreenBase(sc, &dMod, false);
		float x1 = sc->getFX();
		float y1 = sc->getFY();
		
		
		float myZoom = std::min(1.0f, cameraZoom);
		x1 = x1 * (myZoom) / bufferModDim.getFX();
		y1 = y1 * (myZoom) / bufferModDim.getFY();

		if (centerIsOrigin)
		{

		}
		else
		{
			x1 = (x1 + 1.0) / 2.0;
			y1 = (y1 + 1.0) / 2.0;
		}
		
		


		sc->setFX(x1);
		sc->setFY(y1);
	}

	

	void mouseClick(int button, int state, int _x, int _y)
	{


		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		lastPosX = x;
		lastPosY = y;
		
		guiX = _x/UI_SCALE_FACTOR;
		guiY = _y/UI_SCALE_FACTOR;

		GameBlock *curBlock;

		int res;
		int i;
		int j;
		int k;
		int ii;
		int jj;
		int bestInd;
		float bestDis;
		float curDis;

		float wheelDelta = 0.0f;
		bool mbClicked = false;
		bool rbClicked = false;
		bool lbClicked = false;

		int mouseMovingStart;

		FIVector4 testVec;
		FIVector4 oneVec;
		oneVec.setFXYZ(1.0f, 1.0f, 1.0f);
		oneVec.normalize();

		
		hitGUI = false;
		
		if ((mainGUI != NULL)&&guiOn) {
			if (mainGUI->isReady) {
				hitGUI = mainGUI->testHit(button, state, guiX, guiY);
			}
		}
		

		if (hitGUI)
		{
			bufferInvalid = true;
			return;
		}
		

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			lbDown = (state == GLUT_DOWN);
			lbClicked = (state == GLUT_UP);

			break;
		case GLUT_RIGHT_BUTTON:
			rbDown = (state == GLUT_DOWN);
			rbClicked = (state == GLUT_UP);

			break;
		case GLUT_MIDDLE_BUTTON:
			mbDown = (state == GLUT_DOWN);
			mbClicked = (state == GLUT_UP);

			break;

		case 3: // wheel up
			wheelDelta = 1.0f / 20.0f;
			//changesMade = true;
			break;

		case 4: // wheel down
			wheelDelta = -1.0f / 20.0f;
			//changesMade = true;
			break;
		}

		abDown = lbDown || rbDown || mbDown;
		


		if (rbClicked)
		{
			
			if (tiltChanged) {
				tiltChanged = false;
				createVTListTilt();
				restartGen(false, true);
				
				//readyForRestart = true;
			}
			
			if (lbDown)
			{

			}
			else
			{
				isPanning = false;
			}

		}
		if (lbClicked)
		{
			
			
			
			if (rbDown)
			{

			}
			else
			{
				isPanning = false;
			}

		}





		if (state == GLUT_DOWN)
		{
			mouseVel.setFXY(0.0f, 0.0f);
		}

		if (rbClicked || lbClicked)
		{




			if (abDown)
			{

			}
			else
			{

				muTime = myTimer.getElapsedTimeInMilliSec();

				mouseEnd.setIXY(x, y);
				//mouseVel.copyFrom(&mouseEnd);
				//mouseVel.addXYZRef(&mouseMoving, -1.0f);

				if ( (activeObject == E_OBJ_CAMERA) && (muTime - mdTime > 300.0f) )
				{
					mouseMovingStart = (mouseMovingLoc - min(mouseMovingStepsBack, mouseCount) + mouseMovingSize) % mouseMovingSize;


					if (mouseCount > 0)
					{
						mouseVel.copyFrom( &(mouseMoving[mouseMovingLoc]) );
						mouseVel.addXYZRef( &(mouseMoving[mouseMovingStart]), -1.0f);
					}


				}




				/*
				mouseMovingSize = 100;
				mouseMovingLoc = 0;
				mouseCount = 0;
				mouseMovingStepsBack = 10;
				*/

				lastModXYZ.normalize();


				//mouseVel.multXYZ( clampf(1.0f-(muTime-mdTime)/1000.0f, 0.1f, 1.0f)/cameraZoom );

				if (shiftDown())
				{

				}
				else
				{




					activeObject = E_OBJ_CAMERA;
					wsBufferInvalid = true;
					getPixData(&mouseUpPD, x, y);


					
					
					
					if (mouseState == E_MOUSE_STATE_PICKING) {
						selectedGeom = findNearestGeom(
							&mouseUpPD,
							true,
							false
						);
					}
					else {
						selectedGeom = findNearestGeom(
							&mouseUpPD,
							false,
							true
						);
					}

					if (
						(selectedGeom == NULL) ||
						(mouseState == E_MOUSE_STATE_PICKING) ||
						(mouseState == E_MOUSE_STATE_BRUSH)
					)	{

					}
					else
					{

						switch (selectedGeom->buildingType)
						{
						case E_CT_DOOR:
						case E_CT_WINDOW:
							
							
						
							
						
							gw->getHoldersInGeom(selectedGeom);
							selectedGeom->toggleTransform();
							gw->getHoldersInGeom(selectedGeom);
							gw->refreshHoldersInList(true, true); //holderCount <= 12
							gw->holdersToRefresh.clear();
							
							if (selectedGeom->isToggled) {
								// open
								switch (selectedGeom->buildingType)
								{
									case E_CT_DOOR:
										playSoundPosAndPitch(
											"open3",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
									case E_CT_WINDOW:
										playSoundPosAndPitch(
											"open1",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
								}
							}
							else {
								// close
								
								switch (selectedGeom->buildingType)
								{
									case E_CT_DOOR:
										playSoundPosAndPitch(
											"close2",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
									case E_CT_WINDOW:
										playSoundPosAndPitch(
											"close1",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
								}
							}
							

							bufferInvalid = true;
							changesMade = true;
							wsBufferInvalid = true;
							break;

						case E_CT_LANTERN:
							selectedGeom->light->isOn = !(selectedGeom->light->isOn);
							playSoundPosAndPitch(
								"castinet0",
								cameraPos,
								selectedGeom->getVisMinInPixelsT(),
								0.3f
							);
							
							doTraceND("");
							doTraceND("CUR LIGHT DIS ", f__s(selectedGeom->light->screenDistance));
							doTraceND("");
							for (i = 0; i < gw->lightCount; i++)
							{
							 	doTraceND("LIGHT DIS ", f__s(gw->activeLights[i]->screenDistance));
							}
							doTraceND("");
							doTraceND("");

							gw->updateLights();
							break;

						}

					}






					if ( mouseEnd.distance(&mouseStart) > 30.0 )
					{

					}
					else
					{
						
						if (pathfindingOn) {
							if (lbClicked) {
								
								if (currentStep == 2) {
									currentStep = 0;
									moveNodes[0].setFXYZ(0.0,0.0,0.0);
									moveNodes[1].setFXYZ(0.0,0.0,0.0);
								}
								else {
									moveNodes[currentStep].copyFrom(&(gw->lastUnitPos));
									currentStep++;
								}
							}
						}
						else {
							switch (mouseState) {
								case E_MOUSE_STATE_BRUSH:
									
									if (lbClicked)
									{
										gw->modifyUnit(&mouseUpPD, E_BRUSH_ADD);
									}
									else
									{
										gw->modifyUnit(&mouseUpPD, E_BRUSH_SUB);
									}

									forceGetPD = true;

								break;
							}
						}
						
						
						
					}

				}


			}


		}
		else
		{
			if (abDown)
			{

				if (rbDown && lbDown)
				{

				}
				else
				{


					lastModXYZ.setFXYZ(0.0f, 0.0f, 0.0f);

					mouseMovingLoc = 0;
					mouseCount = 0;
					mdTime = myTimer.getElapsedTimeInMilliSec();
					mouseStart.setIXY(x, y);

					getPixData(&mouseDownPD, x, y);










					activeObject = E_OBJ_CAMERA;
					
					
					
					
					if (bCtrl) {
						if (mouseDownPD.getFW() != 0.0) {
							// find nearest dyn object
							
							cout << "OBJECT ID " << mouseDownPD.getFW() << "\n";
							

							bestInd = mouseDownPD.getFW();
							
							if ((bestInd >= E_OBJ_LENGTH)||(bestInd <= 0)) {
								
							}
							else {
								activeObject = (E_OBJ)(bestInd);
							}
							
							//bestDis = 99999.0f;
							
							//getPixData(&geomPD, x, y, 2, true);
							//doTraceVecND("GEOM PD ", &geomPD);
							
							//worldToScreenBase(&tempVec1, &mouseDownPD);
							
							// for (i = 1; i < dynObjects.size(); i++)
							// {


							// 	//worldToScreenBase(&tempVec2, &(dynObjects[i]->pos));

							// 	curDis = geomPD.distance(&(dynObjects[i]->pos));


							// 	if (curDis < bestDis)
							// 	{
							// 		bestDis = curDis;
							// 		bestInd = i;
							// 	}
							// }

							
						}
					}
					else {
						
						if (entOn) {
							updateNearestEntNode(true, &mouseDownPD);
						}
						
					}
					
					
					
				}


			}
		}



		


		if ( (button == 3) || (button == 4) ) {
			
			myDelta += wheelDelta;
			targetZoom = pow(2.0, myDelta);
			isZooming = true;

		}

		if (x >= 0 && y >= 0 && x < baseW && y < baseH)
		{
			bufferInvalid = true;
		}

	}
	
	
	void resetActiveNode() {
		
		GameEntNode* curNode = NULL;
		
		if (selectedNode == NULL) {
			curNode = lastSelNode;
		}
		else {
			curNode = selectedNode;
		}
		
		if (curNode != NULL) {
			curNode->rotThe = 0.0f;
			curNode->rotPhi = 0.0f;
			curNode->rotRho = 0.0f;
			
			curNode->tbnRadScale0.setFXYZ(1.0f,1.0f,1.0f);
			curNode->tbnRadScale1.setFXYZ(1.0f,1.0f,1.0f);
			makeDirty();
		}
	}
	
	void updateNearestEntNode(bool setActive, FIVector4* mousePosWS) {
		// tempVec3.setFXYZRef(mousePosWS);
		// tempVec3.addXYZRef(&(testHuman->basePosition),-1.0f);
		
		worldToScreenBase(&tempVec1, mousePosWS);
		
		bestNode = NULL;
		bestNodeDis = 99999.0f;
		findNearestEntNode(
			testHuman->baseNode,
			&tempVec1
		);
		
		if (bestNodeDis >= 1.0f*pixelsPerMeter) {
			bestNode = NULL;
			activeNode = NULL;
			setSelNode(NULL);
		}
		
		if (bestNode != NULL) {
			
			setSelNode(bestNode);
			if (setActive) {
				activeNode = bestNode;				
			}
		}
	}
	
	void findNearestEntNode(
		GameEntNode* curNode,
		FIVector4* mousePosSS
	) {
		
		tempVec3.setFXYZRef(&(curNode->orgTrans[1]));
		tempVec3.multXYZ(pixelsPerMeter);
		tempVec3.addXYZRef(&(testHuman->basePosition));
		
		worldToScreenBase(&tempVec2, &tempVec3);
		float curDis = mousePosSS->distanceXY(&tempVec2);
		
		if (curDis < bestNodeDis) {
			bestNodeDis = curDis;
			bestNode = curNode;
		}
		
		int i;
		
		for (i = 0; i < curNode->children.size(); i++) {
			findNearestEntNode(curNode->children[i],mousePosSS);
		}
		
	}


	void processB64(charArr *sourceBuffer, charArr *saveBuffer)
	{

		char *buf = sourceBuffer->data;
		int len = sourceBuffer->size;

		if (saveBuffer != &nullBuffer)
		{
			if (saveBuffer->data != NULL)
			{
				delete[] saveBuffer->data;
				saveBuffer->data = NULL;
			}
			saveBuffer->data = new char[len];
			strncpy(saveBuffer->data, buf, len);
			saveBuffer->size = len;
		}


		FBOSet *fbos = &(fboMap["palFBO"]);


		//unsigned char* resultImage = new unsigned char[256*256*4];

		membuf inBuffer(sourceBuffer->data, sourceBuffer->data + sourceBuffer->size);
		std::istream myIS(&inBuffer);
		
		
#ifdef USE_POCO
		Poco::Base64Decoder b64in(myIS);
		std::ostringstream oss;
		oss << b64in.rdbuf();
		std::string strConst = oss.str();
#else
		std::string sbString = string(sourceBuffer->data, sourceBuffer->size);
		std::string strConst = base64_decode(sbString);
#endif
		
		
		const char *inString = strConst.c_str();
		
		
		
		


		lodepng_decode32(&resultImage, &palWidth, &palHeight, (unsigned char *)inString, strConst.size() );

		fbos->copyFromMem(0, resultImage);

	}


	bool processJSONFromString(
		string* sourceBuffer,
		JSONValue** destObj
	) {
		if (*destObj != NULL)
		{
			delete *destObj;
			*destObj = NULL;
		}
		
		*destObj = JSON::Parse(sourceBuffer->c_str());

		if (*destObj == NULL)
		{
			doTraceND("Invalid JSON\n\n");
			cout << sourceBuffer << "\n\n";
			return false;
		}
		else
		{
			doTraceND("\nValid JSON\n");
			return true;
		}
		
	}

	bool processJSON(
		charArr *sourceBuffer,
		charArr *saveBuffer,
		JSONValue** destObj
	) {
		
		if (*destObj != NULL)
		{
			delete *destObj;
			*destObj = NULL;
		}

		//doTraceND("destObj is now NULL");
		

		//doTraceND("processJSON()");

		char *buf = sourceBuffer->data;
		int len = sourceBuffer->size;
		//JSONValue *jsonVal = NULL;

		if (saveBuffer != &nullBuffer)
		{
			if (saveBuffer->data != NULL)
			{
				delete[] saveBuffer->data;
				saveBuffer->data = NULL;
			}
			saveBuffer->data = new char[len];
			strncpy(saveBuffer->data, buf, len);
			saveBuffer->size = len;
		}

		//doTraceND("Begin JSON::Parse()");

		if (buf == NULL)
		{
			//doTraceND("buf is NULL");
			return false;
		}
		else
		{
			//doTraceND("buf is not NULL");
			*destObj = JSON::Parse(buf);
		}


		//doTraceND("End JSON::Parse()");


		if (*destObj == NULL)
		{
			doTraceND("Invalid JSON\n\n");
			return false;
		}
		else
		{
			doTraceND("\nValid JSON\n");
			return true;
		}


	}
	
	
	
	// void mergeJSON(
	// 	JSONValue** destJV,
	// 	JSONValue* srcJV	
	// ) {
		
	// 	int i;
		
	// 	if (srcJV != NULL) {
	// 		if (srcJV->HasChild("value")) {
	// 			if ((*destJV)->HasChild("value")) {
	// 				(*destJV)->Child("value")->number_value = srcJV->Child("value");
	// 			}	
	// 		}
	// 	}
		
		
	// 	for (i = 0; i < destJV; i++) {
			
	// 	}
		
		
	// }
	
	
	// bool saveJSON(
	// 	string path,
	// 	JSONValue** jvToSave,
	// 	bool mergeFile = true
	// ) {
		
	// 	bool res = false;
		
	// 	string saveString;
		
	// 	charArr dest;
	// 	dest.data = NULL;
	// 	dest.size = 0;
		
	// 	JSONValue* jvToMergeFrom = NULL;
		
	// 	if (mergeFile) {
	// 		if ( loadFile(path, &dest) )
	// 		{
	// 			if (processJSON(&dest, &nullBuffer, &jvToMergeFrom)) {
	// 				res = true;
	// 			}
	// 			else {
	// 				res = false;
	// 			}
	// 		}
	// 		else {
	// 			res = false;
	// 		}
	// 	}
		
		
	// 	if (res) { // jvToMergeFrom is ready to merge
	// 		//mergeJSON(jvToSave,jvToMergeFrom);
	// 	}
		
	// 	saveFileString(path, &saveString);
		
		
	// 	if (dest.data != NULL)
	// 	{
	// 		delete[] dest.data;
	// 		dest.data = NULL;
	// 	}
	// 	if (jvToMergeFrom != NULL)
	// 	{
	// 		delete jvToMergeFrom;
	// 		jvToMergeFrom = NULL;
	// 	}
		
		
	// 	return res;
		
		
	// }
	
	bool loadJSON(
		string path,
		JSONValue** destObj
	) {
		
		bool res = false;
		
		charArr dest;
		dest.data = NULL;
		dest.size = 0;
		
		if ( loadFile(path, &dest) )
		{
			if (processJSON(&dest, &nullBuffer, destObj)) {
				res = true;
			}
			else {
				res = false;
			}
		}
		else {
			res = false;
		}
		
		
		if (dest.data != NULL)
		{
			delete[] dest.data;
			dest.data = NULL;
		}
		
		return res;
		
	}
	
	
	void setGUIText(
		string key,
		string stringValue,
		float floatValue = 0.0f,
		bool applyVal = false,
		bool applyString = true
	) {
		UICStruct* curComp;
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				if (applyString) {
					curComp->uic->setText(stringValue);
				}
				if (applyVal) {
					curComp->uic->setValue(floatValue);
				}
				
			}
		}
	}
	
	float getGUIValue(string key) {
		UICStruct* curComp;
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				return curComp->uic->getValue();
			}
		}
		
		return 0.0;
	}
	
	void setGUIValue(
		string key,
		float floatValue,
		bool dispatchEvent = false,
		bool preventRefresh = false
	) {
		UICStruct* curComp;
		
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				curComp->uic->setValue(floatValue,dispatchEvent,preventRefresh);
			}
		}
	}
	
	
	void loadGUIValues(bool applyValues = false) {
		
		cout << "Loading GUI Values\n";
		
		int i;
		
		charArr dest;
		dest.data = NULL;
		dest.size = 0;
		
		UICStruct* curComp;
		
		string loadBuf;
		vector<string> splitStrings;
		if ( loadFile(guiSaveLoc, &dest) )
		{
			loadBuf = string(dest.data);
			splitStrings = split(loadBuf, '^');
			
			for (i = 0; i < splitStrings.size(); i += 2) {
				
				setGUIValue(
					splitStrings[i],
					hexToFloat( &(splitStrings[i+1]) ),
					true,
					true
				);
				
				if (applyValues) {
					
				}
				else {
					
				}
				
			}
			
		}
		else {
			cout << "Unable to load GUI Values\n";
			
		}
		
		if (dest.data != NULL)
		{
			delete[] dest.data;
			dest.data = NULL;
		}
		
		cout << "End Loading GUI Values\n";
	}
	
	
	void saveGUIValues() {
		
		cout << "Saving GUI Values\n";
		
		stringBuf = "";
		
		for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
				
				if (
					(iterator->second.uic == NULL) ||
					(iterator->second.nodeId < 0)
				) {
					
				}
				else {
					if (iterator->first[0] ==  '$') {
						stringBuf.append(
							iterator->first + "^" + floatToHex(iterator->second.uic->getValue()) + "^"
						);
					}
					
					
				}
				
		    // iterator->first = key
		    // iterator->second = value
		}
		
		saveFileString(guiSaveLoc,&stringBuf);
		
		cout << "End Saving GUI Values\n";
	}
	
	
	void updateGUI() {
		
		float chunkMem;
		float fbMem;
		
		
		
		int mvPerPage = (volGenFBOX*volGenFBOX*volGenFBOX)/(1024*1024);
		
		float voxelsGen = PAGE_COUNT*mvPerPage;
		
		string maxGPUMString = " / " + fi__s(MAX_GPU_MEM);
		
		if (frameCount%120 == 0) {
			
			chunkMem = ((float)gpuPool->holderPoolItems.size())*holderSizeMB;
			fbMem = TOT_GPU_MEM_USAGE - chunkMem;
			
			
			setGUIText("debug.fbMem", "Frame Buffer Mem Used: " + fi__s(fbMem) + maxGPUMString, fbMem/MAX_GPU_MEM, true );
			setGUIText("debug.chunkMem", "Chunk Mem Used: " + fi__s(chunkMem) + maxGPUMString, chunkMem/MAX_GPU_MEM, true );
			setGUIText("debug.totMem", "Total Mem Used: " + fi__s(TOT_GPU_MEM_USAGE) + maxGPUMString, TOT_GPU_MEM_USAGE/MAX_GPU_MEM, true );
			setGUIText("debug.chunksGen", "Voxels Generated (In Millions!): " + fi__s(voxelsGen) );
			 
		}
		
	}

	void loadGUI() {
		
		
		for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
				iterator->second.uic = NULL;
				iterator->second.nodeId = -1;
		    // iterator->first = key
		    // iterator->second = value
		}
		
		
		if (
			loadJSON("..\\cdat\\lastJSONBufferGUI.js", &guiRootJS)
		) {
			mainGUI->guiFromJSON(
				guiRootJS
			);
		
			for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
					
					
					if (iterator->second.nodeId != -1) {
						iterator->second.uic = mainGUI->findNodeById(iterator->second.nodeId);
					}
			}
		
		}
		
		
		
		//testTT = mainGUI->findNodeByString("testTT");
		
		bufferInvalid = true;
	}


	void loadAllData()
	{
		if ( loadFile("..\\cdat\\lastJSONBuffer.js", &lastJSONBuffer) )
		{
			processJSON(&lastJSONBuffer, &nullBuffer, &rootObjJS);
		}

		if ( loadFile("..\\cdat\\lastImageBuffer.txt", &lastImageBuffer) )
		{
			processB64(&lastImageBuffer, &nullBuffer);
		}

		bufferInvalid = true;
	}

	void saveAllData()
	{
		
		
		saveFile("..\\cdat\\lastJSONBuffer.js", &lastJSONBuffer);
		saveFile("..\\cdat\\lastImageBuffer.txt", &lastImageBuffer);
		
		cout << "All Data Saved\n";
	}


	bool loadFile(string fnString, charArr *dest)
	{
		
		const char* fileName = fnString.c_str();
		
		doTraceND("Loading: ", fileName);

		if (dest == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ifstream infile (fileName, std::ifstream::in);


		if ( ! infile.is_open() )
		{
			doTraceND("Could Not Open File For Loading");
			return false;
		}

		// get size of file
		infile.seekg (0, infile.end);
		long size = (long)infile.tellg();
		infile.seekg (0, infile.beg);


		dest->size = size;

		if (dest->data != NULL)
		{
			delete[] dest->data;
			dest->data = NULL;
		}

		dest->data = new char[size+1];

		// read content of infile
		infile.read (dest->data, size);

		if ( infile.bad() )
		{
			doTraceND("Could Not Load From File");
			infile.close();
			return false;
		}

		infile.close();
		
		dest->data[size] = '\0';

		doTraceND("Load Successful");

		return true;
	}

	bool saveFileString(string fileName, string* source)
	{

		if (source == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ofstream outfile (fileName.c_str(), std::ofstream::out);

		if ( ! outfile.is_open() )
		{
			doTraceND("Could Not Open File For Saving");
			return false;
		}

		outfile.write(source->c_str(), source->size());

		if ( outfile.bad() )
		{
			doTraceND("Could Not Save To File");
			outfile.close();
			return false;
		}

		outfile.close();

		doTraceND("Save Successful");

		return true;
	}

	bool saveFile(char *fileName, charArr *source)
	{

		if (source->data == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ofstream outfile (fileName, std::ofstream::out);

		if ( ! outfile.is_open() )
		{
			doTraceND("Could Not Open File For Saving");
			return false;
		}

		outfile.write (source->data, source->size);

		if ( outfile.bad() )
		{
			doTraceND("Could Not Save To File");
			outfile.close();
			return false;
		}

		outfile.close();

		doTraceND("Save Successful");

		return true;
	}



	


	void updateAmbientSounds() {
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		
		int i;
		int j;
		
		int maxRad = 2.0f;
		
		float avgHeight = 0.0f;
		float tot = 0.0f;
		
		for (i = -maxRad; i <= maxRad; i++) {
			for (j = -maxRad; j <= maxRad; j++) {
				avgHeight += getHeightAtPixelPos(
					cameraPos->getFX() + i*32.0f*pixelsPerMeter,
					cameraPos->getFY() + j*32.0f*pixelsPerMeter
				);
				tot += 1.0f;
			}
		}
		
		float terHeight = avgHeight/tot;
		
		float seaHeight = getSLInPixels();
		
		float heightDif = clampf((terHeight-seaHeight)/(16.0*pixelsPerMeter), 0.0, 1.0);
		
		music[EML_BIRDSONG0]->setVolume(masterVolume*ambientVolume*timeOfDay*heightDif);
		music[EML_CRICKETS0]->setVolume(masterVolume*ambientVolume*(1.0f-timeOfDay)*heightDif);
		music[EML_OCEANWAVES0]->setVolume(masterVolume*ambientVolume*(1.0f-heightDif));
		
	}
	
	
	
	
	void frameUpdate() {
		
		
		
		float hs = holderSizeInPixels;
		
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		float scrollAmount = 0.0f;
		
		updateAmbientSounds();
		if ((mainGUI != NULL)&&guiOn) {
			if (mainGUI->isReady) {
				//mainGUI->testOver(guiX, guiY);
			}
			
		}
		
		
		if (autoScroll) {
			changesMade = true;
			cameraPos->copyFrom(&baseScrollPos);
			scrollAmount = scrollTimer.getElapsedTimeInMilliSec()/scrollDiv;
			cameraPos->addXYZ(-scrollAmount,-scrollAmount,0.0f);
			
			// cameraPosAdjusted.copyFrom(cameraPos);
			// setObjToElevationBase(&cameraPosAdjusted);
			// cameraPos->addXYZ(16.0*pixelsPerMeter,16.0*pixelsPerMeter,0.0f);
			//syncObjects(&cameraPosAdjusted);
			
			syncObjects(cameraPos);
			
			
			
			if (gw->curLoadRadius == maxWInPages) {
				gw->curLoadRadius = minWInPages;
			}
			
		}
		else {
			if (
				(
					readyForRestart &&
					(guiLock == false) &&
					(gw->curLoadRadius > minWInPages)	
				)
				||
				forceRestart
			) {
				
				if (forceRestart) {
					forceRestart = false;			
				}
				readyForRestart = false;
				guiLock = true;
				restartGen(false, false);
				guiLock = false;
				
			}
			
			updateGUI();
		}
		
		
		
		
		gw->update();
		
		
		
		
		TRACE_ON = false;
		changesMade = false;
		bufferInvalid = false;
		
		frameCount++;
	}
	
	


	void display(void)
	{

		curTime = myTimer.getElapsedTimeInMilliSec();

		float elTime = curTime - lastTime;
		float dz;
		float fMouseVel;

#ifdef USE_POCO
		if (myWS == NULL)
		{

		}
		else
		{

			if (myWS->dataReady)
			{

				if (myWS->isJSON)
				{
					if ( processJSON( &(myWS->recBuffer), &lastJSONBuffer, &rootObjJS ) )
					{
						saveAllData();

					}
				}
				else
				{
					processB64(  &(myWS->recBuffer), &lastImageBuffer );

				}

				bufferInvalid = true;

				myWS->dataReady = false;
				myWS->isWorking = false;
			}
		}
#else
		//processB64NoPoco();
#endif

		



		if (abs(timeOfDay - targetTimeOfDay) > 0.001)
		{
			bufferInvalid = true;
			changesMade = true;
		}


		if (elTime >= ( msPerFrame  )  ) { // / ((float)skipFrames)

			if (firstRun)
			{
				
			}
			else
			{
				if ( (frameCount % 120) == 0)
				{
					gw->updateLights();
					bufferInvalid = true;
					changesMade = true;
				}
			}




			lastTime = curTime;


			timeOfDay += (targetTimeOfDay - timeOfDay) / 8.0;


			mouseMovingLoc = (mouseMovingLoc + 1) % mouseMovingSize;
			mouseCount++;
			mouseMoving[mouseMovingLoc].setIXY(lastMouseX, lastMouseY);



			lastModXYZ.multXYZ(0.95f);

			mouseVel.multXYZ(0.95f);

			fMouseVel = mouseVel.distance(&origin);

			// if ( fMouseVel < 2.0f ) {
			//  mouseVel.setFXY(0.0f,0.0f);
			//  isPanning = false;
			// }
			// else {
			//  isPanning = true;


			//  panMod.copyFrom(&lastModXYZ);
			//  panMod.multXYZ(fMouseVel/16.0f);
			//  moveCamera(&panMod);
			// }


			dz = (targetZoom - cameraZoom) / (4.0f);

			/*
			if (abs(dz) < 0.0001) {
			  dz = 0.0f;
			}
			*/

			/*
			if (cameraZoom > 8.0f) {
			  cameraZoom = 8.0f;
			}
			if (cameraZoom < 1.0f/8.0f) {
			  cameraZoom = 1.0f/8.0f;
			}
			*/

			//curMS = fpsTimer.getElapsedTimeInMilliSec() / renderCount;

			cameraZoom += dz;
			

			if ( ( abs(dz) / cameraZoom < 0.001 ) && (isZooming))
			{
				isZooming = false;
				wsBufferInvalid = true;
				bufferInvalid = true;
				changesMade = true;
			}
			else
			{
				if (isZooming)
				{
					bufferInvalid = true;
					changesMade = true;
				}

			}
			

			if (shadersAreLoaded)
			{

				if (traceOn)
				{
					traceOn = false;
					TRACE_ON = true;
				}
				if (updateLock)
				{

				}
				else
				{
					frameUpdate();
				}
			}

			
		}

		if (firstRun)
		{
			//toggleFullScreen();
		}

		firstRun = false;

		//doTrace( "POSSIBLE ERROR: " , i__s(glGetError()) , "\n" );

	}
	void reshape(int w, int h)
	{

		setWH(w, h);

		screenWidth = w;
		screenHeight = h;

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
		orthographicProjection();


		setMatrices(baseW, baseH);
	}
	void idleFunc(void)
	{

	}

};
