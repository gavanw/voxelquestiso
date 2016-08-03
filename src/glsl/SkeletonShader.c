#version 120

uniform sampler2D Texture0; //cityFBO
//uniform sampler2D Texture1; //hmFBO
varying vec2 TexCoord0;
uniform float mapStep;
uniform float texPitch;
uniform float seaLevel;
//uniform vec2 offVec;

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

    int i;
    int j;

    float fi;
    float fj;

    vec4 tex1 = texture2D(Texture0, TexCoord0.xy);
    //vec4 tex2 = texture2D(Texture1, TexCoord0.xy);

    float offsetAmount = 1.0/texPitch;
    float tp2 = texPitch/2.0;

    vec2 newTex = TexCoord0.xy;

    

    float DVAL = 999999.0;
    float minDis = DVAL;
    float maxDis = 0.0;
    float res;
    float res2;
    float testDis;
    
    vec2 baseCoord = TexCoord0.xy;
    vec2 testCoord = vec2(0.0);
    vec2 offsetCoord = vec2(0.0);

    vec2 origin = vec2(0.0);

    float tot = 0.0;
    float totHit = 0.0;

    float bestRes = 1.0;

    int maxR = 32;

   // bool isAbove = tex2.r > seaLevel;

    if (tex1.b == 1.0) {


        for (i = -maxR; i <= maxR; i++) {
            fi = float(i);
            for (j = -maxR; j <= maxR; j++) {
                fj = float(j);

                offsetCoord = vec2(fi,fj)*offsetAmount;//*4.0;
                testCoord = baseCoord + offsetCoord;

                res = texture2D(Texture0, testCoord ).b;
                //res2 = texture2D(Texture1, testCoord ).r;

                if (res != 1.0) {

                    //if ((res2 > seaLevel) == isAbove) {
                        testDis = length(offsetCoord);//,origin);

                        if (testDis < minDis) {
                            minDis = testDis;
                            tex1.b = res;

                        }
                    //}

                    

                    
                }

                tot += 1.0;


            }
        }
        

    }

    




    // if (minDis == DVAL) {

    // }
    // else {
    //     tex1.b = minDis*12.0*(2.0-totHit/tot);

    // }
    

/*
    if (abs(minDis-maxDis) > 2.0) {
        tex1.b = 0.0;
    }
*/



    // int no = 1-int(texture2D(Texture0, vec2(newTex.x, newTex.y + offsetAmount) ).b);
    // int so = 1-int(texture2D(Texture0, vec2(newTex.x, newTex.y - offsetAmount) ).b);
    // int we = 1-int(texture2D(Texture0, vec2(newTex.x - offsetAmount, newTex.y) ).b);
    // int ea = 1-int(texture2D(Texture0, vec2(newTex.x + offsetAmount, newTex.y) ).b);

    // int nw = 1-int(texture2D(Texture0, vec2(newTex.x - offsetAmount, newTex.y + offsetAmount) ).b);
    // int ne = 1-int(texture2D(Texture0, vec2(newTex.x + offsetAmount, newTex.y + offsetAmount) ).b);
    // int sw = 1-int(texture2D(Texture0, vec2(newTex.x - offsetAmount, newTex.y - offsetAmount) ).b);
    // int se = 1-int(texture2D(Texture0, vec2(newTex.x + offsetAmount, newTex.y - offsetAmount) ).b);
    

    
    // int A  = int(no == 0 && ne == 1) + int(ne == 0 && ea == 1) + 
    //          int(ea == 0 && se == 1) + int(se == 0 && so == 1) + 
    //          int(so == 0 && sw == 1) + int(sw == 0 && we == 1) +
    //          int(we == 0 && nw == 1) + int(nw == 0 && no == 1);
    // int B  = no + ne + ea + se + so + sw + we + nw;
    // int m1 = mapStep == 0.0 ? (no * ea * so) : (no * ea * we);
    // int m2 = mapStep == 0.0 ? (ea * so * we) : (no * so * we);

    // bool proc = true;

    // if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0) {


    //     // if ( (nw+no+ne+we+ea == 5) ) { // && (sw + so + se == 0)
    //     //     proc = false;
    //     // }

    //     // if ( (no+ne+ea+se+so == 5) ) { // && (nw + we + sw == 0)
    //     //     proc = false;
    //     // }

    //     // if (proc) {
    //     //     tex1.b = 0.0;
    //     // }
        
    //     tex1.b = 0.0;        

    // }
    

                // int p2 = we;//im.at<uchar>(i-1, j);
                // int p3 = sw;//im.at<uchar>(i-1, j+1);
                // int p4 = so;//im.at<uchar>(i, j+1);
                // int p5 = se;//im.at<uchar>(i+1, j+1);
                // int p6 = ea;//im.at<uchar>(i+1, j);
                // int p7 = ne;//im.at<uchar>(i+1, j-1);
                // int p8 = no;//im.at<uchar>(i, j-1);
                // int p9 = nw;//im.at<uchar>(i-1, j-1);

                // int A  = int(p2 == 0 && p3 == 1) + int(p3 == 0 && p4 == 1) + 
                //          int(p4 == 0 && p5 == 1) + int(p5 == 0 && p6 == 1) + 
                //          int(p6 == 0 && p7 == 1) + int(p7 == 0 && p8 == 1) +
                //          int(p8 == 0 && p9 == 1) + int(p9 == 0 && p2 == 1);
                // int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                // int m1 = mapStep == 0.0 ? int(p2 * p4 * p6) : int(p2 * p4 * p8);
                // int m2 = mapStep == 0.0 ? int(p4 * p6 * p8) : int(p2 * p6 * p8);

                // if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0) {
                //     tex1.b = 0.0;
                // }










                // bool p2 = bool(we);//im.at<uchar>(i-1, j);     //we
                // bool p3 = bool(sw);//im.at<uchar>(i-1, j+1);   //nw
                // bool p4 = bool(so);//im.at<uchar>(i, j+1);     //no
                // bool p5 = bool(se);//im.at<uchar>(i+1, j+1);   //ne
                // bool p6 = bool(ea);//im.at<uchar>(i+1, j);     //ea
                // bool p7 = bool(ne);//im.at<uchar>(i+1, j-1);   //se
                // bool p8 = bool(no);//im.at<uchar>(i, j-1);     //so
                // bool p9 = bool(nw);//im.at<uchar>(i-1, j-1);   //sw

                // int C  =
                //     int( (!p2) && (p3 || p4)) +
                //     int( (!p4) && (p5 || p6)) +
                //     int( (!p6) && (p7 || p8)) +
                //     int( (!p8) && (p9 || p2));

                // int N1 =
                //     int(p9 || p2) +
                //     int(p3 || p4) +
                //     int(p5 || p6) +
                //     int(p7 || p8);

                // int N2 =
                //     int(p2 || p3) +
                //     int(p4 || p5) +
                //     int(p6 || p7) +
                //     int(p8 || p9);
                
                // int N = N1 < N2 ? N1 : N2;
                // int m = mapStep == 0.0 ? int((p6 || p7 || (!p9) ) && p8) : int((p2 || p3 || (!p5) ) && p4);

                // if ( C == 1 && (N >= 2 && N <= 3) && (m == 0) ) {
                //     tex1.b = 0.0;
                // }







    // float v1 = 0.0;
    // float v2 = 0.0;
    // float v3 = 0.0;

    // if (doDilate == 1.0) {
    //     v1 = max( max(tex1u.b,tex1d.b), max(tex1l.b,tex1r.b) );
    //     v2 = max( max(tex1ul.b,tex1dl.b), max(tex1ur.b,tex1dr.b) );
    //     tex1.b = max( max(v1,v2), tex1.b);
    //     //tex1.b = max( v1, tex1.b);
    // }
    // else {

    //     v3 = tex1u.b + tex1d.b + tex1l.b + tex1r.b + tex1ur.b + tex1ul.b + tex1dr.b + tex1dl.b;

    //     // if (v1 >= 3.0) {
    //     //     tex1.b = 0.0;
    //     // }
    //     // else {
    //     //     tex1.b = 1.0;
    //     // }

    //     if ( (tex1.b > 0.0) && (v3 <= 4.0) ) {

    //     }
    //     else {
            
    //     }

    //     v1 = min( min(tex1u.b,tex1d.b), min(tex1l.b,tex1r.b) );
    //     v2 = min( min(tex1ul.b,tex1dl.b), min(tex1ur.b,tex1dr.b) );
    //     tex1.b = min( min(v1,v2), tex1.b);
    //     //tex1.b = min( v1, tex1.b);

        
    // }
    


    gl_FragData[0] = tex1;
}


