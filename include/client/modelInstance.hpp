#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "model.hpp"
#include "shader.hpp"

/**
 * @brief A single instance of a 3D model placed in the scene.
 * 
 * This instance shares the same mesh and texture data as others using the same model,
 * but has its own local transform to control where and how it appears in the world.
 * 
 * If a parent instance is set, this instance's final world transform is computed
 * relative to the parent's transform, allowing for hierarchical relationships.
 */
struct ModelInstance {
    Model* model;
    glm::mat4 localTransform;
    ModelInstance* parent;
    std::vector<std::unique_ptr<ModelInstance>> children;

    /**
     * @brief Constructs a ModelInstance.
     * 
     * @param model Pointer to the model asset.
     * @param localTransform Transform relative to the parent or world.
     * @param parent Optional parent instance for hierarchical transforms.
     */
    ModelInstance(Model* model,
                  const glm::mat4& localTransform = glm::mat4(1.0f),
                  ModelInstance* parent = nullptr)
        : model(model), localTransform(localTransform), parent(parent) {}

    /**
     * @brief Computes the world transform of this instance.
     * 
     * Multiplies the local transform by the parent's world transform recursively
     * if a parent exists. Otherwise, returns the local transform.
     */
    glm::mat4 getWorldTransform() const {
        return parent ? parent->getWorldTransform() * localTransform :  localTransform;
    }

    /**
     * @brief Draws this instance and its children recursively.
     * 
     * Sets the model matrix uniform, draws this model,
     * then recursively draws all children in the hierarchy.
     */
    void drawRecursive(Shader& shader) const {
        shader.setMat4("model", getWorldTransform());
        model->draw(shader);

        for (const auto& child : children) {
            child->drawRecursive(shader);
        }
    }
};
