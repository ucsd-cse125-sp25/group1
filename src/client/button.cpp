#include "button.hpp"
#include <iostream>

Button::Button() {}

Button::~Button() {}

void Button::onClick() {
    if (!hovered || pressed)
        return;
    pressed = true;
    std::cout << "CLICK" << std::endl;
}

bool Button::update(int xPos, int yPos) {

    // glfwGetCursorPos(xpos, ypos);
    //std::cout << "(" << xPos << "," << yPos << ")" << std ::endl;
    if ((xPos > rectPos.x && xPos < (rectPos.x + rect.x)) &&
        (yPos > rectPos.y && yPos < (rectPos.y + rect.y))) {
        if (!hovered) {
            hovered = true;
            sprite->changeSprite(glm::vec2(texture.spriteDimensions.x, 0.0f));
            // std::cout << "HOVER" << std::endl;
        }
        return true;
    } else {
        if (hovered) {
            hovered = false;
            sprite->changeSprite(glm::vec2(0.0f, 0.0f));
        }
    }
    return false;
}

void Button::draw(Shader& shader) {
    if (!active)
        return;
    sprite->draw(shader);
}
