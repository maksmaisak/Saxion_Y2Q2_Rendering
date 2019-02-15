#version 330

in vec2 texCoords;

uniform sampler2D fontAtlas;
uniform vec3 textColor;

out vec4 color;

void main() {

    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(fontAtlas, texCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  