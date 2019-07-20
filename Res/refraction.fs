#ifdef GL_ES
precision mediump float;
#endif
uniform vec4 U_CameraPos;
varying vec4 V_WorldPos;
varying vec4 V_Normal;
uniform samplerCube U_Texture;
void main()
{
	vec3 eyeVec=normalize(V_WorldPos.xyz-U_CameraPos.xyz);
	vec3 n=normalize(V_Normal.xyz);
	vec3 r=refract(eyeVec,n,1.0/1.52);
	vec4 color=textureCube(U_Texture,r);
	gl_FragColor=color;
}