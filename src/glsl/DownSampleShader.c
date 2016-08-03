// result fbo
uniform sampler2D Texture0;
uniform vec2 bufferDimSrc;
uniform vec2 bufferDimDst;


varying vec2 v_TexCoords;

float volumePitch;
int iVolumePitch;	

$

void main()
{
    gl_Position = gl_Vertex;
    v_TexCoords = gl_MultiTexCoord0.xy;
    volumePitch = bufferDimDst.x;
    iVolumePitch = int(volumePitch);

}

$

void main()
{

	int i;
	int j;

	vec3 newCoords = vec3(0.0);

	j = int( volumePitch*volumePitch*TexCoord0.y );
	
	newCoords.x = TexCoord0.x;
	newCoords.y = float(intMod(j,iVolumePitch))/volumePitch;
	newCoords.z = float(j/iVolumePitch)/volumePitch;


    vec4 res = texture2D( Texture0, v_TexCoords );
    res = max(res,texture2D( Texture0, v_TexCoords+vec2(0.0/bufferDim.x,1.0/bufferDim.y) ));
    res = max(res,texture2D( Texture0, v_TexCoords+vec2(1.0/bufferDim.x,0.0/bufferDim.y) ));
    res = max(res,texture2D( Texture0, v_TexCoords+vec2(1.0/bufferDim.x,1.0/bufferDim.y) ));

    gl_FragData[0] = res;

}
