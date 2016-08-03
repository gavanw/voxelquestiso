/* Lets build upon Dean Edwards "Base" class, as it makes for good foundations for code like this */
/* http://dean.edwards.name/weblog/2006/03/base/*/
/* ColorJizz Library by mikeefranklin@gmail.com */

var Base = function () {
    if (arguments.length) {
        if (this == window) {
            Base.prototype.extend.call(arguments[0], arguments.callee.prototype);
        } else {
            this.extend(arguments[0]);
        }
    }
};
Base.version = "1.0.2";
Base.prototype = {
    extend: function (source, value) {
        var extend = Base.prototype.extend;
        if (arguments.length == 2) {
            var ancestor = this[source];
            if ((ancestor instanceof Function) && (value instanceof Function) && ancestor.valueOf() != value.valueOf() && /\bbase\b/.test(value)) {
                var method = value;
                value = function () {
                    var previous = this.base;
                    this.base = ancestor;
                    var returnValue = method.apply(this, arguments);
                    this.base = previous;
                    return returnValue;
                };
                value.valueOf = function () {
                    return method;
                };
                value.toString = function () {
                    return String(method);
                };
            }
            return this[source] = value;
        } else if (source) {
            var _prototype = {
                toSource: null
            };
            var _protected = ["toString", "valueOf"];
            if (Base._prototyping) _protected[2] = "constructor";
            for (var i = 0;
            (name = _protected[i]); i++) {
                if (source[name] != _prototype[name]) {
                    extend.call(this, name, source[name]);
                }
            }
            for (var name in source) {
                if (!_prototype[name]) {
                    extend.call(this, name, source[name]);
                }
            }
        }
        return this;
    },
    base: function () {}
};
Base.extend = function (_instance, _static) {
    var extend = Base.prototype.extend;
    if (!_instance) _instance = {};
    Base._prototyping = true;
    var _prototype = new this;
    extend.call(_prototype, _instance);
    var constructor = _prototype.constructor;
    _prototype.constructor = this;
    delete Base._prototyping;
    var klass = function () {
        if (!Base._prototyping) constructor.apply(this, arguments);
        this.constructor = klass;
    };
    klass.prototype = _prototype;
    klass.extend = this.extend;
    klass.implement = this.implement;
    klass.toString = function () {
        return String(constructor);
    };
    extend.call(klass, _static);
    var object = constructor ? klass : _prototype;
    if (object.init instanceof Function) object.init();
    return object;
};
Base.implement = function (_interface) {
    if (_interface instanceof Function) _interface = _interface.prototype;
    this.prototype.extend(_interface);
};


var AbstractColor = Base.extend({
    constructor: function () {
        this.warn();
    },
    toHex: function () {
        this.warn();
    },
    toRGB: function () {
        this.warn();
    },
    toXYZ: function () {
        this.warn();
    },
    toYxy: function () {
        this.warn();
    },
    toCIELab: function () {
        this.warn();
    },
    toCIELCh: function () {
        this.warn();
    },
    toCMY: function () {
        this.warn();
    },
    toCMYK: function () {
        this.warn();
    },
    toHSV: function () {
        this.warn();
    },
    distance: function (destinationColor) {
        var a = this.toCIELab();
        var b = destinationColor.toCIELab();
        return Math.sqrt(Math.pow((a.l - b.l), 2) + Math.pow((a.a - b.a), 2) + Math.pow((a.b - b.b), 2));
    },
    websafe: function () {
        var c = new Array('00', 'CC', '33', '66', '99', 'FF');
        var palette = [];
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 6; k++) {
                    palette.push(new Hex(c[i] + c[j] + c[k]));
                }
            }
        }
        return this.match(palette);
    },
    match: function (palette) {
        var distance = null;
        var closest = null;
        for (var i = 0; i < palette.length; i++) {
            var cdistance = this.distance(palette[i]);
            if (distance == null || distance > cdistance) {
                distance = cdistance;
                closest = palette[i];
            }
        }
        return closest[this.toSelf]();
    },
    equal: function (parts, include) {
        if (include == null) include = false;
        if (parts < 2) parts = 2;
        var distance = 360 / parts;
        var palette = [];
        if (include) palette.push(this);
        for (var i = 1; i < parts; i++) {
            palette.push(this.hue(distance * i)[this.toSelf]());
        }
        return palette;
    },
    split: function (include) {
        if (include == null) include = false;
        var rtn = [];
        rtn.push(this.hue(150)[this.toSelf]());
        if (include) rtn.push(this);
        rtn.push(this.hue(-150)[this.toSelf]());
        return rtn;
    },
    complement: function (include) {
        if (include == null) include = false;
        var rtn = [
        this.hue(180)[this.toSelf]()];
        if (include) rtn.unshift(this);
        return rtn;
    },
    sweetspot: function (include) {
        if (include == null) include = false;
        var colors = [this.toHSV()];
        colors[1] = new HSV(colors[0].h, Math.round(colors[0].s * 0.3), Math.min(Math.round(colors[0].v * 1.3), 100));
        colors[3] = new HSV((colors[0].h + 300) % 360, colors[0].s, colors[0].v);
        colors[2] = new HSV(colors[1].h, Math.min(Math.round(colors[1].s * 1.2), 100), Math.min(Math.round(colors[1].v * 0.5), 100));
        colors[4] = new HSV(colors[2].h, 0, (colors[2].v + 50) % 100);
        colors[5] = new HSV(colors[4].h, colors[4].s, (colors[4].v + 50) % 100);
        if (!include) {
            colors.shift();
        }
        for (var i = 0; i < colors.length; i++) {
            colors[i] = colors[i][this.toSelf]();
        }
        return colors;
    },
    analogous: function (include) {
        if (include == null) include = false;
        var rtn = [];
        rtn.push(this.hue(30)[this.toSelf]());
        if (include) rtn.push(this);
        rtn.push(this.hue(-30)[this.toSelf]());
        return rtn;
    },
    rectangle: function (sidelength, include) {
        if (include == null) include = false;
        var side1 = sidelength;
        var side2 = (360 - (sidelength * 2)) / 2;
        var current = this.toCIELCh();
        var rtn = [
        this.hue(side1)[this.toSelf](), this.hue(side1 + side2)[this.toSelf](), this.hue(side1 + side2 + side1)[this.toSelf]()];
        if (include) rtn.unshift(this);
        return rtn;
    },
    range: function (destinationColor, steps, include) {
        if (include == null) include = false;
        var a = this.toRGB();
        var b = destinationColor.toRGB();
        var colors = [];
        steps--;
        for (n = 1; n < steps; n++) {
            var nr = Math.floor(a.r + (n * (b.r - a.r) / steps));
            var ng = Math.floor(a.g + (n * (b.g - a.g) / steps));
            var nb = Math.floor(a.b + (n * (b.b - a.b) / steps));
            colors.push(new RGB(nr, ng, nb)[this.toSelf]());
        }
        if (include) {
            colors.unshift(this);
            colors.push(destinationColor[this.toSelf]());
        }
        return colors;
    },
    greyscale: function () {
        var a = this.toRGB();
        var ds = (Math.max(a.r, a.g, a.b) + Math.min(a.r, a.g, a.b)) / 2;
        return new RGB(ds, ds, ds)[this.toSelf]();
    },
    hue: function (degreeModifier) {
        var a = this.toCIELCh();
        a.h += degreeModifier;
        return a[this.toSelf]();
    },
    saturation: function (satModifier) {
        var a = this.toHSV();
        a.s += (satModifier / 100);
        a.s = Math.min(1, Math.max(0, a.s));
        return a[this.toSelf]();
    },
    brightness: function (brightnessModifier) {
        var a = this.toCIELab();
        a.l += brightnessModifier;
        return a[this.toSelf]();
    },
    warn: function () {
        alert('AbstractColor should not be created directly. Treat this as an abstract class.');
    }
});


var Hex = AbstractColor.extend({
    constructor: function (hex) {
        this.hex = hex;
    },
    toHex: function () {
        return this;
    },
    toRGB: function () {
        var r = ((this.hex & 0xFF0000) >> 16);
        var g = ((this.hex & 0x00FF00) >> 8);
        var b = ((this.hex & 0x0000FF));
        return new RGB(r, g, b);
    },
    toXYZ: function () {
        return this.toRGB().toXYZ();
    },
    toYxy: function () {
        return this.toRGB().toYxy();
    },
    toHSV: function () {
        return this.toRGB().toHSV();
    },
    toCMY: function () {
        return this.toRGB().toCMY();
    },
    toCMYK: function () {
        return this.toCMY().toCMYK();
    },
    toCIELab: function () {
        return this.toXYZ().toCIELab();
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        var s = this.hex.toString(16)
        return ("000000".substr(0, (6 - s.length)) + s).toUpperCase();
    },
    toSelf: "toHex"
}, {
    fromString: function (str) {
        str = (str + '').replace(/[^a-f0-9]/gi, '');
        return new Hex(parseInt(str, 16));
    }
});

var RGB = AbstractColor.extend({
    constructor: function (r, g, b) {
        this.r = Math.min(255, Math.max(r, 0));
        this.g = Math.min(255, Math.max(g, 0));
        this.b = Math.min(255, Math.max(b, 0));
    },
    toHex: function () {
        return new Hex(this.r << 16 | this.g << 8 | this.b);
    },
    toRGB: function () {
        return this;
    },
    toXYZ: function () {
        var tmp_r = this.r / 255;
        var tmp_g = this.g / 255;
        var tmp_b = this.b / 255;
        if (tmp_r > 0.04045) {
            tmp_r = Math.pow(((tmp_r + 0.055) / 1.055), 2.4)
        } else {
            tmp_r = tmp_r / 12.92;
        }
        if (tmp_g > 0.04045) {
            tmp_g = Math.pow(((tmp_g + 0.055) / 1.055), 2.4)
        } else {
            tmp_g = tmp_g / 12.92
        }
        if (tmp_b > 0.04045) {
            tmp_b = Math.pow(((tmp_b + 0.055) / 1.055), 2.4);
        } else {
            tmp_b = tmp_b / 12.92
        }
        tmp_r = tmp_r * 100
        tmp_g = tmp_g * 100
        tmp_b = tmp_b * 100
        var x = tmp_r * 0.4124 + tmp_g * 0.3576 + tmp_b * 0.1805;
        var y = tmp_r * 0.2126 + tmp_g * 0.7152 + tmp_b * 0.0722;
        var z = tmp_r * 0.0193 + tmp_g * 0.1192 + tmp_b * 0.9505;
        return new XYZ(x, y, z);
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        var r = this.r / 255;
        var g = this.g / 255;
        var b = this.b / 255;

        var h, s, v = 0;
        var min, max, delta = 0;

        min = Math.min(r, g, b);
        max = Math.max(r, g, b);

        v = max;
        delta = max - min;
        if (max != 0) {
            s = delta / max;
        } else {
            s = 0;
            h = -1;
            return new HSV(h, s, v);
        }
        if (r == max) {
            h = (g - b) / delta;
        } else if (g == max) {
            h = 2 + (b - r) / delta;
        } else {
            h = 4 + (r - g) / delta;
        }
        h *= 60;
        if (h < 0) {
            h += 360;
        }

        return new HSV(h, s * 100, v * 100);
    },
    toCMY: function () {
        var C = 1 - (this.r / 255);
        var M = 1 - (this.g / 255);
        var Y = 1 - (this.b / 255);
        return new CMY(C, M, Y);
    },
    toCMYK: function () {
        return this.toCMY().toCMYK();
    },
    toCIELab: function () {
        return this.toXYZ().toCIELab();
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        return this.r + ',' + this.g + ',' + this.b;
    },
    toSelf: "toRGB"
});

var HSV = AbstractColor.extend({
    constructor: function (h, s, v) {
        this.h = h;
        this.s = s;
        this.v = v;
    },
    toHex: function () {
        return this.toRGB().toHex();
    },
    toRGB: function () {
        var h = this.h / 360;
        var s = this.s / 100;
        var v = this.v / 100;

        if (s == 0) {
            var R = v * 255;
            var G = v * 255;
            var B = v * 255;
        }
        else {
            var_h = h * 6
            if (var_h == 6) var_h = 0;
            var_i = Math.floor(var_h);
            var_1 = v * (1 - s);
            var_2 = v * (1 - s * (var_h - var_i));
            var_3 = v * (1 - s * (1 - (var_h - var_i)));

            if (var_i == 0) {
                var_r = v;
                var_g = var_3;
                var_b = var_1
            }
            else if (var_i == 1) {
                var_r = var_2;
                var_g = v;
                var_b = var_1
            }
            else if (var_i == 2) {
                var_r = var_1;
                var_g = v;
                var_b = var_3
            }
            else if (var_i == 3) {
                var_r = var_1;
                var_g = var_2;
                var_b = v
            }
            else if (var_i == 4) {
                var_r = var_3;
                var_g = var_1;
                var_b = v
            }
            else {
                var_r = v;
                var_g = var_1;
                var_b = var_2
            }

            var R = var_r * 255;
            var G = var_g * 255;
            var B = var_b * 255;
        }

        return new RGB(R, G, B);
    },
    toXYZ: function () {
        return this.toRGB().toXYZ();
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        return this;
    },
    toCMY: function () {
        return this.toRGB().toCMY();
    },
    toCMYK: function () {
        return this.toCMY().toCMYK();
    },
    toCIELab: function () {
        return this.toRGB().toCIELab();
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        return this.h + ',' + this.s + ',' + this.v;
    },
    toSelf: "toHSV"
});


var CMY = AbstractColor.extend({
    constructor: function (c, m, y) {
        this.c = c;
        this.m = m;
        this.y = y;
    },
    toHex: function () {
        return this.toRGB().toHex();
    },
    toRGB: function () {
        var R = (1 - this.c) * 255;
        var G = (1 - this.m) * 255;
        var B = (1 - this.y) * 255;
        return new RGB(R, G, B);
    },
    toXYZ: function () {
        return this.toRGB().toXYZ();
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        return this.toRGB().toHSV();
    },
    toCMY: function () {
        return this;
    },
    toCMYK: function () {
        var var_K = 1

        if (this.c < var_K) var_K = this.c;
        if (this.m < var_K) var_K = this.m;
        if (this.y < var_K) var_K = this.y;
        if (var_K == 1) {
            var C = 0;
            var M = 0;
            var Y = 0;
        }
        else {
            var C = (this.c - var_K) / (1 - var_K);
            var M = (this.m - var_K) / (1 - var_K);
            var Y = (this.y - var_K) / (1 - var_K);
        }
        var K = var_K;
        return new CMYK(C, M, Y, K);
    },
    toCIELab: function () {
        return this.toRGB().toCIELab();
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        return this.c + ',' + this.m + ',' + this.y;
    },
    toSelf: "toCMY"
});

var CMYK = AbstractColor.extend({
    constructor: function (c, m, y, k) {
        this.c = c;
        this.m = m;
        this.y = y;
        this.k = k;
    },
    toHex: function () {
        return this.toRGB().toHex();
    },
    toRGB: function () {
        return this.toCMY().toRGB();
    },
    toXYZ: function () {
        return this.toRGB().toXYZ();
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        return this.toRGB().toHSV();
    },
    toCMY: function () {
        var C = (this.c * (1 - this.k) + this.k);
        var M = (this.m * (1 - this.k) + this.k);
        var Y = (this.y * (1 - this.k) + this.k);
        return new CMY(C, M, Y);
    },
    toCMYK: function () {
        return this;
    },
    toCIELab: function () {
        return this.toRGB().toCIELab();
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        return this.c + ',' + this.m + ',' + this.y + ',' + this.k;
    },
    toSelf: "toCMYK"
});

var XYZ = AbstractColor.extend({
    constructor: function (x, y, z) {
        this.x = x;
        this.y = y;
        this.z = z;
    },
    toHex: function () {
        return this.toRGB().toHex();
    },
    toRGB: function () {
        var var_X = this.x / 100;
        var var_Y = this.y / 100;
        var var_Z = this.z / 100;

        var var_R = var_X * 3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
        var var_G = var_X * -0.9689 + var_Y * 1.8758 + var_Z * 0.0415;
        var var_B = var_X * 0.0557 + var_Y * -0.2040 + var_Z * 1.0570;

        if (var_R > 0.0031308) {
            var_R = 1.055 * Math.pow(var_R, (1 / 2.4)) - 0.055;
        } else {
            var_R = 12.92 * var_R;
        }
        if (var_G > 0.0031308) {
            var_G = 1.055 * Math.pow(var_G, (1 / 2.4)) - 0.055;
        } else {
            var_G = 12.92 * var_G;
        }
        if (var_B > 0.0031308) {
            var_B = 1.055 * Math.pow(var_B, (1 / 2.4)) - 0.055;
        } else {
            var_B = 12.92 * var_B;
        }
        var r = Math.round(var_R * 255);
        var g = Math.round(var_G * 255);
        var b = Math.round(var_B * 255);

        return new RGB(r, g, b);
    },
    toXYZ: function () {
        return this;
    },
    toYxy: function () {
        var Y = this.y;
        var x = this.x / (this.x + this.y + this.z);
        var y = this.y / (this.x + Y + this.z);
        return new Yxy(Y, x, y);
    },
    toHSV: function () {
        return this.toRGB().toHSV();
    },
    toCMY: function () {
        return this.toRGB().toCMY();
    },
    toCMYK: function () {
        return this.toCMY().toCMYK();
    },
    toCIELab: function () {

        var Xn = 95.047;
        var Yn = 100.000;
        var Zn = 108.883;

        var x = this.x / Xn;
        var y = this.y / Yn;
        var z = this.z / Zn;

        if (x > 0.008856) {
            x = Math.pow(x, 1 / 3);
        } else {
            x = (7.787 * x) + (16 / 116);
        }
        if (y > 0.008856) {
            y = Math.pow(y, 1 / 3);
        } else {
            y = (7.787 * y) + (16 / 116);
        }
        if (z > 0.008856) {
            z = Math.pow(z, 1 / 3);
        } else {
            z = (7.787 * z) + (16 / 116);
        }

        if (y > 0.008856) {
            var l = (116 * y) - 16;
        } else {
            var l = 903.3 * y;
        }
        var a = 500 * (x - y);
        var b = 200 * (y - z);

        return new CIELab(l, a, b);
    },
    toCIELCh: function () {
        return this.toCIELab().toCIELCh();
    },
    toString: function () {
        return this.x + ',' + this.y + ',' + this.z;
    },
    toSelf: "toXYZ"
});

var Yxy = AbstractColor.extend({
    constructor: function (Y, x, y) {
        this.Y = Y;
        this.x = x;
        this.y = y;
    },
    toHex: function () {
        return this.toXYZ().toHex();
    },
    toRGB: function () {
        return this.toXYZ().toRGB();
    },
    toXYZ: function () {
        var X = this.x * (this.Y / this.y);
        var Y = this.Y;
        var Z = (1 - this.x - this.y) * (this.Y / this.y);
        return new XYZ(X, Y, Z);
    },
    toYxy: function () {
        return this;
    },
    toHSV: function () {
        return this.toXYZ().toHSV();
    },
    toCMY: function () {
        return this.toXYZ().toCMY();
    },
    toCMYK: function () {
        return this.toXYZ().toCMYK();
    },
    toCIELab: function () {
        return this.toXYZ().toCIELab();
    },
    toCIELCh: function () {
        return this.toXYZ().toCIELCh();
    },
    toString: function () {
        return this.Y + ',' + this.x + ',' + this.y;
    },
    toSelf: "toYxy"
});

var CIELCh = AbstractColor.extend({
    constructor: function (l, c, h) {
        this.l = l;
        this.c = c;
        this.h = h < 360 ? h : (h - 360);
    },
    toHex: function () {
        return this.toCIELab().toHex();
    },
    toRGB: function () {
        return this.toCIELab().toRGB();
    },
    toXYZ: function () {
        return this.toCIELab().toXYZ();
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        return this.toCIELab().toHSV();
    },
    toCMY: function () {
        return this.toCIELab().toCMY();
    },
    toCMYK: function () {
        return this.toCIELab().toCMYK();
    },
    toCIELab: function () {
        var l = this.l;
        var hradi = this.h * (Math.PI / 180);
        var a = Math.cos(hradi) * this.c;
        var b = Math.sin(hradi) * this.c;
        return new CIELab(l, a, b);
    },
    toCIELCh: function () {
        return this;
    },
    toString: function () {
        return this.l + ',' + this.c + ',' + this.h;
    },
    toSelf: "toXYZ"
});

var CIELab = AbstractColor.extend({
    constructor: function (l, a, b) {
        this.l = l;
        this.a = a;
        this.b = b;
    },
    toHex: function () {
        return this.toRGB().toHex();
    },
    toRGB: function () {
        return this.toXYZ().toRGB();
    },
    toXYZ: function () {
        var ref_X = 95.047;
        var ref_Y = 100.000;
        var ref_Z = 108.883;

        var var_Y = (this.l + 16) / 116;
        var var_X = this.a / 500 + var_Y;
        var var_Z = var_Y - this.b / 200;

        if (Math.pow(var_Y, 3) > 0.008856) {
            var_Y = Math.pow(var_Y, 3);
        } else {
            var_Y = (var_Y - 16 / 116) / 7.787;
        }
        if (Math.pow(var_X, 3) > 0.008856) {
            var_X = Math.pow(var_X, 3);
        } else {
            var_X = (var_X - 16 / 116) / 7.787;
        }
        if (Math.pow(var_Z, 3) > 0.008856) {
            var_Z = Math.pow(var_Z, 3);
        } else {
            var_Z = (var_Z - 16 / 116) / 7.787;
        }
        x = ref_X * var_X;
        y = ref_Y * var_Y;
        z = ref_Z * var_Z;
        return new XYZ(x, y, z);
    },
    toYxy: function () {
        return this.toXYZ().toYxy();
    },
    toHSV: function () {
        return this.toRGB().toHSV();
    },
    toCMY: function () {
        return this.toRGB().toCMY();
    },
    toCMYK: function () {
        return this.toCMY().toCMYK();
    },
    toCIELab: function () {
        return this;
    },
    toCIELCh: function () {
        var var_H = Math.atan2(this.b, this.a);

        if (var_H > 0) {
            var_H = (var_H / Math.PI) * 180;
        } else {
            var_H = 360 - (Math.abs(var_H) / Math.PI) * 180
        }

        var l = this.l;
        var c = Math.sqrt(Math.pow(this.a, 2) + Math.pow(this.b, 2));
        var h = var_H;

        return new CIELCh(l, c, h);
    },
    toString: function () {
        return this.l + ',' + this.a + ',' + this.b;
    },
    toSelf: "toCIELab"
});