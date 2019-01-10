//DIFFUSE COLOR VERTEX SHADER

#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 matrixProjection;
uniform	mat4 matrixView;
uniform	mat4 matrixModel;

out vec3 worldPosition;
out vec3 worldNormal;

void main(void) {

    vec4 worldPosition4 = matrixModel * vec4(vertex, 1.f);
    worldPosition = vec3(worldPosition4);
    gl_Position = matrixProjection * matrixView * worldPosition4;

    worldNormal = mat3(transpose(inverse(matrixModel))) * normal;
}
