#version 400

const int NUM_DIRECTIONAL_LIGHTS = 4;
const int NUM_POINT_LIGHTS = 10;
const int NUM_SPOT_LIGHTS = 4;

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 texCoords;
in vec4 directionalLightspacePosition[NUM_DIRECTIONAL_LIGHTS];

struct DirectionalLight {

    vec3 color;
    vec3 colorAmbient;

    vec3 direction;

    float falloffConstant;
    float falloffLinear;
    float falloffQuadratic;
};

struct PointLight {

    vec3 color;
    vec3 colorAmbient;

    vec3 position;

    float falloffConstant;
    float falloffLinear;
    float falloffQuadratic;

    float farPlaneDistance;
};

struct SpotLight {

    vec3 color;
    vec3 colorAmbient;

    vec3 position;
    vec3 direction;

    float falloffConstant;
    float falloffLinear;
    float falloffQuadratic;
    float innerCutoff; // cos of inner angle
    float outerCutoff; // cos of outer angle
};

// Builtin uniforms
uniform DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];
uniform sampler2DArrayShadow directionalDepthMaps;
uniform int numDirectionalLights = 0;

uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform samplerCubeArrayShadow depthCubeMaps;
uniform int numPointLights = 0;

uniform SpotLight spotLights[NUM_SPOT_LIGHTS];
uniform int numSpotLights = 0;

uniform vec3 viewPosition;

// Custom uniforms
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform vec3 albedoColor = vec3(1,1,1);
uniform float metallicMultiplier = 1;
uniform float roughnessMultiplier = 1;

const float PI = 3.14159265359;

out vec4 fragmentColor;

vec3 CalculateDirectionalLightContribution(int i, vec3 normal, vec3 viewDirection, vec3 albedo, float metallic, float roughness);
//vec3 CalculatePointLightContribution(int i, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
//vec3 CalculateSpotLightContribution(SpotLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
float CalculateDirectionalShadowMultiplier(int i, float biasMultiplier);
float CalculatePointShadowMultiplier(int i, vec3 fromLight, float distance, float biasMultiplier);

void main() {

    vec3 normal = normalize(worldNormal);
    vec3 viewDirection = normalize(viewPosition - worldPosition);

    vec3  albedo    = albedoColor         * vec3(texture(albedoMap, texCoords));
    float metallic  = metallicMultiplier  * texture(metallicMap , texCoords).r;
    float roughness = roughnessMultiplier * texture(roughnessMap, texCoords).r;

    vec3 color = vec3(0,0,0);

    for (int i = 0; i < numDirectionalLights; ++i) {
        color += CalculateDirectionalLightContribution(i, normal, viewDirection, albedo, metallic, roughness);
    }

//    for (int i = 0; i < numPointLights; ++i) {
//        color += CalculatePointLightContribution(i, normal, viewDirection, materialDiffuse, materialSpecular);
//    }

//    for (int i = 0; i < numSpotLights; ++i) {
//        color += CalculateSpotLightContribution(spotLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
//    }

	fragmentColor = vec4(color, 1);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {

    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {

    float r = roughness + 1.0;
    float k = r * r / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 CalculateDirectionalLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness) {

    DirectionalLight light = directionalLights[i];

    vec3 L = light.direction;
    vec3 H = normalize(V + L);
    float NdotL = dot(N, L);
    float NdotV = dot(N, V);

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);
    vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), mix(vec3(0.04), albedo, metallic));

    vec3  nominator   = NDF * G * F;
    float denominator = 4 * max(NdotV, 0.0) * max(NdotL, 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3  specular = nominator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    vec3 brdf = (kD * albedo / PI + specular);

    float shadowMultiplier = CalculateDirectionalShadowMultiplier(i, 1 - NdotL);
    return brdf * light.color * NdotL * shadowMultiplier;
}

//vec3 CalculatePointLightContribution(int i, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {
//
//    PointLight light = pointLights[i];
//
//    vec3 ambient = light.colorAmbient * materialDiffuse;
//
//    vec3 delta = light.position - worldPosition;
//    float distance = length(delta);
//    vec3 lightDirection = delta / distance;
//
//    float normalDotDirection = dot(normal, lightDirection);
//    vec3 diffuse = max(0, normalDotDirection) * materialDiffuse;
//
//    vec3 reflectedDirection = reflect(-lightDirection, normal);
//    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * materialSpecular;
//
//    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);
//    float shadowMultiplier = CalculatePointShadowMultiplier(i, -delta, distance, 1 - normalDotDirection);
//    //return texture(depthMap, -delta).r * vec3(1);
//    //return shadowMultiplier * vec3(1) / numPointLights;
//    return ambient + shadowMultiplier * attenuation * (diffuse + specular) * light.color;
//}
//
//vec3 CalculateSpotLightContribution(SpotLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {
//
//    vec3 ambient = light.colorAmbient * materialDiffuse;
//
//    vec3 delta = light.position - worldPosition;
//    float distance = length(delta);
//    vec3 lightDirection = delta / distance;
//
//    vec3 diffuse = max(0, dot(normal, lightDirection)) * light.color * materialDiffuse;
//
//    vec3 reflectedDirection = reflect(-lightDirection, normal);
//    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * materialSpecular;
//
//    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);
//    attenuation *= smoothstep(light.outerCutoff, light.innerCutoff, dot(-lightDirection, light.direction));
//
//    return ambient + attenuation * (diffuse + specular);
//}

float CalculateDirectionalShadowMultiplier(int i, float biasMultiplier) {

    vec4 lightspacePosition = directionalLightspacePosition[i];
    vec3 projected = (lightspacePosition.xyz / lightspacePosition.w) * 0.5 + 0.5;
    float currentDepth = projected.z;
    if (currentDepth > 1.f)
        return 1;

    float bias = max(0.002 * biasMultiplier, 0.001);
    return texture(directionalDepthMaps, vec4(projected.xy, i, currentDepth - bias));
}

float CalculatePointShadowMultiplier(int i, vec3 fromLight, float distance, float biasMultiplier) {

    float bias = max(0.1 * biasMultiplier, 0.05);
    return texture(depthCubeMaps, vec4(fromLight, i), (distance - bias) / pointLights[i].farPlaneDistance);
}