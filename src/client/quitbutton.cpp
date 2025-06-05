#include <iostream>
#include "quitbutton.hpp"

QuitButton::QuitButton(glm::vec2 spritePos) : Button() {
    this->spritePos = spritePos;
    rectPos = glm::vec2(360.0f, 860.0f);
    rect = glm::vec2(240.0f, 90.0f);

    scale = glm::vec2(.5f, .5f);

    texture = {"../src/client/ui/lobby_quit.png", glm::vec2(758.0f, 208.0f),
               glm::vec2(379.0f, 208.0f)};

    sprite =
        new CanvasImage(glm::vec3(this->spritePos, 0.0f), scale, glm::vec2(0.0f, 0.0f), texture);
}

QuitButton::~QuitButton() {
    delete sprite;
}

void QuitButton::onClick() {
    if (!hovered || pressed)
        return;
    pressed = true;

    std::cout << "QUIT" << std::endl;
}
