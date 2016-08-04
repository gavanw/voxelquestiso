#version 120

// old combine
uniform sampler2D Texture0;
uniform sampler2D Texture1;

// water combine
uniform sampler2D Texture2;
uniform sampler2D Texture3;

// rendered
uniform sampler2D Texture4;

// rendered blurred
uniform sampler2D Texture5;

// noise fbo
uniform sampler2D Texture6;

// wave fbo
uniform sampler2D Texture7;


uniform sampler2D Texture8; // solid
uniform sampler2D Texture9; // transparent
uniform sampler2D Texture10; // object
uniform sampler2D Texture11; // all


varying vec2 TexCoord0;

uniform float tiltAmount;
uniform float pixelsPerMeter;
uniform float timeOfDay;
uniform float seaLevel;
uniform float curTime;
uniform float cameraZoom;
uniform vec3 cameraPos;
uniform vec2 bufferDim;


const float TEX_WATER = 32.0/255.0;
const float TEX_GLASS = 35.0/255.0;
const float pi = 3.14159;

const int maxEntries = 5;
const int maxEntriesM1 = maxEntries-1;



// vec3 colVecs[4] = vec3[](
//     vec3( 1.0, 1.0, 1.0 ),
//     vec3( 1.0, 0.0, 1.0 ),
//     vec3( 0.0, 1.0, 1.0 ),
//     vec3( 0.0, 1.0, 1.0 )
// );

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;// = ;//TexCoord0 = gl_MultiTexCoord0;
    gl_Position = gl_Vertex;
}

$

vec3 randv(vec2 co) {
    return vec3(
        fract(sin(dot(co.xy ,vec2(12.989, 78.233))) * 43758.8563),
        fract(sin(dot(co.yx ,vec2(93.989, 67.345))) * 24634.6345),
        fract(sin(dot(co.yx ,vec2(43.332, 93.532))) * 56445.2345)
    );
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

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


void main() {
    float newZoom = min(cameraZoom,1.0);

    vec4 tex0 = texture2D(Texture0, TexCoord0.xy);
    vec4 tex1 = texture2D(Texture1, TexCoord0.xy);

    vec4 tex2 = texture2D(Texture2, TexCoord0.xy);
    vec4 tex3 = texture2D(Texture3, TexCoord0.xy);

    vec4 tex4 = texture2D(Texture4, TexCoord0.xy);
    vec4 tex5 = texture2D(Texture5, TexCoord0.xy);
    
    
    vec4 tex8 = texture2D(Texture10, TexCoord0.xy);
    //vec4 tex9 = texture2D(Texture9, TexCoord0.xy);
    //vec4 tex10 = texture2D(Texture10, TexCoord0.xy);
    //vec4 tex11 = texture2D(Texture11, TexCoord0.xy);
    

    float tot = float(tex0.r + tex0.g + tex0.b + tex0.a > 0.0);    
    vec4 oneVec = vec4(1.0);
    
    
    
    
    
    float baseHeight = tex8.z;
    //float baseHeightWater = tex9.z;
    vec3 worldPosition = tex8.xyz;
    //vec3 worldPositionWater = tex9.xyz;
    
    vec4 worldPositionRef = vec4(0.0);
    
    
    
    
    
    
    float tilt = tiltAmount;
    float itilt = 1.0-tiltAmount;
    float baseHeightWater = unpack16(tex2.rg);

    vec3 worldPositionWater = vec3(0.0,0.0,0.0);
    vec2 ssCoord = vec2(0.0);
    
    ssCoord = vec2(TexCoord0.x,1.0-TexCoord0.y)*2.0-1.0;
    ssCoord.x *= bufferDim.x/(newZoom);
    ssCoord.y *= bufferDim.y/(newZoom);
    ssCoord.y -= cameraPos.z*tilt*2.0;
    ssCoord.y += baseHeightWater*tilt*2.0;

    worldPositionWater.x = (ssCoord.y*0.5/itilt + ssCoord.x*0.5);
    worldPositionWater.y = (ssCoord.y*0.5/itilt - ssCoord.x*0.5);
    worldPositionWater.z = baseHeightWater;
    worldPositionWater.x += cameraPos.x;
    worldPositionWater.y += cameraPos.y;
    
    
    
    

    float distances[maxEntries];

    distances[0] = 0.0*pixelsPerMeter;
    distances[1] = 0.5*pixelsPerMeter;
    distances[2] = 4.0*pixelsPerMeter;
    distances[3] = 8.0*pixelsPerMeter;
    distances[4] = 16.0*pixelsPerMeter;

    vec3 colVecs[maxEntries];

    colVecs[0] = vec3(0.9,0.9,1.0);
    colVecs[1] = vec3(0.3,1.0,1.0);
    colVecs[2] = vec3(0.1,0.4,0.8);
    colVecs[3] = vec3(0.0,0.1,0.5);
    colVecs[4] = vec3(0.0,0.0,0.2);

    float maxDis = distances[maxEntriesM1];

    float heightDif = 0.0;
    float heightDifNoRef = 0.0;

    vec3 waterNorm = -normalize((tex3.rgb-0.5)*2.0);

    //vec2 newTC2 = vec2(0.0);
    vec2 newTC = vec2(0.0);
    vec2 resTC = vec2(0.0);


    vec4 tex0Ref = vec4(0.0);
    vec4 tex1Ref = vec4(0.0);

    vec4 tex2Ref = vec4(0.0);
    vec4 tex3Ref = vec4(0.0);

    vec4 tex4Ref = vec4(0.0);
    vec4 tex5Ref = vec4(0.0);

    //vec4 tex5Ref2 = vec4(0.0);

    vec4 tex7Ref = vec4(0.0);
    vec4 tex7Ref2 = vec4(0.0);
    vec4 tex7Ref3 = vec4(0.0);

    float baseHeightRef = 0.0;

    int i;

    float curLerp = 0.0;
    float lval;

    float lerpVal;
    float lerpValNorm = 0.0;
    float curSeaLev = seaLevel;

    float totRef;

    float facingEye = clamp(dot(oneVec.xyz,-waterNorm.xyz),0.0,1.0);

    vec3 finalCol = vec3(0.0);

    vec3 lastCol = vec3(0.0);
    
    vec3 refMod = vec3(0.0);
    

    if (tex2.a == TEX_WATER) {


        heightDifNoRef = clamp((baseHeightWater - baseHeight), 0.0, maxDis);
        newTC.xy = TexCoord0.xy + (waterNorm.xy-waterNorm.z)*tex3.a*32.0/(bufferDim/newZoom)*heightDifNoRef/maxDis;

        //newTC2.xy = TexCoord0.xy - (waterNorm.xy-waterNorm.z)*tex3.a*32.0/(bufferDim/newZoom)*heightDifNoRef/maxDis;
        //tex5Ref2 = texture2D(Texture5, newTC2.xy);


        tex0Ref = texture2D(Texture0, newTC.xy);
        
        tex1Ref = texture2D(Texture1, newTC.xy);

        tex5Ref = texture2D(Texture5, newTC.xy);
        
        worldPositionRef = texture2D(Texture10, newTC.xy);
        baseHeightRef = worldPositionRef.z;//unpack16(tex0Ref.rg);

        totRef = float(dot(tex0Ref, oneVec) > 0.0);

        if (totRef == 0.0) {
            baseHeightRef = baseHeightWater-1.0*pixelsPerMeter;
        }

        heightDif = clamp(abs(baseHeightWater - baseHeightRef), 0.0, maxDis);

        lval = dot(oneVec.rgb, tex5Ref.rgb)/3.0;


        refMod = normalize((tex1Ref.xyz-0.5)*2.0)/2.0;
        refMod.xy += refMod.z;
        //refMod *= 0.5;

        tex7Ref = texture2D(Texture7, newTC.xy);
        tex7Ref2 = texture2D(Texture7, newTC.xy + refMod.xy + tex7Ref.xy - (baseHeightWater - baseHeightRef)/bufferDim.xy );
        tex7Ref3 = texture2D(Texture7, newTC.xy + refMod.xy + 1.0 - (tex7Ref.xy - (baseHeightWater - baseHeightRef)/bufferDim.xy) );


        // bigger == deeper under water

        

        if (tex3.a == 0.0 ) {
            heightDif = max(heightDif,distances[1]+1.0);
        }

        for (i = 0; i < maxEntriesM1; i++) {

            if (
                (heightDif >= distances[i]) &&
                (heightDif <= distances[i+1]) 
            ) {

                

                lerpVal = clamp( (heightDif - distances[i])/(distances[i+1]-distances[i]), 0.0, 1.0);
                lerpValNorm = heightDif/maxDis;
                
                lastCol = mix(colVecs[i], colVecs[i+1], lerpVal);
                finalCol = lastCol*lval;
                
                

                

            }
        }

        if (tex3.a == 0.0 ) {

            resTC = TexCoord0.xy;

            if ( abs(waterNorm.z) > 0.5) {
                
            }
            else {
                
                // rays

                // finalCol += sin(
                //     (worldPositionWater.x + worldPositionWater.y + worldPositionWater.z/2.0)/(100.0) + curTime/500.0
                // )*vec3(0.2,0.2,0.4);
                // * pow(1.0-clamp((curSeaLev-worldPositionWater.z)/2000.0,0.0,1.0),5.0 )*mix(0.5,1.0,timeOfDay);

            }

            // caustics


            if (cameraZoom >= 1.0) {
                finalCol += pow(
                (
                    //pow(abs(sin(tex7Ref.a*10.0)),4.0) +
                    pow( ( (tex7Ref2.a ) ), 2.0 ) +
                    pow( ( (tex7Ref3.a ) ), 2.0 ) 
                ) *
                clamp( 1.0 - ((baseHeightWater - baseHeightRef)/512.0),0.0,1.0 )*
                totRef
                ,2.0)*vec3(0.2,0.2,0.4)*mix(0.2,1.0,timeOfDay)*lval;
            }
            


            // bubbles

            finalCol += 
            pow(
                texture2D(Texture6, resTC*vec2(1.0,1.0)-vec2(0.0,(curTime/20000.0))  ).rgb*0.85,
                vec3(10.0)
            ) * 
            abs(sin(rand(TexCoord0.xy)*1000.0 + curTime/200.0))*(1.0-lerpValNorm)*mix(0.75,1.0,timeOfDay);



        }
        else {
            resTC = newTC.xy;
            if (
                (heightDifNoRef >= distances[0]) &&
                (heightDifNoRef <= distances[1]) 
            ) {
                // shore foam

                //finalCol = vec3(1.0);
                
                lerpVal = clamp( (heightDifNoRef - distances[0])/(distances[1]-distances[0]), 0.0, 1.0);
                finalCol += 4.0*finalCol*(rand(TexCoord0.xy*curTime/10000.0)*0.15+0.25)*(1.0-lerpVal)*4.0*mix(0.5,1.0,timeOfDay);
            
            }



            finalCol = mix(
                finalCol,
                finalCol*vec3(0.4,0.5,0.6) + tex4.rgb,
                facingEye*0.3
            ) + tex4.rgb*vec3(0.1,0.2,0.4);


            // highlights

            finalCol += 
            pow(
                clamp(dot(
                    -waterNorm,
                    vec3(0.0,0.0,1.0)
                ),0.0,1.0),
                6.0
            )*vec3(0.5,0.45,1.0)*0.5*timeOfDay;

            
            finalCol *= 0.5;
            finalCol += tex5Ref.rgb*0.25;


        }
        
        //finalCol = mix(finalCol, tex4.rgb, 0.25);

        //finalCol = mix(finalCol*tex5Ref.rgb,finalCol,0.5);

        //finalCol = mix(finalCol, finalCol+tex5Ref2.rgb*0.3, facingEye);
        

        gl_FragData[0] = vec4(
            
            finalCol + lastCol*mix(vec3(0.05,0.1,0.2),vec3(0.5),timeOfDay) + 
            
            mix(
             vec3(0.0),
             tex4.rgb-vec3(0.2),
             float(tex3.a == 0.0)
            ),
            1.0
        );
    }
    else {

        if (tex2.a == TEX_GLASS) {
            gl_FragData[0] = tex4*0.5 + tex5*1.2;
        }
        else {
            gl_FragData[0] = tex4;
        }


        
    }
    
    //gl_FragData[0] = tex4;
    
    //float gridAmount = 512.0;
    //gl_FragData[0].rgb = (worldPositionWater.xyz-floor(worldPositionWater.xyz/gridAmount)*gridAmount)/gridAmount;
    
    //gl_FragData[0] = tex4;


    
}
