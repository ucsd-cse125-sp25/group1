#include "interactdisplay.hpp"

InteractDisplay::InteractDisplay(glm::vec2 pos) {
    name = "interactdisplay";
    position = glm::vec2(pos.x, pos.y);
    scale = glm::vec2(0.6f, 0.6f);
    uiTexture = {"../src/client/ui/interact.png", glm::vec2(1024.0f, 1024.0f),
                 glm::vec2(1024.0f, 1024.0f)};
    uiELement = new UIElement(glm::vec3(position.x, position.y, 0.0f), scale, initialSpriteCoords,
                              uiTexture);
}

void InteractDisplay::onWindowUpdate(int width, int height) {
    float widthOffset = (1600.0f / (float)width);
    float heightOffset = (900.0f / (float)height);
    float xPos = -(uiELement->getBaseWidth() * widthOffset) / 2;

    uiELement->changeDimensions(glm::vec2(widthOffset, heightOffset));
    uiELement->changePosition(glm::vec2(xPos, uiELement->getPosition().y));
}

InteractDisplay::~InteractDisplay() {
    delete uiELement;
}
