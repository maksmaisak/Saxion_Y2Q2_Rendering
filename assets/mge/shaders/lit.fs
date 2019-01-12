#version 330

in vec3 worldPosition;
in vec3 worldNormal;

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

uniform DirectionalLight directionalLights[4];
uniform int numDirectionalLights = 0;

uniform PointLight pointLights[10];
uniform int numPointLights = 0;

uniform vec3 viewPosition;

uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

out vec4 fragmentColor;

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 viewDirection);

void main() {

    vec3 normal = normalize(worldNormal);
    vec3 viewDirection = normalize(viewPosition - worldPosition);

    vec3 color = vec3(0,0,0);

    for (int i = 0; i < numDirectionalLights; ++i) {
        color += CalculateDirectionalLightContribution(directionalLights[i], normal, viewDirection);
    }

    for (int i = 0; i < numPointLights; ++i) {
        color += CalculatePointLightContribution(pointLights[i], normal, viewDirection);
    }

	fragmentColor = vec4(color, 1);
}

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewDirection) {

    vec3 ambient = light.colorAmbient * diffuseColor;

    vec3 diffuse = max(0, dot(normal, light.direction)) * light.color * diffuseColor;

    vec3 reflectedDirection = reflect(-light.direction, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * specularColor;

    return ambient + diffuse + specular;
}

vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 viewDirection) {

    vec3 ambient = light.colorAmbient * diffuseColor;

    vec3 delta = light.position - worldPosition;
    float distance = length(delta);
    vec3 lightDirection = delta / distance;

    vec3 diffuse = max(0, dot(normal, lightDirection)) * light.color * diffuseColor;

    vec3 reflectedDirection = reflect(-lightDirection, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * specularColor;

    float attenuation = 1.f / (light.falloffConstant + light.falloffLinear * distance + light.falloffQuadratic * distance * distance);

    return ambient + attenuation * (diffuse + specular);
}