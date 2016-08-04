
class GameEnt {

public:

	Singleton* singleton;
	GamePageHolder* gph;
	GameEntNode* baseNode;
	FIVector4 basePosition;

	float defVecLength;

	float gv(float* vals) {
		float lerp = fGenRand();
		return vals[0]*lerp + vals[1]*(1.0f-lerp);
	}

	GameEnt() {
		defVecLength = 0.05f;
	}


	void init(
		Singleton* _singleton
	) {
		singleton = _singleton;

		baseNode = new GameEntNode(
			NULL,
			E_BONE_C_BASE,
			0.5f,
			defVecLength, defVecLength, defVecLength,
			
			0.0f, 1.0f, 0.0f,			
			1.0f, 0.0f, 0.0f,
			0.0f,0.0f,1.0f
		);
		
		initHuman();
		
		gph = new GamePageHolder();
		gph->init(
			singleton,
			
			singleton->curEntId,
			0,
			
			0,
			0,
			0,
			
			true
		);
		
		singleton->curEntId++;
		
		
	}
	
	
	
	void initHuman() {
		
		int i;
		int j;
		int lrMod;
		
		float dirMod = 1.0f;
		
		GameEntNode* curNode;
		curNode = baseNode;
		
		

		float numSpineSegs = E_BONE_C_SKULL-E_BONE_C_SPINE0;
		
		for (i = E_BONE_C_SPINE0; i < E_BONE_C_SKULL; i++) {
			curNode = curNode->addChild(
				i,
				0.75f/numSpineSegs,
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,
				1.0f,0.0f,0.0f
				
			);
		}
		
		curNode = curNode->addChild(
			E_BONE_C_SKULL,
			0.25f, 
			defVecLength, defVecLength, defVecLength,
			0.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,
			1.0f,0.0f,0.0f
		);
		
		
		for (j = 0; j < 2; j++) {
			
			if (j == 0) { // left limbs
				lrMod = 0;
				dirMod = 1.0f;
			}
			else { // right limbs
				lrMod = E_BONE_R_BEG - E_BONE_L_BEG;
				dirMod = -1.0f;
			}
			
			curNode = baseNode->getNode(E_BONE_C_SKULL-2);
			
			
			curNode = curNode->addChild(
				E_BONE_L_SHOULDER + lrMod,
				0.20f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_UPPERARM + lrMod,
				0.25f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_LOWERARM + lrMod,
				0.25f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_METACARPALS + lrMod,
				0.1f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			
			
			curNode = baseNode;
			
			curNode = curNode->addChild(
				E_BONE_L_HIP + lrMod,
				0.1f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_UPPERLEG + lrMod,
				0.45f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,-1.0f,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_LOWERLEG + lrMod,
				0.45f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,-1.0f,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_TALUS + lrMod,
				0.2f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			
		}
		
		
		baseNode->doTransform(singleton);
		
	}
	
	

};
