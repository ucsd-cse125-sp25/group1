#include "crosshair.hpp"

Crosshair::Crosshair(glm::vec2 pos) {
    name = "crosshair";
    glm::vec2 offset = glm::vec2(-(64.0f / 1600.0f), (64.0f / 900.0f));
    position = glm::vec2(pos.x + offset.x, pos.y + offset.y);
    scale = glm::vec2(.2f, .35f);
    uiTexture = {"../src/client/ui/crosshair_interact.png", glm::vec2(128.0f, 128.0f),
                 glm::vec2(128.0f, 128.0f)};
    uiELement = new UIElement(glm::vec3(position.x, position.y, 0.0f), scale, initialSpriteCoords,
                              uiTexture);
}

Crosshair::~Crosshair() {
    delete uiELement;
}
