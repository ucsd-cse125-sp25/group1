#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "animatedModel.hpp"
#include "animation.hpp"

/**
 * @brief Updates animation time and computes bone transforms for skeletal animation.
 *
 * The Animator tracks the current time of an animation and computes the final
 * bone transformation matrices based on that time.
 */
class Animator {
  public:
    /**
     * @brief Constructs the animator with an initial animation.
     * @param animation The animation to use.
     */
    Animator(Animation* animation);

    /**
     * @brief Sets a new animation and resets the current time.
     * @param animation The new animation to switch to.
     */
    void setAnimation(Animation* animation);

    /**
     * @brief Updates current time and recalculates bone transforms.
     * @param deltaTime Time step used to update the animation.
     */
    void update(float deltaTime);

    /**
     * @brief Gets the final bone matrices used for skeletal animation.
     * @return A reference to the list of bone matrices.
     */
    const std::vector<glm::mat4>& getBoneMatrices() const {
        return boneMatrices;
    }

  private:
    /**
     * @brief Recursively computes final bone transforms from the scene hierarchy.
     * @param node The current node in the hierarchy.
     * @param parentTransform The parent node's global transform.
     */
    void computeBoneTransform(const aiNode* node, const glm::mat4& parentTransform);

    Animation* animation = nullptr;
    float currentTime = 0.0f;

    std::vector<glm::mat4> boneMatrices;
};
