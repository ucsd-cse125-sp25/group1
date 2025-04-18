#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const std::string& vertPath, const std::string& fragPath);

    void use() const;

    void setBool(const std::string& name, bool val) const;
    void setInt(const std::string& name, int val) const;
    void setFloat(const std::string& name, float val) const;
    void setVec3(const std::string& name, const glm::vec3& val) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    GLuint id;
};
