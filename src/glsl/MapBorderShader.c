#version 120

uniform sampler2D Texture0; // heightmap
varying vec2 TexCoord0;

uniform float mapStep;
uniform float texPitch;
uniform float seaLevel;

$

void main() {

    TexCoord0 = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
}

$

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {

    vec4 tex1 = texture2D(Texture0, TexCoord0.xy);
    //vec4 tex0 = texture2D( Texture0, vec2(tex1.r, (5.0 + 0.5)/255.0 ) );


    //int iNumProv = int(numProvinces);
    int i;

    float closestDis = 9999.0;
    float testDis = 0.0;

    int bestIndex = 0;

    vec2 dir;

    float angle;

    vec4 tex1u = vec4(0.0);
    vec4 tex1d = vec4(0.0);
    vec4 tex1l = vec4(0.0);
    vec4 tex1r = vec4(0.0);

    vec4 tex1ul = vec4(0.0);
    vec4 tex1ur = vec4(0.0);
    vec4 tex1dl = vec4(0.0);
    vec4 tex1dr = vec4(0.0);

    float isGreen;

    //float res = tex1.g;

    float offsetAmount = 1.0/texPitch;
    float testHeight = 0.0;
    float heightMod = 0.0;
    float tot = 0.0;
    float isAboveSea = 0.0;
    float rand1 = 0.0;
    float rand2 = 0.0;
    float maxVal = 0.0;
    float tval;

    if (tex1.g == 0.0) {

        tex1u = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y + offsetAmount) );
        tex1d = texture2D(Texture0, vec2(TexCoord0.x, TexCoord0.y - offsetAmount) );
        tex1l = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y) );
        tex1r = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y) );

        
        tex1ul = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y + offsetAmount) );
        tex1ur = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y + offsetAmount) );
        tex1dl = texture2D(Texture0, vec2(TexCoord0.x - offsetAmount, TexCoord0.y - offsetAmount) );
        tex1dr = texture2D(Texture0, vec2(TexCoord0.x + offsetAmount, TexCoord0.y - offsetAmount) );
        
    
        if (tex1u.g > 0.0) {
            testHeight = tex1u.r;
            tot+=1.0;
        }
        if (tex1d.g > 0.0) {
            testHeight = tex1d.r;
            tot+=1.0;
        }
        if (tex1l.g > 0.0) {
            testHeight = tex1l.r;
            tot+=1.0;
        }
        if (tex1r.g > 0.0) {
            testHeight = tex1r.r;
            tot+=1.0;
        }

        
        if (tex1ul.g > 0.0) {
            tot+=1.0;
        }
        if (tex1ur.g > 0.0) {
            tot+=1.0;
        }
        if (tex1dl.g > 0.0) {
            tot+=1.0;
        }
        if (tex1dr.g > 0.0) {
            tot+=1.0;
        }
        


        isGreen = float(tex1u.g + tex1d.g + tex1l.g + tex1r.g > 0.0);
        isAboveSea = float(tex1.r > seaLevel);
        heightMod = clamp( ( testHeight + -tex1.r )*50.0, -1.0, 1.0)/2.0;
        rand1 = rand(TexCoord0.xy + sin(mapStep/1000.0));
        rand2 = clamp(rand(1.0-TexCoord0.xy + rand1)/2.0,0.0,0.5);

        if (mapStep < 0.0) {
            maxVal = 0.0;
            rand2 *= 0.25;
            tval = 255.0;
        }
        else {
            maxVal = mix(1.0,0.3, abs(mapStep-512.0)/512.0);
            tval = mapStep/256.0;
        }
        

        if ( ((rand1 + heightMod)*isGreen*isAboveSea > maxVal+rand2 ) || (tot*isGreen*isAboveSea > 4.0)) { //  || (tot > 4.0)
            if (tex1u.g > 0.0) {
                tex1.g = tex1u.g;
            }
            if (tex1d.g > 0.0) {
                tex1.g = tex1d.g;
            }
            if (tex1l.g > 0.0) {
                tex1.g = tex1l.g;
            }
            if (tex1r.g > 0.0) {
                tex1.g = tex1r.g;
            }

            tex1.b = tval;
        }

        if (tex1.g == 1.0) {
            tex1.b = 1.0;
        }

        if (isAboveSea == 0.0) {
            tex1.b = 1.0;
        }

        





    }

    




/*


    vec v[9];

    // Add the pixels which make up our window to the pixel array.
    for(int dX = -1; dX <= 1; ++dX) {
        for(int dY = -1; dY <= 1; ++dY) {       
          vec2 offset = vec2(float(dX), float(dY));
                
          // If a pixel in the window is located at (x+dX, y+dY), put it at index (dX + R)(2R + 1) + (dY + R) of the
          // pixel array. This will fill the pixel array, with the top left pixel of the window at pixel[0] and the
          // bottom right pixel of the window at pixel[N-1].
          v[(dX + 1) * 3 + (dY + 1)] = toVec(texture2D(Texture0, gl_TexCoord[0].xy + offset * offsetAmount));
        }
    }
    v[(0 + 1) * 3 + (0 + 1)] = tex1.g;

    vec temp;

    // Starting with a subset of size 6, remove the min and max each time
    mnmx6(v[0], v[1], v[2], v[3], v[4], v[5]);
    mnmx5(v[1], v[2], v[3], v[4], v[6]);
    mnmx4(v[2], v[3], v[4], v[7]);
    mnmx3(v[3], v[4], v[8]);
    vec medianResult = v[4];



    if (medianResult == 0.0) {

    }
    else {
        tex1.g = medianResult;
    }

    

*/








    gl_FragData[0] = tex1;

    /*
    for (i = 0; i < iNumProv; i++) {


        dir = normalize(TexCoord0.xy-paramArrMap[i].xy);

        angle = atan(dir.y,dir.x);

        testDis = distance(TexCoord0.xy,paramArrMap[i].xy)*(1.0+sin(angle*8.0)/10.0 +sin(angle*16.0)/20.0);

        if (testDis < closestDis) {
            bestIndex = i;
            closestDis = testDis;
        }

    }


    float mod = float(bestIndex)/64.0;

*/


    /*
    vec4 res = tex1;

    if (tex1.r < 0.5) {
        res.r *= 0.0;
        res.g *= 0.5;
        res.b *= 1.0;
    }
    else {

        if (tex1.r < 0.52) {
            res.r *= 1.0;
            res.g *= 0.8;
            res.b *= 0.7;
            res.rgb += 0.1;
        }
        else {
            res.r *= 0.1;
            res.g *= 0.5;
            res.b *= 0.1;
        }

        
    }
    */


    //gl_FragData[0] = tex1;//tex0*mod;//vec4(mod);//
}




/*

// Input texture
uniform sampler2D T;
uniform vec2 Tinvsize;

// Change these 2 defines to change precision,
#define vec float
#define toVec(x) x.g

//#define vec vec4
//#define toVec(x) x.rgba

#define s2(a, b)                temp = a; a = min(a, b); b = max(temp, b);
#define mn3(a, b, c)            s2(a, b); s2(a, c);
#define mx3(a, b, c)            s2(b, c); s2(a, c);

#define mnmx3(a, b, c)          mx3(a, b, c); s2(a, b);                                   // 3 exchanges
#define mnmx4(a, b, c, d)       s2(a, b); s2(c, d); s2(a, c); s2(b, d);                   // 4 exchanges
#define mnmx5(a, b, c, d, e)    s2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e);           // 6 exchanges
#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); mn3(a, b, c); mx3(d, e, f); // 7 exchanges

void main() {

  vec v[9];

  // Add the pixels which make up our window to the pixel array.
  for(int dX = -1; dX <= 1; ++dX) {
    for(int dY = -1; dY <= 1; ++dY) {       
      vec2 offset = vec2(float(dX), float(dY));
            
      // If a pixel in the window is located at (x+dX, y+dY), put it at index (dX + R)(2R + 1) + (dY + R) of the
      // pixel array. This will fill the pixel array, with the top left pixel of the window at pixel[0] and the
      // bottom right pixel of the window at pixel[N-1].
      v[(dX + 1) * 3 + (dY + 1)] = toVec(texture2D(Texture0, gl_TexCoord[0].xy + offset * Tinvsize));
    }
  }

  vec temp;

  // Starting with a subset of size 6, remove the min and max each time
  mnmx6(v[0], v[1], v[2], v[3], v[4], v[5]);
  mnmx5(v[1], v[2], v[3], v[4], v[6]);
  mnmx4(v[2], v[3], v[4], v[7]);
  mnmx3(v[3], v[4], v[8]);
  vec medianResult = v[4];

}

*/