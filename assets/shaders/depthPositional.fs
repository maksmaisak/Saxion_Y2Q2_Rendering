#version 330

const int MAX_NUM_LIGHTS = 12;

in vec4 worldspacePosition;
flat in int lightIndex;
flat in int layerFace;

struct LightInfo {

    vec3 position;
    float farPlaneDistance;
};

uniform LightInfo lights[MAX_NUM_LIGHTS];

void main() {

   int index = int(floor(layerFace / 6));
   gl_FragDepth = length(worldspacePosition.xyz - lights[index].position) / lights[index].farPlaneDistance;
}
