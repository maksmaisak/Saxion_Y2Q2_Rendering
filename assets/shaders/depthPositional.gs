#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices=18) out;

uniform mat4 matrixPV[6];

out vec4 worldspacePosition;

void main() {

    for (int face = 0; face < 6; ++face) {
        gl_Layer = face;

        for (int i = 0; i < 3; ++i) {
            worldspacePosition = gl_in[i].gl_Position;
            gl_Position = matrixPV[face] * worldspacePosition;
            EmitVertex();
        }
        EndPrimitive();
    }
}
