
#ifdef GL_ES
precision mediump float
#endif

attribute vec4 position;
attribute vec4 texcoord;
attribute vec4 normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;

uniform vec4 U_AmbientMaterial;
uniform vec4 U_DiffuseMaterial;
uniform vec4 U_SpecularMaterial;

uniform vec4 U_AmbientLight;
uniform vec4 U_DiffuseLight;
uniform vec4 U_SpecularLight;

uniform vec4 U_LightPos;
uniform vec4 U_CameraPos;

varying vec4 V_Color;

void main(){
    vec3 L = U_LightPos.xyz;
    L = normalize(L);
    vec3 n = normalize((IT_ModelMatrix * normal).xyz);
    float diffuseIntensity = max(0.0,dot(L,n));
    vec4 diffuseColor = U_DiffuseLight * U_DiffuseMaterial * diffuseIntensity;
    vec4 specularColor = vec4(0.0,0.0,0.0,0.0);
    if(diffuseIntensity > 0.0){
        vec3 worldPos = (ModelMatrix * position).xyz;
        vec3 viewDir = normalize(U_CameraPos.xyz - worldPos);
        vec3 halfVector = normalize(L + viewDir);
        specularColor = U_SpecularLight * U_SpecularMaterial * pow(max(0.0,dot(n,halfVector)),4.0);
    }
    V_Color = U_AmbientMaterial * U_AmbientLight + diffuseColor + specularColor;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;
}
