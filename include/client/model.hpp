#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.hpp"

struct SubMesh {
    GLuint vao, vbo, ebo;
    GLuint indexCount;
    glm::vec3 color;

    GLuint textureId = 0;
    bool hasTexture = false;

    void draw() const {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

class Model {
public:
    Model(const std::string& path);
    ~Model();

    void draw(Shader& shader);

private:
    std::vector<SubMesh> subMeshes;

    void loadModel(const std::string& path);
    void setupSubMesh(SubMesh& mesh,
                      const std::vector<GLfloat>& vertices,
                      const std::vector<GLuint>& indices);
};
