#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 3) in ivec4 aBoneIDs;
layout(location = 4) in vec4 aWeights;

uniform mat4 model;
uniform mat4 boneMatrices[30];
uniform bool isSkinned;

void main() {
    vec4 skinnedPosition = vec4(aPosition, 1.0);

    if (isSkinned) {
        mat4 skinMatrix =
            aWeights[0] * boneMatrices[aBoneIDs[0]] + aWeights[1] * boneMatrices[aBoneIDs[1]] +
            aWeights[2] * boneMatrices[aBoneIDs[2]] + aWeights[3] * boneMatrices[aBoneIDs[3]];
        skinnedPosition = skinMatrix * skinnedPosition;
    }

    gl_Position = model * skinnedPosition;
}
