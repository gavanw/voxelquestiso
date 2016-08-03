
int intDiv(int v, int s) {
	float fv = v;
	float fs = s;

	if (v < 0) {
		return -ceil(-fv / fs);
	}
	else {
		return v / s;
	}
}

void pack16(float num, float &outR, float &outG) {

    int iz = int(num);
    int ir = iz%256;
    int ig = iz/256;

    outR = float(ir)/255.0;
    outG = float(ig)/255.0;

}

int getPackedColor(uint r, uint g, uint b) {
	return (
					 (1 << 15) |
					 ((b >> 3) << 10) |
					 ((g >> 3) << 5) |
					 ((r >> 3))
				 );
}

int clamp(int val, int min, int max) {
	if (val > max) {
		val = max;
	}
	if (val < min) {
		val = min;
	}
	return val;
}

float mixf(float v1, float v2, float lerpVal) {
	return v1*(1.0f-lerpVal) + v2*lerpVal;
}




float clampf(float val, float min, float max) {
	if (val > max) {
		val = max;
	}
	if (val < min) {
		val = min;
	}
	return val;
}

float smoothstep(float edge0, float edge1, float x) {
    // Scale, bias and saturate x to 0..1 range
    x = clampf((x - edge0)/(edge1 - edge0), 0.0f, 1.0f); 
    // Evaluate polynomial
    return x*x*(3.0f - 2.0f*x);
}

inline float clampfZO(float val) {
	return clampf(val, 0.0f, 1.0f);
}


// float genRand(float LO, float HI)
// {

// 	return LO + (float)rand() / ((float)RAND_MAX / (HI - LO));
// }

inline float fGenRand() {

	return (float)rand() / (float)RAND_MAX;
	//return ((float)(rand()%100000))/100000.0f;
}

float fSeedRand2(float x, float y) {
	float intPart;
	return modf(sin(x * 12.9898 + y * 78.233) * 43758.5453, &intPart);
}

int iSeedRand2(float x, float y, int minV, int maxV) {
	float res = fSeedRand2(x, y);
	return minV + max(int((maxV + 1 - minV) * res), 0);
}


inline int iGenRand(int nMin, int nMax)
{
	return nMin + (int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
}

unsigned int intLogB2 (unsigned int val) {
	unsigned int ret = -1;
	while (val != 0) {
		val >>= 1;
		ret++;
	}
	return ret;
}

int intPow(int x, int p) {
	int i = 1;
	for (int j = 1; j <= p; j++) {
		i *= x;
	}
	return i;
}

int wrapCoord(int val, int max) {
	while (val < 0) {
		val += max;
	}
	while (val >= max) {
		val -= max;
	}

	return val;
}



class FIVector4 {
private:
	iVector4 iv4;
	fVector4 fv4;

	iVector3 iv3;
	fVector3 fv3;

	iVector2 iv2;
	fVector2 fv2;

public:

	FIVector4() {
		iv4.x = 0;
		iv4.y = 0;
		iv4.z = 0;
		iv4.w = 0;
		fv4.x = 0.0;
		fv4.y = 0.0;
		fv4.z = 0.0;
		fv4.w = 0.0;
	}

	float operator[] (int ind) { //float&
		
		switch (ind) {
			case 0:
				return fv4.x;
			break;
			case 1:
				return fv4.y;
			break;
			case 2:
				return fv4.z;
			break;
			case 3:
				return fv4.w;
			break;
		}
		
		cout << "invalid vector index";
		return -1.0f;
	}



	void setIXYZW(int x, int y, int z, int w) {
		iv4.x = x;
		iv4.y = y;
		iv4.z = z;
		iv4.w = w;
		fv4.x = (float)x;
		fv4.y = (float)y;
		fv4.z = (float)z;
		fv4.w = (float)w;
	}
	void setIXYZ(int x, int y, int z) {
		iv4.x = x;
		iv4.y = y;
		iv4.z = z;
		fv4.x = (float)x;
		fv4.y = (float)y;
		fv4.z = (float)z;
	}
	void setIXY(int x, int y) {
		iv4.x = x;
		iv4.y = y;
		fv4.x = (float)x;
		fv4.y = (float)y;
	}
	void setIX(int x) {
		iv4.x = x;
		fv4.x = (float)x;
	}
	void setIY(int y) {
		iv4.y = y;
		fv4.y = (float)y;
	}
	void setIZ(int z) {
		iv4.z = z;
		fv4.z = (float)z;
	}
	void setIW(int w) {
		iv4.w = w;
		fv4.w = (float)w;
	}

	void copyFrom(FIVector4 *cf) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();
	}

	void copyIntDiv(FIVector4 *cf, int val) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();

		intDivXYZ(val);
	}

	void copyIntMult(FIVector4 *cf, int val) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();

		multXYZ(val);
	}



	void setFXYZW(float x, float y, float z, float w) {
		fv4.x = x;
		fv4.y = y;
		fv4.z = z;
		fv4.w = w;
		iv4.x = (int)x;
		iv4.y = (int)y;
		iv4.z = (int)z;
		iv4.w = (int)w;
	}
	void setFXYZ(float x, float y, float z) {
		fv4.x = x;
		fv4.y = y;
		fv4.z = z;
		iv4.x = (int)x;
		iv4.y = (int)y;
		iv4.z = (int)z;
	}

	void setFXYZRef(FIVector4 *v1) {
		fv4.x = v1->getFX();
		fv4.y = v1->getFY();
		fv4.z = v1->getFZ();
		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void setFXY(float x, float y) {
		fv4.x = x;
		fv4.y = y;
		iv4.x = (int)x;
		iv4.y = (int)y;
	}
	void setFX(float x) {
		fv4.x = x;
		iv4.x = (int)x;
	}
	void setFY(float y) {
		fv4.y = y;
		iv4.y = (int)y;
	}
	void setFZ(float z) {
		fv4.z = z;
		iv4.z = (int)z;
	}
	void setFW(float w) {
		fv4.w = w;
		iv4.w = (int)w;
	}
	
	
	
	
	void setRand(FIVector4 *seedPos) {

		FIVector4 r0;
		FIVector4 r1;
		FIVector4 r2;

		FIVector4 l0;
		FIVector4 l1;
		FIVector4 l2;

		float intPart;

		r0.setFXYZ(12.989f, 78.233f, 98.422f);
		r1.setFXYZ(93.989f, 67.345f, 54.256f);
		r2.setFXYZ(43.332f, 93.532f, 43.734f);

		l0.setFXYZ(
			seedPos->getFX(),
			seedPos->getFY(),
			seedPos->getFZ()
		);
		l1.setFXYZ(
			seedPos->getFZ(),
			seedPos->getFY(),
			seedPos->getFX()
		);
		l2.setFXYZ(
			seedPos->getFY(),
			seedPos->getFX(),
			seedPos->getFZ()
		);

		fv4.x = modf(sin(l0.dot(&r0)) * 43758.8563f, &intPart);
		fv4.y = modf(sin(l1.dot(&r1)) * 24634.6345f, &intPart);
		fv4.z = modf(sin(l2.dot(&r2)) * 56445.2345f, &intPart);

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void addXYZ(float scalar, float multiplier = 1.0f) {
		fv4.x += scalar * multiplier;
		fv4.y += scalar * multiplier;
		fv4.z += scalar * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void addXYZ(float scalarX, float scalarY, float scalarZ, float multiplier = 1.0f) {
		fv4.x += scalarX * multiplier;
		fv4.y += scalarY * multiplier;
		fv4.z += scalarZ * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void addXYZRef(FIVector4 *scalar, float multiplier = 1.0f) {
		fv4.x += scalar->getFX() * multiplier;
		fv4.y += scalar->getFY() * multiplier;
		fv4.z += scalar->getFZ() * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}



	void multXYZ(float scalar) {
		fv4.x *= scalar;
		fv4.y *= scalar;
		fv4.z *= scalar;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void multXYZ(float scalarX, float scalarY, float scalarZ) {
		fv4.x *= scalarX;
		fv4.y *= scalarY;
		fv4.z *= scalarZ;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}


	void multXYZ(FIVector4 *scalar) {
		fv4.x *= scalar->getFX();
		fv4.y *= scalar->getFY();
		fv4.z *= scalar->getFZ();

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void divXYZ(FIVector4 *scalar) {
		fv4.x /= scalar->getFX();
		fv4.y /= scalar->getFY();
		fv4.z /= scalar->getFZ();

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void floorXYZ() {
		fv4.x = floor(fv4.x);
		fv4.y = floor(fv4.y);
		fv4.z = floor(fv4.z);

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}


	void intDivXYZ(int scalar) {

		iv4.x = intDiv(iv4.x, scalar);
		iv4.y = intDiv(iv4.y, scalar);
		iv4.z = intDiv(iv4.z, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}
	
	void intDivXYZ(int scalarX, int scalarY, int scalarZ) {


		iv4.x = intDiv(iv4.x, scalarX);
		iv4.y = intDiv(iv4.y, scalarY);
		iv4.z = intDiv(iv4.z, scalarZ);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	void modXYZ(int scalar) {
		iv4.x = iv4.x % scalar;
		iv4.y = iv4.y % scalar;
		iv4.z = iv4.z % scalar;

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	

	void wrapXYZ(int scalar) {
		iv4.x = wrapCoord(iv4.x, scalar);
		iv4.y = wrapCoord(iv4.y, scalar);
		iv4.z = wrapCoord(iv4.z, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	void wrapXY(int scalar) {
		iv4.x = wrapCoord(iv4.x, scalar);
		iv4.y = wrapCoord(iv4.y, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;

	}


	void minXYZ(FIVector4 *v1, FIVector4 *v2) {
		fv4.x = std::min(v1->getFX(), v2->getFX());
		fv4.y = std::min(v1->getFY(), v2->getFY());
		fv4.z = std::min(v1->getFZ(), v2->getFZ());

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void maxXYZ(FIVector4 *v1, FIVector4 *v2) {
		fv4.x = std::max(v1->getFX(), v2->getFX());
		fv4.y = std::max(v1->getFY(), v2->getFY());
		fv4.z = std::max(v1->getFZ(), v2->getFZ());

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void clampXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			fv4.x = minV->getFX();
		}
		if (fv4.y < minV->getFY()) {
			fv4.y = minV->getFY();
		}
		if (fv4.z < minV->getFZ()) {
			fv4.z = minV->getFZ();
		}
		if (fv4.x > maxV->getFX()) {
			fv4.x = maxV->getFX();
		}
		if (fv4.y > maxV->getFY()) {
			fv4.y = maxV->getFY();
		}
		if (fv4.z > maxV->getFZ()) {
			fv4.z = maxV->getFZ();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void clampX(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			fv4.x = minV->getFX();
		}
		if (fv4.x > maxV->getFX()) {
			fv4.x = maxV->getFX();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void clampY(FIVector4 *minV, FIVector4 *maxV) {

		if (fv4.y < minV->getFY()) {
			fv4.y = minV->getFY();
		}
		if (fv4.y > maxV->getFY()) {
			fv4.y = maxV->getFY();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void clampZ(float minV, float maxV) {

		if (fv4.z < minV) {
			fv4.z = minV;
		}
		if (fv4.z > maxV) {
			fv4.z = maxV;
		}

		iv4.z = (int)fv4.z;
	}



	bool inBoundsIsEqualXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.z < minV->getFZ()) {
			return false;
		}
		if (fv4.x > maxV->getFX()) {
			return false;
		}
		if (fv4.y > maxV->getFY()) {
			return false;
		}
		if (fv4.z > maxV->getFZ()) {
			return false;
		}

		return true;
	}

	static void normalizeBounds(FIVector4 *minBounds, FIVector4 *maxBounds) {
		float temp;

		if (minBounds->getFX() > maxBounds->getFX()) {
			temp = maxBounds->getFX();
			maxBounds->setFX(minBounds->getFX());
			minBounds->setFX(temp);
		}
		if (minBounds->getFY() > maxBounds->getFY()) {
			temp = maxBounds->getFY();
			maxBounds->setFY(minBounds->getFY());
			minBounds->setFY(temp);
		}
		if (minBounds->getFZ() > maxBounds->getFZ()) {
			temp = maxBounds->getFZ();
			maxBounds->setFZ(minBounds->getFZ());
			minBounds->setFZ(temp);
		}
	}

	static bool intersect(FIVector4 *aMin, FIVector4 *aMax, FIVector4 *bMin, FIVector4 *bMax) {

		float aWidth = aMax->getFX() - aMin->getFX();
		float aHeight = aMax->getFY() - aMin->getFY();
		float aDepth = aMax->getFZ() - aMin->getFZ();

		float bWidth = bMax->getFX() - bMin->getFX();
		float bHeight = bMax->getFY() - bMin->getFY();
		float bDepth = bMax->getFZ() - bMin->getFZ();

		float aWidthC = (aMax->getFX() + aMin->getFX()) / 2.0f;
		float aHeightC = (aMax->getFY() + aMin->getFY()) / 2.0f;
		float aDepthC = (aMax->getFZ() + aMin->getFZ()) / 2.0f;

		float bWidthC = (bMax->getFX() + bMin->getFX()) / 2.0f;
		float bHeightC = (bMax->getFY() + bMin->getFY()) / 2.0f;
		float bDepthC = (bMax->getFZ() + bMin->getFZ()) / 2.0f;



		return  (abs(aWidthC - bWidthC) * 2.0f <= (aWidth + bWidth)) &&
						(abs(aHeightC - bHeightC) * 2.0f <= (aHeight + bHeight)) &&
						(abs(aDepthC - bDepthC) * 2.0f <= (aDepth + bDepth));
	}

	static void growBoundary(FIVector4 *minB, FIVector4 *maxB, FIVector4 *minV, FIVector4 *maxV) {
		if (minB->getFX() > minV->getFX()) {
			minB->setFX(minV->getFX());
		}
		if (minB->getFY() > minV->getFY()) {
			minB->setFY(minV->getFY());
		}
		if (minB->getFZ() > minV->getFZ()) {
			minB->setFZ(minV->getFZ());
		}
		if (maxB->getFX() < maxV->getFX()) {
			maxB->setFX(maxV->getFX());
		}
		if (maxB->getFY() < maxV->getFY()) {
			maxB->setFY(maxV->getFY());
		}
		if (maxB->getFZ() < maxV->getFZ()) {
			maxB->setFZ(maxV->getFZ());
		}

	}



	bool inBoundsXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.z < minV->getFZ()) {
			return false;
		}
		if (fv4.x >= maxV->getFX()) {
			return false;
		}
		if (fv4.y >= maxV->getFY()) {
			return false;
		}
		if (fv4.z >= maxV->getFZ()) {
			return false;
		}

		return true;
	}
	
	bool inBoundsXYZSlack(FIVector4 *minV, FIVector4 *maxV, float slack) {
		if (fv4.x < minV->getFX()-slack) {
			return false;
		}
		if (fv4.y < minV->getFY()-slack) {
			return false;
		}
		if (fv4.z < minV->getFZ()-slack) {
			return false;
		}
		if (fv4.x >= maxV->getFX()+slack) {
			return false;
		}
		if (fv4.y >= maxV->getFY()+slack) {
			return false;
		}
		if (fv4.z >= maxV->getFZ()+slack) {
			return false;
		}

		return true;
	}





	bool inBoundsXY(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.x > maxV->getFX()) {
			return false;
		}
		if (fv4.y > maxV->getFY()) {
			return false;
		}

		return true;
	}

	bool iNotEqual(FIVector4 *otherVec) {
		if (
			(iv4.x == otherVec->getIX()) &&
			(iv4.y == otherVec->getIY()) &&
			(iv4.z == otherVec->getIZ())
		) {
			return false;
		}
		else {
			return true;
		}
	}



	float wrapDistance(FIVector4 *otherVec, int maxPitch, bool doSet = true) {

		int i;
		int j;

		int bestI;
		int bestJ;

		float shortestDis = FLT_MAX;
		float curDis;

		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {

				otherVec->addXYZ(i * maxPitch, j * maxPitch, 0, 1.0f);
				curDis = distance(otherVec);
				otherVec->addXYZ(i * maxPitch, j * maxPitch, 0, -1.0f);

				if (curDis < shortestDis) {
					shortestDis = curDis;
					bestI = i;
					bestJ = j;
				}

			}
		}

		if (doSet) {
			otherVec->addXYZ(bestI * maxPitch, bestJ * maxPitch, 0);
		}


		return shortestDis;

	}

	/*

	var raw_dx = Math.abs(x2 - x1);
	var raw_dy = Math.abs(y2 - y1);

	var dx = (raw_dx < (xmax / 2)) ? raw_dx : xmax - raw_dx;
	var dy = (raw_dy < (ymax / 2)) ? raw_dy : ymax - raw_dy;

	var l2dist = Math.sqrt((dx * dx) + (dy * dy));

	*/

	void rotate(float a, int plane) {

		float xp = fv4.x;
		float yp = fv4.y;
		float zp = fv4.z;

		switch (plane) {
		case E_PLANE_XY:
			xp = fv4.x * cos(a) - fv4.y * sin(a);
			yp = fv4.y * cos(a) + fv4.x * sin(a);
			break;

		case E_PLANE_YZ:
			zp = fv4.z * cos(a) - fv4.y * sin(a);
			yp = fv4.y * cos(a) + fv4.z * sin(a);
			break;

		case E_PLANE_XZ:
			xp = fv4.x * cos(a) - fv4.z * sin(a);
			zp = fv4.z * cos(a) + fv4.x * sin(a);
			break;
		}

		fv4.x = xp;
		fv4.y = yp;
		fv4.z = zp;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;

	}

	void rotate90(int ind) {
		switch (ind) {
		case 0: // 0 deg

			break;

		case 1: // 90 deg
			setFXY(-fv4.y, fv4.x);
			break;

		case 2: // 180 deg
			setFXY(-fv4.x, -fv4.y);
			break;

		case 3: // 270 deg
			setFXY(fv4.y, -fv4.x);
			break;
		}
	}
	
	float distanceXY(FIVector4 *otherVec) {

		float dx = fv4.x - otherVec->getFX();
		float dy = fv4.y - otherVec->getFY();

		return sqrt(dx * dx + dy * dy);
	}

	float distance(FIVector4 *otherVec) {

		float dx = fv4.x - otherVec->getFX();
		float dy = fv4.y - otherVec->getFY();
		float dz = fv4.z - otherVec->getFZ();

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	float length() {
		return sqrt(fv4.x * fv4.x + fv4.y * fv4.y + fv4.z * fv4.z);
	}

	float manhattanDis(FIVector4 *otherVec) {

		float dx = abs(fv4.x - otherVec->getFX());
		float dy = abs(fv4.y - otherVec->getFY());
		float dz = abs(fv4.z - otherVec->getFZ());

		return max(max(dx, dy), dz);
	}

	void normalize() {
		float len = sqrt(fv4.x * fv4.x + fv4.y * fv4.y + fv4.z * fv4.z);

		fv4.x = fv4.x / len;
		fv4.y = fv4.y / len;
		fv4.z = fv4.z / len;


	}

	float dot(FIVector4 *otherVec) {

		return fv4.x * otherVec->getFX() +
					 fv4.y * otherVec->getFY() +
					 fv4.z * otherVec->getFZ();
	}

	static void cross(FIVector4 *outVec, FIVector4 *v1, FIVector4 *v2) {


		float x1 = v1->getFX();
		float y1 = v1->getFY();
		float z1 = v1->getFZ();

		float x2 = v2->getFX();
		float y2 = v2->getFY();
		float z2 = v2->getFZ();

		outVec->setFXYZ(
			(y1 * z2) - (y2 * z1),
			(z1 * x2) - (z2 * x1),
			(x1 * y2) - (x2 * y1)
		);

	}




	iVector4 *getIXYZW() {
		return &iv4;
	}
	fVector4 *getFXYZW() {
		return &fv4;
	}

	iVector3 *getIXYZ() {
		iv3.x = iv4.x;
		iv3.y = iv4.y;
		iv3.z = iv4.z;
		return &iv3;
	}
	fVector3 *getFXYZ() {
		fv3.x = fv4.x;
		fv3.y = fv4.y;
		fv3.z = fv4.z;
		return &fv3;
	}

	iVector2 *getIXY() {
		iv2.x = iv4.x;
		iv2.y = iv4.y;
		return &iv2;
	}
	fVector2 *getFXY() {
		fv2.x = fv4.x;
		fv2.y = fv4.y;
		return &fv2;
	}

	int getIX() {
		return iv4.x;
	}
	int getIY() {
		return iv4.y;
	}
	int getIZ() {
		return iv4.z;
	}
	int getIW() {
		return iv4.w;
	}

	float getFX() {
		return fv4.x;
	}
	float getFY() {
		return fv4.y;
	}
	float getFZ() {
		return fv4.z;
	}
	float getFW() {
		return fv4.w;
	}


};

struct RotationInfo {
	float rotMatrix[16];
	FIVector4 basePoint;
	FIVector4 axisAngle;
		
};


float getRandSeeded(FIVector4 *seedPos, FIVector4 *seedVals) {
	float intPart;		
	return abs ( modf(sin(seedPos->dot(seedVals)) * 43758.8563f, &intPart) );
}

int iGetRandSeeded(
	FIVector4 *seedPos,
	FIVector4 *seedVals,
	int minV,
	int maxV
) {
	float intPart = 0.0f;		
	int res = abs( modf(sin(seedPos->dot(seedVals)) * 43758.8563f, &intPart) )*1000000.0f;
	res = (res % (maxV + 1 - minV)) + minV;
	
	return res;
}




class AxisRotation {

public:

	float rotationMatrix[16];
	float inputMatrix[4];
	float outputMatrix[4];

	FIVector4 tempRes1;
	FIVector4 tempRes2;
	FIVector4 tempRes3;

	void doRotation(FIVector4 *output, FIVector4 *input, FIVector4 *axis, float angle)
	{
		int i;
		int j;
		int k;

		float u = axis->getFX();
		float v = axis->getFY();
		float w = axis->getFZ();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotationMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotationMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotationMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotationMatrix[3] = 0.0f;

		rotationMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotationMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotationMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotationMatrix[7] = 0.0f;

		rotationMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotationMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotationMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotationMatrix[11] = 0.0f;

		rotationMatrix[12] = 0.0f;
		rotationMatrix[13] = 0.0f;
		rotationMatrix[14] = 0.0f;
		rotationMatrix[15] = 1.0f;



		outputMatrix[0] = 0.0f;
		outputMatrix[1] = 0.0f;
		outputMatrix[2] = 0.0f;
		outputMatrix[3] = 0.0f;

		inputMatrix[0] = input->getFX();
		inputMatrix[1] = input->getFY();
		inputMatrix[2] = input->getFZ();
		inputMatrix[3] = 1.0;


		for (i = 0; i < 4; i++ ) {
			for (j = 0; j < 1; j++) {
				outputMatrix[i] = 0;
				for (k = 0; k < 4; k++) {
					outputMatrix[i] += rotationMatrix[i*4+k] * inputMatrix[k];
				}
			}
		}

		output->setFXYZW(
			outputMatrix[0],
			outputMatrix[1],
			outputMatrix[2],
			outputMatrix[3]
		);

	}
	
	
	
	void buildRotMatrix(
		RotationInfo* rotInfo
	) {
		
		float u = rotInfo->axisAngle.getFX();
		float v = rotInfo->axisAngle.getFY();
		float w = rotInfo->axisAngle.getFZ();
		float angle = rotInfo->axisAngle.getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotInfo->rotMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotInfo->rotMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotInfo->rotMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotInfo->rotMatrix[3] = 0.0f;

		rotInfo->rotMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotInfo->rotMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotInfo->rotMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotInfo->rotMatrix[7] = 0.0f;

		rotInfo->rotMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotInfo->rotMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotInfo->rotMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotInfo->rotMatrix[11] = 0.0f;

		rotInfo->rotMatrix[12] = 0.0f;
		rotInfo->rotMatrix[13] = 0.0f;
		rotInfo->rotMatrix[14] = 0.0f;
		rotInfo->rotMatrix[15] = 1.0f;

	}
	
	
	void applyRotation(
		FIVector4 *output,
		FIVector4 *input,
		RotationInfo* rotInfo
	) {
		int i;
		int j;
		int k;
		int m;
		
		//tempRes3.copyFrom(baseOffset);
		//tempRes3.addXYZRef(parentOffset,-1.0f);

		float u = rotInfo->axisAngle.getFX();
		float v = rotInfo->axisAngle.getFY();
		float w = rotInfo->axisAngle.getFZ();
		float angle = rotInfo->axisAngle.getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		


		for (m = 0; m < 3; m++) {
			outputMatrix[0] = 0.0f;
			outputMatrix[1] = 0.0f;
			outputMatrix[2] = 0.0f;
			outputMatrix[3] = 0.0f;

			inputMatrix[0] = input[m].getFX();// - (rotInfo->basePoint[0]);
			inputMatrix[1] = input[m].getFY();// - (rotInfo->basePoint[1]);
			inputMatrix[2] = input[m].getFZ();// - (rotInfo->basePoint[2]);
			inputMatrix[3] = 1.0;


			for (i = 0; i < 4; i++ ) {
				for (j = 0; j < 1; j++) {
					outputMatrix[i] = 0;
					for (k = 0; k < 4; k++) {
						outputMatrix[i] += rotInfo->rotMatrix[i*4+k] * inputMatrix[k];
					}
				}
			}

			output[m].setFXYZW(
				outputMatrix[0],// + (rotInfo->basePoint[0]),
				outputMatrix[1],// + (rotInfo->basePoint[1]),
				outputMatrix[2],// + (rotInfo->basePoint[2]),
				outputMatrix[3]
			);
			//output[m].normalize();
		}

		

	}
	
	
	void doRotationTBN(
		FIVector4 *output,
		FIVector4 *input,
		FIVector4 *axisAngle,
		FIVector4 *parentOffset,
		FIVector4 *baseOffset
	)
	{
		int i;
		int j;
		int k;
		int m;
		
		tempRes3.copyFrom(baseOffset);
		tempRes3.addXYZRef(parentOffset,-1.0f);

		float u = axisAngle->getFX();
		float v = axisAngle->getFY();
		float w = axisAngle->getFZ();
		float angle = axisAngle->getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotationMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotationMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotationMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotationMatrix[3] = 0.0f;

		rotationMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotationMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotationMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotationMatrix[7] = 0.0f;

		rotationMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotationMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotationMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotationMatrix[11] = 0.0f;

		rotationMatrix[12] = 0.0f;
		rotationMatrix[13] = 0.0f;
		rotationMatrix[14] = 0.0f;
		rotationMatrix[15] = 1.0f;



		for (m = 0; m < 3; m++) {
			outputMatrix[0] = 0.0f;
			outputMatrix[1] = 0.0f;
			outputMatrix[2] = 0.0f;
			outputMatrix[3] = 0.0f;

			inputMatrix[0] = input[m].getFX() + (tempRes3[0]);
			inputMatrix[1] = input[m].getFY() + (tempRes3[1]);
			inputMatrix[2] = input[m].getFZ() + (tempRes3[2]);
			inputMatrix[3] = 1.0;


			for (i = 0; i < 4; i++ ) {
				for (j = 0; j < 1; j++) {
					outputMatrix[i] = 0;
					for (k = 0; k < 4; k++) {
						outputMatrix[i] += rotationMatrix[i*4+k] * inputMatrix[k];
					}
				}
			}

			output[m].setFXYZW(
				outputMatrix[0] - (tempRes3[0]),
				outputMatrix[1] - (tempRes3[1]),
				outputMatrix[2] - (tempRes3[2]),
				outputMatrix[3]
			);
			output[m].normalize();
		}

		

	}
	

};
AxisRotation axisRotationInstance;




class GameLight {
public:

	int id;
	int globalId;
	int colPacked;
	FIVector4 pos;
	FIVector4 color;
	float screenDistance;
	bool isOn;

	GameLight() {
		isOn = true;
	}

	void updateCP() {
		colPacked = getPackedColor(color.getFX() * 255.0f, color.getFY() * 255.0f, color.getFZ() * 255.0f);
	}

	void init(
		int _id,
		int _globalId,
		FIVector4 *_pos,
		FIVector4 *_color
	) {
		id = _id;
		globalId = _globalId;
		pos.setFXYZRef(_pos);
		color.setFXYZRef(_color);
		updateCP();
	}

	// void initFrom(DynObject* dyno) {
	//     id = -1;
	//     globalId = -1;

	//     pos.setFXYZRef(&(dyno->pos));
	//     color.setFXYZRef(&(dyno->color));
	//     updateCP();
	// }

};


class DynObject {

public:

	FIVector4 pos;
	FIVector4 color;
	FIVector4 posRel;

	int r;
	int g;
	int b;

	int colPacked;
	bool isRelative;
	bool doRender;

	float radius;

	GameLight childLight;


	DynObject() {

	}

	GameLight *getLight() {
		childLight.id = -1;
		childLight.globalId = -1;

		childLight.pos.setFXYZRef(&pos);
		childLight.color.setFXYZRef(&color);
		childLight.updateCP();
		return &childLight;
	}

	void init(int _x, int _y, int _z, int _r, int _g, int _b, bool _doRender, bool _isRelative, FIVector4 *_cameraPos, float _radius) {
		isRelative = _isRelative;
		doRender = _doRender;

		if (isRelative) {
			posRel.setIXYZ(_x, _y, _z);
			pos.setFXYZRef(_cameraPos);
			pos.addXYZRef(&posRel);
		}
		else {
			pos.setIXYZ(_x, _y, _z);
			posRel.setIXYZ(0, 0, 0);
		}

		radius = _radius;

		r = _r;
		g = _g;
		b = _b;

		color.setFXYZ(
			((float)r) / 255.0f,
			((float)g) / 255.0f,
			((float)b) / 255.0f
		);

		colPacked = getPackedColor(r, g, b);
	}


};






