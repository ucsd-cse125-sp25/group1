#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Cube {
public:
    Cube();
    ~Cube();

    void draw() const;

private:
    GLuint vao, vbo, ebo;
};
