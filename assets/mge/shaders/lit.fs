#version 330

in vec3 worldPosition;
in vec3 worldNormal;

struct LightDirectinal {

    vec3 color;
    vec3 direction;
};

struct LightPoint {

    vec3 color;
    vec3 colorAmbient;

    vec3 position;

    float falloffConstant;
    float falloffLinear;
    float falloffQuadratic;
};

uniform LightPoint pointLights[10];
uniform int numPointLights;

uniform vec3 viewPosition;

uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

out vec4 fragmentColor;

vec3 CalculatePointLightContribution(LightPoint light, vec3 normal, vec3 viewDirection);

void main() {

    vec3 normal = normalize(worldNormal);
    vec3 viewDirection = normalize(viewPosition - worldPosition);

    vec3 color = vec3(0,0,0);
    for (int i = 0; i < numPointLights; ++i) {
        color += CalculatePointLightContribution(pointLights[i], normal, viewDirection);
    }

	fragmentColor = vec4(color, 1);
}

vec3 CalculatePointLightContribution(LightPoint light, vec3 normal, vec3 viewDirection) {

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