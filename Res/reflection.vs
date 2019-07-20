#ifdef GL_ES
precision mediump float;
#endif
attribute vec4 position;
attribute vec4 normal;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;
varying vec4 V_WorldPos;
varying vec4 V_Normal;
void main()
{
	V_WorldPos=ModelMatrix*position;
	V_Normal=IT_ModelMatrix*normal;
	gl_Position=ProjectionMatrix*ViewMatrix*ModelMatrix*position;
}