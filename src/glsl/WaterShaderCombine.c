#version 120

// old combine
uniform sampler2D Texture0;
uniform sampler2D Texture1;

// water
uniform sampler2D Texture2;
uniform sampler2D Texture3;

// water height
uniform sampler2D Texture4;



uniform sampler2D Texture5; // solid
uniform sampler2D Texture6; // transparent
uniform sampler2D Texture7; // object
uniform sampler2D Texture8; // all


varying vec2 TexCoord0;

uniform float pixelsPerMeter;
uniform float seaLevel;
uniform float curTime;
uniform float cameraZoom;
uniform vec3 cameraPos;
uniform vec2 bufferDim;


const float TEX_WATER = 32.0/255.0;
const float TEX_GLASS = 35.0/255.0;
const float pi = 3.14159;


$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
    gl_Position = gl_Vertex;
}

$



int intMod(int lhs, int rhs) {
    return lhs - ( (lhs/rhs)*rhs );
}
float unpack16(vec2 num) {
    return num.r*255.0 + num.g*65280.0;
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
bool isGeom(float aVal) {
    return aVal >= 0.5;
    // int test = int(unpack16(num));
    // return (test >= 32768);
}


void main() {

    vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
    vec4 tex1 = texture2D(Texture1, TexCoord0.xy);

    bool isGeometry = isGeom(tex0.a);
    bool outOfWater = true;

    vec4 tex2 = texture2D(Texture2, TexCoord0.xy);
    vec4 tex3 = texture2D(Texture3, TexCoord0.xy);
    vec4 tex3Orig = tex3;

    vec4 tex4 = texture2D(Texture4, TexCoord0.xy);
    
    
    vec4 tex5 = texture2D(Texture5, TexCoord0.xy);
    vec4 tex6 = texture2D(Texture6, TexCoord0.xy);
    vec4 tex7 = texture2D(Texture7, TexCoord0.xy);
    //vec4 tex8 = texture2D(Texture8, TexCoord0.xy);
    
    
    
    

    float newZoom = min(cameraZoom,1.0);    
    float tot = float(tex0.r + tex0.g + tex0.b + tex0.a > 0.0);    
    
    vec4 oneVec = vec4(1.0);
    
    
    float maxWaveHeight = @maxWaveH@*pixelsPerMeter*4.0;

    float seaLev = seaLevel;//+maxWaveHeight;
    
    
    float baseHeightSolid = tex5.z;
    float baseHeightWater = tex6.z;
    vec3 worldPosition = tex5.xyz;
    vec3 worldPositionWater = tex6.xyz;
    
    

    int i;
    float fi;
    const int numSteps = 64;
    const float fNumSteps = float(numSteps);
    float flerp = 0.0;

    

    float curHeight = 0.0;

    
    float curWaterHeight = 0.0;
    float waveDif = 0.0;

    vec2 newTC = vec2(0.0);
    vec4 samp = vec4(0.0);

    bool hitWater = false;
    bool hitLand = false;


    vec2 newTC2 = vec2(0.0);
    vec4 samp2 = vec4(0.0);
    vec4 samp3 = vec4(0.0);
    bool isTopOfWater = false;


    int i2;
    float fi2 = 0.0;
    const int numSteps2 = 64;
    const float fNumSteps2 = float(numSteps2);
    float flerp2 = 0.0;


    bool hitAir = false;
    bool hitWaterSide = false;

    bool hitSideWater = (tex3Orig.a == 0.0)&&(dot(tex3Orig.rgb,oneVec.rgb) != 0.0)&&(baseHeightWater>=baseHeightSolid);

    float endRes = 0.0;

    float yOff = 0.0;
    
    if (tex3Orig.a == 0.0) {
        yOff = (seaLev-baseHeightWater)*0.5;
    }

    if (tex2.a == TEX_WATER) {
        for (i = 0; i < numSteps; i++) {
            fi = float(i);
            flerp = fi/fNumSteps;
            newTC = TexCoord0.xy + vec2(yOff,fi+yOff)/(bufferDim/newZoom);
            samp = texture2D(Texture4, newTC);

            waveDif = samp.a;//pow( (samp.a-0.2,0.0,1.0),10.0);

            curHeight = baseHeightWater-flerp*maxWaveHeight;//mix(tallestHeight, lowestHeight, flerp);
            curWaterHeight = seaLev-waveDif*maxWaveHeight;


            if ( (baseHeightSolid > curHeight) ) { //&&(!hitSideWater)
                hitLand = true;
                break;
            }
            if ( curWaterHeight > curHeight ) {
                hitWater = true;
                break;
            }

        }
        
        if (hitLand||hitWater) {

        }
        else {
            hitWater = true;
        }

        for (i2 = 0; i2 < numSteps2; i2++) {
            fi2 = float(i2);
            flerp2 = fi2/fNumSteps2;
            newTC2 = TexCoord0.xy + vec2(0.0,fi2)/(bufferDim/newZoom);
            samp2 = texture2D(Texture2, newTC2);
            samp3 = texture2D(Texture3, newTC2);

            // if ((samp3.a == 0.0) && (tex3.a == 1.0)) {
            //     hitWaterSide = true;
            //     break;
            // }

            if (dot(oneVec,samp2) == 0.0) {
                hitAir = true;
                break;
            }

            

        }



        if ( (flerp2 < samp.a) && hitWater ) { //(tot == 0.0) &&   && (!hitWaterSide)
            isTopOfWater = true;
        }
        else {

        }

        if (hitLand || (!hitWater) || isTopOfWater ) {
            endRes = 0.0;
            
        }
        else {

            tex2.rg = pack16(curHeight);
            tex3.rgb = samp.rgb;

            if (tex3.a == 0.0) {
                if (i >= 2) {
                    tex3.a = 1.0;
                }
            }

            endRes = 1.0;

            outOfWater = false;

            if (tex3.a == 0.0) {
                gl_FragData[1].rgb = tex3Orig.rgb;
            }

            if (tex3Orig.b < 0.4) {
                gl_FragData[1].rgba = vec4(0.0);
            }

        }
    }
    else {
        if (baseHeightSolid > baseHeightWater) {
            endRes = 0.0;
        }
        else {
            endRes = 1.0;
            outOfWater = false;
        }
    }

    if (isGeometry) {
        if (outOfWater) {

        }
        else {
            //tex0.b = 0.0/255.0;
            //tex0.a = 140.0/255.0;
            
        }

        endRes = 0.0;
        
        
    }

    // if (
    //     (tex2.a == TEX_WATER) || 
    //     (tex2.a == TEX_GLASS)
    // ) {
    //     gl_FragData[0].rg = tex0.rg;
    // }


    
    
    // vec3 normWater = normalize( (tex3.rgb-0.5)*2.0 );
    // vec3 normSolid = vec3(0.0,0.0,-1.0);
    
    // TODO: use pixels per meter instead of constant
    //float waterDepth = clamp((worldPositionWater-worldPosition)/(128.0),0.0,1.0);


    if (tex7.z > tex5.z) {
        if (tex7.z < curHeight ) {
            //tex0.b = 0.0/255.0;
            //tex0.a = 140.0/255.0;
            endRes = 1.0;
        }
    }    

    if (endRes == 0.0) {
        
        // solid
        
        gl_FragData[0] = tex0;
        gl_FragData[1] = tex1;
    }
    else {
        
        // water
        
        gl_FragData[0] = tex2;
        gl_FragData[1] = tex3;
        
        // if (tex3.a == 0.0) {
        //     gl_FragData[1].rgb = vec3(0.0);
        // }
        
        //gl_FragData[1].rgb = (normalize( mix(normSolid, normWater, waterDepth) )+1.0)/2.0;
        
    }

    
    

    
}


