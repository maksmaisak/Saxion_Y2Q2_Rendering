#version 330

in vec3 vertex;

uniform	mat4 matrixModel;

void main() {

    gl_Position = matrixModel * vec4(vertex, 1);
}
