
var gob;

j$(function() {

	function gup( name, def ){
		name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");  
		var regexS = "[\\?&]"+name+"=([^&#]*)";  
		var regex = new RegExp( regexS );  
		var results = regex.exec( window.location.href ); 
		if( results == null ) {
			return def;
		}  
		else {
			return results[1];
		}
	}


	var dat;
	var g_curGroup = 0;
	var a_DataArr = ["a_Data0","a_Data1"];

	var enums = {
		fillDir: {
			horizontal:0,
			vertical:1
		},
		align: {
			left:0,
			center:1,
			right:2,

			top:3,
			middle:4,
			bottom:5
		},
		types: {

			reserved: 0,

			untypedList: 1,
			untyped: 2,
			
			nodeList: 3,
			node: 4,
			
			numberList:5,
			number: 6,
			
			colorList: 7, 
			color: 8,

			gradientList: 9,
			gradient: 10,

			gradientStepList: 11,
			gradientStep: 12,

			boolList:13,
			bool:14
		},
		invalidations: {
			gradient: 0
		},
		materials: {
			/*BlueGray: 0,
			Gold: 1,
			Purple: 2,
			SkyBlue: 3,
			Silver: 4,
			LightBlueGray: 5
			*/
		}
	};

	var enumStrings = {};


	//var gradArr = [];

	


	var isNode = new Array(256);



	function logInPlace(obj) {
		//console.log(obj);
		return obj;
	}

	function combineObjs(oArr, noClone) {
		var resObj = {};

		var i;
		var j;
		var curObj;

		if (oArr.length) {

		}
		else {

			if (noClone) {
				return oArr;
			}
			else {
				return JSON.parse(JSON.stringify(oArr));
			}

			
		}

		for (i = 0; i < oArr.length; i++) {

			curObj = oArr[i];

			for (j in curObj) {
				if (curObj.hasOwnProperty(j)) {
					resObj[j] = curObj[j];
				}
			}
		}

		if (noClone) {
			return resObj;
		}
		else {
			return JSON.parse(JSON.stringify(resObj));
		}
	}

	function createNode(propArr, childArr, iv) {
		var obj;
		var myProps;

		if (propArr.noClone) {
			myProps = combineObjs( [ combineObjs(propArr.doClone, false), propArr.noClone], true);


			obj = {
				props:myProps,
				childArr:childArr
			};
		}
		else {
			obj = {
				props:combineObjs(propArr, false),
				childArr:childArr
			};
		}

		

		var i;



		if (obj.props.type) {

			obj.props.value = 0;

			switch(obj.props.type) {
				
				case enums.types.untypedList:

				break;
				case enums.types.untyped:

				break;
				case enums.types.nodeList:

				break;
				case enums.types.node:

				break;
				case enums.types.numberList:

				break;
				case enums.types.number:
					if (iv === undefined) {
						obj.props.value = 0;
					}
					else {
						obj.props.value = iv;
					}

					//obj.props.actionFunc = "updatePalette";

				break;
				case enums.types.colorList:

				break;
				case enums.types.color:
					/*
					obj.childArr.push(

						createNode( {label:"Hue", type:enums.types.number}, [], iv.hue ),
						createNode( {label:"Saturation", type:enums.types.number}, [], iv.saturation ),
						createNode( {label:"Lightness", type:enums.types.number}, [], iv.lightness )

					);
					*/
				break;
				case enums.types.gradientList:
					for (i = 0; i < iv.length; i++) {
						obj.childArr.push(
							createNode( {label:enumStrings.materials[i], type:enums.types.gradientStepList /*, ind:i*/ }, [], iv[i].steps )
						);
					}
				break;
				case enums.types.gradient:
					/*obj.childArr.push(
						createNode( {label:"Steps", type:enums.types.gradientStepList}, [], iv.steps )
					);
					*/
				break;
				case enums.types.gradientStepList:
					
					for (i = 0; i < iv.length; i++) {
						obj.childArr.push(
							createNode( {label:"Step" + i, type:enums.types.gradientStep}, [], iv[i] )
						);
					}
					
				break;
				case enums.types.gradientStep:
					obj.childArr.push(
						/*
						createNode( {label:"Color", type:enums.types.color}, [], {
							hue: iv.h,
							saturation: iv.s,
							lightness: iv.l
						} ),*/

						createNode( {label:"Hue", type:enums.types.number}, [], iv.h ),
						createNode( {label:"Saturation", type:enums.types.number}, [], iv.s ),
						createNode( {label:"Lightness", type:enums.types.number}, [], iv.l ),
						createNode( {label:"Power", type:enums.types.number}, [], iv.pow ),
						createNode( {label:"Position", type:enums.types.number}, [], iv.pos )

					);
				break;
			}

		}

		return obj;
	}

	if(!Array.prototype.last) {
	    Array.prototype.last = function() {
	        return this[this.length - 1];
	    }
	}

	window.performance = window.performance || {};
	performance.now = (function() {
	    return performance.now       ||
	        performance.mozNow    ||
	        performance.msNow     ||
	        performance.oNow      ||
	        performance.webkitNow ||
	        function() {
	            //Doh! Crap browser!
	            return new Date().getTime(); 
	        };
	})();




	var DisplayNode = new Class({
		initialize: function() {
			this.children = {};
			this.childArr = [];
			this.isBatchRoot = false;

		},
		addChild: function(obj) {
			this.childArr.push(obj);
			this.children[obj.nodeId] = obj;
		}
	});

	var container;
	//var stats;
	var camera, scene, renderer;
	var texture;
	//var testObj;

	var zoom = 1;
	var atArr;
	var atArrs = [
		[0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0],
		[0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0]
	];
	
	var rtScene;
	var layerScene;
	
	var meshText;
	var meshBG;
	var meshFSQ;
	
	var invalidValue = -999;

	gob = {

		lastNode: 0,

		palX:1008,
		palY:48,
		invalidValue:invalidValue,

		connectionRetryCount:0,
		messageStack:[],
		waitingForResponse:false,
		powMax: 4.0,
		//callbacks:{},
		superSample: false,
		lastHit: 0,
		lastParent: 0,
		disTraveledX: 0,
		disTraveledY: 0,
		timeoutVar: null,
		lastMouseX: null,
		lastMouseY: null,
		shiftDown: false,
		buttonWidth: 384,
		isScrolling: 0,
		scrollX:0.0,
		scrollY:0.0,
		targScrollX:0.0,
		targScrollY:0.0,
		guiInvalidated:false,
		showFullBuffer:false,
		lockOn: false,
		activeGUI: 0,
		autoUpdate: false,
		curDebugSection:0.0,
		traceVals:[],
		styleSheets:{},
		mainRoot:null,
		bufferWidth: parseInt(gup('width',1024),10),
		bufferHeight: parseInt(gup('height',768),10),

		isRendering: true,
		scrollSpeed: parseInt(gup('scrollSpeed',300),10)/10.0,
		maxLayers: parseInt(gup('maxheight',20),10),
		updateBaseRT:true,
		renderTargets:{},
		shaderNames:["lightingShader","palShader","palFromTexShader","palFromTex2Shader","aoShader","aoHighShader","extrudeShader","layerShader","bgShader","textShader","bgIdShader","textIdShader","heightShader","normShader","downscaleShader","upscaleShader", "pickerShader", "debugShader"],
		fontNames:["arial_black_regular_48","arial_black_regular_96","old_london_regular_96"],
		fontLoaded:{},
		shaders:{},
		materials:{},
		debugTex:null,
		displayList:[],
		traceOn:false,
		traceLevel: 0,
		lastTraceLevel: 0,
		hasConnection:false,
		tracesAtLevel: 0,
		traceArr: [],
		maxFrameSize: 16777216,
		
		doError: function(str) {
			console.log(str);
		},
		getShader: function(i) {
			var res = gob.shaders[gob.shaderNames[i]];

			if (res) {
				return res;
			}
			else {
				gob.doError(gob.shaderNames[i] + " not found");
			}
		},
		pushTrace: function() {
			gob.traceLevel++;
			gob.tracesAtLevel = 0;
		},
		popTrace: function() {
			

			if (gob.traceLevel < gob.lastTraceLevel) {
				gob.doTrace("END");
			}

			gob.traceLevel--;
			if (gob.traceLevel < 0) {
				gob.traceLevel = 0;
			}

			gob.tracesAtLevel = 0;



			
		},
		doTrace:function(traceStr, otherPrefix) {
			
			var resStr;

			if (gob.traceOn) {
				gob.tracesAtLevel++;

				

				gob.lastTraceLevel = gob.traceLevel;

				var op = otherPrefix;

				if (op) {} else {
					op = "";
				}

				var prefix = gob.getTracePrefix() + op;
				var prefixn = "\n"+prefix;

				if (typeof traceStr == "object") {

					var objStr = JSON.stringify(traceStr,null,"\t");
					var newStr = prefix + objStr.replace(/[\r\n]/g, prefixn);

					resStr = ( newStr );
				}
				else {
					resStr = (prefix + traceStr);
				}
			}
			else {
				resStr = (traceStr);
			}

			console.log(resStr);
			
		},
		doTraceTab: function(traceStr) {
			if (gob.traceOn) {
				gob.doTrace(traceStr,"|  ");
			}
			else {
				console.log(traceStr);
			}
			
		},
		getTracePrefix: function() {
			return gob.traceArr[gob.traceLevel];
		},
		wf:function(varName, func, avoidArgs) {
			if (gob.traceOn) {
				gob[varName] = function() {

					var argArr = Array.prototype.slice.call(arguments, 0);
					var i;
					gob.pushTrace();

					var aStr = "";

					if (avoidArgs || (gob.traceVals.length > 0) ) {
						for (i = 0; i < gob.traceVals.length; i++) {
							aStr += argArr[0].props[gob.traceVals[i]] + " ";
						}
					}
					else {
						aStr = argArr.join(",");
					}

					gob.doTrace(varName + "("+aStr+")");
					
					var myr = func.apply(func,arguments);
					gob.popTrace();
					return myr;
				}
			}
			else {
				gob[varName] = func;
			}

			return gob[varName];
			
		}

	};


	/*
	gradArr[enums.materials.BlueGray] = {
		steps: [
			{h:0.9, s:0.0, l:0.1, pow:0.5/gob.powMax, pos:0/255.0},
			{h:0.4, s:0.1, l:1.0, pow:0.3/gob.powMax, pos:255/255.0}
		]
	};

	

	gradArr[enums.materials.Gold] = {
		steps: [ // gold

			{h:0.8, s:0.0, l:0.0, pow:0.5/gob.powMax, pos:0/255.0},
			{h:0.75, s:0.5, l:0.2, pow:2.0/gob.powMax, pos:20/255.0},
			{h:0.75, s:0.3, l:0.1, pow:0.5/gob.powMax, pos:28/255.0},
			{h:0.75, s:0.2, l:0.2, pow:0.5/gob.powMax, pos:40/255.0},
			{h:0.75, s:0.8, l:0.8, pow:2.0/gob.powMax, pos:120/255.0},
			{h:0.8, s:0.5, l:0.4, pow:0.5/gob.powMax, pos:128/255.0},
			{h:0.75, s:0.8, l:0.9, pow:0.5/gob.powMax, pos:192/255.0},
			{h:0.75, s:0.1, l:1.0, pow:2.0/gob.powMax, pos:255/255.0}
		]
	};

	gradArr[enums.materials.Purple] = {
		steps: [ // fill
			{h:0.0, s:0.4, l:0.0, pow:0.5/gob.powMax, pos:0/255.0},
			{h:0.0, s:0.2, l:0.5, pow:0.3/gob.powMax, pos:192/255.0},
			{h:0.0, s:0.1, l:1.0, pow:0.1/gob.powMax, pos:255/255.0}
		]
	};

	gradArr[enums.materials.SkyBlue] = {
		steps: [ // background
			{h:0.1, s:0.0, l:0.0, pow:2.0/gob.powMax, pos:0/255.0},
			{h:0.4, s:0.8, l:1.0, pow:0.5/gob.powMax, pos:128/255.0},
			{h:0.4, s:0.1, l:1.0, pow:2.0/gob.powMax, pos:255/255.0}
		]
	};

	gradArr[enums.materials.Silver] = {
		steps: [ // background
			{h:0.0, s:0.0, l:0.0, pow:0.5/gob.powMax, pos:0/255.0},
			{h:0.0, s:0.1, l:0.2, pow:2.0/gob.powMax, pos:20/255.0},
			{h:0.0, s:0.0, l:0.1, pow:0.5/gob.powMax, pos:28/255.0},
			{h:0.0, s:0.0, l:0.2, pow:0.5/gob.powMax, pos:40/255.0},
			{h:0.0, s:0.2, l:0.8, pow:2.0/gob.powMax, pos:120/255.0},
			{h:0.0, s:0.1, l:0.4, pow:0.5/gob.powMax, pos:128/255.0},
			{h:0.0, s:0.2, l:0.9, pow:0.5/gob.powMax, pos:192/255.0},
			{h:0.0, s:0.2, l:1.0, pow:2.0/gob.powMax, pos:255/255.0}
		]
	};

	gradArr[enums.materials.LightBlueGray] = {
		steps: [
			{h:0.1, s:0.1, l:0.1, pow:0.3/gob.powMax, pos:0/255.0},
			{h:0.4, s:0.2, l:1.0, pow:0.5/gob.powMax, pos:255/255.0}
		]
	};
	*/



	gob.scrollY = gob.maxLayers;

	gob.wf("connectionOnOpen",function() {
		gob.hasConnection = true;

	});
	gob.wf("connectionOnError",function(error) {
		gob.doTraceTab("ERROR: " + JSON.stringify(error) );
	});
	gob.wf("connectionOnMessage",function(message) {

		var result = JSON.parse(message.data);

		//console.log("REC MESSAGE");

		if (result.cc) {
			//console.log("CONNECTION CODE: " + result.cc);

			switch (result.cc) {
				case "REC__OK":
					gob.waitingForResponse = false;
				break;
				default:
					gob.waitingForResponse = false;
				break;
			}
		}

		//gob.doTraceTab("MESSAGE: " + message.data);

	});
	gob.wf("connectionClose",function() {
		gob.hasConnection = false;
	});

	gob.wf("openNewConnection", function(url) {

		gob.connection = new WebSocket(url);
		gob.connection.onopen = gob.connectionOnOpen;
		gob.connection.onerror = gob.connectionOnError;
		gob.connection.onmessage = gob.connectionOnMessage;
		gob.connection.onclose = gob.connectionClose;

	});

	gob.wf("sendMessage",function(msg) {

		var url = 'ws://127.0.0.1:9980';
		var sendStr;
		var messageSent = false;
		var doOpenCon = false;


		if (gob.hasConnection) {


			
			//gob.doTraceTab("READYSTATE: " + gob.connection.readyState);

			if (gob.connection.readyState !== 1) {
				gob.connection.close();
				gob.hasConnection = false;
				doOpenCon = true;

				
			}
			else {

				

				if (gob.waitingForResponse) {

				}
				else {

					gob.connectionRetryCount = 0;

					//console.log("SEND MESSAGE");
					//console.log(msg);


					gob.waitingForResponse = true;


					if (typeof(msg) == "string") {
						sendStr = msg;
						
					}
					else {
						sendStr = JSON.stringify(msg, null, "\t");

						gob.lastMessage = sendStr;

						

						//console.log(sendStr);

						/*
						sendStr = sendStr.substring(1);
						sendStr = '{"cc":"SENDING",' + sendStr;
						*/
					}

					

					
					if (sendStr.length + 256 >= gob.maxFrameSize) {
						doTraceTab("ERROR: Frame Size Exceeded");
					}
					else {
						gob.connection.send(sendStr);
					}

					messageSent = true;


				}


				
			}
		}
		else {
			
			doOpenCon = true;
		}


		if (messageSent) {

		}
		else {
			gob.messageStack.push(msg);
		}

		if (doOpenCon) {
			gob.openNewConnection(url);
		}

		
	});


	gob.unpackData = function(srcObj, resObj, isRoot) {
		var i;

		var props;
		var ind;

		for (i in srcObj) {

			if (srcObj.hasOwnProperty(i)) {
				props = i.split('_');
				ind = parseInt(props[2],10);

				if (isRoot) {
					resObj.props = {
						label:props[1],
						type:enums.types[ props[0] ],
						value:0
					}
					resObj.childArr = [];

					gob.unpackData(srcObj[i], resObj, false);

					
				}
				else {

					resObj.childArr[ind] = {
						props:{
							label:props[1],
							type:enums.types[ props[0] ],
							value:0
						},
						childArr: [

						]
					}

					if (typeof(srcObj[i]) == "object" ) {

						gob.unpackData(srcObj[i], resObj.childArr[ind], false);
					}
					else {
						resObj.childArr[ind].props.value = srcObj[i];
					}
					
					

				}
			}

			

			

		}
	}
		

	gob.packData = function(srcObj, resObj, ind) {
		var i;
		var isList = (srcObj.childArr.length > 0);

		var propName = enumStrings.types[srcObj.props.type] + "_" + srcObj.props.label + "_" + ind;

		if (isList) {
			resObj[propName] = {};
			for (i = 0; i < srcObj.childArr.length; i++) {
				gob.packData(srcObj.childArr[i], resObj[propName], i)
			}
		}
		else {
			resObj[propName] = srcObj.props.value;
		}

		
	}


	gob.loadJSON = function(filePath, callback) {

	    j$.ajax({
	        'async': false,
	        'global': false,
	        'url': filePath,
	        'dataType': "json",
	        'success': function (data) {
				callback(data);
			},
	        'error': function ( jqXHR, textStatus, errorThrown) {
				console.log("loadJSON failed: ", textStatus, errorThrown);
			}
	    });
	    
	}; 

	/*

	gob.loadJSON = function(filePath, callback) {
		j$.getJSON(filePath, callback);

	}
	*/


	gob.getStringWidth = function(curParentProps) {
		var i;
		var curChar;
		var charCode;
		var nextCharCode;
		var curX = 0;
		var str = curParentProps.str;

		var totPadding = curParentProps.padding + curParentProps.border;


		for (i = 0; i < str.length; i++) {
			charCode = str.charCodeAt(i);
			curChar = gob.curFont.chars[charCode-32];
			
			if (i < str.length - 1) {
				nextCharCode = str.charCodeAt(i+1);
				curX += curChar.width + gob.curFont.kernMap[charCode*128 + nextCharCode];
			}
			else {
				curX += curChar.width;
			}
		}

		return curX*curParentProps.scale + totPadding*2;
	}







	gob.wf("getMinWidths", function(rootObj) {
		var i;
		var curParentProps = rootObj.props;
		var curChildProps;
		var minWidth = 0;
		var totPadding = curParentProps.padding + curParentProps.border;

		if (rootObj.childArr.length == 0) {
			if (curParentProps.maxLines == 1 && curParentProps.fitText) {
				minWidth = gob.getStringWidth(curParentProps);
			}
		}
		else {

			for (i = 0; i < rootObj.childArr.length; i++) {
				minWidth = Math.max(gob.getMinWidths(rootObj.childArr[i]), minWidth); 
			}

			
		}

		curParentProps.minWidth = minWidth+(totPadding)*(2);// + Math.max(0,rootObj.childArr.length-1) );

		return curParentProps.minWidth;
		
	});



	gob.wf("setResultWidths", function(rootObj) {
		var i;
		var j;
		var curX;

		var curParentProps = rootObj.props;
		var curChildProps;
		var availWidth;

		var totRatio = 0;
		var totFilled = 0;
		var maxWidth;
		var totWidth;
		var wordCount;
		var curLine;

		var startItem;
		var endItem;
		var curLineWidth;

		var totPadding = curParentProps.padding + curParentProps.border;

		rootObj.lineWidthArr = [];
		rootObj.lineArr = [];



		if (rootObj.childArr.length == 0) {
			
		}
		else {


			if (curParentProps.fillDir == enums.fillDir.horizontal) {
				
				
				totWidth = totPadding*2;
				wordCount = 0;
				curLine = 0;


				// determine lines and line widths
				for (i = 0; i < rootObj.childArr.length; i++) {
					
					wordCount++;
					curChildProps = rootObj.childArr[i].props;


					totWidth += curChildProps.minWidth + totPadding;

					while (rootObj.lineArr.length <= curLine) {
						rootObj.lineArr.push([]);
					}

					if (totWidth-totPadding > curParentProps.resultWidth) {

						if (wordCount == 1) {

							rootObj.lineArr[curLine].push(i);
							rootObj.lineWidthArr.push(curParentProps.resultWidth - totPadding*2);
						}
						else {
							i--;
							rootObj.lineWidthArr.push(totWidth - (curChildProps.minWidth + totPadding*2) );
						}
						wordCount = 0;
						totWidth = totPadding*2;
						curLine++;

						
					}
					else {

						rootObj.lineArr[curLine].push(i);
					}
				}


				if (totWidth != totPadding*2) {

					rootObj.lineWidthArr.push(totWidth - totPadding );
				}

				for (j = 0; j < rootObj.lineArr.length; j++) {
					startItem = rootObj.lineArr[j][0];
					endItem = rootObj.lineArr[j].last();
					curLineWidth = rootObj.lineWidthArr[j];
					availWidth = curParentProps.resultWidth - curLineWidth;


					totRatio = 0;
					for (i = startItem; i <= endItem; i++) {
						curChildProps = rootObj.childArr[i].props;
						totRatio += curChildProps.fillRatio;
					}

					totFilled = 0;
					curX = curParentProps.x + totPadding;
					
					
					for (i = startItem; i <= endItem; i++) {
						curChildProps = rootObj.childArr[i].props;
						
						curChildProps.resultWidth = (curChildProps.minWidth + Math.floor(curChildProps.fillRatio*availWidth/totRatio));
						curChildProps.x = curX;
						
						totFilled += curChildProps.resultWidth;

						curX += totPadding + curChildProps.resultWidth;
					}

					//add on left over space from rounding down
					//curChildProps.resultWidth += availWidth - totFilled;


				}

			}
			else {

				for (i = 0; i < rootObj.childArr.length; i++) {



					curChildProps = rootObj.childArr[i].props;
					maxWidth = curParentProps.resultWidth - totPadding*2;

					if (curChildProps.fillRatio > 0) {
						curChildProps.resultWidth = (maxWidth);
					}
					else {
						curChildProps.resultWidth = (Math.min(curChildProps.minWidth,maxWidth));
					}

					rootObj.lineArr.push([i]);
					rootObj.lineWidthArr.push(curChildProps.resultWidth);

				}

				


				for (i = 0; i < rootObj.childArr.length; i++) {
					curChildProps = rootObj.childArr[i].props;
					curChildProps.x = curParentProps.x + totPadding;
				}


			}


			for (i = 0; i < rootObj.childArr.length; i++) {
				gob.setResultWidths(rootObj.childArr[i]);
			}
		}
		
	});

	gob.wf("getMinHeights",function(rootObj) {
		var i;
		var j;
		var curY;
		var curParentProps = rootObj.props;
		var curChildProps;
		var minHeight = 0;
		var totalMinHeight = 0;
		var curMod;

		var totPadding = curParentProps.padding + curParentProps.border;

		curY = curParentProps.y + totPadding;

		if (rootObj.childArr.length == 0) {
			if (curParentProps.maxLines == 1 ) {
				minHeight = gob.curFont.metrics.height*curParentProps.scale;
			}
			else {
				minHeight = gob.drawTextArea(rootObj, null, true);
			}
		}
		else {
			
			if (curParentProps.fillDir == enums.fillDir.horizontal) {


				for (j = 0; j < rootObj.lineArr.length; j++) {
					startItem = rootObj.lineArr[j][0];
					endItem = rootObj.lineArr[j].last();

					minHeight = 0;
					for (i = startItem; i <= endItem; i++) {
						curChildProps = rootObj.childArr[i].props;
						curChildProps.y = curY;

						minHeight = Math.max(gob.getMinHeights(rootObj.childArr[i]), minHeight); 

						
					}



					totalMinHeight += minHeight;

					if (j != rootObj.lineArr.length-1) {
						totalMinHeight += totPadding;
					}

					curY += minHeight + totPadding;

				}

				minHeight = totalMinHeight;
			}
			else {

				for (i = 0; i < rootObj.childArr.length; i++) {
					curChildProps = rootObj.childArr[i].props;
					curChildProps.y = curY;

					curMod = gob.getMinHeights(rootObj.childArr[i]);
					


					if (i != rootObj.childArr.length-1) {
						curMod += totPadding;
					}

					minHeight += curMod;

					curY += curMod;


				}
				
			}


			
		}

		curParentProps.minHeight = minHeight+(totPadding)*(2);// + Math.max(0,rootObj.childArr.length-1) );

		curParentProps.resultHeight = curParentProps.minHeight;

		return curParentProps.minHeight;
		
	});


	gob.wf("addMeshes",function(rootObj) {
		var i;

		gob.drawTextArea(rootObj, meshBG, false);
		gob.drawTextArea(rootObj, meshText, false);

		for (i = 0; i < rootObj.childArr.length; i++) {
			gob.addMeshes(rootObj.childArr[i]);
		}

	});

	gob.findParent = function(parentObj, rootObj) {
		//gob.lastParent = parentObj;

		var i;
		var res;

		if (rootObj == gob.activeGUI) {
			gob.lastParent = parentObj;
			return true;
		}



		for (i = 0; i < rootObj.childArr.length; i++) {
			res = gob.findParent(rootObj,rootObj.childArr[i]);

			if (res) {
				return true;
			}
		}
	}


	gob.testHit = function(parentObj, rootObj, mouseX, mouseY) {
		var i;
		var j;

		var cp = rootObj.props;
		var res;

		if (rootObj.props.isGroup) {

			if (
				mouseX >= cp.x &&
				mouseY >= cp.y &&
				mouseX <= (cp.x + cp.resultWidth) &&
				mouseY <= (cp.y + cp.resultHeight)
			) {

				return rootObj;
			}
			else {
				return 0;
			}

		}


		for (i = 0; i < rootObj.childArr.length; i++) {
			res = gob.testHit(rootObj,rootObj.childArr[i], mouseX, mouseY);

			if (res !== 0) {
				return res;
			}
		}

		return 0;
	}

	gob.numberGroups = function(rootObj, newHeight) {
		var i;

		if (rootObj.props.isGroup) {
			rootObj.props.groupId = g_curGroup;
			g_curGroup++;
		}

		rootObj.props.baseDepth = newHeight;

		for (i = 0; i < rootObj.childArr.length; i++) {
			gob.numberGroups(rootObj.childArr[i], newHeight);
		}
	}

	gob.setGroups = function(rootObj, curGroup) {
		var i;
		var newGroup;


		if (rootObj.props.groupId == 0) {
			newGroup = curGroup;
		}
		else {
			newGroup = rootObj.props.groupId;
		}

		rootObj.props.groupId = newGroup;

		for (i = 0; i < rootObj.childArr.length; i++) {
			gob.setGroups(rootObj.childArr[i], newGroup);
		}
	}

	gob.selectCurNode = function() {
		var i;
		var tempval;


		if (gob.activeGUI === 0) {

		}
		else {
			if (isNode[gob.activeGUI.props.baseProps.type]) {
				tempval = 1.0 - gob.activeGUI.props.baseProps.value;

				if (gob.lastParent) {
					for (i = 0; i < gob.lastParent.childArr.length; i++) {

						if (isNode[gob.lastParent.childArr[i].props.baseProps.type]) {
							gob.lastParent.childArr[i].props.baseProps.value = 0.0;
						}

						
					}
				}

				gob.activeGUI.props.baseProps.value = tempval;
			}
		}

		

		
	}

	gob.updateActiveGUI = function(xval, mouseUp) {

		

		if (gob.lastHit === 0) {

		}
		else {

			switch (gob.activeGUI.props.baseProps.type) {

					
					case enums.types.number:
						gob.activeGUI.props.baseProps.value = Math.min(Math.max(xval-gob.activeGUI.props.x,0),gob.activeGUI.props.resultWidth)/gob.activeGUI.props.resultWidth;

						

						/*
						if (gob.activeGUI.props.baseProps.actionFunc) {
							gob.callbacks[gob.activeGUI.props.baseProps.actionFunc](gob.activeGUI.props.baseProps.value);
						}
						*/

					break;
					case enums.types.bool:
						

						if (mouseUp) {

							gob.activeGUI.props.baseProps.value = 1.0-gob.activeGUI.props.baseProps.value;

							/*
							if (gob.activeGUI.props.baseProps.actionFunc) {
								gob.callbacks[gob.activeGUI.props.baseProps.actionFunc](gob.activeGUI.props.baseProps.value);
							}
							*/
						}

					break;
					default:
						
						if (mouseUp) {

							
							gob.selectCurNode();
							gob.updateGUIStack();
							gob.guiInvalidated = true;
						}
						
						
					break;
				

			}

			gob.performAction(gob.activeGUI.props.baseProps, mouseUp);


			if ( (!gob.lockOn) || (mouseUp) ) {
				gob.lockOn = true;

				gob.layoutGUI(gob.mainRoot,false);

				//gob.lockOn = false;

				gob.mouseClicked = mouseUp;
			}

			

		}
	}


	gob.objFromNode = function(rootObj) {

		var i;
		var res;
		var isList;

		if (rootObj.childArr.length == 0) {
			return rootObj.props.value;
		}

		isList = (rootObj.props.type%2 != 0);

		if (isList) {
			res = [];
		}
		else {
			res = {};
		}

		for (i = 0; i < rootObj.childArr.length; i++) {

			if (isList) {
				res[i] = gob.objFromNode(rootObj.childArr[i]);
			}
			else {
				res[rootObj.childArr[i].props.label] = gob.objFromNode(rootObj.childArr[i]);
			}

		}

		return res;

		
	}


    gob.createGrad = function(col, baseObj, data) {
		
		var i;
		var j;
		var jPrev;
    	var ind;

    	var mRes;
    	var nRes;
    	var oRes;
    	var lerpVal;
    	var iLerpVal;
    	var sm,sn,so,em,en,eo;

    	var prevPos;
    	var curPos;
    	var curPow;

    	

    	var value;
    	var cl = new CIELCh(0,0,0);

    	i = 0;

    	var numCols = baseObj.length - 2;


    	for (j = 0; j < baseObj.length; j++) {

    		jPrev = Math.max(j-1,0);
    		prevPos = Math.floor(baseObj[jPrev].Position*256.0);
    		curPos = Math.floor(baseObj[j].Position*256.0);

    		while ( (i < 256) && (i < curPos) ) {

    			
    			lerpVal = (i-prevPos)/(curPos-prevPos);
    			iLerpVal = 1.0-lerpVal;


    			startCol = baseObj[jPrev];
    			endCol = baseObj[j];

    			curPow = iLerpVal*startCol.Power*gob.powMax + lerpVal*endCol.Power*gob.powMax;

    			lerpVal = Math.pow(lerpVal,curPow);
    			iLerpVal = 1.0-lerpVal;


    			cl.h = Math.floor(  (iLerpVal*startCol.Hue + lerpVal*endCol.Hue)*360.0  );
    			cl.c = Math.floor(  (iLerpVal*startCol.Saturation + lerpVal*endCol.Saturation)*100.0  );
    			cl.l = Math.floor(  (iLerpVal*startCol.Lightness + lerpVal*endCol.Lightness)*100.0  );


    			value = cl.toRGB();

    			data[col*256 + i] =
    			    (255   << 24) |
    			    (value.r << 16) |
    			    (value.g <<  8) |
    			     value.b;

    			i++;
    		}
    	}

    	

    }


    gob.genPicker = function() {





    	var firstTime = true;

		if (gob.canvData2) {
			firstTime = false;
		}
		else {
			gob.canvData2 = {}
			gob.canvData2.canvas = document.getElementById('canvas2');
			gob.canvData2.canvasWidth = gob.canvData2.canvas.width;
			gob.canvData2.canvasHeight = gob.canvData2.canvas.height;
			gob.canvData2.ctx = gob.canvData2.canvas.getContext('2d');
			gob.canvData2.imageData = gob.canvData2.ctx.getImageData(0, 0, gob.canvData2.canvasWidth, gob.canvData2.canvasHeight);
			gob.canvData2.buf = new ArrayBuffer(gob.canvData2.imageData.data.length);
			gob.canvData2.buf8 = new Uint8ClampedArray(gob.canvData2.buf);
			gob.canvData2.data = new Uint32Array(gob.canvData2.buf);
		}
		

	    var canvas = 		gob.canvData2.canvas;
	    var canvasWidth  = 	gob.canvData2.canvasWidth;
	    var canvasHeight = 	gob.canvData2.canvasHeight;
	    var ctx = 			gob.canvData2.ctx;
	    var imageData = 	gob.canvData2.imageData;
	    var buf = 			gob.canvData2.buf;
	    var buf8 = 			gob.canvData2.buf8;
	    var data = 			gob.canvData2.data;







	    /*
        var canvas = document.getElementById('canvas2');
        var canvasWidth  = canvas.width;
        var canvasHeight = canvas.height;
        var ctx = canvas.getContext('2d');
        var imageData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);
        var buf = new ArrayBuffer(imageData.data.length);
        var buf8 = new Uint8ClampedArray(buf);
        var data = new Uint32Array(buf);
        */

        var value;
        var o;
        var n;
        var m;
        var q;
        var myArr = [0,0,0];
        var lerpVal;

        var xv;
        var yv;

        var xvAbs;
        var yvAbs;

        var qmodH = [0,1,1];
        var qmodC = [2,0,2];
        var qmodL = [1,2,0];

        var cl = new CIELCh(0,0,0);


        if (firstTime) {
        	for (n = 0; n < canvasHeight; n++) {
        	    for (m = 0; m < canvasWidth; m++) {

        	        data[(n) * canvasWidth + m] =
        	            (255   << 24) |
        	            ((m/4) << 16) |
        	            ((m/4) <<  8) |
        	             (m/4);
        	    }
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


						xv = (o)*32+n;
						yv = (m+q*32);

						/*
						xvAbs = Math.abs(xv-gob.palX);
						yvAbs = Math.abs(yv-gob.palY);


						
						if (xvAbs < 20 && yvAbs < 20) {

							if ((yvAbs > 17) || (xvAbs > 17)) {
								cl.h = 0.0;
								cl.c = 0.0;
								cl.l = 100.0;
							}

							
						}
						*/

						/*
						if (
							(
								(xvAbs > 13) &&
								(xvAbs < 16)
							) ||
							(
								(yvAbs > 13) &&
								(yvAbs < 16)
							)
							

						) {
							cl.h = 0.0;
							cl.c = 0.0;
							cl.l = 100.0;
						}
						*/



                        value = cl.toRGB();


                        data[yv * canvasWidth + xv] =
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



        if (gob.palTexture2) {

        }
        else {
        	gob.palTexture2 = new THREE.Texture(canvas);
        	gob.palTexture2.minFilter = THREE.LinearFilter;
        	gob.palTexture2.magFilter = THREE.LinearFilter;
        }

        gob.palTexture2.needsUpdate = true;

        gob.shaders.palFromTex2Shader.uniforms.u_PalPos.value.x = gob.palX;
        gob.shaders.palFromTex2Shader.uniforms.u_PalPos.value.y = gob.palY;

        gob.renderToTarget(
        	"palFromTex2Shader",
        	gob.renderTargets.pal2RT,
        	[
        		gob.palTexture2
        	]
        );

        ctx.beginPath();
        ctx.lineWidth="2";
        ctx.strokeStyle="magenta";
        ctx.rect(gob.palX-19,gob.palY-19,38,38); 
        ctx.stroke();



        gob.isRendering = true;



    }



	gob.updatePalCanv = function(mouseUp) {

		var firstTime = true;

		if (gob.canvData) {
			firstTime = false;
		}
		else {
			gob.canvData = {}
			gob.canvData.canvas = document.getElementById('canvas');
			gob.canvData.canvasWidth = gob.canvData.canvas.width;
			gob.canvData.canvasHeight = gob.canvData.canvas.height;
			gob.canvData.ctx = gob.canvData.canvas.getContext('2d');
			gob.canvData.imageData = gob.canvData.ctx.getImageData(0, 0, gob.canvData.canvasWidth, gob.canvData.canvasHeight);
			gob.canvData.buf = new ArrayBuffer(gob.canvData.imageData.data.length);
			gob.canvData.buf8 = new Uint8ClampedArray(gob.canvData.buf);
			gob.canvData.data = new Uint32Array(gob.canvData.buf);
		}
		

	    var canvas = 		gob.canvData.canvas;
	    var canvasWidth  = 	gob.canvData.canvasWidth;
	    var canvasHeight = 	gob.canvData.canvasHeight;
	    var ctx = 			gob.canvData.ctx;
	    var imageData = 	gob.canvData.imageData;
	    var buf = 			gob.canvData.buf;
	    var buf8 = 			gob.canvData.buf8;
	    var data = 			gob.canvData.data;
	    
	    var o;
	    var n;
	    var m;
	    var lerpVal;

	    var grads = gob.findLabel(gob.mainDat, "Gradients");

	    var omax;

	    var hueVals = [

	        10,
	        40,
	        70,
	        110,
	        170,
	        210,
	        250,
	        290
	    ]

	    if (firstTime) {
	    	for (n = 0; n < 256; n++) {
	    	    for (m = 0; m < 256; m++) {



	    	        data[(n) * canvasWidth + m] =
	    	            (255   << 24) |
	    	            (m << 16) |
	    	            (m <<  8) |
	    	             m;
	    	    }
	    	}
	    }

	    var myobj;


	    

	    for (m = 0; m < grads.childArr.length; m++) {
	    	myobj = gob.objFromNode( grads.childArr[m] );//gob.findLabel(grads.childArr[m],"Steps") );
	    	gob.createGrad(m, myobj, data );
	    }


	    imageData.data.set(buf8);
	    ctx.putImageData(imageData, 0, 0);


		if (gob.palTexture) {

		}
		else {
			gob.palTexture = new THREE.Texture(canvas);
			gob.palTexture.minFilter = THREE.LinearFilter; 
			gob.palTexture.magFilter = THREE.LinearFilter;
		}

		gob.palTexture.needsUpdate = true;

		gob.renderToTarget(
			"palFromTexShader",
			gob.renderTargets.palRT,
			[
				gob.palTexture
			]
		);

		if (gob.timeoutVar) {
			clearTimeout(gob.timeoutVar);
		}

		var to = 500;
		if (mouseUp) {
			to = 100;
		}

		gob.timeoutVar = setTimeout(function(){
			    var tempData = gob.canvData.canvas.toDataURL().split(',')[1];//.substring(22);
			    //0123456789012345678901
				//data:image/png;base64,
				console.log("img data sent");

			    gob.sendMessage(tempData);
		},to);

	    
	}


	gob.renderPal = function(r,g,b,a,x,y) {

		gob.shaders.palShader.uniforms.u_PalCol.value.x = r;
		gob.shaders.palShader.uniforms.u_PalCol.value.y = g;
		gob.shaders.palShader.uniforms.u_PalCol.value.z = b;
		gob.shaders.palShader.uniforms.u_PalCol.value.w = a;
		
		gob.shaders.palShader.uniforms.u_PalCoords.value.x = x;
		gob.shaders.palShader.uniforms.u_PalCoords.value.y = y;


		gob.renderToTarget(
			"palShader",
			gob.renderTargets.palRT,
			[
				
			]
		);

	}


	

	gob.calcVertices = function(rootObj, curMesh) {
		var i;


		if (curMesh.isBG) {
			curMesh.maxInd += 8;
			for (i = 0; i < rootObj.childArr.length; i++) {
				gob.calcVertices(rootObj.childArr[i], curMesh);
			}
		}
		else {
			if (rootObj.childArr.length == 0) {
				curMesh.maxInd += 8*rootObj.props.str.length;
			}
			else {
				for (i = 0; i < rootObj.childArr.length; i++) {
					gob.calcVertices(rootObj.childArr[i], curMesh);
				}
			}
		}

		

		
	}

	gob.layoutGUI = function(rootObj, firstRun) {

		meshText.curInd = 0;
		meshBG.curInd = 0;
		g_curGroup = 1;

		if (firstRun) {
			//meshText.maxInd = 0;
			//meshBG.maxInd = 0;
			//gob.calcVertices(rootObj, meshBG);
			//gob.calcVertices(rootObj, meshText);

			gob.zeroOutVerts(rootObj,meshBG, true);
			gob.zeroOutVerts(rootObj,meshText, true);
		}
		
		gob.traceVals = ["x","y","resultWidth","resultHeight", "fillDir"];

		if (firstRun || gob.guiInvalidated) {
			gob.numberGroups(rootObj,5);
			gob.setGroups(rootObj,0);
			gob.getMinWidths(rootObj);
			gob.setResultWidths(rootObj);
			gob.getMinHeights(rootObj);
		}

		

		gob.addMeshes(rootObj);
		gob.traceVals = [];


		gob.zeroOutVerts(rootObj,meshBG, false);
		gob.zeroOutVerts(rootObj,meshText, false);

		gob.guiInvalidated = false;
		gob.updateBaseRT = true;
		gob.isRendering = true;


	};

	gob.setActiveGUI = function(res, newParent) {



		if (gob.activeGUI === 0) {

		}
		else {
			gob.activeGUI.props.outlineMatId = enums.materials.BlueGray;
		}

		gob.activeGUI = res;

		if (gob.activeGUI === 0) {

		}
		else {

			gob.activeGUI.props.outlineMatId = enums.materials.Gold;
		}

		if (newParent == 0) {
			gob.findParent(0, gob.mainRoot);
		}
		else {
			gob.lastParent = newParent;
		}

		
		if ( isNode[gob.activeGUI.props.baseProps.type] ) {
			gob.lastNode = res;
		}
		

		
	}


	gob.wf("initScene", function() {
		var curShader;
		var i;

		
		// normal x
		// normal y
		// depth
		// tex id

		
		for (i = 0; i < gob.shaderNames.length; i++) {


			j$.ajax({
				url: './shaders/'+gob.shaderNames[i]+'.c',
				success: function(result) {

					var splitText = result.split("$");

					if (splitText.length != 4) {
						gob.doError("Invalid Shader, missing some sections ($)");
					}

					gob.shaders[gob.shaderNames[i]] = {};
					curShader = gob.getShader(i);
					curShader.transparent = false;
					
					
					
					curShader.side = THREE.DoubleSide;
					curShader.depthWrite = false;

					curShader.vertexShader = splitText[0] + splitText[1] + splitText[2];
					curShader.fragmentShader = splitText[0] + splitText[3];
					curShader.uniforms = gob.getUniforms(splitText[0],"uniform");
					curShader.attributes = gob.getUniforms(splitText[1],"attribute");

					gob.materials[gob.shaderNames[i]] = new THREE.ShaderMaterial(curShader);


				},
				error: function() {
					gob.doError("Invalid Shader: " + gob.shaderNames[i]);
				},
				async:   false,
				dataType:"text"
			});

		}

		for (i in g_fonts) {
			if (g_fonts.hasOwnProperty(i)) {
				gob.getKernMap(g_fonts[i]);
			}
		}


		gob.initSceneFinal();
	});

	gob.init = function() {

		console.log("-- gob.init() --");

		var i;
		var curStr = "";
		

		gob.traceLevel = 0;
		gob.tracesAtLevel = 0;
		gob.traceArr = ["",""];

		for (i = 2; i < 100; i++) {
			curStr += "|  ";
			gob.traceArr.push(curStr);
		}

		if (window.WebSocket || window.MozWebSocket) {} else {
			gob.doError("Browser does not support WebSockets");
			return;
		}
		if ( ! Detector.webgl ) {
			gob.doError("Browser does not support WebGL");
		}

		window.onbeforeunload = function() {

			// TODO: Why is this not working?
		    // gob.connection.onclose = function () {}; // disable onclose handler first
		    // gob.connection.close()
		};

		//renderer.deallocateRenderTarget(gob.renderTargets.baseRT);
		// NearestFilter // LinearFilter

		gob.renderTargets.baseRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.LinearFilter, 
			magFilter: THREE.LinearFilter, 
			format: THREE.RGBAFormat
		} );

		gob.renderTargets.idRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.NearestFilter,
			magFilter: THREE.NearestFilter, 
			format: THREE.RGBAFormat
		} );
		gob.renderTargets.extrudeRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.NearestFilter,
			magFilter: THREE.NearestFilter, 
			format: THREE.RGBAFormat
		} );

		gob.renderTargets.layerRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.LinearFilter,
			magFilter: THREE.LinearFilter, 
			format: THREE.RGBAFormat
		} );
		gob.renderTargets.aoRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.LinearFilter,
			magFilter: THREE.LinearFilter, 
			format: THREE.RGBAFormat
		} );

		gob.renderTargets.lightingRT = new THREE.WebGLRenderTarget( gob.bufferWidth, gob.bufferHeight, {
			minFilter: THREE.LinearFilter,
			magFilter: THREE.LinearFilter, 
			format: THREE.RGBAFormat
		} );

		gob.renderTargets.downscaleRT = new THREE.WebGLRenderTarget( gob.bufferWidth/2, gob.bufferHeight/2, {
			minFilter: THREE.NearestFilter,
			magFilter: THREE.NearestFilter, 
			format: THREE.RGBAFormat
		} );


		gob.renderTargets.palRT = new THREE.WebGLRenderTarget( 256, 256, {
			minFilter: THREE.LinearFilter,
			magFilter: THREE.LinearFilter, 
			format: THREE.RGBAFormat
		} );

		gob.renderTargets.pal2RT = new THREE.WebGLRenderTarget( 32, 32, {
			minFilter: THREE.NearestFilter,
			magFilter: THREE.NearestFilter, 
			format: THREE.RGBAFormat
		} );

		

		gob.curFLIndex = 0;

		


		


		for (i = 0; i < gob.fontNames.length; i++) {

			var cfName = gob.fontNames[i];

			g_fonts[cfName].heightRT = new THREE.WebGLRenderTarget( g_fonts[cfName].texture.width,g_fonts[cfName].texture.height, {
				minFilter: THREE.LinearFilter, // NearestFilter // LinearFilter
				magFilter: THREE.LinearFilter, 
				format: THREE.RGBAFormat
			} );
			g_fonts[cfName].normRT = new THREE.WebGLRenderTarget( g_fonts[cfName].texture.width,g_fonts[cfName].texture.height, {
				minFilter: THREE.LinearFilter, 
				magFilter: THREE.LinearFilter, 
				format: THREE.RGBAFormat
			} );
			g_fonts[cfName].normHalfRT = new THREE.WebGLRenderTarget( g_fonts[cfName].texture.width/2,g_fonts[cfName].texture.height/2, {
				minFilter: THREE.LinearFilter, 
				magFilter: THREE.LinearFilter, 
				format: THREE.RGBAFormat
			} );
		}


		var loadFont = function() {

			g_fonts[gob.fontNames[ gob.curFLIndex] ].texData = THREE.ImageUtils.loadTexture( './fonts/'+gob.fontNames[gob.curFLIndex]+'.png', new THREE.UVMapping(), function() {

				gob.curFLIndex++;

				if (gob.curFLIndex == gob.fontNames.length) {
					gob.initScene();
				}
				else {
					loadFont();
				}

			});

		}

		loadFont();

	}

	gob.zeroOutVerts = function(obj,curMesh, firstRun) {
		

		var i;
		var j;
		var k;
		var curShader;
		var curShaders;

		if (curMesh.isBG) {
			curShaders = ["bgShader","bgIdShader"];
		}
		else {
			curShaders = ["textShader","textIdShader"];
		}
		
		
		// zero out the remaining vertices
		
		if (firstRun) {

			for (i = curMesh.curInd; i < curMesh.maxInd; i += 4) {
				curMesh.geometry.vertices.push(
					new THREE.Vector3( 0, 0, 0 ),
					new THREE.Vector3( 0, 0, 0 ),
					new THREE.Vector3( 0, 0, 0 ),
					new THREE.Vector3( 0, 0, 0 )
				);

				curMesh.geometry.faceVertexUvs[0].push([
					new THREE.Vector2( 0, 0 ),
					new THREE.Vector2( 0, 0 ),
					new THREE.Vector2( 0, 0 ),
					new THREE.Vector2( 0, 0 )
				]);

				for (k = 0; k < curShaders.length; k++) {
					for (j = 0; j < a_DataArr.length; j++) {
						gob.shaders[curShaders[k]].attributes[a_DataArr[j]].value.push(

							new THREE.Vector4( 0, 0, 0, 0 ),
							new THREE.Vector4( 0, 0, 0, 0 ),
							new THREE.Vector4( 0, 0, 0, 0 ),
							new THREE.Vector4( 0, 0, 0, 0 )

						);
					}
					
				}
				

				curMesh.geometry.faces.push( new THREE.Face4(i+0, i+1, i+2, i+3) );
			}

		}
		else {
			for (i = curMesh.curInd; i < curMesh.maxInd; i += 4) {

				curInd0 = i;
				curInd1 = i+1;
				curInd2 = i+2;
				curInd3 = i+3;
				curIndDiv4 = Math.floor(curInd0/4);

				curMesh.geometry.vertices[curInd0].set( 0, 0, 0 );
				curMesh.geometry.vertices[curInd1].set( 0, 0, 0 );
				curMesh.geometry.vertices[curInd2].set( 0, 0, 0 );
				curMesh.geometry.vertices[curInd3].set( 0, 0, 0 );

				curMesh.geometry.faceVertexUvs[0][curIndDiv4][0].set( 0, 0 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][1].set( 0, 0 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][2].set( 0, 0 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][3].set( 0, 0 );

				for (k = 0; k < curShaders.length; k++) {
					for (j = 0; j < a_DataArr.length; j++) {
						curShader = curShaders[k];
						gob.shaders[curShader].attributes[a_DataArr[j]].value[curInd0].set( 0, 0, 0, 0 );
						gob.shaders[curShader].attributes[a_DataArr[j]].value[curInd1].set( 0, 0, 0, 0 );
						gob.shaders[curShader].attributes[a_DataArr[j]].value[curInd2].set( 0, 0, 0, 0 );
						gob.shaders[curShader].attributes[a_DataArr[j]].value[curInd3].set( 0, 0, 0, 0 );
					}
				}

			}
		}


		curMesh.geometry.verticesNeedUpdate = true;
		curMesh.geometry.elementsNeedUpdate = true;
		curMesh.geometry.uvsNeedUpdate = true;

		for (i = 0; i < curShaders.length; i++) {
			for (j = 0; j < a_DataArr.length; j++) {
				gob.shaders[curShaders[i]].attributes[ a_DataArr[j] ].needsUpdate = true;
			}
		}

		//curMesh.geometry.morphTargetsNeedUpdate = true;
		//curMesh.geometry.normalsNeedUpdate = true;
		//curMesh.geometry.colorsNeedUpdate = true;
		//curMesh.geometry.tangentsNeedUpdate = true;
	}
	
	gob.drawTextArea = function(objB, curMesh, calcHeight) {

		var obj = objB.props;

		var curShaders;
		var curShader;
		var str = obj.str;
		var x = obj.x;
		var y = obj.y;
		var scale = obj.scale;

		var tempValue;


		obj.maxWidth = obj.resultWidth;
		obj.maxHeight = obj.resultHeight;

		var pMaxW = obj.maxWidth;
		var pMaxH = obj.maxHeight;//maxLines*gob.curFont.metrics.height;
		//var curFont = obj.font;

		var xOff;
		var yOff;

		var totPadding = obj.padding + obj.border;


		var maxW = (pMaxW - totPadding*2.0)/scale;
		var maxH = (pMaxH - totPadding*2.0)/scale;
		var i;
		var j;
		var k;
		var lineArr = str.split('\n');
		var wordArr = [];
		var wordObjArr = [];
		var finalLineArr = [];
		
		
		var curChar;
		var charCode;
		var curWordObj;
		var curWordWidth;
		var curWordStr;
		var curLineWidth;
		var nextCharCode;
		var resSourceX = gob.curFont.texture.width;
		var resSourceY = gob.curFont.texture.height;
		var curLineStr;
		var spaceWidth = gob.curFont.chars[0].width;
		var dashWidth = gob.curFont.chars[13].width;
		var wordMod;

		var hTextAlign = obj.hTextAlign ? obj.hTextAlign:enums.align.left;
		var vTextAlign = obj.vTextAlign ? obj.vTextAlign:enums.align.top;
		var tempWordStart;

		var curInd0;
		var curInd1;
		var curInd2;
		var curInd3;
		var curIndDiv4;

		var dStr;
		var emptyMat;
		var filledMat;
		var outMat;

		var tempH;
		var tempS;
		var tempL;

		for (i = 0; i < lineArr.length; i++) {
			wordArr.push(lineArr[i].split(' '));
		}

		// determine width of each word
		for (i = 0; i < wordArr.length; i++) {
			wordObjArr.push([]);
			
			for (j = 0; j < wordArr[i].length; j++) {

				curWordWidth = 0;
				tempWordStart = 0;
				curWordStr = wordArr[i][j];



				for (k = 0; k < curWordStr.length; k++) {

					charCode = curWordStr.charCodeAt(k);
					curChar = gob.curFont.chars[charCode-32];

					
					if (k < curWordStr.length - 1) {
						nextCharCode = curWordStr.charCodeAt(k+1);
						curWordWidth += curChar.width + gob.curFont.kernMap[charCode*128 + nextCharCode];
					}
					else {
						curWordWidth += curChar.width;
					}


					if (curWordWidth + dashWidth*3 > maxW) {

						dStr = "-";
						if (k+1 == curWordStr.length) {
							dStr = "";
						}

						wordObjArr[i].push({
							wordStr:curWordStr.substring(tempWordStart,k+1)+dStr,
							wordWidth:curWordWidth+dashWidth
						});
						curWordWidth = 0;
						tempWordStart = k+1;


					}

				}

				

				if (curWordWidth > 0) {


					if (tempWordStart == 0) {
						wordObjArr[i].push({
							wordStr:curWordStr,
							wordWidth:curWordWidth
						});
					}
					else {
						wordObjArr[i].push({
							wordStr:curWordStr.substring(tempWordStart,k+1),
							wordWidth:curWordWidth
						});
					}

					
				}
				
			}
		}

		// determine width of each line
		for (i = 0; i < wordObjArr.length; i++) {
			
			curLineStr = "";
			curLineWidth = 0;


			for (j = 0; j < wordObjArr[i].length; j++) {

				curWordObj = wordObjArr[i][j];

				if (curLineWidth + curWordObj.wordWidth + spaceWidth > maxW) {
					
					finalLineArr.push({
						lineStr:curLineStr,
						lineWidth: curLineWidth
					});
					curLineStr = "";
					curLineWidth = 0;
				}
				

				if (curLineWidth == 0) {
					curLineStr += curWordObj.wordStr;
					curLineWidth += curWordObj.wordWidth;
				}
				else {
					curLineStr += " " + curWordObj.wordStr;
					curLineWidth += spaceWidth + curWordObj.wordWidth;
				}
				
			}

			finalLineArr.push({
				lineStr:curLineStr,
				lineWidth: curLineWidth
			});

		}

		// trim off newlines at start/end;

		while ( (finalLineArr.length > 0) && (finalLineArr.last().lineWidth == 0) ) {
			finalLineArr.pop();
		}

		while ( (finalLineArr.length > 0) && (finalLineArr[0].lineWidth == 0) ) {
			finalLineArr.shift();
		}



		if (calcHeight) {
			return Math.min(finalLineArr.length, obj.maxLines)*gob.curFont.metrics.height*scale;
		}
		else {

			filledMat = obj.fillMatId;

			if (curMesh.isBG) {
				emptyMat = obj.bgMatId;
				
				outMat = obj.outlineMatId;
				if (  obj.baseProps.value == 1.0 && isNode[obj.baseProps.type] ) {
					//filledMat = obj.selMatId;
					outMat = enums.materials.SkyBlue;
				}

				if (obj.outlineMatId != emptyMat) {
					outMat = obj.outlineMatId
				}

				

				if (obj.baseProps.type == enums.types.gradientStep || obj.baseProps.type == enums.types.gradientStepList) {
					tempValue = 1.0;

				}
				else {
					tempValue = obj.baseProps.value;
				}

				if (obj.baseProps.type == enums.types.gradientStepList) {
					filledMat = enums.materials[obj.baseProps.label] ;//[obj.baseProps.ind];
				}
				if (obj.baseProps.type == enums.types.gradientStep) {
					

					tempH = Math.floor(objB.props.baseChildArr[0].props.value*31.0);
					tempS = Math.floor(objB.props.baseChildArr[1].props.value*31.0);
					tempL = Math.floor(objB.props.baseChildArr[2].props.value*31.0);

					filledMat = (32768)|(tempH<<10)|(tempS<<5)|(tempL);
				}



			}
			else {
				

				emptyMat = enums.materials.Gold;

				//if (  obj.baseProps.value == 1.0 && isNode[obj.baseProps.type] ) {	
				//	emptyMat = enums.materials.Gold;
				//}
			}

			atArr = atArrs[0];
			atArr[0] =  obj.maxWidth;  atArr[1] = obj.maxHeight;  atArr[2] = obj.groupId;  atArr[3] = emptyMat;
			atArr[4] =  obj.maxWidth;  atArr[5] = obj.maxHeight;  atArr[6] = obj.groupId;  atArr[7] = emptyMat;
			atArr[8] =  obj.maxWidth;  atArr[9] = obj.maxHeight;  atArr[10] = obj.groupId; atArr[11] = emptyMat;
			atArr[12] = obj.maxWidth; atArr[13] = obj.maxHeight; atArr[14] = obj.groupId; atArr[15] = emptyMat;

			atArr = atArrs[1];
			atArr[0] =  tempValue;  atArr[1] = obj.baseDepth;  atArr[2] =  outMat;  atArr[3] = filledMat;
			atArr[4] =  tempValue;  atArr[5] = obj.baseDepth;  atArr[6] =  outMat;  atArr[7] = filledMat;
			atArr[8] =  tempValue;  atArr[9] = obj.baseDepth;  atArr[10] = outMat;  atArr[11] = filledMat;
			atArr[12] = tempValue; atArr[13] = obj.baseDepth;  atArr[14] = outMat; atArr[15] = filledMat;


			if (curMesh.isBG && obj.drawBG) {
				curShaders = ["bgShader","bgIdShader"];

				
				
				gob.drawString(obj, "", x, y, 0, 0, curMesh);
			}
			else {
				curShaders = ["textShader","textIdShader"];
				
				/*
				atArr = atArrs[0];
				atArr[0] = 0.0;  atArr[1] = 0.0;  atArr[2] = obj.groupId;  atArr[3] = 0.0;
				atArr[4] = 0.0;  atArr[5] = 0.0;  atArr[6] = obj.groupId;  atArr[7] = 0.0;
				atArr[8] = 0.0;  atArr[9] = 0.0;  atArr[10] = obj.groupId; atArr[11] = 0.0;
				atArr[12] = 0.0; atArr[13] = 0.0; atArr[14] = obj.groupId; atArr[15] = 0.0;

				atArr = atArrs[1];
				atArr[0] =  0.0;  atArr[1] = 0.0;  atArr[2] =  0.0;  atArr[3] = 0.0;
				atArr[4] =  0.0;  atArr[5] = 0.0;  atArr[6] =  0.0;  atArr[7] = 0.0;
				atArr[8] =  0.0;  atArr[9] = 0.0;  atArr[10] = 0.0; atArr[11] = 0.0;
				atArr[12] = 0.0; atArr[13] = 0.0; atArr[14] =  0.0; atArr[15] = 0.0;
				*/

				
				for (i = 0; i < finalLineArr.length; i++) {
					yOff = i*gob.curFont.metrics.height  + gob.curFont.metrics.descender;//ascender + gob.curFont.metrics.descender;
					switch (hTextAlign) {
						case enums.align.left:
							xOff = 0;
						break;
						case enums.align.center:
							xOff = (maxW-finalLineArr[i].lineWidth)/(2);
						break;
						case enums.align.right:
							xOff = (maxW-finalLineArr[i].lineWidth);
						break;
					}
					

					//if ( (i+1)*gob.curFont.metrics.ascender - gob.curFont.metrics.descender < maxH) {
					if ( i < obj.maxLines )
					{	
						gob.drawString(obj, finalLineArr[i].lineStr, x, y, xOff, yOff, curMesh);
					}
					else {

					}
				}
			}

		}


	}

	gob.drawString = function(obj, str, xBase, yBase, xOff, yOff, curMesh) {
		var curShader;
		var curShaders;
		var scale = obj.scale;
		var isRect = obj.isRect;
		//var curFont = obj.font;

		var i;
		var j;
		var k;
		var curChar;
		var charCode;
		var nextCharCode;

		var curX = xOff;
		var curY = yOff;
		
		var resSourceX = gob.curFont.texture.width;
		var resSourceY = gob.curFont.texture.height;

		var vx;
		var vy;
		var vw;
		var vh;

		var vx1;
		var vy1;
		var vx2;
		var vy2;

		var tx1;
		var ty1;
		var tx2;
		var ty2;

		

		var curInd0;
		var curInd1;
		var curInd2;
		var curInd3;
		var curIndDiv4;


		var curGBLen;

		var strln = str.length;

		var totPadding = obj.padding + obj.border;

		if (curMesh.isBG) {
			curShaders = ["bgShader","bgIdShader"];
			strln = 1;
		}
		else {
			curShaders = ["textShader","textIdShader"];
		}


		for (i = 0; i < strln; i++) {
			

			if (curMesh.isBG) {

				vx1 = xBase;
				vy1 = yBase;
				vx2 = xBase + obj.maxWidth;
				vy2 = yBase + obj.maxHeight;

				tx1 = -1.0;
				ty1 = -1.0;
				tx2 = 1.0;
				ty2 = 1.0;




			}
			else {
				charCode = str.charCodeAt(i);
				curChar = gob.curFont.chars[charCode-32];

				vx = (xBase + (curX + curChar.ox)*scale) + totPadding;
				vy = (yBase + (curY + gob.curFont.metrics.height - (curChar.oy) )*scale) + totPadding;
				vw = (curChar.w)*scale;
				vh = (curChar.h)*scale;

				vx1 = vx;
				vy1 = vy;
				vx2 = vx+vw;
				vy2 = vy+vh;

				tx1 = (curChar.x)/resSourceX;
				ty1 = (resSourceY - (curChar.y) )/resSourceY;
				tx2 = (curChar.x + curChar.w)/resSourceX;
				ty2 = (resSourceY - (curChar.y + curChar.h) )/resSourceY;

				


				if (i < str.length - 1) {
					nextCharCode = str.charCodeAt(i+1);
					curX += curChar.width + gob.curFont.kernMap[charCode*128 + nextCharCode];
				}
			}

			//%%%


			curInd0 = curMesh.curInd;
			curInd1 = curMesh.curInd+1;
			curInd2 = curMesh.curInd+2;
			curInd3 = curMesh.curInd+3;
			curIndDiv4 = Math.floor(curInd0/4);

			/*
			if (firstRun) {
				curMesh.geometry.vertices.push(
					new THREE.Vector3( vx1, vy1, 0 ),
					new THREE.Vector3( vx2, vy1, 0 ),
					new THREE.Vector3( vx2, vy2, 0 ),
					new THREE.Vector3( vx1, vy2, 0 )
				);

				curMesh.geometry.faceVertexUvs[0].push([
					new THREE.Vector2( tx1, ty1 ),
					new THREE.Vector2( tx2, ty1 ),
					new THREE.Vector2( tx2, ty2 ),
					new THREE.Vector2( tx1, ty2 )
				]);

				for (j = 0; j < curShaders.length; j++) {

					for (k = 0; k < a_DataArr.length; k++) {
						atArr = atArrs[k];
						gob.shaders[curShaders[j]].attributes[a_DataArr[k]].value.push(

							new THREE.Vector4( atArr[0], atArr[1], atArr[2], atArr[3] ),
							new THREE.Vector4( atArr[4], atArr[5], atArr[6], atArr[7] ),
							new THREE.Vector4( atArr[8], atArr[9], atArr[10], atArr[11] ),
							new THREE.Vector4( atArr[12], atArr[13], atArr[14], atArr[15] )

						);
					}

					
				}
				

				curGBLen = curMesh.geometry.vertices.length - 4;
				curMesh.geometry.faces.push( new THREE.Face4(curGBLen+0, curGBLen+1, curGBLen+2, curGBLen+3) );
			}
			else {
				
			}
			*/

			if ( curInd0 < curMesh.maxInd ) {
				curMesh.geometry.vertices[curInd0].set( vx1, vy1, 0 );
				curMesh.geometry.vertices[curInd1].set( vx2, vy1, 0 );
				curMesh.geometry.vertices[curInd2].set( vx2, vy2, 0 );
				curMesh.geometry.vertices[curInd3].set( vx1, vy2, 0 );

				curMesh.geometry.faceVertexUvs[0][curIndDiv4][0].set( tx1, ty1 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][1].set( tx2, ty1 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][2].set( tx2, ty2 );
				curMesh.geometry.faceVertexUvs[0][curIndDiv4][3].set( tx1, ty2 );

				for (j = 0; j < curShaders.length; j++) {
					curShader = curShaders[j];
					for (k = 0; k < a_DataArr.length; k++) {
						atArr = atArrs[k];
						gob.shaders[curShader].attributes[a_DataArr[k]].value[curInd0].set( atArr[0], atArr[1], atArr[2], atArr[3] );
						gob.shaders[curShader].attributes[a_DataArr[k]].value[curInd1].set( atArr[4], atArr[5], atArr[6], atArr[7] );
						gob.shaders[curShader].attributes[a_DataArr[k]].value[curInd2].set( atArr[8], atArr[9], atArr[10], atArr[11] );
						gob.shaders[curShader].attributes[a_DataArr[k]].value[curInd3].set( atArr[12], atArr[13], atArr[14], atArr[15] );
					}
					
				}

				//curMesh.geometry.faces[ curIndDiv4 ].set(curInd0, curInd1, curInd2, curInd3);
			}
			else {
				gob.doError("Exceeded Buffer Length (" + curInd0 + " of " + curMesh.maxInd + ")");
				console.log(curMesh);
			}


			curMesh.curInd += 4;

		}

	}

	gob.onWindowResize = function( event ) {

		var i;
		
		
		for (i = 0; i < gob.shaderNames.length; i++) {
			gob.getShader(i).uniforms.u_Resolution.value.x = gob.bufferWidth;//window.innerWidth;
			gob.getShader(i).uniforms.u_Resolution.value.y = gob.bufferHeight;//window.innerHeight;
		}

		gob.shaders.downscaleShader.uniforms.u_TexResolution.value.x = Math.floor(gob.bufferWidth/2);
		gob.shaders.downscaleShader.uniforms.u_TexResolution.value.y = Math.floor(gob.bufferHeight/2);
		gob.shaders.upscaleShader.uniforms.u_TexResolution.value.x = Math.floor(gob.bufferWidth/2);
		gob.shaders.upscaleShader.uniforms.u_TexResolution.value.y = Math.floor(gob.bufferHeight/2);

		gob.shaders.bgShader.uniforms.u_MaxLayers.value = gob.maxLayers/255.0;
		gob.shaders.textShader.uniforms.u_MaxLayers.value = gob.maxLayers/255.0;
		gob.shaders.aoShader.uniforms.u_MaxLayers.value = gob.maxLayers/255.0;
		gob.shaders.aoHighShader.uniforms.u_MaxLayers.value = gob.maxLayers/255.0;

		//renderer.setClearColorHex( 0xffffff, 1 );
		renderer.setSize( gob.bufferWidth, gob.bufferHeight );


	}


	gob.processMessages = function() {

		var curMsg;

		if (gob.waitingForResponse) {

		}
		else {
			if (gob.messageStack.length > 0 && gob.hasConnection && gob.connectionRetryCount < 3) {
				curMsg = gob.messageStack.pop();
				gob.sendMessage(curMsg);
				gob.connectionRetryCount++;
			}
		}

	}

	gob.animate = function() {

		var i;
		var myRt;



		gob.processMessages();



		if (gob.scrollX != gob.targScrollX) {

			gob.scrollX += (gob.targScrollX-gob.scrollX)/2.0;

			if (Math.abs(gob.scrollX-gob.targScrollX) < 2) {
				gob.scrollX = gob.targScrollX;
			}


			gob.isScrolling = 15;
			gob.updateBaseRT = true;
			gob.isRendering = true;
		}




		gob.isScrolling--;

		if (gob.isScrolling < 0) {
			gob.isScrolling = 0;
		}

		//console.log(gob.isScrolling);

		if (gob.isScrolling == 1) {
			
			gob.isRendering = true;
			gob.updateBaseRT = true;
		}

		requestAnimationFrame( gob.animate );

		if (gob.isRendering || gob.autoUpdate || gob.mouseDown || gob.mouseClicked) {




			
			for (i = 0; i < gob.shaderNames.length; i++) {
				
				//console.log(gob.getShader(i));
				//console.log(gob.shaderNames[i]);
				gob.getShader(i).uniforms.u_Zoom.value = zoom;

				

			}
			



			gob.shaders.bgShader.uniforms.u_BorderRad.value = gob.styleSheets.defContH.border;
			gob.shaders.bgIdShader.uniforms.u_BorderRad.value = gob.styleSheets.defContH.border;
			gob.shaders.bgShader.uniforms.u_CornerRad.value = gob.styleSheets.defContH.cornerRad;
			gob.shaders.bgIdShader.uniforms.u_CornerRad.value = gob.styleSheets.defContH.cornerRad;



			if (gob.debugTex) {
				gob.debugTexture();
			}
			else {

				if (gob.updateBaseRT) {


					gob.shaders.textShader.uniforms.u_Scroll.value.x = gob.scrollX;
					gob.shaders.textShader.uniforms.u_Scroll.value.y = gob.scrollY;
					gob.shaders.bgShader.uniforms.u_Scroll.value.x = gob.scrollX;
					gob.shaders.bgShader.uniforms.u_Scroll.value.y = gob.scrollY;

					gob.shaders.textIdShader.uniforms.u_Scroll.value.x = gob.scrollX;
					gob.shaders.textIdShader.uniforms.u_Scroll.value.y = gob.scrollY;
					gob.shaders.bgIdShader.uniforms.u_Scroll.value.x = gob.scrollX;
					gob.shaders.bgIdShader.uniforms.u_Scroll.value.y = gob.scrollY;


					//gl.disable(gl.BLEND);
					//gl.enable(gl.DEPTH_TEST);

					gob.updateBaseRT = false;
					

					meshText.setMaterial(gob.materials.textShader);
					meshBG.setMaterial(gob.materials.bgShader);
					renderer.render( scene, camera, gob.renderTargets.baseRT, true );


					meshText.setMaterial(gob.materials.textIdShader);
					meshBG.setMaterial(gob.materials.bgIdShader);
					renderer.render( scene, camera, gob.renderTargets.idRT, true );

					
					gob.renderLayers();


					gob.renderToTarget(
						"extrudeShader",
						gob.renderTargets.extrudeRT,
						[
							gob.renderTargets.layerRT,
							gob.renderTargets.idRT
						]
					);



					if (gob.mouseDown || (gob.isScrolling > 1) ) {

						gob.renderToTarget(
							"aoShader",
							gob.renderTargets.aoRT,
							[
								gob.renderTargets.layerRT
							]
						);
					}
					else {
						gob.renderToTarget(
							"aoHighShader",
							gob.renderTargets.aoRT,
							[
								gob.renderTargets.layerRT
							]
						);
					}
					
					gob.lockOn = false;

				}
				//else {
					
					gob.shaders.lightingShader.uniforms.u_Time.value = performance.now();

					//gob.renderPal(1.0,1.0,1.0,1.0, 1.0,1.0);

					if (gob.superSample) {
						myRt = gob.renderTargets.lightingRT;
					}
					else {
						myRt = undefined;
					}

					gob.renderToTarget(
						"lightingShader",
						myRt,
						[
							gob.renderTargets.aoRT,
							gob.renderTargets.layerRT,
							gob.renderTargets.extrudeRT,
							gob.renderTargets.palRT,
							gob.palTexture2
						]
					);

					if (gob.superSample) {
						gob.renderToTarget(
							"downscaleShader",
							gob.renderTargets.downscaleRT,
							[
								gob.renderTargets.lightingRT
							]
						);

						gob.renderToTarget(
							"upscaleShader",
							undefined,
							[
								gob.renderTargets.downscaleRT,
								gob.renderTargets.layerRT

							]
						);
					}
					
					

					
				//}

				

				//gob.renderTargets.baseRT
				//renderer.render( scene, camera );


				if (gob.palX != gob.invalidValue) {
					gob.bigPicker();	
				}


			}

			gob.mouseClicked = false;
			gob.isRendering = false;
		}


		

		//stats.update();

		

	}

	gob.renderLayers = function() { //shad, renderTarg, textureArr

		gob.shaders.layerShader.uniforms.u_Texture0.value = gob.renderTargets.baseRT;
		gob.shaders.layerShader.uniforms.u_Time.value = performance.now();
		renderer.render( layerScene, camera, gob.renderTargets.layerRT, true );
	}

	gob.renderToTarget = function(shad, renderTarg, textureArr) {

		var i;
		meshFSQ.material = gob.materials[shad];

		for (i = 0; i < textureArr.length; i++) {
			gob.shaders[shad].uniforms["u_Texture"+i].value = textureArr[i];
		}

		renderer.render( rtScene, camera, renderTarg, true );
	}

	gob.debugTexture = function() {
		meshFSQ.material = gob.materials["debugShader"];
		gob.shaders["debugShader"].uniforms.u_Texture0.value = gob.debugTex;
		renderer.render( rtScene, camera );
	}

	gob.bigPicker = function() {
		meshFSQ.material = gob.materials["pickerShader"];
		gob.shaders["pickerShader"].uniforms.u_Texture0.value = gob.renderTargets.pal2RT;
		renderer.render( rtScene, camera );
	}


	gob.wf("setCurFont", function(fName) {
		gob.curFont = fName;
		gob.shaders.textShader.uniforms.u_Texture0.value = gob.curFont.heightRT;
		gob.shaders.textShader.uniforms.u_Texture1.value = gob.curFont.normHalfRT;

		gob.shaders.textIdShader.uniforms.u_Texture0.value = gob.curFont.heightRT;
		gob.shaders.textIdShader.uniforms.u_Texture1.value = gob.curFont.normHalfRT;


		


		gob.shaders.heightShader.uniforms.u_TexResolution.value.x = gob.curFont.texture.width;
		gob.shaders.heightShader.uniforms.u_TexResolution.value.y = gob.curFont.texture.height;
		gob.shaders.normShader.uniforms.u_TexResolution.value.x = gob.curFont.texture.width;
		gob.shaders.normShader.uniforms.u_TexResolution.value.y = gob.curFont.texture.height;

		gob.shaders.downscaleShader.uniforms.u_TexResolution.value.x = gob.curFont.texture.width;
		gob.shaders.downscaleShader.uniforms.u_TexResolution.value.y = gob.curFont.texture.height;
		gob.shaders.upscaleShader.uniforms.u_TexResolution.value.x = gob.curFont.texture.width;
		gob.shaders.upscaleShader.uniforms.u_TexResolution.value.y = gob.curFont.texture.height;

		gob.renderToTarget(
			"heightShader",
			gob.curFont.heightRT,
			[
				gob.curFont.texData
			]
		);

		gob.renderToTarget(
			"normShader",
			gob.curFont.normRT,
			[
				gob.curFont.texData,
				gob.curFont.heightRT
			]
		);

		gob.renderToTarget(
			"downscaleShader",
			gob.curFont.normHalfRT,
			[
				gob.curFont.normRT
			]
		);

	});


	gob.initEnums = function(jdat) {
		var i;
		var j;
		var count;


		for (i = 0; i < 256; i++) {
			isNode[i] = true;
		}

		isNode[enums.types.number] = false;
		isNode[enums.types.bool] = false;

		var tempDat = jdat.untypedList_root_0.gradientList_Gradients_0;

		var counter = 0;;
		var tempSplit;

		for (i in tempDat) {
			if (tempDat.hasOwnProperty(i)) {
				tempSplit = i.split("_");

				enums.materials[tempSplit[1]] = counter;

				counter++;
			}
		}


		for (i in enums) {

			if ( enums.hasOwnProperty(i) ) {
				count = 0;
				enumStrings[i] = [];
				for (j in enums[i]) {
					if ( enums[i].hasOwnProperty(j) ) {
						enumStrings[i].push(j);
					}

					
				}
			}

			
		}

		gob.enumStrings = enumStrings;

	}
	gob.guiFromJSON = function(rootObj, mBG, mText) {

		// rootObj = gob.mainDat

		var i;
		var curParentProps = rootObj.props;
		var curStr;
		

		var myGUIDat = createNode(
			[
				gob.styleSheets.defContV,
				{baseProps: {label:"",type:enums.types.untyped,value:0},baseChildArr:[]}
			],
			[

			]
		);

		Object.defineProperty(
			rootObj,
			'guiData',
			{
				configurable:true,
				writeable:true,
				get: function() {
					return myGUIDat;
				}
			}
		);

		
		rootObj.guiData = myGUIDat;
		
		mBG.maxInd += 8;


		for (i = 0; i < rootObj.childArr.length; i++) {


			curStr = rootObj.childArr[i].props.label;

			mBG.maxInd += 8;
			mText.maxInd += 8*curStr.length;


			rootObj.guiData.childArr.push(
				createNode(
					{
						doClone:[gob.styleSheets.defContHG,{str:curStr}],
						noClone:{baseProps:rootObj.childArr[i].props,
						baseChildArr:rootObj.childArr[i].childArr}
					}, []
				)
			);
		}

		for (i = 0; i < rootObj.childArr.length; i++) {
			gob.guiFromJSON(rootObj.childArr[i], mBG, mText);
		}

	}

	gob.updateGUIElement = function(curEl) {
		var i;
		var curType;


		for (i = 0; i < curEl.childArr.length; i++) {

			curType = curEl.guiData.childArr[i].props.baseProps.type;

			if (isNode[curType]) {
				if (curEl.guiData.childArr[i].props.baseProps.value == 1) {
					gob.mainRoot.childArr.push(curEl.childArr[i].guiData);
				}
			}

		}

		

		for (i = 0; i < curEl.childArr.length; i++) {

			curType = curEl.guiData.childArr[i].props.baseProps.type;

			if (isNode[curType]) {
				if (curEl.guiData.childArr[i].props.baseProps.value == 1) {

					gob.updateGUIElement(curEl.childArr[i]);
				}
			}

		}

	}

	gob.moveFocus = function(curEl,moveFocus) {
		var i;
		var j;

		var curType;
		var res;
		

		for (i = 0; i < curEl.childArr.length; i++) {

			curType = curEl.guiData.childArr[i].props.baseProps.type;

			if (isNode[curType]) {
				if (curEl.guiData.childArr[i].props.baseProps.value == 1) {

					res = gob.moveFocus(curEl.childArr[i],moveFocus);

					if (res) {
						return true;
					}
				}
			}

		}

		if (moveFocus == 1) {
			for (i = 0; i < curEl.childArr.length; i++) {

				curType = curEl.guiData.childArr[i].props.baseProps.type;

				if (gob.activeGUI == curEl.guiData.childArr[i] && isNode[curType]) {
					gob.setActiveGUI(curEl.childArr[i].guiData.childArr[0], curEl.childArr[i].guiData);
					return true;
				}
			}
		}
		else {
			for (i = 0; i < curEl.childArr.length; i++) {

				curType = curEl.guiData.childArr[i].props.baseProps.type;

				for (j = 0; j < curEl.childArr[i].guiData.childArr.length; j++) {
					if (gob.activeGUI == curEl.childArr[i].guiData.childArr[j] ) {
						gob.setActiveGUI(curEl.guiData.childArr[i], curEl.guiData);
						return true;
					}
				}

				
			}
		}

		

		return false;


	}


	gob.updateGUIStack = function() {
		gob.mainRoot.childArr = [gob.mainDat.guiData];
		gob.updateGUIElement(gob.mainDat);

		gob.mainRoot.props.resultWidth = gob.buttonWidth*gob.mainRoot.childArr.length;

		gob.targScrollX = ( (gob.bufferWidth) - (gob.buttonWidth*(gob.mainRoot.childArr.length))*zoom );
	}

	gob.findLabel = function(rootObj,lab) {
		var i;
		var res = 0;

		if (rootObj.props.label == lab) {
			return rootObj;
		}
		else {
			res = 0;
		}

		for (i = 0; i < rootObj.childArr.length; i++) {
			res = gob.findLabel(rootObj.childArr[i],lab);

			if (res === 0) {

			}
			else {
				return res;
			}


		}

		return res;

	}

	gob.performAction = function(baseProps, mouseUp) {

		var val = baseProps.value;
		

		switch(baseProps.label) {
			case "Hue":
			case "Saturation":
			case "Lightness":
			case "Power":
			case "Position":
				gob.updatePalCanv(mouseUp);
			break;

			case "Down Samp":
				if (mouseUp) {
					if (val == 1.0) {
						gob.superSample = true;
					}
					else {
						gob.superSample = false;
					}
				}
			break;
		}

		if ( isNode[baseProps.type] ) {
			
		}
		else {
			if (mouseUp) {
				
			}
			
			
		}
	}


	gob.wf("initSceneFinal", function() {

		var i;

		container = document.getElementById( 'container' );
		camera = new THREE.Camera();
		camera.position.z = 1;
		scene = new THREE.Scene();
		
		var gbText = new THREE.Geometry();
		gbText.dynamic = true;
		meshText = new THREE.Mesh( gbText, gob.materials.textShader);


		var gbBG = new THREE.Geometry();
		gbBG.dynamic = true;
		meshBG = new THREE.Mesh( gbBG, gob.materials.bgShader);
		
		
		meshBG.isBG = true;
		meshText.isBG = false;



		rtScene = new THREE.Scene();
		layerScene = new THREE.Scene();


		renderer = new THREE.WebGLRenderer();
		renderer.sortObjects = false;
		renderer.autoClear = false;

		var geoBufferFSQ = new THREE.Geometry();
		meshFSQ = new THREE.Mesh( geoBufferFSQ);
		geoBufferFSQ.vertices.push(
			new THREE.Vector3( -1, -1, 0 ),
			new THREE.Vector3(  1, -1, 0 ),
			new THREE.Vector3(  1,  1, 0 ),
			new THREE.Vector3( -1,  1, 0 )
		);
		geoBufferFSQ.faceVertexUvs[0].push([
			new THREE.Vector2( 0, 0 ),
			new THREE.Vector2( 1, 0 ),
			new THREE.Vector2( 1, 1 ),
			new THREE.Vector2( 0, 1 )
		]);
		geoBufferFSQ.faces.push( new THREE.Face4(0, 1, 2, 3) );
		rtScene.add(meshFSQ);

		var geoBufferLayer = new THREE.Geometry();
		
		var curh;
		var curd;
		var curscale;
		var layerScale;
		for (i = 0; i < gob.maxLayers; i++) {
			curh = 2.0*i/gob.bufferHeight;
			curd = i/255.0;
			curscale = 1.0;

			geoBufferLayer.vertices.push(
				new THREE.Vector3( -curscale, -curscale+curh, curd ),
				new THREE.Vector3(  curscale, -curscale+curh, curd ),
				new THREE.Vector3(  curscale,  curscale+curh, curd ),
				new THREE.Vector3( -curscale,  curscale+curh, curd )
			);
			geoBufferLayer.faceVertexUvs[0].push([
				new THREE.Vector2( 0, 0 ),
				new THREE.Vector2( 1, 0 ),
				new THREE.Vector2( 1, 1 ),
				new THREE.Vector2( 0, 1 )
			]);
			geoBufferLayer.faces.push( new THREE.Face4(i*4+0, i*4+1, i*4+2, i*4+3) );
		}
		meshLayer = new THREE.Mesh( geoBufferLayer);
		meshLayer.material = gob.materials["layerShader"];
		layerScene.add(meshLayer);



		
		


		/*
		gob.mainDat = createNode( 

			{
				label:"root",
				type: enums.types.untypedList,
				value: 0
			},
			
			[

				createNode( {label:"Gradients", type:enums.types.gradientList}, [],
					gradArr
				),

				createNode( {label:"Settings", type:enums.types.untypedList}, [

					createNode( {label:"Down Samp", type:enums.types.bool }, [])

				])

			]
		);
		*/


		//var ro = {};
		//var roup = {};
		//gob.packData(gob.mainDat,ro,0);
		///gob.unpackData(ro,roup,true);
		
		// console.log( JSON.stringify(ro, null, "\t") );
		// console.log("------------");
		// console.log("------------");
		// console.log("------------");
		// console.log("------------");
		
		// console.log( JSON.stringify(roup, null, "\t") );
		// console.log("------------");
		// console.log("------------");
		// console.log("------------");
		// console.log("------------");
		// console.log( JSON.stringify(gob.mainDat, null, "\t") );


		gob.loadJSON("../../cdat/lastJSONBuffer.js", function(jdat) {
			gob.mainDat = {};

			gob.unpackData(jdat, gob.mainDat, true);





			//////////////


			gob.initEnums(jdat);


			
			gob.setCurFont(g_fonts["arial_black_regular_96"]);


			gob.styleSheets.defContH = {
				str: 			"",
				drawBG: 		true,
				scale: 			0.25,
				//font: 			gob.curFont,
				hTextAlign:		enums.align.left,
				vTextAlign:		enums.align.top,

				bgMatId: 			enums.materials.BlueGray,
				textMatId: 			enums.materials.Gold,
				fillMatId: 			enums.materials.SkyBlue,
				outlineMatId: 		enums.materials.BlueGray,
				selMatId: 			enums.materials.SkyBlue,

				//curValue: 		0.0,

				groupId: 		0,

				isGroup: 		false,

				fillDir: 		enums.fillDir.horizontal,
				fillRatio: 		1,
				maxLines: 		1,
				fitText: 		true,
				itemsPerLine: 	0,

				cornerRad: 		16,
				margin: 		0,
				border: 		4,
				padding: 		4,
				
				baseDepth: 		5
			};

			
			gob.styleSheets.defContV = combineObjs([
				gob.styleSheets.defContH,
				{
					fillDir: 		enums.fillDir.vertical
				}
			],false);

			
			gob.styleSheets.defContHG = combineObjs([
				gob.styleSheets.defContH,
				{
					isGroup: true
				}
			],false);
			gob.styleSheets.defContVG = combineObjs([
				gob.styleSheets.defContV,
				{
					isGroup: true
				}
			],false);



			//////////////






			gob.mainRoot = createNode( 


				[
					gob.styleSheets.defContH,
					{
						resultWidth:gob.bufferWidth,
						resultHeight:gob.bufferHeight,
						x:0,
						y:0,
						baseProps:{type:enums.types.untypedList, label: "", value: 0},
						baseChildArr:[]
						//,str:"Lorem ipsum dolor sit amet, pro nostrum ullamcorper at\nLorem ipsum dolor sit amet, pro nostrum ullamcorper at"
					}
				],

				[]
				

			);

			
			
			
			meshBG.maxInd = 0;
			meshText.maxInd = 0;

			gob.guiFromJSON(gob.mainDat, meshBG, meshText);
			gob.updateGUIStack();
			gob.layoutGUI(gob.mainRoot,true);


			
			scene.add( meshText );
			scene.add( meshBG );
			
			
			container.appendChild( renderer.domElement );
			//stats = new Stats();
			//stats.domElement.style.position = 'absolute';
			//stats.domElement.style.bottom = '0px';
			//container.appendChild( stats.domElement );


			gob.genPicker();

			gob.updatePalCanv(true);

			


			gob.onWindowResize();
			window.addEventListener( 'resize', gob.onWindowResize, false );












			j$("#container").mousemove(function(e){

				var x = ((e.pageX/gob.bufferWidth)-0.5)*2.0;
				var y = -((e.pageY/gob.bufferHeight)-0.5)*2.0;
				var sx;
				var sy;


				var doPan = false;

				if (gob.lastHit === 0) {
					doPan = true;
				}
				else {
					doPan = isNode[gob.activeGUI.props.baseProps.type];
				}



				if (gob.mouseDown && doPan) {

					if (gob.lastMouseX == null) {
						gob.lastMouseX = e.pageX;
						gob.lastMouseY = e.pageY;
						
					}

					sx = (e.pageX-gob.lastMouseX);// (zoom);
					sy = (e.pageY-gob.lastMouseY);// (zoom);

					gob.scrollX += sx;
					gob.scrollY += sy;

					gob.disTraveledX += sx;
					gob.disTraveledY += sy;
					

					gob.lastMouseX = e.pageX;
					gob.lastMouseY = e.pageY;

					gob.targScrollX = gob.scrollX;

					gob.isScrolling = 15;
					gob.updateBaseRT = true;
					gob.isRendering = true;
				}
				else {
					gob.lastMouseX = null;
					gob.lastMouseY = null;
				}

				gob.isRendering = true;

				//TODO: update rendering on mouse movement instead


				gob.shaders.lightingShader.uniforms.u_MouseCoords.value.x = x;
				gob.shaders.lightingShader.uniforms.u_MouseCoords.value.y = y;

				gob.shaders.pickerShader.uniforms.u_MouseCoords.value.x = x;
				gob.shaders.pickerShader.uniforms.u_MouseCoords.value.y = y;

				//gob.shaders.textShader.uniforms.u_MouseCoords.value.x = e.pageX;
				//gob.shaders.textShader.uniforms.u_MouseCoords.value.y = e.pageY;
				//gob.shaders.bgShader.uniforms.u_MouseCoords.value.x = e.pageX;
				//gob.shaders.bgShader.uniforms.u_MouseCoords.value.y = e.pageY;


				if (gob.mouseDown) {

					gob.updateActiveGUI( (e.pageX - gob.scrollX)/zoom , false);
				}


			});

			j$("#canvas2").mouseup(function(e){

				var newX = Math.floor( (e.pageX-this.offsetLeft)/32.0 )*32.0 + 16.0;
				var newY = Math.floor( (e.pageY-this.offsetTop)/32.0 )*32.0 + 16.0;

				if (gob.palX == newX && gob.palY == newY) {
					gob.palX = gob.invalidValue;
					gob.palY = gob.invalidValue;
				}
				else {
					gob.palX = newX;
					gob.palY = newY;
				}

				

				gob.genPicker();

				



				//console.log(gob.palX, gob.palY);
			});

			j$("#container").mousedown(function(e){
				
				var wRatio = e.pageX/gob.bufferWidth;
				var hRatio = e.pageY/gob.bufferHeight;
				var res;

				var mx;
				var my;
				var myzoom;

				var proc;

				switch (e.which) {
					
					case 1: // left
						if (gob.debugTex) {
							if (gob.curDebugSection == 0.0) {
								if (hRatio < 0.5) {
									if (wRatio < 0.5) {
										gob.curDebugSection = 1.0;
									}
									else {
										gob.curDebugSection = 2.0;
									}
								}
								else {
									if (wRatio < 0.5) {
										gob.curDebugSection = 3.0;
									}
									else {
										gob.curDebugSection = 4.0;
									}
								}
							}
							else {
								gob.curDebugSection = 0.0;
							}

							if (gob.showFullBuffer) {
								gob.curDebugSection = 5.0;
							}


							gob.shaders.debugShader.uniforms.u_Section.value = gob.curDebugSection;

						}
						else {

							proc = true;

							if (gob.palX != gob.invalidValue) {
								if (wRatio < 0.5 && hRatio >= 0.5) {
									proc = false;
								}
							}

							if (proc) {
								myzoom = 1.0/zoom;

								mx = (e.pageX - gob.scrollX)*myzoom;
								my = (e.pageY - gob.scrollY)*myzoom + gob.maxLayers; 
								res = gob.testHit(0, gob.mainRoot, mx, my );

								
								if (res === 0) {
									mx = (e.pageX - gob.scrollX)*myzoom;
									my = (e.pageY - gob.scrollY)*myzoom; 
									res = gob.testHit(0, gob.mainRoot, mx, my );
								}
								

								if (res === 0) {

								}
								else {
									gob.setActiveGUI(res,0);
								}

								gob.lastHit = res;

								
								gob.mouseDown = true;
							}

							

							
						}
					break;
					case 2: // right
						
					break;
					case 3: // middle

					break;
					default: // unknown

					break;


				}

				
				

				
			});

			j$("#container").mouseup(function(e){
				
				var wRatio = e.pageX/gob.bufferWidth;
				var hRatio = e.pageY/gob.bufferHeight;
				var res;
				var proc;

				var vx;
				var vy;

				var myH;
				var myS;
				var myL;

				switch (e.which) {
					
					case 1: // left
						if (gob.debugTex) {
							
						}
						else {

							proc = true;

							if (gob.palX != gob.invalidValue) {
								if (wRatio < 0.5 && hRatio >= 0.5) {
									proc = false;
									
									vx = Math.floor(wRatio*2.0*32.0);
									vy = Math.floor((hRatio-0.5)*2.0*32.0);
									

									switch (gob.palY) {
										case 16:
											myL = vx;
											myS = 31-vy;
											myH = (gob.palX-16)/32;
										break;

										case 48:
											myH = vx;
											myL = 31-vy;
											myS = (gob.palX-16)/32;
										break;

										case 80:
											myH = vx;
											myS = 31-vy;
											myL = (gob.palX-16)/32;
										break;
									}


									console.log(myH,myS,myL);

									if (gob.lastNode != 0) {
										if (gob.lastNode.props.baseProps.type == enums.types.gradientStep) {
											gob.lastNode.props.baseChildArr[0].props.value = myH/31.0;
											gob.lastNode.props.baseChildArr[1].props.value = myS/31.0;
											gob.lastNode.props.baseChildArr[2].props.value = myL/31.0;


											gob.updatePalCanv(true);
											gob.layoutGUI(gob.mainRoot,false);

										}
									}
									



								}
							}




							gob.mouseDown = false;
							gob.lockOn = false;

							if (proc) {
								if (Math.abs(gob.disTraveledX) + Math.abs(gob.disTraveledY) < 50) {
									gob.updateActiveGUI( (e.pageX - gob.scrollX)/zoom, true);
								}
							}
							

							gob.disTraveledX = 0;
							gob.disTraveledY = 0;

							
						}
					break;
					case 2: // right
						
					break;
					case 3: // middle

					break;
					default: // unknown

					break;


				}
				
			});

			j$(document).mousewheel(function(event, delta, deltaX, deltaY) {


				gob.scrollY += deltaY*400.0/gob.scrollSpeed;

				gob.isScrolling = 15;
				gob.updateBaseRT = true;
				gob.isRendering = true;

				// if (gob.palX != gob.invalidValue) {
					

				// 	if (gob.shiftDown) {
						
				// 		gob.palY += deltaX*32.0;


				// 		if (gob.palY < 16.0) {
				// 			gob.palY = 16.0;
				// 		}  
				// 		if (gob.palY > 80.0) {
				// 			gob.palY = 80.0;
				// 		}
				// 	}
				// 	else {
				// 		gob.palX += deltaY*32.0;

				// 		if (gob.palX < 16.0) {
				// 			gob.palX = 16.0;
				// 		}  
				// 		if (gob.palX > 1008.0) {
				// 			gob.palX = 1008.0;
				// 		}
				// 	}

					

				// 	gob.genPicker();
				// }
				






				/*
				zoom += deltaY/gob.scrollSpeed;

				if (zoom < 0.25) {
					zoom = 0.25;
				}

				if (gob.scrollY > gob.maxLayers) {
					//gob.scrollY = gob.maxLayers;
				}

				gob.isScrolling = 15;
				gob.updateBaseRT = true;
				gob.isRendering = true;

				*/
				

			});


			j$(document).keydown(function(e) {

				var code = (e.keyCode ? e.keyCode : e.which);

				switch (code) {
					case 16: //shift
						gob.shiftDown = true;
					break;
				}

			});
			j$(document).keyup(function(e) {

				var code = (e.keyCode ? e.keyCode : e.which);

				var ind;

				switch (code) {

					case 27: //escape
						if (gob.palX != gob.invalidValue) {
							gob.palX = gob.invalidValue;
							gob.genPicker();
						}
					break;

					case 16: //shift
						gob.shiftDown = false;
					break;
					case 37: //left

						//if (isNode[gob.activeGUI.props.baseProps.type]) {
							

							
							gob.moveFocus(gob.mainDat,-1);
							

							if (gob.activeGUI.props.baseProps.value == 1) {
								gob.selectCurNode();
							}
							else {
								
							}

							gob.updateGUIStack();


							gob.guiInvalidated = true;
							gob.layoutGUI(gob.mainRoot,false);
						//}

					break;
					
					case 39: //right
						
						if (isNode[gob.activeGUI.props.baseProps.type]) {
							if (gob.activeGUI.props.baseProps.value == 0) {
								gob.selectCurNode();
								gob.updateGUIStack();
								
							}
							else {
								
							}

													
							gob.moveFocus(gob.mainDat,1);
							//gob.updateGUIStack();



							gob.guiInvalidated = true;
							gob.layoutGUI(gob.mainRoot,false);
						}
						
					break;
					case 38: //up
						ind = 0;

						if (gob.lastParent === 0 || gob.activeGUI == 0) {
							
						}
						else {
							while (gob.lastParent.childArr[ind] != gob.activeGUI) {
								ind--;
								if (ind < 0) {
									ind = gob.lastParent.childArr.length-1;
								}
							}
							ind--;

							if (ind < 0) {
								ind = gob.lastParent.childArr.length-1;
							}


							gob.setActiveGUI(gob.lastParent.childArr[ind],gob.lastParent);
							gob.layoutGUI(gob.mainRoot,false);
							
						}

					break;
					case 40: //down
						ind = 0;

						if (gob.lastParent === 0 || gob.activeGUI == 0) {

						}
						else {
							while (gob.lastParent.childArr[ind] != gob.activeGUI) {
								ind++;
								if (ind >= gob.lastParent.childArr.length) {
									ind = 0;
								}
							}
							ind++;

							if (ind >= gob.lastParent.childArr.length) {
								ind = 0;
							}


							gob.setActiveGUI(gob.lastParent.childArr[ind],gob.lastParent);
							gob.layoutGUI(gob.mainRoot,false);
						}

						
					break;
					
				}

			});


			j$(document).keypress(function(e) {

				var code = (e.keyCode ? e.keyCode : e.which);
				var msgVal = {};
				
				if ( code == "a".charCodeAt(0) ) {
					gob.autoUpdate = !gob.autoUpdate;
					console.log("Auto Update: " + gob.autoUpdate);
				}

				if ( code == "d".charCodeAt(0) ) {
					gob.showFullBuffer = !gob.showFullBuffer;
					console.log("Show Full Buffer:" + gob.showFullBuffer);
				}

				if ( code == "z".charCodeAt(0) ) {
					zoom = 1;
					gob.updateBaseRT = true;
					gob.isRendering = true;
					console.log("Zoom reset");
				}
				
				if ( code == "s".charCodeAt(0) ) {

					
					gob.packData(gob.mainDat,msgVal,0);
					gob.sendMessage(msgVal);
					console.log("Sent JSON for Save");
				}

			});



			gob.animate();









		});

	});

	gob.wf("setFont", function(val) {
		//testObj.scale = val;
		gob.setCurFont(val);		
	});

	gob.wf("getKernMap", function(fontObj) {
		var i;
		var curKern;
		var totSize = 128*128;

		fontObj.kernMap = new Array(totSize);

		for (i = 0; i < totSize; i++) {
			fontObj.kernMap[i] = 0;
		}

		if (fontObj.kernings) {
			for (i = 0; i < fontObj.kernings.length; i++) {
				curKern = fontObj.kernings[i];

				fontObj.kernMap[ curKern.from.charCodeAt(0)*128 + curKern.to.charCodeAt(0) ] = -curKern.offset;

			}
		}
		

	});

	gob.getUniforms = function(str, varType) {
		var strArr = str.split(';\n');
		var resObj = {};
		var i;
		var uInd;
		var newStr;
		var curName;
		var strArr2;

		for (i = 0; i < strArr.length; i++) {
			uInd = strArr[i].indexOf(varType);

			if (uInd > -1) {
				newStr = strArr[i].substr(uInd);

				strArr2 = newStr.split(' ');

				if (strArr2.length == 3) {
					curType = strArr2[1];
					curName = strArr2[2];

					if (varType == "uniform") {
						switch(curType) {
							case "float":
								resObj[curName] = { type: "f", value: 0.0 };
							break;
							case "vec2":
								resObj[curName] = { type: "v2", value: new THREE.Vector2() };
							break;
							case "vec3":
								resObj[curName] = { type: "v3", value: new THREE.Vector3() };
							break;
							case "vec4":
								resObj[curName] = { type: "v4", value: new THREE.Vector4() };
							break;
							case "sampler2D":
								resObj[curName] = { type: "t" };//, value: curMap };
							break;
							default:
								gob.doError("Invalid type: " + curType);
							break;
						}
					}
					else {
						switch(curType) {
							case "float":
								resObj[curName] = { type: "f", value: [] };
							break;
							case "vec2":
								resObj[curName] = { type: "v2", value: [] };
							break;
							case "vec3":
								resObj[curName] = { type: "v3", value: [] };
							break;
							case "vec4":
								resObj[curName] = { type: "v4", value: [] };
							break;
							default:
								gob.doError("Invalid type: " + curType);
							break;
						}
					}

					

				}
				else {
					gob.doError('Invalid uniform: ' + newStr);
				}
			}
		}

		return resObj;
	};


	
	j$(document).ready(function(){
		document.oncontextmenu = document.body.oncontextmenu = function() {return false;}
		gob.init();
	})
	



});
