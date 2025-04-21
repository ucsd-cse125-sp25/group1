#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
    std::ifstream vertFile(vertPath);
    std::ifstream fragFile(fragPath);

    std::stringstream vertStream, fragStream;
    vertStream << vertFile.rdbuf();
    fragStream << fragFile.rdbuf();

    std::string vertStr = vertStream.str();
    std::string fragStr = fragStream.str();
    const char* vert = vertStr.c_str();
    const char* frag = fragStr.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vert, nullptr);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &frag, nullptr);
    glCompileShader(fragment);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
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
