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
     *
     * @param shader Shader used for rendering.
     * @param boundingBoxMode If true, draws only bounding boxes.
     * @param staticOnly If true, draws only static models; otherwise, draws all models.
     */
    void drawRecursive(Shader& shader, bool boundingBoxMode, bool staticOnly = false) const {
        shader.setMat4("model", getWorldTransform());

        if (!staticOnly || isStatic) {
            model->draw(shader, boundingBoxMode);
        }

        for (const auto& [type, idMap] : children) {
            for (const auto& [id, child] : idMap) {
                if (type == "finalDoor") {
                    glEnable(GL_BLEND);
                    // glDepthMask(GL_FALSE);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    child->drawRecursive(shader, boundingBoxMode, staticOnly);
                    glDisable(GL_BLEND);
                } else {
                    child->drawRecursive(shader, boundingBoxMode, staticOnly);
                }
            }
        }
    }

    /**
     * Draws interactable children of the given type.
     *
     * If no range is provided, draws all. Otherwise, draws only those
     * with IDs from start to end (inclusive).
     *
     * @param shader Shader used for rendering.
     * @param type Type of interactable (e.g., "lilypad").
     * @param start Start ID to draw (default -1 for all).
     * @param end End ID to draw (default -1 for all).
     */
    void drawInteractable(Shader& shader, std::string type, int start = -1, int end = -1) {
        const auto& idMap = children.at(type);

        if (start == -1 || end == -1) {
            for (const auto& [id, child] : idMap) {
                shader.setMat4("model", child->getWorldTransform());
                child->model->draw(shader, false);
            }
        } else {
            for (int id = start; id <= end; ++id) {
                if (idMap.contains(id)) {
                    const auto& child = idMap.at(id);
                    shader.setMat4("model", child->getWorldTransform());
                    child->model->draw(shader, false);
                }
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

    void translateLocal(const glm::vec3& delta) {
        localTransform = glm::translate(localTransform, delta);
    }
};
