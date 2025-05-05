#include "uielement.hpp"
#include <iostream>
#include <stb_image.h>
#include <string>

float atlasWidth = 384.0f;
float atlasHeight = 512.0f;

float spriteX = 256.0f;
float spriteY = 384.0f;
float spriteWidth = 128.0f;
float spriteHeight = 128.0f;

float uMin = spriteX / atlasWidth;
float vMin = spriteY / atlasHeight;
float uMax = (spriteX + spriteWidth) / atlasWidth;
float vMax = (spriteY + spriteHeight) / atlasHeight;

static const GLfloat vertices[] = {
    // positions          // colors           // texture coords
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   uMax, vMax,   // top right
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   uMax, vMin,   // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   uMin, vMin,   // bottom left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   uMin, vMax    // top left 
};

static const GLfloat posCols[] = {
    // positions          // colors           
    1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f
};

static const GLfloat texCoords[] = {
    uMax, vMax,   // top right
    uMax, vMin,   // bottom right
    uMin, vMin,   // bottom left
    uMin, vMax    // top left 
};

static const GLuint indices[] = {
    0,  2,  1,  0,  3,  2 // Front
};

UIElement::UIElement(glm::vec3 position, GLfloat rectWidth, GLfloat rectHeight, const std::string filePath) {
    this->position = position;
    this->width = rectWidth;
    this->height = rectHeight;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posCols), posCols, GL_STATIC_DRAW);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   // color
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);   // texture pos
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture); // glGenTextures takes the number of textures we want to generate (1 in our case) and stores it in an unsigned int array
    glBindTexture(GL_TEXTURE_2D, texture);   // just like other objects (vao, vbo, etc.) we gotta bind our texture so opengl knows what to reference
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width, height, nrChannels;	//nrChannels = number of color channels
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
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
        if(nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if(nrChannels == 4)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // ??? What happens if you construct a UI element, and then on some other class disable gl blend before rendering a transparent texture? Would the background still be transparent? 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);  //good practice to free up the image memory after we generate our texture
}

UIElement::UIElement(glm::vec3 position, const std::string filePath) {
    this->position = position;
    this->width = 1.0f;
    this->height = 1.0f;

    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posCols), posCols, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   // color
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);   // texture pos
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

UIElement::~UIElement() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
    glDeleteBuffers(1, &ebo);
}

void UIElement::changeSprite(glm::vec2 coords) {
    
    float uMin = coords.x / atlasWidth;
    float vMin = coords.y / atlasHeight;
    float uMax = (coords.x + spriteWidth) / atlasWidth;
    float vMax = (coords.y + spriteHeight) / atlasHeight;

    float spriteCoords[] = {
        uMax, vMax,   // top right
        uMax, vMin,   // bottom right
        uMin, vMin,   // bottom left
        uMin, vMax    // top left 
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(spriteCoords), spriteCoords);
}


void UIElement::draw(Shader& shader){
    
    //changeSprite(glm::vec2(128.0f, 0.0f));
    shader.use();
    shader.setInt("ourTexture", 0);
    shader.setVec3("origin", this->position);
    shader.setFloat("width", this->width);
    shader.setFloat("height", this->height);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);   // just like other objects (vao, vbo, etc.) we gotta bind our texture so opengl knows what to reference
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //6 indices
    glBindVertexArray(0);
}
