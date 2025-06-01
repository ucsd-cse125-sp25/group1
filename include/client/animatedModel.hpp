#pragma once

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>
#include "animatedSubMesh.hpp"
#include "shader.hpp"

/**
 * @brief Loads and stores a skinned 3D model with bones and sub-meshes.
 *
 * This class uses Assimp to load a model file (.fbx), extract mesh and bone data,
 * and store them for use in rendering and skeletal animation.
 *
 * It keeps track of all sub-meshes, bone names and IDs, and bone offset matrices.
 */
class AnimatedModel {
  public:
    /**
     * @brief Constructs the model and loads all meshes and bones from file.
     * @param path Path to the model file (.fbx)
     */
    AnimatedModel(const std::string& path);

    /**
     * @brief Draws all submeshes in the model.
     */
    void draw(Shader& shader);

    /**
     * @brief Checks if the model has a bone with the given name.
     * @param name The bone name.
     * @return True if the bone exists, false otherwise.
     */
    bool hasBone(const std::string& name) const {
        return bones.contains(name);
    }

    /**
     * @brief Gets the bone ID associated with a bone name.
     * @param name The bone name.
     * @return The bone ID, or -1 if not found.
     */
    int getBoneID(const std::string& name) const;

    /**
     * @brief Returns the list of bone offset matrices.
     */
    const std::vector<glm::mat4>& getBoneOffsets() const {
        return boneOffsets;
    }

    /**
     * @brief Returns the original Assimp scene pointer.
     */
    const aiScene* getScene() const {
        return scene;
    }

  private:
    std::vector<AnimatedSubMesh> subMeshes; // List of sub-meshes ready for rendering.

    std::map<std::string, int> bones;   // Maps bone names to bone IDs.
    std::vector<glm::mat4> boneOffsets; // Bone offset matrices.
    int boneCount = 0;                  // Total number of bones used in the model.

    Assimp::Importer importer;
    const aiScene* scene = nullptr;

    std::string directory;

    /**
     * @brief Loads a model from the given file path.
     * @param path Path to the model file.
     */
    void loadModel(const std::string& path);

    /**
     * @brief Processes the given node and all its children.
     * Called recursively to process the entire scene hierarchy.
     */
    void processNode(aiNode* node);

    /**
     * @brief Processes an individual mesh and extracts geometry and bone data.
     * @param mesh The mesh to process.
     * @return The resulting GPU-ready AnimatedSubMesh.
     */
    AnimatedSubMesh processMesh(aiMesh* mesh);
};
