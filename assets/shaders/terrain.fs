#version 330

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 texCoords;

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

uniform DirectionalLight directionalLights[4];
uniform int numDirectionalLights = 0;

uniform PointLight pointLights[10];
uniform int numPointLights = 0;

uniform SpotLight spotLights[4];
uniform int numSpotLights = 0;

uniform vec3 viewPosition;

// Custom uniforms
// Height
uniform sampler2D heightmap;
// Diffuse
uniform vec3 diffuseColor  = vec3(1,1,1);
uniform sampler2D diffuse1;
uniform sampler2D diffuse2;
uniform sampler2D diffuse3;
uniform sampler2D diffuse4;
uniform sampler2D splatmap;
// Specular
uniform vec3 specularColor = vec3(1,1,1);
uniform sampler2D specularMap;
uniform float shininess = 1;

out vec4 fragmentColor;

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
vec3 CalculateSpotLightContribution(SpotLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);
vec3 GetLightsContribution(vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular);

vec3 sampleDiffuse(vec2 uv) {

    vec4 weights = texture(splatmap, uv);
    vec4 result =
        weights.r * texture(diffuse1, uv) +
        weights.g * texture(diffuse2, uv) +
        weights.b * texture(diffuse3, uv) +
        weights.a * texture(diffuse4, uv);

    return vec3(result);
}

vec3 samplePositionUVSpace(vec2 heightmapUv) {
    float height = texture(heightmap, heightmapUv).r;
    return vec3(heightmapUv.x, height, heightmapUv.y);
}

vec3 calculateNormal(vec2 heightmapUv) {

    vec3 uvSpacePosition = samplePositionUVSpace(heightmapUv);
    vec3 tangentX = samplePositionUVSpace(heightmapUv + vec2(0.0001, 0)) - uvSpacePosition;
    vec3 tangentZ = samplePositionUVSpace(heightmapUv + vec2(0, 0.0001)) - uvSpacePosition;

    return cross(normalize(tangentZ), normalize(tangentX));
}

void main() {

    vec3 normal = normalize(worldNormal);//calculateNormal(texCoords);
    vec3 viewDirection = normalize(viewPosition - worldPosition);
    vec3 materialDiffuse  = diffuseColor  * sampleDiffuse(texCoords);
    vec3 materialSpecular = specularColor * vec3(texture(specularMap, texCoords));

    vec3 color = GetLightsContribution(normal, viewDirection, materialDiffuse, materialSpecular);
	fragmentColor = vec4(color, 1);
	//fragmentColor = vec4((normal + vec3(1)) * 0.5, 1);
}

vec3 GetLightsContribution(vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {

    vec3 color = vec3(0,0,0);

    for (int i = 0; i < numDirectionalLights; ++i) {
        color += CalculateDirectionalLightContribution(directionalLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

    for (int i = 0; i < numPointLights; ++i) {
        color += CalculatePointLightContribution(pointLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

    for (int i = 0; i < numSpotLights; ++i) {
        color += CalculateSpotLightContribution(spotLights[i], normal, viewDirection, materialDiffuse, materialSpecular);
    }

	return color;
}

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 materialDiffuse, vec3 materialSpecular) {

    vec3 ambient = light.colorAmbient * materialDiffuse;

    vec3 diffuse = max(0, dot(normal, light.direction)) * light.color * materialDiffuse;

    vec3 reflectedDirection = reflect(-light.direction, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * materialSpecular;

    return ambient + diffuse + specular;
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