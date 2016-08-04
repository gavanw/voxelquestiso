
varying vec3 TexCoord0;

$

void main() {
	TexCoord0 = gl_MultiTexCoord0.xyz;
	gl_Position = gl_Vertex;
}

$

void main() {
	gl_FragData[0] = vec4(TexCoord0.xyz,0.0);
}
