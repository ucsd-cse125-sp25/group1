#pragma once
#include "canvasimage.hpp"

class Compass : public CanvasImage {
public:
	Compass(glm::vec2 pos);
	~Compass();
	void draw(Shader& shader) override;
	void rotate(glm::vec3 dir);
	void onWindowUpdate(int width, int height) override;
private:
	UIElement* compassHands;
	UITexture handsTexture;
};