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
private:
	GLfloat width, height;
	glm::vec3 position;
	GLuint vao, vbo, ebo;
	GLuint texture = 0;
};