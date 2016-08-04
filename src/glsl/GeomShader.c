//uniform sampler3D Texture0; //volume texture
//uniform sampler2D Texture0;
//uniform sampler2D Texture1;

//uniform sampler2D Texture0;
//uniform sampler3D Texture1;
//varying vec4 TexCoord0;
//varying vec3 TexCoord1;

//uniform float curHeight;
//uniform vec3 worldMin;
//uniform vec3 worldMax;

varying vec3 TexCoord0;

uniform float objectId;
uniform float curTime;
uniform float cameraZoom;
uniform vec3 cameraPos;
uniform vec2 bufferDim;

uniform float isWire;
uniform float matVal;
uniform float tiltAmount;

varying vec3 finalVec;

$

/*
void main() {

    TexCoord0 = gl_MultiTexCoord0.xyz;

    vec3 myVert = gl_Vertex.xyz - cameraPos.xyz;
    vec3 transVert;

    transVert.x = (myVert.x-myVert.y);
    transVert.y = (-(myVert.x/2.0) + -(myVert.y/2.0) + myVert.z);
    transVert.z = myVert.z;

    
    float newZoom = min(cameraZoom,1.0);
    
    finalVec.x = (transVert.x)*newZoom/(bufferDim.x);
    finalVec.y = (transVert.y)*newZoom/(bufferDim.y);
    finalVec.z = gl_Vertex.z;

    gl_Position = vec4(finalVec.xy, clamp( (1.0-finalVec.z/(256.0*255.0)) ,0.0,1.0),gl_Vertex.w);

}
*/

vec3 worldToScreen(vec3 worldCoords, float zVal, bool forceZ) {
    vec3 resVec;
    vec3 transVert;
    float newZoom = min(cameraZoom,1.0);
    float tilt = tiltAmount;
    float itilt = 1.0-tiltAmount;
    
    transVert.x = (worldCoords.x-worldCoords.y);
    transVert.y = (-(worldCoords.x*itilt) + -(worldCoords.y*itilt) + worldCoords.z*tilt*2.0);
    transVert.z = worldCoords.z;
    
    resVec.x = (transVert.x)*newZoom/(bufferDim.x);
    resVec.y = (transVert.y)*newZoom/(bufferDim.y);
    resVec.z = worldCoords.z;
    
    
    if (forceZ) {
        resVec.z = zVal;
    }
    
    return resVec;
}


void main() {

    TexCoord0 = gl_MultiTexCoord0.xyz;
    finalVec = worldToScreen(gl_Vertex.xyz-cameraPos.xyz, gl_Vertex.z, true);
    gl_Position = vec4(finalVec.xy, clamp( (1.0-finalVec.z/(256.0*255.0)) ,0.0,1.0),gl_Vertex.w);

}

$

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

void main() {

    vec2 heightPacked = pack16(finalVec.z);
    vec2 matPacked = pack16(matVal);

    
    float rad = 0.98;

    if (isWire == 0.0) {

    }
    else {

        if (
            ( (abs(TexCoord0.x) < rad) && (abs(TexCoord0.y) < rad) ) ||
            ( (abs(TexCoord0.y) < rad) && (abs(TexCoord0.z) < rad) ) ||
            ( (abs(TexCoord0.x) < rad) && (abs(TexCoord0.z) < rad) )
        ) {
            discard;
        }
    }

    gl_FragData[0] = vec4(heightPacked.rg,matPacked.rg);//vec4(bhr,bhg,3.0/255.0,tex0.a);
    gl_FragData[1] = vec4(pack16(objectId),0.0,1.0);//vec4(resNorm.rgb, (TexCoord0.z+tex1.a)/2.0 ); //(TexCoord0.xyz+1.0)/2.0

}
