
var gob = {};

gob.genPicker = function() {
    var canvas = document.getElementById('canvas2');
    var canvasWidth  = canvas.width;
    var canvasHeight = canvas.height;
    var ctx = canvas.getContext('2d');
    var imageData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);
    var buf = new ArrayBuffer(imageData.data.length);
    var buf8 = new Uint8ClampedArray(buf);
    var data = new Uint32Array(buf);
    var value;
    var o;
    var n;
    var m;
    var q;
    var myArr = [0,0,0];
    var lerpVal;

    var xv;
    var yv;

    var qmodH = [0,1,1];
    var qmodC = [2,0,2];
    var qmodL = [1,2,0];

    var cl = new CIELCh(0,0,0);

    for (n = 0; n < 512; n++) {
        for (m = 0; m < 1024; m++) {

            data[(n) * canvasWidth + m] =
                (255   << 24) |
                ((m/4) << 16) |
                ((m/4) <<  8) |
                 (m/4);
        }
    }


    for (q = 0; q < 3; q++) {

        for (o = 0; o < 32; o++) {
            myArr[0] = o;
            for (n = 0; n < 32; n++) {
                myArr[1] = n;
                for (m = 0; m < 32; m++) {
                    myArr[2] = m;


                    if (q < 3) {
                        cl.h = myArr[ qmodH[q] ]*360.0/32.0;
                        cl.c = myArr[ qmodC[q] ]*100.0/31.0;
                        cl.l = myArr[ qmodL[q] ]*100.0/31.0;
                    }

                    value = cl.toRGB();

                    xv = (o)*32+n;
                    yv = m;

                    data[(yv+q*32) * canvasWidth + xv] =
                        (255   << 24) |
                        (value.r << 16) |
                        (value.g <<  8) |
                         value.b;

                }
            }
        }
    }

    

    imageData.data.set(buf8);
    ctx.putImageData(imageData, 0, 0);
}

gob.genPicker();