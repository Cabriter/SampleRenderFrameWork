#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 position;
attribute vec4 texcoord;
attribute vec4 normal;
attribute vec4 tangent;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;

uniform mat4 LightViewMatrix;
uniform mat4 LightProjectionMatrix;

varying vec4 V_Normal;
varying vec4 V_WorldPos;
varying vec4 V_LightSpaceFragPos;
varying vec4 V_Texcoord;
varying mat3 V_TBN;

void main(){
    vec3 t = normalize(vec3(ModelMatrix * vec4(tangent.xyz,0.0)));
    vec3 n = normalize(vec3(IT_ModelMatrix * normal));
    vec3 b = cross(n , t);
    
    mat3 nbt = mat3(t,b,n);//inverse transpose
    
//    mat3 yuv = mat3(
//    vec3(yuv_matrix[0].x, yuv_matrix[1].x, yuv_matrix[2].x),
//    vec3(yuv_matrix[0].y, yuv_matrix[1].y, yuv_matrix[2].y),
//    vec3(yuv_matrix[0].z, yuv_matrix[1].z, yuv_matrix[2].z));
    V_TBN = mat3(
        vec3(nbt[0].x, nbt[1].x, nbt[2].x),
        vec3(nbt[0].y, nbt[1].y, nbt[2].y),
        vec3(nbt[0].z, nbt[1].z, nbt[2].z));
    V_WorldPos = ModelMatrix * position;
    V_LightSpaceFragPos = LightProjectionMatrix * LightViewMatrix * V_WorldPos;
    V_Normal = IT_ModelMatrix * normal;
    V_Texcoord = texcoord;
    gl_Position = ProjectionMatrix * ViewMatrix * V_WorldPos;
}
