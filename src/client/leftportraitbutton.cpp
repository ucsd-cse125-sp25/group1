#include <iostream>
#include "leftportraitbutton.hpp"

LeftPortraitButton::LeftPortraitButton(glm::vec2 spritePos) : Button() {
    this->spritePos = spritePos;
    rectPos = glm::vec2(1145.0f, 825.0f);
    rect = glm::vec2(118.0f, 80.0f);

    scale = glm::vec2(0.85f, 1.8f);

    texture = {"../src/client/ui/left_arrow.png", glm::vec2(1288.0f, 826.0f),
               glm::vec2(644.0f, 826.0f)};

    sprite =
        new CanvasImage(glm::vec3(this->spritePos, 0.0f), scale, glm::vec2(0.0f, 0.0f), texture);
}

LeftPortraitButton::~LeftPortraitButton() {
    delete sprite;
}

void LeftPortraitButton::onClick() {
    if (!hovered || pressed)
        return;
    pressed = true;

    std::cout << "Left" << std::endl;
}
