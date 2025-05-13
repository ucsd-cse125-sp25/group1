#include "canvasimage.hpp"

CanvasImage::CanvasImage() {}
CanvasImage::~CanvasImage() {}
void CanvasImage::changeSprite(glm::vec2 coords) {
	uiELement->changeSprite(coords);
}
void CanvasImage::draw(Shader& shader) {
	if (hidden)
		return;
	uiELement->draw(shader);
}
void CanvasImage::setHidden(bool val) {
	hidden = val;
}
std::string CanvasImage::getName() {
	return name;
}