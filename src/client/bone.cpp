#include "bone.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

Bone::Bone(const std::string& name, int id, const aiNodeAnim* channel) : name(name), id(id) {
    for (unsigned int i = 0; i < channel->mNumPositionKeys; ++i) {
        auto key = channel->mPositionKeys[i];
        positions.emplace_back(static_cast<float>(key.mTime),
                               glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
    }

    for (unsigned int i = 0; i < channel->mNumRotationKeys; ++i) {
        auto key = channel->mRotationKeys[i];
        rotations.emplace_back(static_cast<float>(key.mTime),
                               glm::quat(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z));
    }

    for (unsigned int i = 0; i < channel->mNumScalingKeys; ++i) {
        auto key = channel->mScalingKeys[i];
        scales.emplace_back(static_cast<float>(key.mTime),
                            glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
    }
}

void Bone::update(float currentTime) {
    glm::vec3 position = interpolatePosition(currentTime);
    glm::quat rotation = interpolateRotation(currentTime);
    glm::vec3 scale = interpolateScale(currentTime);

    transform = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) *
                glm::scale(glm::mat4(1.0f), scale);
}

float Bone::computeAlpha(float currentTime, float lastTime, float nextTime) const {
    return lastTime == nextTime ? 0.0f : (currentTime - lastTime) / (nextTime - lastTime);
}

glm::vec3 Bone::interpolatePosition(float currentTime) const {
    for (size_t i = 0; i < positions.size() - 1; ++i) {
        if (currentTime < positions[i + 1].first) {
            float alpha = computeAlpha(currentTime, positions[i].first, positions[i + 1].first);
            return glm::mix(positions[i].second, positions[i + 1].second, alpha);
        }
    }

    return positions.back().second;
}

glm::quat Bone::interpolateRotation(float currentTime) const {
    for (size_t i = 0; i < rotations.size() - 1; ++i) {
        if (currentTime < rotations[i + 1].first) {
            float alpha = computeAlpha(currentTime, rotations[i].first, rotations[i + 1].first);
            return glm::slerp(rotations[i].second, rotations[i + 1].second, alpha);
        }
    }

    return rotations.back().second;
}

glm::vec3 Bone::interpolateScale(float currentTime) const {
    for (size_t i = 0; i < scales.size() - 1; ++i) {
        if (currentTime < scales[i + 1].first) {
            float alpha = computeAlpha(currentTime, scales[i].first, scales[i + 1].first);
            return glm::mix(scales[i].second, scales[i + 1].second, alpha);
        }
    }

    return scales.back().second;
}
