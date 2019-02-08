#version 330 core

in vec3 vertex;

uniform	mat4 matrixModel;

void main() {

    gl_Position = matrixModel * vec4(vertex, 1);
}
