#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D U_ShadowMap;
uniform sampler2D U_Texture;
uniform sampler2D U_NormalMap;

uniform vec4 U_AmbientMaterial;
uniform vec4 U_DiffuseMaterial;
uniform vec4 U_SpecularMaterial;

uniform vec4 U_AmbientLight;
uniform vec4 U_DiffuseLight;
uniform vec4 U_SpecularLight;

uniform vec4 U_LightPos;
uniform vec4 U_CameraPos;

varying vec4 V_Normal;
varying vec4 V_WorldPos;
varying vec4 V_LightSpaceFragPos;
varying vec4 V_Texcoord;
varying mat3 V_TBN;

float CalculateShadow(){
    vec3 fragPos = V_LightSpaceFragPos.xyz / V_LightSpaceFragPos.w;
    fragPos = fragPos * 0.5 + vec3(0.5);
    float depthInShadowMap = texture2D(U_ShadowMap,fragPos.xy).r;
    float currentDepth = fragPos.z;
    float shadow = (currentDepth - 0.001)>depthInShadowMap?1.0:0.0;
    return shadow;
}

void main(){
    vec3 RealNormal = texture2D(U_NormalMap,V_Texcoord.xy).rgb;
    RealNormal = normalize(RealNormal * 2.0 - vec3(1.0));
    vec3 worldNormal = normalize(V_TBN * RealNormal);//TBN is bug
    MyApp/scene.cpp
    vec4 basecolor = texture2D(U_Texture,V_Texcoord.xy);
    vec3 L = U_LightPos.xyz;
    L = normalize(L);
    vec3 n = normalize(RealNormal.xyz);//worldNormal
    float diffuseIntensity = max(0.0,dot(L,n));
    vec4 diffuseColor = U_DiffuseLight * U_DiffuseMaterial * diffuseIntensity;
    vec4 specularColor = vec4(0.0,0.0,0.0,0.0);
    
    if(diffuseIntensity > 0.0){
        vec3 reflectDir = reflect(-L,n);
        reflectDir = normalize(reflectDir);
        vec3 worldPos = V_WorldPos.xyz;
        vec3 viewDir = normalize(U_CameraPos.xyz - worldPos);
        specularColor = U_SpecularLight * U_SpecularMaterial * pow(max(0.0,dot(viewDir,reflectDir)),32.0);
    }
    vec4 color = U_AmbientMaterial * U_AmbientLight + diffuseColor + specularColor;
    
    color = basecolor + color * vec4(vec3(1.0 - CalculateShadow()),1.0);
    gl_FragColor = color;
}
