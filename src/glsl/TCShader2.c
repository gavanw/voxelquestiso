varying vec3 TexCoord0;


uniform float fHolderMod;
uniform float tiltAmount;
uniform float cameraZoom;
uniform vec2 bufferDim;
uniform vec3 cameraPos;

varying vec3 finalVec;

$


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
    
    resVec.xy /= fHolderMod;
    
    if (forceZ) {
        resVec.z = zVal;
    }
    
    return resVec;
}


void main() {

    TexCoord0 = gl_MultiTexCoord0.xyz;
    finalVec = worldToScreen(gl_Vertex.xyz-cameraPos.xyz, gl_Vertex.z, true);
    gl_Position = vec4(finalVec.xy, 0.5 ,gl_Vertex.w);

}

$

void main() {
    gl_FragData[0] = vec4((TexCoord0+1.0)/2.0, 1.0);

}
