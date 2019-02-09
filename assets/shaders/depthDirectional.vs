#version 330

in vec3 vertex;

uniform	mat4 matrixModel;
uniform	mat4 matrixPV;

void main() {
    gl_Position = matrixPV * matrixModel * vec4(vertex, 1);
}
