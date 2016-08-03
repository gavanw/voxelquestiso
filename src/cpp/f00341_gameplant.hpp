
class GamePlant {

public:

	Singleton* singleton;

	FIVector4 origin;
	FIVector4 tempv0;
	FIVector4 tempv1;
	FIVector4 tempv2;
	FIVector4 tempv3;

	FIVector4 rootVec;
	FIVector4 trunkVec;

	GamePlantNode* trunkNode;
	GamePlantNode* rootsNode;

	PlantRules* rootRules;
	PlantRules* trunkRules;




	static PlantRules allPlantRules[E_PT_LENGTH];
	
	// static void sv(float* vals, float v0, float v1) {
	// 	vals[0] = v0;
	// 	vals[1] = v1;
	// }

	static void initAllPlants(Singleton* _singleton) {
		int i;
		int j;


		float pi = 3.14159;

		PlantRules* pr;

		pr = &(allPlantRules[E_PT_OAK_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/6.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.4f;
		pr->sphereGen = 2.0f;
		pr->sphereRad = 6.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_OAK_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;		
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;
		
		
		pr = &(allPlantRules[E_PT_OAK2_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/4.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.2f;
		pr->sphereGen = 2.0f;
		pr->sphereRad = 6.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 1.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_OAK2_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 3.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 2.0f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;





		pr = &(allPlantRules[E_PT_BARE_OAK_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/4.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.2f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 4.0f;
		pr->curLength[2] = 6.0f;
		pr->curLength[3] = 4.5f;
		pr->curLength[4] = 4.5f;
		pr->curLength[5] = 1.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_BARE_OAK_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;
		

		


		
		for (i = 0; i < E_PT_LENGTH; i++) {
			if (allPlantRules[i].isInit == 0.0f) {



				allPlantRules[i].begThickness *= _singleton->pixelsPerMeter;
				allPlantRules[i].endThickness *= _singleton->pixelsPerMeter;
				for (j = 0; j < MAX_PLANT_GEN; j++) {
					allPlantRules[i].curLength[j] *= _singleton->pixelsPerMeter;
				}

				

			}
		}
	}


	float gv(float* vals) {
		float lerp = fGenRand();
		return vals[0]*lerp + vals[1]*(1.0f-lerp);
	}

	GamePlant() {
		trunkNode = NULL;
		rootsNode = NULL;
	}



	void init(
		Singleton* _singleton,
		PlantRules* _rootRules,
		PlantRules* _trunkRules,
		FIVector4* _origin
	) {
		singleton = _singleton;
		rootRules = _rootRules;
		trunkRules = _trunkRules;
		origin.setFXYZRef(_origin);

		trunkVec.setFXYZ(fGenRand()*0.1f,fGenRand()*0.1f,1.0f);
		trunkVec.normalize();
		rootVec.setFXYZRef(&trunkVec);
		rootVec.multXYZ(-1.0f);

		if (trunkNode == NULL) {
			trunkNode = new GamePlantNode();
		}
		if (rootsNode == NULL) {
			rootsNode = new GamePlantNode();
		}


		initBase(rootRules, rootsNode, &rootVec);
		initBase(trunkRules, trunkNode, &trunkVec);

	}




	void initBase(
		PlantRules* rules,
		GamePlantNode* curNode,
		FIVector4* baseVec
	) {
		int i;
		float curLerp;
		float maxLength = 0.0f;
		//float curMult = 1.0f;
		int maxGen = rules->numGenerations;

		
		curNode->init(NULL,rules->numChildren[1],gv(rules->numChildren));
		//curNode->tangent.setFXYZRef(baseVec);
		curNode->begPoint.setFXYZRef(&origin);
		curNode->endPoint.setFXYZRef(&origin);
		curNode->endPoint.addXYZRef(baseVec,rules->curLength[0]);
		curNode->updateTangent(gv(rules->divergenceAngleV));

		for (i = 1; i <= maxGen; i++) {
			maxLength += rules->curLength[i]; // *curMult;
			//curMult *= rules->nodeLengthMultiplier;
		}

		

		// curLerp = rules->curLength[0]/maxLength;
		// curNode->endThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

		// curLerp = 0.0f;
		// curNode->begThickness = curNode->endThickness;//(1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

		// curNode->midThickness = (curNode->begThickness+curNode->endThickness)*0.5f;

		curNode->begThickness = rules->begThickness;
		curNode->endThickness = curNode->begThickness;
		curNode->midThickness = curNode->begThickness;

		


		applyRules(
			rules,
			curNode,
			0,
			maxGen,
			//rules->baseLength*(rules->nodeLengthMultiplier),
			0.0f,
			maxLength
		);
	}

	

	void applyRules(
		PlantRules* rules,
		GamePlantNode* curParent,
		int curGen,
		int maxGen,
		//float curLength,
		float totLength,
		float maxLength
	) {


		//cout << "curLength: " << curLength << "\n";

		int i;
		float fi;
		float fCurGen = (float)curGen;
		float fNumChildren;
		float curLerp;
		float twoPi = 6.283185307f;
		float curLength = rules->curLength[curGen];

		GamePlantNode* curChild;

		fNumChildren = (float)(curParent->numChildren);

		for (i = 0; i < curParent->numChildren; i++) {

			fi = ((float)i)/fNumChildren;

			curChild = &(curParent->children[i]);


			if (curGen == maxGen) {
				curChild->init(curParent,0,0);
			}
			else {
				curChild->init(curParent,rules->numChildren[1], max( gv(rules->numChildren)-(float)curGen, 1.0f) );
			}

			
			curChild->begPoint.setFXYZRef(&(curParent->endPoint));
			curChild->endPoint.setFXYZRef(&(curParent->endPoint));

			axisRotationInstance.doRotation(
				&tempv0,
				&(curParent->baseShoot),
				&(curParent->tangent),
				fi*twoPi + (fGenRand()-0.5f)*twoPi*(1.0f-rules->angleUniformityU)/fNumChildren
			);
			curChild->endPoint.addXYZRef(&tempv0,curLength);
			curChild->updateTangent(gv(rules->divergenceAngleV));

			curLerp = (totLength/maxLength);
			curChild->begThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

			curLerp = ((totLength+curLength)/maxLength);
			curChild->endThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

			curChild->midThickness = (curChild->begThickness+curChild->endThickness)*0.5f;

			if ( rules->sphereGen == fCurGen ) {
				curChild->sphereRad = rules->sphereRad*singleton->pixelsPerMeter; //(maxLength-totLength) + 
			}

			if (curGen < maxGen) {
				applyRules(rules, curChild, curGen + 1, maxGen, totLength+curLength, maxLength);
			}

		}
	}

};
