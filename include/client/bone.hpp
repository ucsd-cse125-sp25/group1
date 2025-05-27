#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>

/**
 * @brief Stores keyframe data and computes bone transforms for animation.
 *
 * Each bone holds position, rotation, and scale keyframes, and computes
 * its transform at a given time during animation playback.
 */
class Bone {
  public:
    /**
     * @brief Constructs a bone from animation channel data.
     * @param name Bone name.
     * @param id Bone index.
     * @param channel Animation keyframes from Assimp.
     */
    Bone(const std::string& name, int id, const aiNodeAnim* channel);

    /**
     * @brief Updates the bone's transform based on the current time.
     * @param currentTime Current time in ticks.
     */
    void update(float currentTime);

    /**
     * @brief Returns the bone name.
     */
    const std::string& getName() const {
        return name;
    }

    /**
     * @brief Returns the bone ID.
     */
    int getID() const {
        return id;
    }

    /**
     *  @brief Returns the transformation matrix.
     */
    const glm::mat4& getTransform() const {
        return transform;
    }

  private:
    std::string name;
    int id;
    glm::mat4 transform{1.0f};

    std::vector<std::pair<float, glm::vec3>> positions;
    std::vector<std::pair<float, glm::quat>> rotations;
    std::vector<std::pair<float, glm::vec3>> scales;

    /**
     * @brief Computes the interpolation factor between two keyframes.
     * @param currentTime Current time in ticks.
     * @param lastTime Time of the previous keyframe.
     * @param nextTime Time of the next keyframe.
     * @return A value between 0 and 1, where 0 means at lastTime, and 1 means at nextTime.
     */
    float computeAlpha(float currentTime, float lastTime, float nextTime) const;

    /**
     * @brief Interpolates the bone's position at the given time.
     * @param currentTime Current time in ticks.
     * @return Interpolated position.
     */
    glm::vec3 interpolatePosition(float currentTime) const;

    /**
     * @brief Interpolates the bone's rotation at the given time.
     * @param currentTime Current time in ticks.
     * @return Interpolated rotation.
     */
    glm::quat interpolateRotation(float currentTime) const;

    /**
     * @brief Interpolates the bone's scale at the given time.
     * @param currentTime Current time in ticks.
     * @return Interpolated scale.
     */
    glm::vec3 interpolateScale(float currentTime) const;
};
