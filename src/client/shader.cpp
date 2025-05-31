#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

static GLuint compileShaderFromFile(const std::string& path, GLenum type) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open shader file: " << path << "\n";
        return 0; // invalid shader
    }

    std::stringstream sourceStream;
    sourceStream << file.rdbuf();

    std::string sourceStr = sourceStream.str();
    const char* source = sourceStr.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
    : Shader(vertPath, fragPath, "") {}

Shader::Shader(const std::string& vertPath, const std::string& fragPath,
               const std::string& geomPath) {
    GLuint vertex = compileShaderFromFile(vertPath, GL_VERTEX_SHADER);
    GLuint fragment = compileShaderFromFile(fragPath, GL_FRAGMENT_SHADER);
    GLuint geometry = 0;

    bool hasGeometry = !geomPath.empty();

    if (hasGeometry) {
        geometry = compileShaderFromFile(geomPath, GL_GEOMETRY_SHADER);
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    if (hasGeometry)
        glAttachShader(id, geometry);
    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (hasGeometry)
        glDeleteShader(geometry);
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool val) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(val));
}

void Shader::setInt(const std::string& name, int val) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::setFloat(const std::string& name, float val) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::setVec3(const std::string& name, const glm::vec3& val) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &val[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
