#version 330 core

in vec3 vertex;

uniform	mat4 matrixModel;
uniform	mat4 matrixView;
uniform	mat4 matrixProjection;

void main() {
    gl_Position = matrixProjection * matrixView * matrixModel * vec4(vertex, 1);
}
