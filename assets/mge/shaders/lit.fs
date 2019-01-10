//DIFFUSE COLOR FRAGMENT SHADER

#version 330

in vec3 worldPosition;
in vec3 worldNormal;

struct LightDirectinal {

    vec3 color;
    vec3 direction;
};

struct LightPoint {

    vec3 color;
    vec3 position;
};

uniform vec3 viewPosition;

uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

out vec4 fragmentColor;

vec3 CalculatePointLight(LightPoint light, vec3 normal);

void main() {

    vec3 normal = normalize(worldNormal);

    LightPoint lights[2];
    lights[0].color = vec3(1,0,0);
    lights[0].position = vec3(-2, 1, 0);
    lights[1].color = vec3(0,1,0);
    lights[1].position = vec3(2, 1, 0);

    vec3 color = vec3(0,0,0);
    for (int i = 0; i < 2; ++i) {
        color += CalculatePointLight(lights[i], normal);
    }

	fragmentColor = vec4(color, 1);
}

vec3 CalculatePointLight(LightPoint light, vec3 normal) {

    float ambientIntensity = 0.2;
    vec3 ambientColor = vec3(0,0,1);
    vec3 ambient = ambientIntensity * ambientColor * diffuseColor;

    vec3 delta = light.position - worldPosition;
    float distance = length(delta);
    vec3 lightDirection = delta / distance;

    vec3 diffuse = max(0, dot(normal, lightDirection)) * light.color * diffuseColor;
    diffuse /= (1 + distance * distance);

    vec3 viewDirection = normalize(viewPosition - worldPosition); // TODO avoid recomputing for each light
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    vec3 specular = pow(max(0, dot(reflectedDirection, viewDirection)), shininess) * light.color * specularColor;

    return ambient + diffuse + specular;
}