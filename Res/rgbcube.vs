#ifdef GL_ES
precision mediump float;
#endif
attribute vec4 position;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
varying vec4 V_Color;
void main()
{
	V_Color=vec4(position.x+0.5,position.y+0.5,position.z+0.5,1.0);
	gl_Position=ProjectionMatrix*ViewMatrix*ModelMatrix*position;
}