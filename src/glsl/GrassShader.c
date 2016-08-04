#version 120

uniform sampler2D Texture0;
uniform sampler2D Texture1;

// noise FBO
uniform sampler2D Texture2;

// grass FBO
uniform sampler2D Texture3;


varying vec4 TexCoord0;

uniform vec2 grassWH;
uniform float curTime;
uniform float cameraZoom;
uniform float scaleFactor;
uniform vec3 cameraPos;
uniform vec2 cameraPosSS;
uniform vec2 bufferDim;


varying vec4 resVert;
varying vec3 normMod;
varying float baseHeight;

const float TEX_NULL = 0.0/255.0;
const float TEX_DIRT = 8.0/255.0;
const float TEX_BRICK = 9.0/255.0;
const float TEX_MORTAR = 10.0/255.0;
const float TEX_STONE = 11.0/255.0;
const float TEX_GRASS = 12.0/255.0;
const float TEX_GRASS2 = 13.0/255.0;




int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}

float intModF(float v1, int rhs) {
    int lhs = int(v1);
    return float( lhs - ( (lhs/rhs)*rhs ) );
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


$





void main() {

    

    TexCoord0 = gl_MultiTexCoord0.xyzw;
    //TexCoord1 = gl_MultiTexCoord1.xyz;
    
    //float newZoom = max(cameraZoom,1.0);
    float newZoom = min(cameraZoom,1.0);
    float newZoom2 = mix( max(cameraZoom,1.0), min(cameraZoom,1.0), float(cameraZoom >= 1.0) );

    vec2 newTC = ((TexCoord0.xy)*newZoom2+1.0)/2.0;
    vec3 worldPos = TexCoord0.xyz;
    worldPos.xy -= cameraPosSS.xy;
    vec4 myVert = gl_Vertex;

    vec4 tex0 = texture2D(Texture0, newTC );
    //vec4 tex1 = texture2D(Texture1, newTC );
    //tex1.rgb = (tex1.rgb-0.5)*2.0;
    vec4 tex2 = texture2D(Texture2,worldPos.xy);
    
    vec4 tex3 = texture2D(Texture3, newTC );

    baseHeight = unpack16(tex0.rg);

    

   

    vec2 randMod = tex2.xy;


    normMod = vec3(1.0,0.0,0.0);
    normMod.x = (sin(worldPos.x*8.0 + 1.0/300.0 + 1.0*322.0  + randMod.y*2.0));
    normMod.y = (randMod.x+1.0)*( (abs(  sin(  worldPos.x*32.0 + 1.0/800.0 + randMod.y*223.0 ) + randMod.x) + 1.0));
    normMod.z = 1.0;
    normMod = normalize(normMod);

    
    float isValid = float( (tex0.a == TEX_GRASS) );
    float aspectRatio = bufferDim.x/bufferDim.y;
    
    vec3 wn = normalize((tex2.rgb-0.5)*2.0);//vec3(0.0);//normalize((tex3.rgb-0.5)*2.0);//waveNormal(gl_MultiTexCoord0.x*1000.0, gl_MultiTexCoord0.y*1000.0)*4.0;

    float wind = (sin( curTime/800.0 + worldPos.x*8.0 + worldPos.y*6.0 + wn.x + wn.y ));

    wind += (
        sin( curTime/2000.0 + (worldPos.x + worldPos.y + wn.x + wn.y)*8.0 )*2.0 + 
        cos( curTime/1500.0 + (worldPos.x + worldPos.y + wn.x + wn.y)*4.0 )*1.0 + 
        sin( curTime/1000.0 + (worldPos.x + worldPos.y + wn.x + wn.y)*2.0 )*0.5 + 
        cos( curTime/500.0 + (worldPos.x + worldPos.y + wn.x + wn.y)*1.0 )*0.25 + 
        sin( curTime/250.0 + (worldPos.x + worldPos.y + wn.x + wn.y)*0.5 )*0.125
    )*0.1;


    vec2 windVec = sqrt( abs( vec2(wind,0.0) ) );

    vec2 grassVec = normMod.xy;
    grassVec.x *= -1.0;

    float windAmount = abs(dot(grassVec,windVec));

    vec2 resVec = normalize(mix(grassVec,windVec,windAmount));

    myVert.xy = gl_Vertex.xy * newZoom2;

    float gmod = tex3.g;//pow(tex3.r*tex3.g,2.0);//float(tex3.r>=1.0)*tex3.g;

    myVert.x += ((gl_MultiTexCoord0.w)*grassWH.x  + (resVec.x*2.0 - 0.25)*gl_MultiTexCoord0.z*grassWH.y*2.0*mix(newZoom,1.0,0.5) )*isValid*gmod;
    myVert.y += ((gl_MultiTexCoord0.z)*grassWH.y + gl_MultiTexCoord0.z*grassWH.y*newZoom)*isValid*aspectRatio*gmod;
    myVert.z = gl_MultiTexCoord0.z;
    normMod = normalize(normMod);


    //myVert.xy *= newZoom;
    resVert = myVert;
    gl_Position = myVert;

}

$



void main() {

    float newZoom = min(cameraZoom,1.0);
    float newZoom2 = mix( max(cameraZoom,1.0), min(cameraZoom,1.0), float(cameraZoom >= 1.0) );

    vec2 newTC = (TexCoord0.xy*newZoom2+1.0)/2.0;
    //vec4 tex2 = texture2D(Texture2, newTC );
    vec4 tex0 = texture2D(Texture0, newTC );
    vec4 tex1 = texture2D(Texture1, newTC );

    vec2 newCoords = gl_FragCoord.xy/bufferDim;
    vec4 tex3 = texture2D(Texture3, newCoords );


    float tot = tex0.r + tex0.g + tex0.b + tex0.a;

    if (tot == 0.0 || tex1.a == 0.0) {
        discard;
    }

    
    float newHeight = baseHeight + TexCoord0.z*grassWH.y + 50.0; // *50.0/newZoom + grassWH.y*512.0;// + TexCoord0.z*grassWH.y*bufferDim.y;

   

    vec3 curNorm = (tex1.rgb-0.5)*2.0;

    vec3 upVec = vec3(0.0,0.0,1.0);

    vec3 resNorm = mix(curNorm,normMod,0.5);//mix( , upVec, TexCoord0.z); //
    resNorm = normalize(resNorm);
    resNorm = (resNorm + 1.0)/2.0;


    vec2 packed = pack16(newHeight);

    gl_FragData[0] = vec4(packed.rg,(TexCoord0.z*127.0)/255.0,TEX_GRASS);
    gl_FragData[1] = vec4(resNorm.rgb, (TexCoord0.z+tex1.a)/2.0 );

}






