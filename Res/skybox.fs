#ifdef GL_ES
precision mediump float;
#endif
varying vec3 V_Texcoord;
uniform samplerCube U_Texture;
void main()
{
	gl_FragColor=textureCube(U_Texture,normalize(V_Texcoord));
}