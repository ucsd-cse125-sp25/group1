#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class UIElement {
public:
	UIElement();
	~UIElement();

	void draw() const;
private:
	GLuint vao, vbo, ebo;
};