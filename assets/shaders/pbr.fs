#version 400

const int NUM_DIRECTIONAL_LIGHTS = 4;
const int NUM_POINT_LIGHTS = 10;
const int NUM_SPOT_LIGHTS = 4;

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 worldTangent;
in vec3 worldBitangent;
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
uniform sampler2D metallicSmoothnessMap;
uniform sampler2D normalMap;
uniform sampler2D aoMap;
uniform vec4 albedoColor = vec4(1,1,1,1);
uniform float metallicMultiplier = 1;
uniform float smoothnessMultiplier = 1;
uniform float aoMultiplier = 1;

const float PI = 3.14159265359;

out vec4 fragmentColor;

vec3 CalculateDirectionalLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao);
vec3 CalculatePointLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao);
vec3 CalculateSpotLightContribution (int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao);

vec3 GetNormal();
vec3 CookTorranceBRDF(vec3 N, vec3 V, vec3 L, vec3 albedo, float metallic, float roughness);
float CalculateDirectionalShadowMultiplier(int i, float biasMultiplier);
float CalculatePointShadowMultiplier(int i, vec3 fromLight, float distance, float biasMultiplier);

void main() {

    vec3 normal = GetNormal();
    vec3 viewDirection = normalize(viewPosition - worldPosition);

    vec4 msSample   = texture(metallicSmoothnessMap, texCoords);
    float metallic  = metallicMultiplier * msSample.r;
    float roughness = 1.f - smoothnessMultiplier * msSample.a;
    vec4  albedo    = albedoColor  * texture(albedoMap, texCoords);
    float ao        = aoMultiplier * texture(aoMap, texCoords).r;

    vec3 color = vec3(0,0,0);

    for (int i = 0; i < numDirectionalLights; ++i) {
        color += CalculateDirectionalLightContribution(i, normal, viewDirection, albedo.rgb, metallic, roughness, ao);
    }

    for (int i = 0; i < numPointLights; ++i) {
        color += CalculatePointLightContribution(i, normal, viewDirection, albedo.rgb, metallic, roughness, ao);
    }

    for (int i = 0; i < numSpotLights; ++i) {
        color += CalculateSpotLightContribution(i, normal, viewDirection, albedo.rgb, metallic, roughness, ao);
    }

    #ifdef RENDER_MODE_TRANSPARENCY
	    fragmentColor = vec4(color, albedo.a);
	#else
        fragmentColor = vec4(color, 1);
	#endif
}

vec3 GetNormal() {

    vec3 tangentspaceNormal = texture(normalMap, texCoords).xyz * 2.0 - 1.0;

    vec3 N = normalize(worldNormal);
    vec3 T = normalize(worldTangent);
    vec3 B = normalize(worldBitangent);
    return normalize(mat3(T,B,N) * tangentspaceNormal);
}

vec3 CalculateDirectionalLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao) {

    DirectionalLight light = directionalLights[i];

    vec3 L = -light.direction;
    vec3 brdf = CookTorranceBRDF(N, V, L, albedo, metallic, roughness);

    float NdotL = max(dot(N, L), 0.0);
    float shadowMultiplier = CalculateDirectionalShadowMultiplier(i, 1 - NdotL);

    vec3 ambient = light.colorAmbient * albedo * ao;

    return ambient + brdf * light.color * NdotL * shadowMultiplier;
}

vec3 CalculatePointLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao) {

    PointLight light = pointLights[i];

    vec3  delta = light.position - worldPosition;
    float distance = length(delta);
    vec3  L = delta / distance;
    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);

    vec3 brdf = CookTorranceBRDF(N, V, L, albedo, metallic, roughness);

    float NdotL = max(dot(N, L), 0.0);
    float shadowMultiplier =  CalculatePointShadowMultiplier(i, -delta, distance, 1 - NdotL);

    vec3 ambient = light.colorAmbient * albedo * ao;

    return ambient + brdf * light.color * NdotL * attenuation * shadowMultiplier;
}

vec3 CalculateSpotLightContribution(int i, vec3 N, vec3 V, vec3 albedo, float metallic, float roughness, float ao) {

    SpotLight light = spotLights[i];

    vec3  delta = light.position - worldPosition;
    float distance = length(delta);
    vec3  L = delta / distance;
    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);
    attenuation *= smoothstep(light.outerCutoff, light.innerCutoff, dot(-L, light.direction));

    vec3 brdf = CookTorranceBRDF(N, V, L, albedo, metallic, roughness);

    float NdotL = max(dot(N, L), 0.0);
    float shadowMultiplier =  CalculatePointShadowMultiplier(i, -delta, distance, 1 - NdotL);

    vec3 ambient = light.colorAmbient * albedo * ao;

    return ambient + brdf * light.color * NdotL * attenuation * shadowMultiplier;
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {

    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom   = a2;
    float denom = NdotH2 * (a2 - 1.0) + 1.0;
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

vec3 CookTorranceBRDF(vec3 N, vec3 V, vec3 L, vec3 albedo, float metallic, float roughness) {

    float NdotL = dot(N, L);
    float NdotV = dot(N, V);

    vec3 H = normalize(V + L);
    float HdotV = dot(H, V);

    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);
    vec3  F   = FresnelSchlick(max(HdotV, 0.0), mix(vec3(0.04), albedo, metallic));

    vec3  nominator   = NDF * G * F;
    float denominator = 4 * max(NdotV, 0.0) * max(NdotL, 0.0) + 0.001; // 0.001 to prevent divide by zero
    vec3  specular = nominator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    return kD * albedo / PI + specular;
}

float CalculateDirectionalShadowMultiplier(int i, float biasMultiplier) {

    vec4 lightspacePosition = directionalLightspacePosition[i];
    vec3 projected = (lightspacePosition.xyz / lightspacePosition.w) * 0.5 + 0.5;
    float currentDepth = projected.z;
    if (currentDepth > 1.f)
        return 1;

    float bias = max(0.005 * biasMultiplier, 0.001);

    float shadow = 0.0;
    vec3 texelSize = 1.0 / textureSize(directionalDepthMaps, 0);
    vec2 scale = texelSize.xy * (1 + currentDepth * 0.1);
    for (float x = -1; x <= 1; x += 1)
        for (float y = -1; y <= 1; y += 1)
            shadow += texture(directionalDepthMaps, vec4(projected.xy + vec2(x, y) * scale, i, currentDepth - bias));
    shadow /= 9.0;

    return shadow;
}

const vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1),
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);

float CalculatePointShadowMultiplier(int i, vec3 fromLight, float distance, float biasMultiplier) {

    float shadow = 0.0;
    float bias = max(0.1 * biasMultiplier, 0.05);
    int samples = 20;
    float depth = (distance - bias) / pointLights[i].farPlaneDistance;
    float viewDistance = length(viewPosition - worldPosition);
    float diskRadius = (1.0 + (viewDistance / pointLights[i].farPlaneDistance)) / 25.0;
    for (int j = 0; j < samples; ++j)
        shadow += texture(depthCubeMaps, vec4(fromLight + sampleOffsetDirections[j] * diskRadius, i), depth);
    shadow /= float(samples);
    return shadow;
}