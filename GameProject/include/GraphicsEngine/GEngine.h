#pragma once
#define GLFW_INCLUDE_NONE
#include <Math/ORect.h>
#include <memory>
#include <GraphicsEngine/OVertexArrayObject.h>
#include <GraphicsEngine/OVertexBufferDesc.h>
#include <GraphicsEngine/OShaderProgram.h>
#include <GraphicsEngine/OShaderProgramDesc.h>
#include<glad/glad.h>
/**
* TODO: Make sure you understand how shaders work and what the steps in setShaderProgram are actually doing.
*/
class GEngine {
public:
	GLuint shaderProgram;
	std::shared_ptr<OVertexArrayObject> createVertexArrayObject(const OVertexBufferDesc& data);
	std::shared_ptr<OShaderProgram> createShaderProgram(const OShaderProgramDesc& desc);
	GEngine();
	~GEngine();
	void clear();
	void setViewport(const ORect& size);
	void setVertexArrayObject(const std::shared_ptr<OVertexArrayObject>& vao);
	void setShaderProgram(const std::shared_ptr<OShaderProgram>& program);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
	void setShaderProgram();
private:
	const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";
	const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(0.514, 0.945, 0.839, 1.0); 
}
)";
};