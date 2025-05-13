#pragma once
#include "canvasimage.hpp"

class Compass : public CanvasImage{
public:
	Compass(glm::vec2 pos);
	~Compass();
	void rotate(glm::vec3 dir);
};