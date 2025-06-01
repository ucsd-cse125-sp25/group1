#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in ivec4 aBoneIDs;
layout(location = 4) in vec4 aWeights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 boneMatrices[30];

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

void main() {
    mat4 skinMatrix = mat4(1.0);

    if (aWeights[0] + aWeights[1] + aWeights[2] + aWeights[3] > 0.0) {
        skinMatrix =
            aWeights[0] * boneMatrices[aBoneIDs[0]] + aWeights[1] * boneMatrices[aBoneIDs[1]] +
            aWeights[2] * boneMatrices[aBoneIDs[2]] + aWeights[3] * boneMatrices[aBoneIDs[3]];
    }

    vec4 worldPos = model * skinMatrix * vec4(aPosition, 1.0);

    fragPos = vec3(worldPos);
    normal = normalize(mat3(transpose(inverse(model * skinMatrix))) * aNormal);
    texCoords = aTexCoords;

    gl_Position = projection * view * worldPos;
}
