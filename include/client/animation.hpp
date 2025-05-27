#pragma once

#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <map>
#include <string>
#include <vector>
#include "animatedModel.hpp"
#include "bone.hpp"

/**
 * @brief Stores bone and timing data for a model's skeletal animation.
 *
 * Loads animation data from an Assimp scene, including bones, duration,
 * and tick rate.
 */
class Animation {
  public:
    /**
     * @brief Loads animation data from the given scene and model.
     * @param scene The Assimp scene with animation data.
     * @param model The model associated with this animation.
     */
    Animation(const aiScene* scene, AnimatedModel* model);

    /**
     * @brief Finds a bone by name.
     * @param name The bone name.
     * @return A pointer to the matching Bone, or nullptr if not found.
     */
    Bone* findBone(const std::string& name);

    /**
     * @brief Returns the number of bones used in this animation.
     */
    int getBoneCount() const {
        return bones.size();
    }

    /**
     * @brief Returns the total duration of the animation.
     */
    float getDuration() const {
        return duration;
    }

    /**
     * @brief Returns the number of ticks per second in the animation.
     */
    float getTicksPerSecond() const {
        return ticksPerSecond;
    }

    /**
     * @brief Returns the root node of the scene hierarchy.
     */
    const aiNode* getRootNode() const {
        return rootNode;
    }

    /**
     * @brief Returns the model associated with this animation.
     */
    AnimatedModel* getModel() const {
        return model;
    }

  private:
    const aiNode* rootNode = nullptr;
    AnimatedModel* model = nullptr;

    float duration = 0.0f;
    float ticksPerSecond = 0.0f;

    std::map<std::string, Bone> bones;
};
