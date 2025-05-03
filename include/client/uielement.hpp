#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.hpp"

class UIElement {
public:
	UIElement();
	~UIElement();

	void draw(Shader& shader);
private:
	GLuint vao, vbo, ebo;
	GLuint texture = 0;
};