#version 330 core

in vec4 worldspacePosition;

uniform vec3 lightPosition;
uniform float farPlaneDistance;

void main() {

    gl_FragDepth = length(worldspacePosition.xyz - lightPosition) / farPlaneDistance;
}
