

// list<int> cachedPoolIds;
// vector<intPair> cachedOrderedIds;
// vector<PooledResource *> cachedPoolItems;



class FontWrapper {
public:
	
	Singleton* singleton;
	
	charArr lastJSONBuffer;
	JSONValue *jsRoot;
	
	Image *fontImage;
	
	float ascender;
	float descender;
	float fontHeight;
	
	float maxWidth;
	float fontScale;
	float additionalOffset;
	
	bool isIcons;
	
	CharStruct charVals[4096];
	
	FontWrapper() {
		
	}
	
	void init(
		Singleton* _singleton,
		string fontName,
		bool _isIcons,
		float _fontScale,
		float _additionalOffset = 0.0f
	) {
		
		int counter;
		int i;
		int j;
		int ind;
		
		additionalOffset = _additionalOffset;
		fontScale = _fontScale;
		isIcons = _isIcons;
		
		JSONValue *cn;
		JSONValue *cc;
		
		singleton = _singleton;
		lastJSONBuffer.data = NULL;
		lastJSONBuffer.size = 0;
		
		cout << "\n\n\nFONT LOAD\n\n\n";
		
		fontImage = loadBMP("../data/fonts/"+fontName+".bmp");
		if (isIcons) {
			fontImage->getTextureId(GL_NEAREST);
		}
		else {
			fontImage->getTextureId(GL_LINEAR);
		}
		
		
		maxWidth = 0.0f;
		counter = 0;
		
		if (isIcons) {
			maxWidth = 16.0f;
			ascender = 0.0f;
			descender = -15.0f+additionalOffset;
			fontHeight = 16.0f;
			
			
			for (j = 0; j < fontImage->height/16; j++) {
				for (i = 0; i < fontImage->width/16; i++) {
					charVals[counter].consumedW = 16.0f;
					charVals[counter].consumedH = 16.0f;
					charVals[counter].offsetX = 0.0f;
					charVals[counter].offsetY = 0.0f;
					charVals[counter].sampX = i*16;
					charVals[counter].sampY = j*16;
					charVals[counter].sampW = 16.0f;
					charVals[counter].sampH = 16.0f;
					
					counter++;
				}
			}
			
		}
		else {
			if ( singleton->loadFile("../data/fonts/"+fontName+".js", &lastJSONBuffer) )
			{
				if (singleton->processJSON(&lastJSONBuffer, &(singleton->nullBuffer), &jsRoot)) {
					
					ascender = jsRoot->Child("metrics")->Child("ascender")->number_value;
					descender = jsRoot->Child("metrics")->Child("descender")->number_value;
					fontHeight = jsRoot->Child("metrics")->Child("height")->number_value;
					
					cn = jsRoot->Child("chars");
					
					
					for (i = 32; i <= 126; i++) {
						ind = i-32;
						cc = cn->Child(ind);
						
						charVals[i].consumedH = fontHeight;
						charVals[i].consumedW = cc->Child("width")->number_value;
						
						charVals[i].offsetX = cc->Child("ox")->number_value;
						charVals[i].offsetY = cc->Child("oy")->number_value;
						
						charVals[i].sampX = cc->Child("x")->number_value;
						charVals[i].sampY = cc->Child("y")->number_value;
						charVals[i].sampW = cc->Child("w")->number_value;
						charVals[i].sampH = cc->Child("h")->number_value;
						
						if (charVals[i].consumedW > maxWidth) {
							maxWidth = charVals[i].consumedW;
						}
					}
					
					
					
				}
			}
		}
		
		
		
		
	}

};



