#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.hpp"

class UIElement {
public:
	UIElement(glm::vec3 position, const std::string filePath);
	UIElement(glm::vec3 position, GLfloat rectWidth, GLfloat rectHeight, const std::string filePath);
	~UIElement();
	void draw(Shader& shader);
	void changeSprite(glm::vec2 coords);
private:
	GLfloat width, height;
	glm::vec3 position;
	GLuint vao, ebo;
	GLuint vbo[2];
	GLuint texture = 0;
};