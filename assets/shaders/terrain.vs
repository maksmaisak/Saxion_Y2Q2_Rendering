#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 matrixProjection;
uniform	mat4 matrixView;
uniform	mat4 matrixModel;

out vec3 worldPosition;
out vec3 worldNormal;
out vec2 texCoords;

uniform sampler2D heightmap;
uniform float maxHeight = 1;

float sampleHeight(vec2 heightmapUv) {
    return texture(heightmap, heightmapUv).r * maxHeight;
}

vec3 sampleDisplacement(vec2 heightmapUv) {
    return vec3(0, sampleHeight(heightmapUv), 0);
}

vec3 samplePositionUVSpace(vec2 heightmapUv) {
    return vec3(heightmapUv.x, texture(heightmap, heightmapUv).r, heightmapUv.y);
}

void main(void) {

    vec3 uvSpacePosition = samplePositionUVSpace(uv);
    vec3 tangentX = samplePositionUVSpace(uv + vec2(0.01, 0)) - uvSpacePosition;
    vec3 tangentZ = samplePositionUVSpace(uv + vec2(0, 0.01)) - uvSpacePosition;

    worldPosition = vec3(matrixModel * vec4(vertex, 1)) + vec3(0, sampleHeight(uv), 0);
    gl_Position = matrixProjection * matrixView * vec4(worldPosition, 1);

    worldNormal = normalize(cross(normalize(tangentZ), normalize(tangentX)));
    //worldNormal = mat3(transpose(inverse(matrixModel))) * normal;
    texCoords = uv;
}
