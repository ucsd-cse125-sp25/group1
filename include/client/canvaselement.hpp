#pragma once
#include "shader.hpp"
#include <string>
class CanvasElement {
public:
	virtual void draw(Shader& shader) = 0;
	virtual void setHidden(bool val) = 0;
	virtual std::string getName() = 0;
};