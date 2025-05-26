#pragma once
#include <glm/glm.hpp>

constexpr int MAX_BONES_PER_VERTEX = 4;

/**
 * @brief GPU-ready vertex format for skeletal animation.
 */
struct SkinnedVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    int boneIDs[MAX_BONES_PER_VERTEX] = {0};
    float weights[MAX_BONES_PER_VERTEX] = {0.0f};
};

/**
 * @brief CPU-side helper for assigning bone data to a vertex.
 */
struct SkinnedVertexCPU : SkinnedVertex {
    int boneCount = 0; // Number of bones currently assigned.

    /**
     * @brief Adds bone data if the weight is non-zero and space is available.
     * @param boneID Bone ID.
     * @param weight Bone weight.
     */
    void addBoneData(int boneID, float weight) {
        if (weight > 0.0f && boneCount < MAX_BONES_PER_VERTEX) {
            boneIDs[boneCount] = boneID;
            weights[boneCount++] = weight;
        }
    }
};
