#version 330

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

    sampler2D depthMap;
};

struct PointLight {

    vec3 color;
    vec3 colorAmbient;

    vec3 position;

    float falloffConstant;
    float falloffLinear;
    float falloffQuadratic;
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

uniform DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];
uniform int numDirectionalLights = 0;

uniform PointLight pointLights[10];
uniform int numPointLights = 0;

uniform SpotLight spotLights[4];
uniform int numSpotLights = 0;

uniform vec3 viewPosition;

// Custom uniforms
uniform vec3 diffuseColor  = vec3(1,1,1);
uniform sampler2D diffuseMap;
uniform vec3 specularColor = vec3(1,1,1);
uniform sampler2D specularMap;
uniform float shininess = 1;

out vec4 fragmentColor;

vec3 CalculateDirectionalLightContribution(int i, DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
vec3 CalculateSpotLightContribution(SpotLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
float CalculateShadowMultiplier(vec4 lightspacePosition, sampler2D depthMap, float biasMultiplier);

void main() {

    vec3 normal = normalize(worldNormal);
    vec3 viewDirection = normalize(viewPosition - worldPosition);
    vec3 materialDiffuse  = diffuseColor  * vec3(texture(diffuseMap , texCoords));
    vec3 materialSpecular = specularColor * vec3(texture(specularMap, texCoords));

    vec3 color = vec3(0,0,0);

    for (int i = 0; i < numDirectionalLights; ++i) {
        color += CalculateDirectionalLightContribution(i, directionalLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

    for (int i = 0; i < numPointLights; ++i) {
        color += CalculatePointLightContribution(pointLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

    for (int i = 0; i < numSpotLights; ++i) {
        color += CalculateSpotLightContribution(spotLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

	fragmentColor = vec4(color, 1);
}

vec3 CalculateDirectionalLightContribution(int i, DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {

    float normalDotDirection = dot(normal, light.direction);

    vec3 ambient = light.colorAmbient * materialDiffuse;

    vec3 diffuse = max(0, dot(normal, light.direction)) * materialDiffuse;

    vec3 reflectedDirection = reflect(-light.direction, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * materialSpecular;

    float shadowMultiplier = CalculateShadowMultiplier(directionalLightspacePosition[i], light.depthMap, 1 - normalDotDirection);
    return ambient + shadowMultiplier * (diffuse + specular) * light.color;
    vec3 projected = (directionalLightspacePosition[i].xyz / directionalLightspacePosition[i].w) * 0.5 + 0.5;
    float closestDepth = texture(light.depthMap, projected.xy).r;
    return texture(light.depthMap, projected.xy).rgb;// light.color * shadowMultiplier;
}

float CalculateShadowMultiplier(vec4 lightspacePosition, sampler2D depthMap, float biasMultiplier) {

    vec3 projected = (lightspacePosition.xyz / lightspacePosition.w) * 0.5 + 0.5;
    float closestDepth = texture(depthMap, projected.xy).r;
    float thisDepth = projected.z;

    float bias = max(0.002 * biasMultiplier, 0.001);
    return thisDepth > (closestDepth + bias) ? 0 : 1;
}

vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {

    vec3 ambient = light.colorAmbient * materialDiffuse;

    vec3 delta = light.position - worldPosition;
    float distance = length(delta);
    vec3 lightDirection = delta / distance;

    vec3 diffuse = max(0, dot(normal, lightDirection)) * light.color * materialDiffuse;

    vec3 reflectedDirection = reflect(-lightDirection, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * materialSpecular;

    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);

    return ambient + attenuation * (diffuse + specular);
}

vec3 CalculateSpotLightContribution(SpotLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {

    vec3 ambient = light.colorAmbient * materialDiffuse;

    vec3 delta = light.position - worldPosition;
    float distance = length(delta);
    vec3 lightDirection = delta / distance;

    vec3 diffuse = max(0, dot(normal, lightDirection)) * light.color * materialDiffuse;

    vec3 reflectedDirection = reflect(-lightDirection, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * materialSpecular;

    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);
    attenuation *= smoothstep(light.outerCutoff, light.innerCutoff, dot(-lightDirection, light.direction));

    return ambient + attenuation * (diffuse + specular);
}