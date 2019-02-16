#version 330

in vec2 texCoords;

uniform sampler2D fontAtlas;
uniform vec3 textColor;

out vec4 color;

void main() {

    color = vec4(textColor, 1.0) * texture(fontAtlas, texCoords);
}