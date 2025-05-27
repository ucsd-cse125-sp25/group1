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

void CanvasImage::onWindowUpdate(int width, int height) {
    float widthOffset = (1600.0f / (float)width);
    float heightOffset = (900.0f / (float)height);
    uiELement->changeDimensions(glm::vec2(widthOffset, heightOffset));
}

std::string CanvasImage::getName() {
    return name;
}
