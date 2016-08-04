

// class GamePlantNode {

// };

class GamePlantNode {

public:
	FIVector4 begPoint;
	FIVector4 endPoint;
	//FIVector4 ctrPoint;


	FIVector4 tangent;
	FIVector4 baseShoot;

	//float rotation;
	float shootLength;
	float begThickness;
	float endThickness;
	float midThickness;

	float sphereRad;

	FIVector4 startEndWidth;
	FIVector4 upVec;

	GamePlantNode* parent;
	GamePlantNode* children;
	int maxChildren;
	int numChildren;

	GamePlantNode() {
		sphereRad = 0.0f;
		parent = NULL;
		children = NULL;
		upVec.setFXYZ(0.0f,0.0f,1.0f);
	}

	void updateTangent(float angleInRadians) {
		tangent.setFXYZRef(&endPoint);
		tangent.addXYZRef(&begPoint,-1.0f);
		tangent.normalize();
		baseShoot.setFXYZRef(&tangent);
		baseShoot.rotate(angleInRadians, E_PLANE_XZ);
		baseShoot.normalize();

		shootLength = begPoint.distance(&endPoint);

		// ctrPoint.copyFrom(&begPoint);
		// if (parent == NULL) {
		// 	ctrPoint.addXYZRef(&endPoint);
		// 	ctrPoint.multXYZ(0.5f);
		// }
		// else {
		// 	ctrPoint.addXYZRef(&(parent->tangent), shootLength/2.0f);
		// }
		

	}

	void init(
		GamePlantNode* _parent,
		int _maxChildren,
		int _numChildren
	) {
		parent = _parent;
		
		maxChildren = _maxChildren;	
		numChildren = _numChildren;

		sphereRad = 0.0f;

		if (maxChildren > 0) {

			if (children == NULL) {
				children = new GamePlantNode[maxChildren];
			}
			else {

			}

			
		}
		
	}
};
