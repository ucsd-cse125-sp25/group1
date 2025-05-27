#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "shader.hpp"
#include "uitexture.hpp"

class UIElement {
public:
	UIElement(glm::vec3 position, glm::vec2 scale, glm::vec2 initSpriteCoords, UITexture& uiTexture);
	UIElement(glm::vec3 position, glm::vec2 initSpriteCoords, UITexture& uiTexture);

	~UIElement();
	void draw(Shader& shader);
	void changeSprite(glm::vec2 coords);
	void changeDimensions(glm::vec2 dim);
	void rotate(float deg);
public:
	GLfloat widthModifier, heightModifier;
	glm::vec2 positionModifier;
	glm::vec3 position;

private:
	GLfloat baseWidth, baseHeight, angle;

	GLuint vao, ebo;
	GLuint vbo[2];
	GLuint texture = 0;

	UITexture uiTexture;

    UITexture uiTexture;

    const GLuint indices[6] = {
        0, 2, 1, 0, 3, 2 // Front
    };

    const GLfloat posCols[24] = {
        // positions          // colors
        1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 0.0f};

    const GLfloat texCoords[8] = {
        0.0f, 0.0f, // top right
        0.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 0.0f  // top left
    };
};
