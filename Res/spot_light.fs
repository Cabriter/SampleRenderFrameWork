#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 U_AmbientMaterial;
uniform vec4 U_DiffuseMaterial;
uniform vec4 U_SpecularMaterial;

uniform vec4 U_AmbientLight;
uniform vec4 U_DiffuseLight;
uniform vec4 U_SpecularLight;

uniform vec4 U_LightPos;
uniform vec4 U_LightDirection;
uniform vec4 U_LightOption;
uniform vec4 U_CameraPos;

varying vec4 V_Normal;
varying vec4 V_WorldPos;

void main(){
    vec3 L = vec3(0.0,0.0,0.0);
    vec3 n = normalize(V_Normal.xyz);
    float distance = 0.0;
    float attenuation = 1.0;
    float constantFactor = 0.5;
    float linearFactor = 0.3;
    float expFactor = 0.1;
    
    L = U_LightPos.xyz - V_WorldPos.xyz;
    distance = length(L);
    attenuation = 1.0/(constantFactor + linearFactor * distance + expFactor * distance * distance);
    L = normalize(L);
    float diffuseIntensity = max(0.0,dot(L,n));
    //vec4 diffuseColor = U_DiffuseLight * U_DiffuseMaterial * diffuseIntensity * attenuation;
    vec4 specularColor = vec4(0.0,0.0,0.0,0.0);
    
    if(diffuseIntensity > 0.0){
        vec3 spot_direction = normalize(U_LightDirection.xyz);
        float currentCosThta = max(0.0,dot(-L,spot_direction));
        float radianCutoff = U_LightDirection.w * 3.14 / 180.0;
        float cosThta = cos(radianCutoff);
        if(currentCosThta > cosThta){
            diffuseIntensity = pow(currentCosThta,U_LightOption.x) * U_LightOption.y;
        }else{
            diffuseIntensity = 0.0;
        }
    }
    if(diffuseIntensity > 0.0){
        vec3 worldPos = V_WorldPos.xyz;
        vec3 viewDir = normalize(U_CameraPos.xyz - worldPos);
        vec3 reflectDir = reflect(-L,n);
        reflectDir = normalize(reflectDir);
        specularColor = U_SpecularLight * U_SpecularMaterial * pow(max(0.0,dot(viewDir,reflectDir)),4.0);
    }
    vec4 diffuseColor = U_DiffuseLight * U_DiffuseMaterial * diffuseIntensity * attenuation;
    gl_FragColor = U_AmbientMaterial * U_AmbientLight + diffuseColor + specularColor;
}
