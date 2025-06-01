#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "shader.hpp"

class Scene;

/**
 * @brief Handles shadow rendering for point lights using a depth cubemap.
 *
 * Sets up and manages a framebuffer and cubemap texture to capture shadows
 * in all directions from a point light source.
 */
class ShadowMap {
  public:
    /**
     * @brief Creates a shadow map for a point light at the given position.
     * @param lightPos World position of the light.
     * @param resolution Size of each cubemap face.
     */
    ShadowMap(glm::vec3 lightPos, int resolution);

    /**
     * @brief Cleans up OpenGL resources.
     */
    ~ShadowMap();

    /**
     * @brief Initializes the cubemap texture and framebuffer.
     */
    void init();

    /**
     * @brief Prepares for shadow rendering by binding the framebuffer
     * and uploading projection-view matrices for the cubemap faces.
     */
    void begin();

    /**
     * @brief Ends shadow rendering and restores the previous viewport.
     */
    void end();

    /**
     * @return Shader used to render the shadow map.
     */
    Shader& getShader() {
        return shader;
    }

    /**
     * @return OpenGL texture ID of the depth cubemap.
     */
    GLuint getDepthCubemap() const {
        return depthCubemap;
    }

  private:
    glm::vec3 lightPos;

    GLuint depthCubemap;
    GLuint fbo;
    unsigned int resolution;

    Shader shader;
    GLint prevViewport[4];
};

/**
 * @brief Returns a reusable 1x1 dummy depth cubemap.
 */
GLuint getDummyCubemap();
