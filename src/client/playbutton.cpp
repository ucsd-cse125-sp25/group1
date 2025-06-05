#include "playbutton.hpp"
#include <iostream>

PlayButton::PlayButton(glm::vec2 spritePos) : Button() {
    this->spritePos = spritePos;
    rectPos = glm::vec2(276.0f, 631.0f);
    rect = glm::vec2(409.0f, 163.0f);

    scale = glm::vec2(.5f, .5f);

    texture = {"../src/client/ui/lobby_play.png", glm::vec2(758.0f, 208.0f),
               glm::vec2(379.0f, 208.0f)};

    sprite =
        new CanvasImage(glm::vec3(this->spritePos, 0.0f), scale, glm::vec2(0.0f, 0.0f), texture);
}

PlayButton::~PlayButton() {
    delete sprite;
}

void PlayButton::onClick() {
    if (!hovered || pressed)
        return;
    pressed = true;

    std::cout << "PLAY" << std::endl;
}
