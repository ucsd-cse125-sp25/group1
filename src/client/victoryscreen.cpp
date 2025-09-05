#include "victoryscreen.hpp"

VictoryScreen::VictoryScreen(glm::vec2 pos) {
    name = "victoryscreen";
    position = glm::vec2(pos.x, pos.y);
    hidden = true;
    scale = glm::vec2(2.0f, 2.0f);
    uiTexture = {"../src/client/ui/victory_screen.png", glm::vec2(1600.0f, 900.0f),
                 glm::vec2(1600.0f, 900.0f)};
    uiELement = new UIElement(glm::vec3(position.x, position.y, 0.0f), scale, initialSpriteCoords,
                              uiTexture);
}

void VictoryScreen::onWindowUpdate(int width, int height) {
    //float widthOffset = (1600.0f / (float)width);
    //float heightOffset = (900.0f / (float)height);
    //float xPos = -(uiELement->getBaseWidth() * widthOffset) / 2;

    //uiELement->changeDimensions(glm::vec2(widthOffset, heightOffset));
    //uiELement->changePosition(glm::vec2(xPos, uiELement->getPosition().y));
}

VictoryScreen::~VictoryScreen() {
    delete uiELement;
}
