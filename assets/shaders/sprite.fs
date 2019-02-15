#version 330

in vec2 texCoords;

uniform sampler2D spriteTexture;

out vec4 color;

void main() {

    color = texture(spriteTexture, texCoords);
}  