

class GamePage {//: public Poco::Runnable {

private:

	uint *volData;
	uint *volDataLinear;

public:

	Singleton *singleton;

	int thisPageId;
	int terRes;

	int bufferedPageSizeInUnits;
	FIVector4 offsetInUnits;
	FIVector4 offsetInPages;
	FIVector4 offsetInPagesLocal;
	float pageDepth;
	//float seaHeightInPixels;
	int iVolumeSize;

	bool hasSolids;
	bool hasTrans;
	bool hasGeom;
	bool hasLines;
	bool hasTerrain;
	bool hasWater;
	bool hasWindow;
	bool hasTree;
	bool isDirty;

	int voroCount;

	bool volDataModified;

	bool isRendering;
	bool isEntity;

	int paramsPerEntry;
	int numEntries;
	int totParams;
	int maxEntries;



	bool threadRunning;

	float unitSizeInPixels;

	GameWorld *gw;


	FIVector4 worldMinVisInPixels;
	FIVector4 worldMaxVisInPixels;
	FIVector4 worldMinBufInPixels;
	FIVector4 worldMaxBufInPixels;

	FIVector4 centerPosition;


	FIVector4 scaleAndOffset;

	FIVector4 worldUnitMin;
	FIVector4 worldUnitMax;


	FIVector4 voroSize;
	FIVector4 curPos;
	FIVector4 randNum;
	FIVector4 testNum;
	FIVector4 newPos;
	
	FIVector4 tempVec1;
	FIVector4 tempVec2;



	GamePageHolder *parentGPH;
	GameBlock *parentBlock;

	

	GamePage() {
		terRes = -1;
		parentBlock = NULL;
		volData = NULL;
		volDataLinear = NULL;
	}



	void init(
		Singleton *_singleton,
		GamePageHolder *_parentGPH,
		int _thisPageId,
		int offsetX,
		int offsetY,
		int offsetZ,
		int oxLoc,
		int oyLoc,
		int ozLoc,
		bool _isEntity = false
	) {


		isEntity = false;
		hasLines = false;
		hasSolids = false;
		hasTrans = false;
		isDirty = true;
		

		isEntity = _isEntity;

		thisPageId = _thisPageId;
		singleton = _singleton;
		parentGPH = _parentGPH;
		gw = singleton->gw;
		
		if (!isEntity) {
			parentBlock = gw->getBlockAtId(parentGPH->blockId);
		}
		
		

		maxEntries = 32;
		isRendering = true;

		int i;

		volDataModified = false;
		threadRunning = false;


		//maxHeightInUnits = (singleton->maxHeightInUnits);



		int visPageSizeInUnits = singleton->visPageSizeInUnits;
		bufferedPageSizeInUnits = (visPageSizeInUnits) * (singleton->bufferMult);

		offsetInPages.setIXYZ(offsetX, offsetY, offsetZ);
		offsetInUnits.copyFrom(&offsetInPages);
		offsetInUnits.multXYZ(singleton->visPageSizeInUnits);

		offsetInPagesLocal.setIXYZ(oxLoc, oyLoc, ozLoc);

		float hzp = (float)(singleton->holderSizeInPages);

		pageDepth = ((1.0f - ( (offsetInPagesLocal.getFZ() * hzp * hzp + offsetInPagesLocal.getFY() * hzp + offsetInPagesLocal.getFX()) / (hzp * hzp * hzp) )) * 0.9f + 0.05f) * 0.5f;


		unitSizeInPixels = (float)(singleton->unitSizeInPixels);



		iVolumeSize = bufferedPageSizeInUnits * bufferedPageSizeInUnits * bufferedPageSizeInUnits;




		worldMinVisInPixels.copyFrom(&offsetInUnits);
		worldMaxVisInPixels.copyFrom(&offsetInUnits);
		worldMaxVisInPixels.addXYZ(visPageSizeInUnits);
		worldMinVisInPixels.multXYZ((float)unitSizeInPixels);
		worldMaxVisInPixels.multXYZ((float)unitSizeInPixels);

		worldUnitMin.copyFrom(&offsetInUnits);
		worldUnitMax.copyFrom(&offsetInUnits);
		worldUnitMax.addXYZ(visPageSizeInUnits);

		worldUnitMin.addXYZ( -(bufferedPageSizeInUnits - visPageSizeInUnits) / 2 );
		worldUnitMax.addXYZ( (bufferedPageSizeInUnits - visPageSizeInUnits) / 2 );

		worldMinBufInPixels.copyFrom(&worldUnitMin);
		worldMaxBufInPixels.copyFrom(&worldUnitMax);
		worldMinBufInPixels.multXYZ((float)unitSizeInPixels);
		worldMaxBufInPixels.multXYZ((float)unitSizeInPixels);

		voroSize.setFXYZ(
			singleton->visPageSizeInPixels,
			singleton->visPageSizeInPixels,
			singleton->visPageSizeInPixels
		);


		centerPosition.copyFrom(&worldMinVisInPixels);
		centerPosition.addXYZRef(&worldMaxVisInPixels);
		centerPosition.multXYZ(0.5f);

		
		
		hasWater = ( singleton->getSLInPixels() >= worldMinVisInPixels.getFZ() );
		
		
		if (isEntity) {
			addEntityGeom(true);
		}
		else {			
			addGeom(true);
		}
		
		



	}

	uint *getVolData() {
		int i;

		if (volData == NULL) {
			volData = new uint[iVolumeSize];
			for (i = 0; i < iVolumeSize; i++) {
				volData[i] = 0;
			}
		}

		return volData;

	}

	uint *getVolDataLinear() {
		int i;

		if (volDataLinear == NULL) {
			volDataLinear = new uint[iVolumeSize];
			for (i = 0; i < iVolumeSize; i++) {
				volDataLinear[i] = (0 << 24) | (0 << 16) | (0 << 8) | (0);
			}
		}

		return volDataLinear;
	}

	void copyToTexture(bool isForEmptyVD) {


		int id1 = singleton->volId;
		int id2 = singleton->volIdLinear;

		if (isForEmptyVD) {
			id1 = singleton->volIdEmpty;
			id2 = singleton->volIdEmptyLinear;
		}

		glBindTexture(GL_TEXTURE_3D, id1);
		glTexSubImage3D(
			GL_TEXTURE_3D,
			0,

			0,
			0,
			0,

			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,

			GL_RGBA,
			GL_UNSIGNED_BYTE,

			getVolData()
		);

		glBindTexture(GL_TEXTURE_3D, 0);
		glBindTexture(GL_TEXTURE_3D, id2);
		glTexSubImage3D(
			GL_TEXTURE_3D,
			0,

			0,
			0,
			0,

			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,

			GL_RGBA,
			GL_UNSIGNED_BYTE,

			getVolDataLinear()
		);
		glBindTexture(GL_TEXTURE_3D, 0);





		/*
		glTexSubImage2D(
		  GLenum    target,
		  GLint   level,
		  GLint   xoffset,
		  GLint   yoffset,
		  GLsizei   width,
		  GLsizei   height,
		  GLenum    format,
		  GLenum    type,
		  const GLvoid *    data
		 );


		void glTexSubImage3D(

		  GLenum target,
		  GLint level,
		  GLint xoffset,
		  GLint yoffset,
		  GLint zoffset,
		  GLsizei width,
		  GLsizei height,
		  GLsizei depth,
		  GLenum format,
		  GLenum type,


		glBindTexture(GL_TEXTURE_2D, singleton->volId);
		  glTexSubImage2D(
		    GL_TEXTURE_2D,
		    0,

		    xoff,
		    yoff,

		    width,
		    height,

		    GL_RGBA,
		    GL_UNSIGNED_SHORT,

		    cpuArrPtr
		  );
		glBindTexture(GL_TEXTURE_2D, 0);


		*/


	}



	void setFalse() {
		hasLines = false;
		hasSolids = false;
		hasTrans = false;
		hasTree = false;
		hasWindow = false;
		hasGeom = false;
		hasTerrain = false;
	}


	void addEntityGeom(bool justTesting) {
		
		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int ind;
		int bufSize = (singleton->visPageSizeInPixels * singleton->bufferMult);
		int geomInPage;
		int baseInd;

		GamePageHolder *gph;
		GameGeom *gg;

		paramsPerEntry = E_GP_LENGTH * 3;
		numEntries = 0;

		bool doProc;

		for (i = 0; i < E_MAT_PARAM_LENGTH; i++) {
			singleton->matCountArr[i] = 0.0f;
		}

		


		if (justTesting) {
			setFalse();
		}

		
		gph = parentGPH;

		if (gph) {
			geomInPage = gph->entityGeom.size();
			

			for (m = 0; m < geomInPage; m++) {
				
				gg = gph->entityGeom[m];

				if (

					FIVector4::intersect( gg->getVisMinInPixelsT(), gg->getVisMaxInPixelsT(), &worldMinBufInPixels, &worldMaxBufInPixels )
					&& (gg->visible)

				) {

					if (justTesting) {
						
						
						if (gg->buildingType == E_CT_LINES) {
							hasLines = true;
						}
						else {
							hasGeom = true;
						}
						
						
					}
					else {
						for (p = 0; p < E_GP_LENGTH; p++) {
							baseInd = numEntries * paramsPerEntry + p * 3;
							singleton->paramArr[baseInd + 0] = gg->geomParams[p].getFX();
							singleton->paramArr[baseInd + 1] = gg->geomParams[p].getFY();
							singleton->paramArr[baseInd + 2] = gg->geomParams[p].getFZ();
						}

						singleton->matCountArr[gg->geomParams[E_GP_MATPARAMS].getIX()] += 1.0f;

						numEntries++;
						
					}
				}
			}
		}
		
		

		if (justTesting) {
			parentGPH->hasTrans = false;
			hasTrans = false;
			if (hasGeom||hasLines) {
				parentGPH->hasSolids = true;
				hasSolids = true;
			}
		}
		else {
			if (numEntries > maxEntries) {
				numEntries = maxEntries;
				doTraceND("limit exceeded");
			}

			totParams = numEntries * paramsPerEntry;
		}


	}

	void addGeom(bool justTesting) {

		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int ind;
		int bufSize = (singleton->visPageSizeInPixels * singleton->bufferMult);
		intPair curId;
		int geomInPage;
		int baseInd;

		FIVector4 start;
		FIVector4 end;

		GamePageHolder *gph;
		GameGeom *gg;

		paramsPerEntry = E_GP_LENGTH * 3;
		numEntries = 0;

		bool doProc;

		start.copyFrom( &worldMinBufInPixels );
		end.copyFrom( &worldMaxBufInPixels );

		start.addXYZ(-bufSize);
		end.addXYZ(bufSize);

		start.intDivXYZ(singleton->holderSizeInPixels);
		end.intDivXYZ(singleton->holderSizeInPixels);

		start.clampZ( singleton->origin.getFZ(), singleton->worldSizeInHolders.getFZ() - 1.0f );
		end.clampZ( singleton->origin.getFZ(), singleton->worldSizeInHolders.getFZ() - 1.0f );

		for (i = 0; i < E_MAT_PARAM_LENGTH; i++) {
			singleton->matCountArr[i] = 0.0f;
		}

		if (justTesting) {
			setFalse();
		}


		for (k = start.getIZ(); k <= end.getIZ(); k++ ) {
			for (j = start.getIY(); j <= end.getIY(); j++ ) {
				for (i = start.getIX(); i <= end.getIX(); i++ ) {
					gph = gw->getHolderAtCoords(i, j, k);

					// TODO critical: make sure holders are ready before pages


					if (gph) {
						geomInPage = gph->containsGeomIds.size();

						for (m = 0; m < geomInPage; m++) {
							curId = gph->containsGeomIds[m];
							gg = gw->blockData[curId.v0]->gameGeom[curId.v1];


							if (

								FIVector4::intersect( gg->getVisMinInPixelsT(), gg->getVisMaxInPixelsT(), &worldMinBufInPixels, &worldMaxBufInPixels )
								&& (gg->visible)

							) {

								if (justTesting) {
									if ( (gg->buildingType == E_CT_WINDOW) || (gg->buildingType == E_CT_LANTERN)) {
										hasWindow = true;
									}

									if (gg->buildingType == E_CT_TREE) {
										hasTree = true;
									}
									hasGeom = true;
								}
								else {

									doProc = true;

									for (n = 0; n < numEntries; n++) {
										if (singleton->geomIdArr[n] == gg->globalId) {
											doProc = false;
										}
									}

									if (doProc) {

										singleton->geomIdArr[numEntries] = gg->globalId;



										for (p = 0; p < E_GP_LENGTH; p++) {

											baseInd = numEntries * paramsPerEntry + p * 3;

											singleton->paramArr[baseInd + 0] = gg->geomParams[p].getFX();
											singleton->paramArr[baseInd + 1] = gg->geomParams[p].getFY();
											singleton->paramArr[baseInd + 2] = gg->geomParams[p].getFZ();
										}

										singleton->matCountArr[gg->geomParams[E_GP_MATPARAMS].getIX()] += 1.0f;

										numEntries++;
									}
								}
							}
						}
					}
				}
			}
		}

		if (justTesting) {
			
			terRes = parentBlock->isNearTerrain(&centerPosition);
			
			hasTerrain = (terRes == E_TER_GROUNDLEVEL);
			
			if (terRes == E_TER_UNDERGROUND) {
				
			}
			else {
				if (hasWindow || hasWater) {
					parentGPH->hasTrans = true;
					hasTrans = true;
					if (MAX_LAYERS < 2) {
						parentGPH->hasSolids = true;
						hasSolids = true;
					}
				}

				if (hasTerrain || hasGeom || volDataModified) {
					parentGPH->hasSolids = true;
					hasSolids = true;
				}
			}
			
			
						
			
		}
		else {
			if (numEntries > maxEntries) {
				numEntries = maxEntries;
				cout << "limit exceeded " << numEntries << " / " << maxEntries << "\n";
			}

			totParams = numEntries * paramsPerEntry;
		}




	}










	void getVoroPoints() {


		int i, j, k;

		int counter = 0;
		int rad = 2;
		int tempi = 0;
		
		//int iMaxPoints = 27;
		//float fMaxPoints = (float)iMaxPoints;

		float fi, fj, fk;

		
		FIVector4 posFloored;
		FIVector4 posFlooredInPixels;
		
		// posFloored.copyFrom(&worldMaxVisInPixels);
		// posFloored.addXYZRef(&worldMinVisInPixels);
		// posFloored.multXYZ(0.5f);

		posFloored.copyFrom(&offsetInPages);
		posFloored.addXYZ(0.5f);
		
		posFlooredInPixels.copyFrom(&posFloored);
		posFlooredInPixels.multXYZ(&voroSize);

		// posFloored.divXYZ(&voroSize);
		// posFloored.floorXYZ();


		int totVoro = 27;
		
		

		for (i = -rad; i <= rad; i++) {
			fi = (float)i;
			for (j = -rad; j <= rad; j++) {
				fj = (float)j;
				for (k = -rad; k <= rad; k++) {
					fk = (float)k;


					curPos.copyFrom(&posFloored);
					curPos.addXYZ(fi, fj, fk);


					// if (
					//  (curPos.getIX() + curPos.getIY() + curPos.getIZ()) % 3 == 0
					// ) {




					//if (curPos.getIZ()%3 == 0) {

					randNum.setRand(&curPos);
					//randNum.multXYZ(1.0f);

					singleton->voroVecArr[counter].copyFrom(&curPos);
					singleton->voroVecArr[counter].addXYZRef(&randNum);
					singleton->voroVecArr[counter].multXYZ(&voroSize);

					//testNum.setRand(&curPos);

					//if (testNum.getFX() > 1.0f - (fMaxPoints/125.0f) ) { //true) {//
					// singleton->voroArr[counter * 4 + 0] = newPos.getFX();
					// singleton->voroArr[counter * 4 + 1] = newPos.getFY();
					// singleton->voroArr[counter * 4 + 2] = newPos.getFZ();
					//singleton->voroArr[counter * 4 + 3] = (testNum.getFX()) * 0.5 + 0.5;
					counter++;
					//}

					// if (counter >= iMaxPoints) {
					// 	counter = iMaxPoints;
					// 	goto VORO_DONE;
					// }
					//}



				}
			}
		}

// VORO_DONE:
// 		voroCount = counter;


		


		for (i = 0; i < 125; i++){
			singleton->indexArr[i].index1 = i;
			singleton->indexArr[i].value = singleton->voroVecArr[i].distance(&posFlooredInPixels);
		}
		
		bubbleSortF(singleton->indexArr, 125);
		
		int curInd = 0;
		for (i = 0; i < 27; i++) {
			curInd = singleton->indexArr[i].index1;
			singleton->voroArr[i * 4 + 0] = singleton->voroVecArr[curInd].getFX();
			singleton->voroArr[i * 4 + 1] = singleton->voroVecArr[curInd].getFY();
			singleton->voroArr[i * 4 + 2] = singleton->voroVecArr[curInd].getFZ();
		}

		
		voroCount = 27;
	}





	void generateVolume(bool dd = false) {
		PAGE_COUNT++;

		int curVGFBO = CUR_VG_FBO;
		CUR_VG_FBO++;
		if (CUR_VG_FBO >= MAX_VG_FBOS) {
			CUR_VG_FBO = 0;
		}
		
		// 1 = 0
		// 2 = 1
		// 4 = 2
		// 8 = 2
		
		float curBlendAmount = 0.5f;
		

		int hspLog = 2;
		
		switch (singleton->holderSizeInPages) {
			case 1:
				hspLog = 0;
			break;
			case 2:
				hspLog = 1;
			break;
		}
		
		
		int resIndex = 0;
		int i;
		isRendering = true;
		
		if (volDataModified) {
			copyToTexture(false);
		}
		else {
			if (singleton->emptyVDNotReady) {
				singleton->emptyVDNotReady = false;
				copyToTexture(true);
			}
		}
		
		if (isEntity) {
			curBlendAmount = 1.0f;
			addEntityGeom(true);
			addEntityGeom(false);
		}
		else {
			resIndex = parentBlock->copyTerToTexture();
			addGeom(true);
			addGeom(false);
			
		}
		

		parentGPH->clearSet(); //false
		getVoroPoints();


		if (dd) {
			
			hasTerrain = true;
			hasSolids = true;
			parentGPH->hasSolids = true;
			
		}


		/////////////////////////////////////////
		// BEGIN GEN VOLUME
		/////////////////////////////////////////


		if (isEntity) {
			singleton->bindShader("GenerateVolumeEnt");
		}
		else {
			singleton->bindShader("GenerateVolume");
		}

		

		singleton->bindFBODirect(&(singleton->vgFBOArr[curVGFBO]), 0);

		if (volDataModified) {
			singleton->setShaderTexture3D(0, singleton->volId);
			singleton->setShaderTexture3D(1, singleton->volIdLinear);
		}
		else {
			singleton->setShaderTexture3D(0, singleton->volIdEmpty);
			singleton->setShaderTexture3D(1, singleton->volIdEmptyLinear);
		}

		singleton->sampleFBO("hmFBOLinear", 2);
		
		if (!isEntity) {
			singleton->setShaderTexture3D(4, singleton->terTextures[resIndex].texId);
		}
		
		
		singleton->setShaderFloat("totLayers", MAX_LAYERS);
		singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);	
		singleton->setShaderFloat("volumePitch", (float)( singleton->volGenFBOX ));
		singleton->setShaderfVec4("worldMinBufInPixels", &(worldMinBufInPixels));
		singleton->setShaderfVec4("worldMaxBufInPixels", &(worldMaxBufInPixels));

		if (isEntity) {
			
		}
		else {
			singleton->setShaderfVec4("worldSizeInPixels", &(singleton->worldSizeInPixels));	
			singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
			singleton->setShaderfVec4("blockMinBufInPixels", &(parentBlock->blockMinBufInPixels));
			singleton->setShaderfVec4("blockMaxBufInPixels", &(parentBlock->blockMaxBufInPixels));
		}
		
		


		singleton->setShaderInt("hasTree", (int)hasTree);
		singleton->setShaderInt("hasGeom", (int)hasGeom);
		singleton->setShaderInt("hasTerrain", (int)hasTerrain);
		singleton->setShaderInt("hasLines", (int)hasLines);

		if (hasGeom||hasTree||hasLines) {
			singleton->setShaderInt("paramsPerEntry", (paramsPerEntry / 3) );
			singleton->setShaderInt("numEntries", numEntries);
			singleton->setShaderArrayfVec3("paramArr", singleton->paramArr, totParams / 3);
			singleton->setShaderArray("matCountArr", singleton->matCountArr, E_MAT_PARAM_LENGTH);
		}

		//singleton->setShaderInt("voroCount", voroCount);
		singleton->setShaderArrayfVec4("voroArr", singleton->voroArr, voroCount);

		singleton->drawFSQuad(1.0f);

		if (!isEntity) {
			singleton->setShaderTexture3D(4, 0);
		}

		
		//singleton->setShaderTexture(3,0);
		singleton->unsampleFBO("hmFBOLinear", 2);
		singleton->setShaderTexture3D(1, 0);
		singleton->setShaderTexture3D(0, 0);
		singleton->unbindFBO();
		singleton->unbindShader();


		/////////////////////////////////////////
		// END GEN VOLUME
		/////////////////////////////////////////







		/////////////////////////////////////////
		// BEGIN RENDER VOLUME
		/////////////////////////////////////////


		if (parentGPH->gpuRes != NULL) {
			getCoords();
			singleton->bindShader("RenderVolume");


			for (i = 0; i < MAX_LAYERS; i++) {

				if (
					(
						(i == 0) &&
						(
							(hasTerrain || hasGeom || hasLines) ||
							((MAX_LAYERS < 2)&&(hasWater))
						)
					) ||
					((i == 1) && (hasWater || hasWindow))
				) {
					singleton->bindFBODirect(parentGPH->gpuRes->getFBOS(i), 0);
					//singleton->sampleFBO("volGenFBO0", 0);
					singleton->sampleFBODirect(&(singleton->vgFBOArr[curVGFBO]),0);
					singleton->sampleFBO("frontFaceFBO", 2);
					singleton->sampleFBO("backFaceFBO", 3);

					singleton->setShaderFloat("blendAmount",curBlendAmount);
					singleton->setShaderFloat("curLayer", i);
					//singleton->setShaderFloat("pageDepth", (float)( pageDepth ));
					singleton->setShaderFloat("volumePitch", (float)( singleton->volGenFBOX ));
					singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
					singleton->setShaderFloat("holderSizeInPagesLog", hspLog);
					singleton->setShaderFloat("bufferMult", (float)(singleton->bufferMult));
					singleton->setShaderFloat("visPageSizeInPixels", (float)(singleton->visPageSizeInPixels));
					singleton->setShaderfVec3("worldMinVisInPixels", &(worldMinVisInPixels));
					singleton->setShaderfVec3("worldMaxVisInPixels", &(worldMaxVisInPixels));
					singleton->setShaderfVec4("scaleAndOffset", &scaleAndOffset);

					//glCallList(singleton->volTris);
					singleton->drawFSQuad(1.0f);

					
					singleton->unsampleFBO("backFaceFBO",3);
					singleton->unsampleFBO("frontFaceFBO",2);
					//singleton->unsampleFBO("volGenFBO0",0);
					singleton->unsampleFBODirect(&(singleton->vgFBOArr[curVGFBO]),0);
					singleton->unbindFBO();
				}

			}

			singleton->unbindShader();
		}


		/////////////////////////////////////////
		// END RENDER VOLUME
		/////////////////////////////////////////




		isDirty = false;
		isRendering = false;

	}



	void getCoords() {



		float dx = offsetInPagesLocal.getFX();
		float dy = offsetInPagesLocal.getFY();
		float dz = offsetInPagesLocal.getFZ();

		float pitchSrc = (float)((singleton->visPageSizeInPixels * 2.0f));
		float pitchSrc2 = (pitchSrc) / 2.0f;

		float dxmod = dx * pitchSrc2;
		float dymod = dy * pitchSrc2;
		float dzmod = dz * pitchSrc2;


		// float fx1 = (dxmod - dymod) - pitchSrc2;
		// //float fy1 = (-(dxmod / 2.0f) + -(dymod / 2.0f) + dzmod) - pitchSrc2;
		// float tilt = 1.0-singleton->tiltAmount;
		// float fy1 = (-tilt*dxmod + -tilt*dymod + (1.0-tilt)*2.0f*dzmod) - pitchSrc2;
		
		float tilt = singleton->tiltAmount;
		float itilt = 1.0f-singleton->tiltAmount;
		
		tempVec2.setFXYZ(dxmod,dymod,dzmod);
		singleton->worldToScreenBase(&tempVec1,&tempVec2);
		float fx1 = tempVec1.getFX()*(singleton->fHolderMod);
		float fy1 = tempVec1.getFY()*(singleton->fHolderMod);
		
		
		
		
		fx1 -= pitchSrc2;
		fy1 -= pitchSrc2;
		
		
		float fx2 = fx1 + pitchSrc;
		float fy2 = fy1 + pitchSrc + 2.0;// + 2.0; // TODO: THIS "+ 2.0" is a hack used to cover cracks between pages, it should not be used

		float sx = singleton->holderSizeInPixels;
		float sy = singleton->holderSizeInPixels;


		fx1 = fx1 / sx;
		fy1 = fy1 / sy;
		fx2 = fx2 / sx;
		fy2 = fy2 / sy;

		scaleAndOffset.setFXYZW(
			(fx2 - fx1) / 2.0f,
			(fy2 - fy1) / 2.0f,
			(fx1 + fx2) / 2.0f,
			(fy1 + fy2) / 2.0f

		);

	}
	
	// void run() {
		
	// }

	~GamePage() {

		if (volData != NULL) {
			delete[] volData;
		}
		if (volDataLinear != NULL) {
			delete[] volDataLinear;
		}
	}

};
