#include "uielement.hpp"
#include <iostream>

static const GLfloat vertices[] = {
    -0.3f, 0.7f,  0.2f,  0.0f,  0.0f,  1.0f,   //bottom left
    -0.3f, 0.9f,  0.2f,  0.0f,  0.0f,  1.0f,   //top left
     0.3f, 0.9f,  0.2f,  0.0f,  0.0f,  1.0f,   //top right
     0.3f, 0.7f,  0.2f,  0.0f,  0.0f,  1.0f    //bottom right
};
static const GLuint indices[] = {
    0,  2,  1,  0,  3,  2 // Front
};

UIElement::UIElement() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    /*Defining our first attribute, which will be position.
        * Index 0 means this is the first attribute
        * 3 means there will be 3 data points
        * GL_FLOAT means our attribute is of type float
        * GL_FALSE means that this attribute won't be normalized
        * (3+3) = 3 position values, 3 color values
        * Last 0 argument is the offset from the first attribute.Since this is the first attribute, there's no offset
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3+3) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3+3) * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

UIElement::~UIElement() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void UIElement::draw() const{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //6 indices
    glBindVertexArray(0);
}