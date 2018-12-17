#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 mvpMatrix;
uniform float time;

uniform float timeScale;
uniform float phaseOffsetPerUnitDistance;

out vec2 fUV;

void main() {

    vec3 position = vertex * (1 + 0.2 * sin(time * timeScale + vertex.y * phaseOffsetPerUnitDistance));
    gl_Position = mvpMatrix * vec4(position, 1);
    fUV = uv;
}
