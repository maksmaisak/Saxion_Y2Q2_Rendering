#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec2 fUV;

uniform sampler2D diffuseTexture;

out vec4 fragment_color;

void main() {

    fragment_color = texture(diffuseTexture, fUV);
}
