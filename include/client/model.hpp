#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.hpp"

/**
 * @brief Represents a single sub-mesh inside a model.
 * 
 * Each SubMesh contains its own VAO, VBO, EBO, material color,
 * and optionally a texture.
 */
struct SubMesh {
    GLuint vao, vbo, ebo;
    GLuint indexCount;          // Number of indices to draw.
    glm::vec3 color;            // Base color of the sub-mesh
    glm::vec3 specular;         // Specular reflectivity of the sub-mesh
    float shininess;            // Shininess of the sub-mesh

    GLuint textureId = 0;       // Texture ID if a texture is loaded.
    bool hasTexture = false;    // True if this sub-mesh uses a texture.

    bool isBoundingBox = false;  // True if this sub-mesh is a bounding box.

    /**
     * @brief Draws the sub-mesh.
     * 
     * Binds the VAO and issues a draw call to render the sub-mesh.
     */
    void draw() const {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

/**
 * @brief Represents a complete 3D model, made up of multiple sub-meshes.
 * 
 * Handles loading model data from a file, setting up OpenGL buffers,
 * and drawing the model with appropriate materials and textures.
 */
class Model {
public:
    /**
     * @brief Constructs a Model instance from a file path.
     * 
     * Internally calls loadModel(path) to load and process the model file using Assimp.
     * @param path Path to the model file (.obj)
     */
    Model(const std::string& path);
    ~Model();

    /**
     * @brief Draws the model.
     * 
     * For each sub-mesh, applies material properties (color or texture)
     * and issues the draw call.
     * 
     * @param shader The shader program to use when drawing.
     * @param boundingBoxMode If true, renders only bounding boxes.
     */
    void draw(Shader& shader, bool boundingBoxMode);

private:
    std::vector<SubMesh> subMeshes;      // List of all sub-meshes that make up the model.   

    /**
     * @brief Loads a model from the given file path.
     * 
     * Parses meshes and materials using Assimp, prepares sub-meshes.
     * @param path Path to the model file.
     */
    void loadModel(const std::string& path);

    /**
     * @brief Sets up OpenGL buffers for a given sub-mesh.
     * 
     * Creates VAO, VBO, and EBO and configures vertex attributes.
     * 
     * @param mesh The sub-mesh to set up.
     * @param vertices Vertex data (positions, normals, texture coords).
     * @param indices Index data (triangles).
     */
    void setupSubMesh(SubMesh& mesh,
                      const std::vector<GLfloat>& vertices,
                      const std::vector<GLuint>& indices);
};
