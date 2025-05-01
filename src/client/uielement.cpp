#include "uielement.hpp"
#include <iostream>
#include <stb_image.h>

static const GLfloat vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3+3+2) * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3+3+2) * sizeof(float), (void*)(3 * sizeof(float)));   // color
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)(6 * sizeof(float)));   // texture pos
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

UIElement::~UIElement() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void UIElement::draw(Shader& shader) const{
    shader.use();
    shader.setInt("ourTexture", 0);
    unsigned int texture;
    glGenTextures(1, &texture); // glGenTextures takes the number of textures we want to generate (1 in our case) and stores it in an unsigned int array
    glBindTexture(GL_TEXTURE_2D, texture);   // just like other objects (vao, vbo, etc.) we gotta bind our texture so opengl knows what to reference

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;	//nrChannels = number of color channels
    unsigned char* data = stbi_load("../src/client/ui/banana.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        /**
        * glTexImage is what's gonna generate the texture for us
        * 1st arg: indicates what kind of texture we'll generate (1D, 2D, 3D)
        * 2nd arg: the mipmap level we wanna create a texture for. If you wanna set the mipmap textues manually, you can use
        * this argument. Since our texture is only rendered in 1 distance, we use the base level 0
        * 3rd arg: tells OpenGL what format we wanna store texture in. In our case we'll use RGB
        * 4th/5th arg: width and height of the generated texture
        * 6th arg: always 0, legacy stuff.
        * 7th/8th arg: format and datatype of the source image. In our case, the image was loaded w/ RGB values and stored as a series of unsigned chars.
        * 9th: the actual image data
        */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);  //good practice to free up the image memory after we generate our texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);   // just like other objects (vao, vbo, etc.) we gotta bind our texture so opengl knows what to reference

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //6 indices
    glBindVertexArray(0);
}