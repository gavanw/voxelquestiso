//uniform sampler3D Texture0; //volume texture
uniform sampler2D Texture0;

//uniform sampler2D Texture0;
//uniform sampler3D Texture1;
varying vec3 TexCoord0;
varying vec3 TexCoord1;

uniform vec3 worldMinVisInPixels;
uniform vec3 worldMaxVisInPixels;
uniform vec3 worldMinBufInPixels;
uniform vec3 worldMaxBufInPixels;

uniform vec4 scaleAndOffset;

//uniform vec3 offsetInPagesLocal;

uniform float pageDepth;
uniform float bufferMult;
uniform float visPageSizeInPixels;

//const int iNumRaySteps = 2;
//const float fNumRaySteps = 2.0;

uniform float slicesPerPitch;// = sqrt(pitch);
//varying float pitch;// = 256.0;
//varying float pitchM1;// = pitch-1.0;


$

void main() {
    
    TexCoord0 = gl_MultiTexCoord0.xyz;
    TexCoord1 = gl_MultiTexCoord1.xyz;

    vec4 newPos = gl_Vertex;


    newPos.x *= scaleAndOffset.x;
    newPos.y *= scaleAndOffset.y;
    newPos.x += scaleAndOffset.z;
    newPos.y += scaleAndOffset.w;

    newPos.z = gl_Vertex.z*0.001+pageDepth;

    gl_Position = newPos;

}

$

vec4 sampleAtPoint(vec3 point) {
    vec2 texc;

    float pitch = slicesPerPitch*slicesPerPitch;
    float pitchM1 = pitch-1.0;

    vec3 newPoint = point/bufferMult + (1.0-1.0/bufferMult)/2.0;
    
    vec3 curFace = (newPoint.rgb*pitchM1+0.5)/pitch;
    float bval = curFace.b*pitchM1;
    float xval = floor(mod(bval, slicesPerPitch))/slicesPerPitch;
    float yval = floor(bval/slicesPerPitch)/slicesPerPitch;
    
    texc.x = curFace.r/(slicesPerPitch) + xval;
    texc.y = curFace.g/(slicesPerPitch) + yval;
    return texture2D(Texture0, texc.xy);
    

    //return texture3D(Texture0, newPoint);
}


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 getAO(vec3 tp, vec4 curSamp, vec3 wp) {
    int i;
    int a, b, c;
    

    

    vec3 offVal;
    vec3 offValAbs;

    float len;
    

    float aoVal = 0.0;
    float totalAO = 0.0;

    float notZero;



    vec4 res;

    int maxRad;
    float tsize = visPageSizeInPixels;

    vec3 testPoint = tp + 1.0/(tsize); //bufferMult

    float fMaxRad;
    float curPower;

    float rval;
    float rval2;

    vec3 norm = vec3(0.0,0.0,0.0);
    vec3 norm2 = vec3(0.0,0.0,0.0);

    int rad = 8;
    int radStep = 2;
    float frad = float(radStep);

    float totSteps = 0.0;
    float totHits = 0.0;

    float ovLen = 0.0;

    float rvMix = 0.0;

    //float sval = abs(sin(wp.y/30.0));

    float isRock = float( curSamp.r + curSamp.g + curSamp.b > 0.0);

    for (c = -rad; c <= rad; c+=radStep) {
        for (b = -rad; b <= rad; b+=radStep) {
            for (a = -rad; a <= rad; a+=radStep) {
                
                offVal.x = float(a);
                offVal.y = float(b);
                offVal.z = float(c);

                //offVal = normalize(offVal);
                //offValAbs = offVal*frad/tsize;

                ovLen = 1.0/length(offVal);

                res = sampleAtPoint(offVal/tsize + testPoint);
                rval = float(res.a == 0.0);

                rval2 = float( abs(res.r-curSamp.r) + abs(res.g-curSamp.g) + abs(res.b-curSamp.b) != 0.0 );
                rvMix = mix(rval,rval2,0.5);//mix(rval,rval2, isRock);//abs(sin(wp.y)) );//isRock
                norm += rvMix*(offVal);
                //norm2 += res.a*offVal;

                totHits += rval;
                totSteps += 1.0;
                
            }
        }
    }

    
    if (totHits == 0.0) {
        norm = vec3(0.0,0.0,0.0);//norm2/totSteps;

        
        if (testPoint.x == 1.0) {
            norm.x = 1.0;
        }
        if (testPoint.y == 1.0) {
            norm.y = 1.0;
        }
        if (testPoint.z == 1.0) {
            norm.z = 1.0;
        }
        

        aoVal = 0.0;//curSamp.a;
    }
    else {
        maxRad = 128;
        fMaxRad = float(maxRad);

        for (rad = 32; rad < maxRad; rad *= 2) {
            radStep = rad/2;
            frad = float(rad);

            //curPower = 1.0-frad/fMaxRad;

            for (c = -rad; c <= rad; c+=radStep) {
                for (b = -rad; b <= rad; b+=radStep) {
                    for (a = -rad; a <= rad; a+=radStep) {
                        
                        offVal.x = float(a);
                        offVal.y = float(b);
                        offVal.z = float(c);

                        //offVal = offVal*16.0;

                        offValAbs = abs(offVal);

                        notZero = float( (offValAbs.x + offValAbs.y + offValAbs.z) > 0.0);
                        offVal = normalize(offVal);
                        offVal *= frad/tsize;
                        res = sampleAtPoint(offVal+testPoint); //+norm*2.0/(tsize)
                        rval = float(res.a != 0.0);
                        aoVal += rval*notZero;// *curPower;//frad;
                        totalAO += notZero;// *curPower;//frad*notZero;
                        
                    }
                }
            }
        }

        aoVal = clamp(1.0 - aoVal/totalAO, 1.0/255.0, 1.0);
    }
    


        
    


    norm = normalize(norm);
    norm = (norm + 1.0)/2.0;





    return vec4(norm,aoVal); //totHits/totSteps
}


int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}

vec2 pack16(float num) {

    int iz = int(num);
    int ir = intMod(iz,256);
    int ig = (iz)/256;

    vec2 res;

    res.r = float(ir)/255.0;
    res.g = float(ig)/255.0;

    return res;

}

float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
}

/*
void main() {
    
    gl_FragData[0] = vec4(1.0);
    gl_FragData[1] = vec4(1.0);
}
*/

void main() {

    int i = 0;
    int j = 0;

    float fi;
    float fi2;
    float fiRes;
    float fj;
    float fLerp = 0.0;
    
    vec2 newCoords;
    //vec3 front = TexCoord1.xyz;
    //vec3 back = TexCoord0.xyz;

    
    //vec4 blackCol = vec4(0.0,0.0,0.0,0.0);
    
    
    
    // float curDis = 0.0;
    // int iCurDis = 0;  

    // vec3 curPos = vec3(0.0,0.0,0.0);
    // //vec3 lastGoodPos = vec3(0.0,0.0,0.0);
 
    // curDis = floor(distance(front,back)*visPageSizeInPixels); //visPageSizeInPixels
    // iCurDis = int(curDis);

    // float q;

    // for (i = 0; i < iCurDis; i++) {
    //     fi = float(i);
    //     fLerp = fi/curDis;

    //     curPos = mix(front,back,fLerp);

    //     samp = sampleAtPoint(curPos);

    //     if (samp.a != 0.0) {
    //         break;
    //     }

    //     //lastGoodPos = curPos;
    // }
    // if ( i == iCurDis ) {
    //     discard;
    // }

    vec3 curPos = TexCoord0.xyz;
    vec4 samp = texture2D(Texture0, TexCoord1.xy);

    if (samp.a == 0.0) {
        discard;
    }

    vec3 worldPos;

    worldPos.x = mix(worldMinVisInPixels.x, worldMaxVisInPixels.x, curPos.x);
    worldPos.y = mix(worldMinVisInPixels.y, worldMaxVisInPixels.y, curPos.y);
    worldPos.z = mix(worldMinVisInPixels.z, worldMaxVisInPixels.z, curPos.z);


    vec2 heightVals = pack16(worldPos.z);

    vec4 normAO = getAO(curPos, samp, worldPos);
    vec4 heightMat = vec4(heightVals.rg, samp.a, 1.0);

    gl_FragData[0] = heightMat;//vec4(offsetInPagesLocal/16.0,1.0);// heightMat;
    gl_FragData[1] = normAO;//vec4(curPos,1.0);//normAO;

}
