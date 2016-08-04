
class PoolPageManager {
public:
	
	PoolPageManager() {
		
	}
	
	
	// int poolItemsCreated;
	// bool isCPU;
	
	// list<int> pagePoolIds;
	// vector<intPair> orderedIds;
	// vector<PooledResource *> pagePoolItems;
	
	// Singleton* singleton;
	// GameWorld* gw;
	
	// bool isEntity;
	
	// int sizeX;
	// int sizeY;
	
	
	
	// void init(
	// 	Singleton* _singleton,
	// 	bool _isEntity,
	// 	bool _isCPU,
	// 	int _sizeX,
	// 	int _sizeY
	// ) {
	// 	isEntity = _isEntity;
	// 	poolItemsCreated = 0;
	// 	isCPU = _isCPU;
	// 	singleton = _singleton;
	// 	gw = singleton->gw;
	// 	sizeX = _sizeX;
	// 	sizeY = _sizeY;
	// }
	
	
	// float getMaxMem() {
	// 	if (isCPU) {
	// 		return MAX_CPU_MEM;
	// 	}
	// 	else {
			
	// 		if (isEntity) {
	// 			// TODO: FIX THIS
	// 			return MAX_GPU_MEM*20.0f;
	// 		}
	// 		else {
	// 			return MAX_GPU_MEM;
	// 		}
			
			
	// 	}
	// }
	// float getTotMemUsed() {
	// 	if (isCPU) {
	// 		return TOT_CPU_MEM_USAGE;
	// 	}
	// 	else {
	// 		return TOT_GPU_MEM_USAGE;
	// 	}
	// }
	
	
	
	// void reorderIds()
	// {
	// 	int i;
	// 	int j;

	// 	int oidSize =  orderedIds.size();
	// 	int oidSizeM1 =  oidSize - 1;

	// 	intPair id0;
	// 	intPair id1;

	// 	int tempId;

	// 	int tot0;
	// 	int tot1;

	// 	bool doSwap;

	// 	GamePage *gp0;
	// 	GamePage *gp1;

	// 	for (i = 0; i < oidSizeM1; i++)
	// 	{
	// 		for (j = i + 1; j < oidSize; j++ )
	// 		{

	// 			id0 = orderedIds[i];
	// 			id1 = orderedIds[j];

	// 			if ( pairIsNeg(id0) || pairIsNeg(id1))
	// 			{

	// 			}
	// 			else
	// 			{

	// 				gp0 = gw->getPageAtIndex(id0.v1);
	// 				gp1 = gw->getPageAtIndex(id1.v1);

	// 				if (gp0 == NULL || gp1 == NULL)
	// 				{

	// 				}
	// 				else
	// 				{
	// 					tot0 = gp0->offsetInPages.getFZ();
	// 					tot1 = gp1->offsetInPages.getFZ();

	// 					if (tot0 == tot1)
	// 					{
	// 						tot0 = gp0->offsetInPages.getFY();
	// 						tot1 = gp1->offsetInPages.getFY();

	// 						if (tot0 == tot1)
	// 						{
	// 							tot1 = gp1->offsetInPages.getFX();
	// 							tot0 = gp0->offsetInPages.getFX();

	// 							if (tot0 == tot1)
	// 							{
	// 								doSwap = false;
	// 							}
	// 							else
	// 							{
	// 								doSwap = tot0 > tot1;
	// 							}
	// 						}
	// 						else
	// 						{
	// 							doSwap = tot0 > tot1;
	// 						}
	// 					}
	// 					else
	// 					{
	// 						doSwap = tot0 > tot1;
	// 					}

	// 					if (doSwap)
	// 					{
	// 						orderedIds[i] = id1;
	// 						orderedIds[j] = id0;
	// 					}


	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// int findFurthestPageId()
	// {


	// 	int longestInd = 0;
	// 	int i;

	// 	float longestDis = 0.0f;
	// 	float testDis;

	// 	FIVector4 tempVec;

	// 	GamePage *gp;
	// 	GamePage *bestGP = NULL;

	// 	for (i = 0; i < pagePoolItems.size(); i++)
	// 	{
	// 		gp = gw->getPageAtIndex(pagePoolItems[i]->usedById.v1);

	// 		if (gp == NULL)
	// 		{

	// 		}
	// 		else
	// 		{

	// 			tempVec.copyFrom(&(gw->camPagePos));
	// 			gp->offsetInPages.wrapDistance(&tempVec, singleton->worldSizeInPages.getIX());
	// 			testDis = gp->offsetInPages.distance( &(tempVec) );

	// 			if (testDis > longestDis)
	// 			{
	// 				longestDis = testDis;
	// 				longestInd = i;
	// 				bestGP = gp;
	// 			}
	// 		}
	// 	}

	// 	return longestInd;
	// }



	// int requestPoolId(int blockId, int pageId)
	// {


	// 	int toFreeId;
	// 	intPair usedById;

	// 	int i;


	// 	if (getTotMemUsed() < getMaxMem())
	// 	{
	// 		pagePoolItems.push_back( new PooledResource() );
	// 		pagePoolItems.back()->init(singleton, isCPU, sizeX, sizeY);

	// 		toFreeId = poolItemsCreated;
	// 		pagePoolIds.push_front(toFreeId);
	// 		orderedIds.push_back(intPair());
	// 		orderedIds.back().v0 = blockId;
	// 		orderedIds.back().v1 = pageId;
	// 		poolItemsCreated++;

	// 	}
	// 	else
	// 	{
	// 		toFreeId = findFurthestPageId();
	// 		usedById = pagePoolItems[toFreeId]->usedById;

	// 		GamePage *consumingPage;

	// 		if ( pairIsNeg(usedById) )
	// 		{
	// 			// this pooledItem is already free

	// 		}
	// 		else
	// 		{
	// 			// free this pooledItem from the page that is consuming it and give it to the requesting page

	// 			consumingPage = gw->getPageAtIndex(usedById.v1);

	// 			if (consumingPage == NULL)
	// 			{
	// 				// page was deleted already
	// 			}
	// 			else
	// 			{
	// 				consumingPage->unbindGPUResources();
	// 			}


	// 		}



	// 		for (i = 0; i < orderedIds.size(); i++)
	// 		{
	// 			if ( pairIsEqual(orderedIds[i], usedById) )
	// 			{
	// 				orderedIds[i].v0 = blockId;
	// 				orderedIds[i].v1 = pageId;
	// 				break;
	// 			}
	// 		}


	// 		pagePoolIds.remove(toFreeId);
	// 		pagePoolIds.push_front(toFreeId);
	// 	}


	// 	pagePoolItems[toFreeId]->usedById.v0 = blockId;
	// 	pagePoolItems[toFreeId]->usedById.v1 = pageId;

	// 	//reorderIds();

	// 	return toFreeId;

	// }


};



