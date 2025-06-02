#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "firefly.hpp"
#include "shader.hpp"

/**
 * Handles drawing fireflies using point sprites.
 * Sets up the OpenGL buffers and draws each firefly with blending.
 */
class FireflyRenderer {
  public:
    /**
     * Sets up the VAO, VBO, and shader needed to render fireflies.
     */
    FireflyRenderer();

    /**
     * Frees OpenGL resources.
     */
    ~FireflyRenderer();

    /**
     * Draws all fireflies using the current view and projection matrices.
     *
     * @param fireflies The list of fireflies to draw.
     * @param view The camera's view matrix.
     * @param projection The camera's projection matrix.
     */
    void draw(const std::vector<Firefly>& fireflies, const glm::mat4& view,
              const glm::mat4& projection);

  private:
    GLuint vao, vbo;
    Shader shader;

    /**
     * Sets up a single point used to render all fireflies.
     */
    void setup();
};
