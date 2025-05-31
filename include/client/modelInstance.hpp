#pragma once
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>
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
    bool isStatic;

    /**
     * @brief Stores all child model instances grouped by type and ID.
     *
     * The outer map key is the child type (e.g., "lilypad").
     * The inner map maps unique integer IDs to model instances of that type.
     */
    std::unordered_map<std::string, std::map<int, std::unique_ptr<ModelInstance>>> children;

    /**
     * @brief Constructs a ModelInstance.
     *
     * @param model Pointer to the model asset.
     * @param localTransform Transform relative to the parent or world.
     * @param parent Optional parent instance for hierarchical transforms.
     */
    ModelInstance(Model* model, const glm::mat4& localTransform = glm::mat4(1.0f),
                  ModelInstance* parent = nullptr, bool isStatic = true)
        : model(model), localTransform(localTransform), parent(parent), isStatic(isStatic) {}

    /**
     * @brief Computes the world transform of this instance.
     *
     * Multiplies the local transform by the parent's world transform recursively
     * if a parent exists. Otherwise, returns the local transform.
     */
    glm::mat4 getWorldTransform() const {
        return parent ? parent->getWorldTransform() * localTransform : localTransform;
    }

    /**
     * @brief Draws this instance and its children recursively.
     *
     * Sets the model matrix uniform, draws this model,
     * then recursively draws all children in the hierarchy.
     */
    void drawRecursive(Shader& shader, bool boundingBoxMode) const {
        shader.setMat4("model", getWorldTransform());
        model->draw(shader, boundingBoxMode);

        for (const auto& [type, idMap] : children) {
            for (const auto& [id, child] : idMap) {
                child->drawRecursive(shader, boundingBoxMode);
            }
        }
    }

    /**
     * @brief Removes a child from the children map by type and ID.
     *
     * If the given type or ID doesn't exist, nothing happens.
     * If the type has no more children after deletion, it's removed too.
     *
     * @param type The type name of the child (e.g., "lilypad").
     * @param id The unique ID of the child to remove.
     */
    void deleteChild(const std::string& type, int id) {
        if (!children.contains(type))
            return;

        auto& idMap = children[type];

        if (!idMap.contains(id))
            return;

        idMap.erase(id);

        if (idMap.empty()) {
            children.erase(type);
        }
    }
};
