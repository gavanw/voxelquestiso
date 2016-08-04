
class PoolManager {
public:
	
	int poolItemsCreated;
	bool isCPU;
	
	list<int> holderPoolIds;
	vector<intPair> orderedIds;
	vector<PooledResource *> holderPoolItems;
	
	Singleton* singleton;
	GameWorld* gw;
	
	bool isEntity;
	
	int sizeX;
	int sizeY;
	
	PoolManager() {
		
	}
	
	void init(
		Singleton* _singleton,
		bool _isEntity,
		bool _isCPU,
		int _sizeX,
		int _sizeY
	) {
		isEntity = _isEntity;
		poolItemsCreated = 0;
		isCPU = _isCPU;
		singleton = _singleton;
		gw = singleton->gw;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
	
	
	float getMaxMem() {
		if (isCPU) {
			return MAX_CPU_MEM;
		}
		else {
			
			if (isEntity) {
				// TODO: FIX THIS
				return MAX_GPU_MEM*20.0f;
			}
			else {
				return MAX_GPU_MEM;
			}
			
			
		}
	}
	float getTotMemUsed() {
		if (isCPU) {
			return TOT_CPU_MEM_USAGE;
		}
		else {
			return TOT_GPU_MEM_USAGE;
		}
	}
	
	
	
	void reorderIds()
	{
		int i;
		int j;

		int oidSize =  orderedIds.size();
		int oidSizeM1 =  oidSize - 1;

		intPair id0;
		intPair id1;

		int tempId;

		int tot0;
		int tot1;

		bool doSwap;

		GamePageHolder *gp0;
		GamePageHolder *gp1;

		for (i = 0; i < oidSizeM1; i++)
		{
			for (j = i + 1; j < oidSize; j++ )
			{

				id0 = orderedIds[i];
				id1 = orderedIds[j];

				if ( pairIsNeg(id0) || pairIsNeg(id1))
				{

				}
				else
				{

					gp0 = gw->getHolderAtId(id0);
					gp1 = gw->getHolderAtId(id1);

					if (gp0 == NULL || gp1 == NULL)
					{

					}
					else
					{
						tot0 = gp0->offsetInHolders.getFZ();
						tot1 = gp1->offsetInHolders.getFZ();

						if (tot0 == tot1)
						{
							tot0 = gp0->offsetInHolders.getFY();
							tot1 = gp1->offsetInHolders.getFY();

							if (tot0 == tot1)
							{
								tot1 = gp1->offsetInHolders.getFX();
								tot0 = gp0->offsetInHolders.getFX();

								if (tot0 == tot1)
								{
									doSwap = false;
								}
								else
								{
									doSwap = tot0 > tot1;
								}
							}
							else
							{
								doSwap = tot0 > tot1;
							}
						}
						else
						{
							doSwap = tot0 > tot1;
						}

						if (doSwap)
						{
							orderedIds[i] = id1;
							orderedIds[j] = id0;
						}


					}
				}


			}
		}
	}

	int findFurthestHolderId()
	{


		int longestInd = 0;
		int i;

		float longestDis = 0.0f;
		float testDis;

		FIVector4 tempVec;

		GamePageHolder *gp;
		GamePageHolder *bestGP = NULL;

		for (i = 0; i < holderPoolItems.size(); i++)
		{
			gp = gw->getHolderAtId(holderPoolItems[i]->usedById);

			if (gp == NULL)
			{

			}
			else
			{

				tempVec.copyFrom(&(gw->camHolderPos));
				gp->offsetInHolders.wrapDistance(&tempVec, singleton->worldSizeInHolders.getIX());
				testDis = gp->offsetInHolders.distance( &(tempVec) );

				if (testDis > longestDis)
				{
					longestDis = testDis;
					longestInd = i;
					bestGP = gp;
				}
			}
		}

		return longestInd;
	}



	int requestPoolId(int blockId, int holderId)
	{


		int toFreeId;
		intPair usedById;

		int i;


		if (
			(getTotMemUsed() < getMaxMem()) &&
			(
				(orderedIds.size() < MAX_HOLDERS) ||
				(MAX_HOLDERS <= 0)
			)
		)
		{
			holderPoolItems.push_back( new PooledResource() );
			holderPoolItems.back()->init(singleton, isCPU, sizeX, sizeY);

			toFreeId = poolItemsCreated;
			holderPoolIds.push_front(toFreeId);
			orderedIds.push_back(intPair());
			orderedIds.back().v0 = blockId;
			orderedIds.back().v1 = holderId;
			poolItemsCreated++;

		}
		else
		{
			toFreeId = findFurthestHolderId();//holderPoolIds.back();
			usedById = holderPoolItems[toFreeId]->usedById;

			GamePageHolder *consumingHolder;

			if ( pairIsNeg(usedById) )
			{
				// this pooledItem is already free

			}
			else
			{
				// free this pooledItem from the holder that is consuming it and give it to the requesting holder

				consumingHolder = gw->getHolderAtId(usedById);

				if (consumingHolder == NULL)
				{
					// holder was deleted already
				}
				else
				{
					consumingHolder->unbindGPUResources();
				}


			}



			for (i = 0; i < orderedIds.size(); i++)
			{
				if ( pairIsEqual(orderedIds[i], usedById) )
				{
					orderedIds[i].v0 = blockId;
					orderedIds[i].v1 = holderId;
					break;
				}
			}


			holderPoolIds.remove(toFreeId);
			holderPoolIds.push_front(toFreeId);
		}


		holderPoolItems[toFreeId]->usedById.v0 = blockId;
		holderPoolItems[toFreeId]->usedById.v1 = holderId;

		reorderIds();

		return toFreeId;

	}


};



