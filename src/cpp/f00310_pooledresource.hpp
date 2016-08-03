
class PooledResource {
private:
	FBOSet* fboSet[MAX_LAYERS];
	uint* cpuSet[MAX_LAYERS];
public:

	intPair usedById;
	bool isCPU;
	Singleton* singleton;

	PooledResource() {
		int i;

		for (i = 0; i < MAX_LAYERS; i++) {
			fboSet[i] = NULL;
		}
		
	}

	FBOSet* getFBOS(int fboNum) {
		return fboSet[fboNum];
	}

	void init(
		Singleton* _singleton,
		bool _isCPU,
		int _sizeX,
		int _sizeY
	) {

		singleton = _singleton;
		isCPU = _isCPU;
		usedById.v0 = -1;
		usedById.v1 = -1;

		int i;

		if (isCPU) {
			for (i = 0; i < MAX_LAYERS; i++) {
				cpuSet[i] = new uint[
					_sizeX *
					_sizeY
				];
			}
		}
		else {
			for (i = 0; i < MAX_LAYERS; i++) {
				fboSet[i] = new FBOSet();
			}

			for (i = 0; i < MAX_LAYERS; i++) {
				fboSet[i]->init(
					2,
					_sizeX,
					_sizeY,
					1,
					false //has depth
				);
			}
		}

		

		

	}
};
