#version 330

const int MAX_NUM_LIGHTS = 12;

in vec4 worldspacePosition;
flat in int lightIndex;

struct LightInfo {

    vec3 position;
    float farPlaneDistance;
};

uniform LightInfo lights[MAX_NUM_LIGHTS];

void main() {

   gl_FragDepth = length(worldspacePosition.xyz - lights[lightIndex].position) / lights[lightIndex].farPlaneDistance;
}
