#pragma once
#include <glm/glm.hpp>
#include <string>
#include "canvaselement.hpp"
#include "uielement.hpp"
#include "uitexture.hpp"

class CanvasImage : public CanvasElement {
public:
	CanvasImage();
	~CanvasImage();
	void draw(Shader& shader) override;
	void setHidden(bool val) override;
	std::string getName() override;
	void changeSprite(glm::vec2 coords);
	void onWindowUpdate(int width, int height) override;
protected:
	bool hidden = false;
	std::string name = "canvasimage";
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 initialSpriteCoords = glm::vec2(0.0f, 0.0f);
	UITexture uiTexture;
	UIElement* uiELement;
};