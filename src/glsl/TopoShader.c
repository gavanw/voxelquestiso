#version 120

uniform sampler2D Texture0; // palette
uniform sampler2D Texture1; // heightmap
uniform sampler2D Texture2; // cityFBO;
uniform sampler2D Texture3; // back face
uniform sampler2D Texture4; // front face

varying vec2 TexCoord0;

uniform vec4 mapFreqs;
uniform vec4 mapAmps;


uniform float timeOfDay;
uniform float curTime;
uniform float cameraZoom;
uniform float mapTrans;
uniform float tiltAmount;

uniform float seaLevel;
uniform vec3 cameraPos;
uniform vec2 mapDimInPixels;


uniform vec3 worldSizeInPixels;

float detailAmount = smoothstep(0.000793203*0.25,0.0110403*0.25,cameraZoom);

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;

}    

$


int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}

float getGrid(int val, vec2 gridVecBase, float thickness) {

    int testVal = val;

    int hasDown = testVal / 8;
    testVal -= hasDown * 8;
    
    int hasUp = testVal / 4;
    testVal -= hasUp*4;
    
    int hasRight = testVal/2;
    testVal -= hasRight*2;

    int hasLeft = testVal;

    float maxT = 1.0-thickness;
    float minT = thickness;

    return float(
        ( (gridVecBase.x >= maxT) && (hasLeft > 0) ) ||
        ( (gridVecBase.x <= minT) && (hasRight > 0)  ) ||
        ( (gridVecBase.y >= maxT) && (hasUp > 0)  ) ||
        ( (gridVecBase.y <= minT) && (hasDown > 0) )
    );
}

float getHeightAtCoords(vec2 mapCoord) {

    //vec2 mapCoord = TexCoord0.xy; //(coord / worldSizeInPixels.x);

    vec4 texHM0 =  texture2D(Texture1, mapFreqs.x * mapCoord );
    vec4 texHM1 =  texture2D(Texture1, floor(mapFreqs.y * mapCoord) );
    vec4 texHM2 =  texture2D(Texture1, floor(mapFreqs.z * mapCoord) );
    vec4 texHM3 =  texture2D(Texture1, floor(mapFreqs.w * mapCoord) );

    

    float res =  
        texHM0.r*mapAmps.x 
        + (texHM1.r*mapAmps.y 
        + texHM2.r*mapAmps.z 
        + texHM3.r*mapAmps.w
        -
        ( texHM1.r*mapAmps.y * 0.5 
        + texHM2.r*mapAmps.z * 0.5 
        + texHM3.r*mapAmps.w * 0.5)
        
        )*1.0 //detailAmount
    ;
    
    res = mix(0.125f,0.875f,res);
        
    //return texHM0.r;

    return res;

}

float fNumSteps = mix(64.0,256.0,detailAmount);
int iNumSteps = int(fNumSteps);


void main() {

    float newTime = curTime/20000.0;
    float maxMapDis = 0.45;
    
    int i;
    int j;
    
    
    vec3 backFace = texture2D(Texture3, TexCoord0.xy).xyz;
    vec3 frontFace = texture2D(Texture4, TexCoord0.xy).xyz;
    
    vec2 orig = (cameraPos.xy/worldSizeInPixels.xy)+1.0;// ;
    
    backFace.xy += (cameraPos.xy/worldSizeInPixels.xy)+0.5;
    frontFace.xy += (cameraPos.xy/worldSizeInPixels.xy)+0.5;
    
    float radModMax = 0.1;
    float radMod = abs(mod(curTime,2000.0)*radModMax/2000.0);

    

    float origDis = 0.0;
    float origMin = 0.0 + radMod;
    float origMax = 0.01 + radMod;
    
    origMin = mix(origMin,origMax,radMod/radModMax);

    //float tiltMod = 0.0;//sin(tiltAmount*3.14159/4.0)*0.2;

    // vec2 begCoord = TexCoord0.xy+(cameraPos.xy/worldSizeInPixels.xy)+0.5;
    // vec2 endCoord = begCoord;
    // begCoord.xy += tiltMod;
    
    // vec2 curCoord = vec2(0.0);
    // vec2 orig = (cameraPos.xy/worldSizeInPixels.xy)+1.0 + tiltMod*0.5;// - tiltAmount*0.2;
    
    
    vec3 begCoord = frontFace;
    vec3 endCoord = backFace;
    vec3 curCoord = vec3(0.0);

    float deltaVal = 0.0;
    float fi = 0.0;
    float fj = 0.0;
    float lerpVal = 0.0;
    float curHeight = 0.0;
    float terHeight = 0.0;
    float ringHeight = 0.0;
    float iLerpVal = 0.0;
    float oldLerpMin = 0.0;
    float oldLerpMax = 0.0;
    
    vec2 coordDif = vec2(0.0);
    
    //float terHeightBase = texture2D(Texture1, TexCoord0).r;
    
    bool isMarker = false;
    
    
    
    fi = 0.0;
    
    
    
    
    
    
    for (i = 0; i < iNumSteps; i++) {
        fi = float(i);
        
        //lerpVal = mix(fi/fNumSteps, mix(oldLerpMin,oldLerpMax,fi/fNumSteps), fj);
        lerpVal = fi/fNumSteps;
        
        
        iLerpVal = 1.0-lerpVal;
        curCoord = mix(begCoord, endCoord, lerpVal);        
        curHeight = curCoord.z;
        origDis = distance(curCoord.xy,orig.xy);
        
        //terHeight = texture2D(Texture1, curCoord.xy).r;
        
        terHeight = getHeightAtCoords(curCoord.xy);
        ringHeight = 1.0-radMod/radModMax;
        
        isMarker = isMarker || ( (origDis > origMin)&&(origDis < origMax)&&(ringHeight>terHeight)&&(ringHeight>curHeight) );
        coordDif = abs(curCoord.xy-orig.xy);
        
        if (
            (terHeight >= curHeight) &&
            (max(coordDif.x,coordDif.y) < maxMapDis)
        ) {
            break;
        }
    }
    
    
    
    
    // for (i = 0; i < iNumSteps; i++) {
        
    //     lerpVal = fi/fNumSteps;
    //     iLerpVal = 1.0-lerpVal;
    //     curCoord = mix(begCoord, endCoord, lerpVal);
        
    //     curHeight = curCoord.z;
        
    //     origDis = distance(curCoord.xy,orig.xy);
        
    //     terHeight = texture2D(Texture1, curCoord.xy).r;// + sin((curTime+TexCoord0.y*TexCoord0.x*16000.0)/1000.0)*0.5;
    //     //terHeight = getHeightAtCoords(curCoord.xy);
        
    //     ringHeight = 1.0-radMod/radModMax;
    //     isMarker = isMarker || ( (origDis > origMin)&&(origDis < origMax)&&(ringHeight>terHeight)&&(ringHeight>iLerpVal) );
    //     coordDif = abs(curCoord.xy-orig.xy);
    //     deltaVal = (curHeight-terHeight*float(max(coordDif.x,coordDif.y) < maxMapDis))*4.0; //
        
    //     //deltaVal *= mix(1.0,0.5,float(deltaVal<0.0));
        
    //     fi += deltaVal;
    // }
    
    if ((max(coordDif.x,coordDif.y) > maxMapDis*1.01)) {
        discard;
    }
    
    
    
   
    
    
    
    

    vec2 newTC = curCoord.xy;
    
    
    
    
    

    vec4 tex1 = texture2D( Texture1, newTC.xy);
    vec4 tex2 = texture2D( Texture2, newTC.xy);


    // vec4 texHM0 =  texture2D(Texture1, (newTC.xy*1.0) );
    // vec4 texHM1 =  texture2D(Texture1, (newTC.xy*4.0) );
    // vec4 texHM2 =  texture2D(Texture1, (newTC.xy*16.0) );
    //vec4 texHM3 =  texture2D(Texture1, (newTC.xy*32.0) );

    float testHeight = getHeightAtCoords(newTC); //(texHM0.r);// *0.7 +  texHM1.r*0.2 + texHM2.r*0.1);//(texHM0.r*0.6 + texHM1.r*0.2 + texHM2.r*0.07 + texHM3.r*0.03);
    //testHeight = pow(testHeight,2.0);

    float isAboveWater = float(testHeight > seaLevel);
    vec4 landRes = texture2D( Texture0, vec2( (testHeight-seaLevel)/(1.0-seaLevel), (5.0 + 0.5)/255.0 ) ); //vec4(testHeight);//
    vec4 seaRes = texture2D( Texture0, vec2(testHeight/seaLevel, (6.0 + 0.5)/255.0 ) );
    vec4 topoRes = mix(seaRes,landRes,isAboveWater);

    vec4 tex0 = topoRes;
    tex0.a = 1.0;


    float offsetAmount = (1.0)/mapDimInPixels.x;

    vec4 tex1u = texture2D(Texture1, vec2(newTC.x, newTC.y + offsetAmount) );
    vec4 tex1d = texture2D(Texture1, vec2(newTC.x, newTC.y - offsetAmount) );
    vec4 tex1l = texture2D(Texture1, vec2(newTC.x - offsetAmount, newTC.y) );
    vec4 tex1r = texture2D(Texture1, vec2(newTC.x + offsetAmount, newTC.y) );

    vec4 tex2u = texture2D(Texture2, vec2(newTC.x, newTC.y + offsetAmount) );
    vec4 tex2d = texture2D(Texture2, vec2(newTC.x, newTC.y - offsetAmount) );
    vec4 tex2l = texture2D(Texture2, vec2(newTC.x - offsetAmount, newTC.y) );
    vec4 tex2r = texture2D(Texture2, vec2(newTC.x + offsetAmount, newTC.y) );


    float mod1 = 1.0;
    if (
        tex1u.g != tex1.g ||
        tex1d.g != tex1.g ||
        tex1l.g != tex1.g ||
        tex1r.g != tex1.g

    ) {
        mod1 = 1.0;
    }


    // float mod2 = 0.0;
    // if (
    //     tex2u.b != tex2.b ||
    //     tex2d.b != tex2.b ||
    //     tex2l.b != tex2.b ||
    //     tex2r.b != tex2.b

    // ) {
    //     mod2 = 0.6;
    // }

    

    //float isBridge = float( abs(testHeight - seaLevel) < 10.0/255.0 );

    vec2 gridVecBase = ( (newTC.xy*mapDimInPixels.xy) - floor(newTC.xy*mapDimInPixels.xy) );
    vec2 gridVec = abs( gridVecBase - 0.5)*2.0;
    float gridTest = float( (gridVec.x >= 0.9) || (gridVec.y >= 0.9) )*0.5;

    
    float gv3 = getGrid( int(tex2.b*255.0), gridVecBase, 0.4 );
    float gv2 = getGrid( int(tex2.r*255.0), gridVecBase, 0.2 ); //stchannel
    float gv1 = getGrid( int(tex2.g*255.0), gridVecBase, 0.1 )*0.5; //btchannel
    
    float gridMod = mix( 0.0, max(gv1,gv2), clamp(cameraZoom/0.01,0.0,1.0) );

    vec3 resCol = (tex0.rgb + gridMod)*mod1;

    // mix(
    //     vec3(testHeight/5.0,testHeight/2.0,testHeight),
    //     (tex0.rgb + gridMod)*mod,
    //     isAboveWater
    // );
    resCol = mix(
        resCol,
        
        mix(
            resCol+vec3(0.0,0.125,0.25),
            resCol+0.5,//vec3(1.0,1.0,1.0),//vec3(0.3,0.1,0.0),
            isAboveWater
        ),
        
        gv3
    );

    if (tex2.a > 0.0) {
        resCol.rgb = resCol.rgb*0.75 + (mod(tex2.a*255.0,16.0)/15.0)*0.25;
    }

    // float othick = 0.01;
    // vec2 fracVal = vec2( fract(newTC.x),fract(newTC.y) );
    // if (
    //     ((fracVal.x >= -othick)&&(fracVal.x <= othick)) ||
    //     ((fracVal.y >= -othick)&&(fracVal.y <= othick))
    // ) {
    //     resCol += 0.2;
    // }

    

    //gl_FragData[0] = vec4(tex0.rgb,mapTrans);

    // + tex2.a * 8.0;
    
    if (isMarker) {
        // *clamp(1.0/(cameraZoom*1024.0),0.0,1.0)
        resCol += vec3(
            (smoothstep(origMin, origMax, origDis)*0.5+0.5),
            0.0,
            0.0
        )*(1.0-detailAmount)*(1.0-(radMod/radModMax));
    }
    if (origDis < 0.005) {
        resCol += 0.2*abs(sin(curTime/100.0));
    }
    
    resCol *= mix((1.0-smoothstep(0.9,1.0,max(coordDif.x,coordDif.y)/maxMapDis)) + iLerpVal*0.2,1.0,0.5);   
    
    

    gl_FragData[0] = vec4( resCol, mapTrans );// + float(tex1.a > 0.0)*0.2;// + tex2.a*0.5;// + float(tex1.r < seaLevel);

}


