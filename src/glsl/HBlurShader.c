// credit: http://xissburg.com/faster-gaussian-blur-in-glsl/

// result fbo
uniform sampler2D Texture0;
uniform float cameraZoom;
uniform vec2 bufferDim;
//uniform float blurAmount;

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[14];

$
 
void main()
{
    gl_Position = gl_Vertex;
    v_texCoord = gl_MultiTexCoord0.xy;

    float newZoom = min(cameraZoom,1.0);

    v_blurTexCoords[ 0] = v_texCoord + vec2(-0.028, 0.0)*newZoom;
    v_blurTexCoords[ 1] = v_texCoord + vec2(-0.024, 0.0)*newZoom;
    v_blurTexCoords[ 2] = v_texCoord + vec2(-0.020, 0.0)*newZoom;
    v_blurTexCoords[ 3] = v_texCoord + vec2(-0.016, 0.0)*newZoom;
    v_blurTexCoords[ 4] = v_texCoord + vec2(-0.012, 0.0)*newZoom;
    v_blurTexCoords[ 5] = v_texCoord + vec2(-0.008, 0.0)*newZoom;
    v_blurTexCoords[ 6] = v_texCoord + vec2(-0.004, 0.0)*newZoom;
    v_blurTexCoords[ 7] = v_texCoord + vec2( 0.004, 0.0)*newZoom;
    v_blurTexCoords[ 8] = v_texCoord + vec2( 0.008, 0.0)*newZoom;
    v_blurTexCoords[ 9] = v_texCoord + vec2( 0.012, 0.0)*newZoom;
    v_blurTexCoords[10] = v_texCoord + vec2( 0.016, 0.0)*newZoom;
    v_blurTexCoords[11] = v_texCoord + vec2( 0.020, 0.0)*newZoom;
    v_blurTexCoords[12] = v_texCoord + vec2( 0.024, 0.0)*newZoom;
    v_blurTexCoords[13] = v_texCoord + vec2( 0.028, 0.0)*newZoom;
}

$

void main()
{
    vec4 res = vec4(0.0);
    res += texture2D(Texture0, v_blurTexCoords[ 0])*0.0044299121055113265;
    res += texture2D(Texture0, v_blurTexCoords[ 1])*0.00895781211794;
    res += texture2D(Texture0, v_blurTexCoords[ 2])*0.0215963866053;
    res += texture2D(Texture0, v_blurTexCoords[ 3])*0.0443683338718;
    res += texture2D(Texture0, v_blurTexCoords[ 4])*0.0776744219933;
    res += texture2D(Texture0, v_blurTexCoords[ 5])*0.115876621105;
    res += texture2D(Texture0, v_blurTexCoords[ 6])*0.147308056121;
    res += texture2D(Texture0, v_texCoord         )*0.159576912161;
    res += texture2D(Texture0, v_blurTexCoords[ 7])*0.147308056121;
    res += texture2D(Texture0, v_blurTexCoords[ 8])*0.115876621105;
    res += texture2D(Texture0, v_blurTexCoords[ 9])*0.0776744219933;
    res += texture2D(Texture0, v_blurTexCoords[10])*0.0443683338718;
    res += texture2D(Texture0, v_blurTexCoords[11])*0.0215963866053;
    res += texture2D(Texture0, v_blurTexCoords[12])*0.00895781211794;
    res += texture2D(Texture0, v_blurTexCoords[13])*0.0044299121055113265;

    gl_FragData[0] = vec4(res.rgb,1.0);

}
