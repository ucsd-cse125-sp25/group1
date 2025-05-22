#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

/**
 * @brief A 3D cube that can be drawn with OpenGL.
 *
 * Sets up the cube's data and handles drawing it.
 */
class Cube {
  public:
    /**
     * @brief Constructs a Cube instance.
     *
     * Sets up the vertex array object (VAO), vertex buffer object (VBO),
     * and element buffer object (EBO) with predefined vertex and index data.
     */
    Cube();

    /**
     * @brief Destroys the Cube instance.
     *
     * Deletes the VAO, VBO, and EBO to free GPU resources.
     */
    ~Cube();

    /**
     * @brief Draws the cube.
     *
     * Binds the VAO and issues a draw call to render the cube.
     */
    void draw() const;

  private:
    GLuint vao, vbo, ebo;
};
