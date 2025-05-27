#include <glad/glad.h>
#include <vector>
#include "skinnedVertex.hpp"

/**
 * @brief A GPU-ready sub-mesh used in skeletal animation.
 */
struct AnimatedSubMesh {
    std::vector<SkinnedVertex> vertices;
    std::vector<GLuint> indices;

    GLuint vao, vbo, ebo;

    /**
     * @brief Sets up the VAO, VBO, and EBO for rendering this sub-mesh with OpenGL.
     *
     * This uploads the vertex and index data to the GPU and configures
     * all vertex attributes needed for skeletal animation.
     *
     * Attribute layout:
     * - location 0: vec3 position
     * - location 1: vec3 normal
     * - location 2: vec2 texCoords
     * - location 3: ivec4 boneIDs
     * - location 4: vec4 weights
     */
    void setup();

    /**
     * @brief Draws the sub-mesh.
     */
    void draw() const;
};
