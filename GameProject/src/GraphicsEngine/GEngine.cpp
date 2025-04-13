#include<GraphicsEngine/GEngine.h>
#include<glad/glad.h>
GEngine::GEngine(){
	this->test = 0;
}

GEngine::~GEngine(){}

void GEngine::clear() {
	glClearColor(255, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);	// Clears screen to whatever is set to be the clear color
}

void GEngine::setViewport(const ORect& size) {
	glViewport(size.left, size.top, size.width, size.height);
}