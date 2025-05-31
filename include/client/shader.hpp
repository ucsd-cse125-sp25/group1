#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

/**
 * @brief Encapsulates an OpenGL shader program.
 *
 * Handles loading, compiling, linking, and using vertex and fragment shaders,
 * and provides convenient methods to set uniform variables.
 */
class Shader {
  public:
    /**
     * @brief Constructs a Shader instance from vertex and fragment shader files.
     *
     * Loads, compiles, and links the shaders into a shader program.
     *
     * @param vertPath Path to the vertex shader source file.
     * @param fragPath Path to the fragment shader source file.
     */
    Shader(const std::string& vertPath, const std::string& fragPath);

    /**
     * @brief Constructs a Shader instance from vertex, fragment, and geometry shader files.
     *
     * Loads, compiles, and links the shaders into a shader program.
     *
     * @param vertPath Path to the vertex shader source file.
     * @param fragPath Path to the fragment shader source file.
     * @param geomPath Path to the geometry shader source file.
     */
    Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);

    /**
     * @brief Activates the shader program for rendering.
     */
    void use() const;

    /**
     * @brief Sets a boolean uniform variable in the shader.
     *
     * @param name Name of the uniform variable.
     * @param val Boolean value to set.
     */
    void setBool(const std::string& name, bool val) const;

    /**
     * @brief Sets an integer uniform variable in the shader.
     *
     * @param name Name of the uniform variable.
     * @param val Integer value to set.
     */
    void setInt(const std::string& name, int val) const;

    /**
     * @brief Sets a float uniform variable in the shader.
     *
     * @param name Name of the uniform variable.
     * @param val Float value to set.
     */
    void setFloat(const std::string& name, float val) const;

    /**
     * @brief Sets a vec3 uniform variable in the shader.
     *
     * @param name Name of the uniform variable.
     * @param val glm::vec3 value to set.
     */
    void setVec3(const std::string& name, const glm::vec3& val) const;

    /**
     * @brief Sets a mat4 uniform variable in the shader.
     *
     * @param name Name of the uniform variable.
     * @param mat glm::mat4 value to set.
     */
    void setMat4(const std::string& name, const glm::mat4& mat) const;

  private:
    GLuint id; // OpenGL shader program ID.
};
