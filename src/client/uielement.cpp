#include "uielement.hpp"
#include <iostream>
#include <stb_image.h>
#include <string>

UIElement::UIElement(glm::vec3 position, glm::vec2 scale, glm::vec2 initSpriteCoords,
                     UITexture& uiTexture) {
    this->position = position;
    this->baseWidth = scale.x;
    this->baseHeight = scale.y;
    this->widthModifier = 1.0f;
    this->heightModifier = 1.0f;
    this->uiTexture = uiTexture;
    this->angle = 0.0f;

    this->positionModifier = glm::vec2(1.0f, 1.0f);

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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float))); // color
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // texture pos
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // -> This line causes the weird line to show up
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data =
        stbi_load(this->uiTexture.filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    changeSprite(initSpriteCoords);
}

UIElement::UIElement(glm::vec3 position, glm::vec2 initSpriteCoords, UITexture& uiTexture) {
    this->position = position;
    this->baseWidth = 1.0f;
    this->baseHeight = 1.0f;
    this->widthModifier = 1.0f;
    this->heightModifier = 1.0f;
    this->uiTexture = uiTexture;
    this->angle = 0.0f;

    this->positionModifier = glm::vec2(1.0f, 1.0f);

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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float))); // color
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // texture pos
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // -> This line causes the weird line to show up
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data =
        stbi_load(this->uiTexture.filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    changeSprite(initSpriteCoords);
}

UIElement::~UIElement() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
    glDeleteBuffers(1, &ebo);
}

void UIElement::changeSprite(glm::vec2 coords) {

    float atlasWidth = uiTexture.atlasDimensions.x;
    float atlasHeight = uiTexture.atlasDimensions.y;
    float spriteWidth = uiTexture.spriteDimensions.x;
    float spriteHeight = uiTexture.spriteDimensions.y;

    float uMin = coords.x / atlasWidth;
    float vMin = coords.y / atlasHeight;
    float uMax = (coords.x + spriteWidth) / atlasWidth;
    float vMax = (coords.y + spriteHeight) / atlasHeight;

    float spriteCoords[] = {
        uMax, vMax, // top right
        uMax, vMin, // bottom right
        uMin, vMin, // bottom left
        uMin, vMax  // top left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(spriteCoords), spriteCoords);
}

void UIElement::changeDimensions(glm::vec2 dim) {
    this->widthModifier = dim.x;
    this->heightModifier = dim.y;
}

void UIElement::changePosition(glm::vec2 pos) {
    this->position = glm::vec3(pos, 0.0f);
}

void UIElement::rotate(float deg) {
    this->angle = deg;
}

void UIElement::draw(Shader& shader) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.setInt("ourTexture", 0);
    shader.setVec3("origin", glm::vec3(position.x * positionModifier.x,
                                       position.y * positionModifier.y, position.z));
    shader.setFloat("width", this->widthModifier * this->baseWidth);
    shader.setFloat("height", this->heightModifier * this->baseHeight);
    shader.setFloat("angle", glm::radians(this->angle));

    //    glViewport(0, 0, 1600, 900);

    glDepthMask(GL_FALSE); // Disable writing to the depth buffer

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // just like other objects (vao, vbo, etc.) we gotta bind
                                           // our texture so opengl knows what to reference

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 6 indices
    glDepthMask(GL_TRUE);                                // Enable writing to the depth buffer
    glDisable(GL_BLEND);

    glBindVertexArray(0);
}
