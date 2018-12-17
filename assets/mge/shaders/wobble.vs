#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 mvpMatrix;
uniform float time;

uniform float timeScale;
uniform float phaseOffsetPerUnitDistance;

out vec2 fUV;
out float wobbleFactor; // from -1 to 1. 0 is no wobble.

void main() {

    wobbleFactor = sin(time * timeScale + vertex.y * phaseOffsetPerUnitDistance);

    vec3 position = vertex * (1 + 0.2 * wobbleFactor);
    gl_Position = mvpMatrix * vec4(position, 1);
    fUV = uv;
}
