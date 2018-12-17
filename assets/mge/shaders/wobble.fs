#version 330

in vec2 fUV;
in float wobbleFactor;

uniform sampler2D diffuseTexture;

out vec4 fragment_color;

void main() {

    float t = smoothstep(-1, 1, wobbleFactor);
    fragment_color = mix(texture(diffuseTexture, fUV), vec4(0,0,1,1), t);
}
