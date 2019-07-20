#ifdef GL_ES
precision mediump float;
#endif
varying vec2 V_Texcoord;
uniform sampler2D U_Texture;
void main()
{
	gl_FragColor=texture2D(U_Texture,V_Texcoord);
}