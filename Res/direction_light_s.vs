#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 position;
attribute vec4 texcoord;
attribute vec4 normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;

uniform mat4 LightViewMatrix;
uniform mat4 LightProjectionMatrix;

varying vec4 V_Normal;
varying vec4 V_WorldPos;
varying vec4 V_LightSpaceFragPos;

void main(){
    V_WorldPos = ModelMatrix * position;
    V_LightSpaceFragPos = LightProjectionMatrix * LightViewMatrix * V_WorldPos;
    V_Normal = IT_ModelMatrix * normal;
    gl_Position = ProjectionMatrix * ViewMatrix * V_WorldPos;
}
