#pragma once
#include "canvasimage.hpp"
#include <GLFW/glfw3.h>


class Button {
  public:
    Button();
    ~Button();
    virtual void onClick();
    bool update(int xPos, int yPos);
    void draw(Shader& shader);
    bool pressed = false;
    bool hovered = false;

  protected:
    UITexture texture;
    CanvasImage* sprite;
    glm::vec2 rectPos;
    glm::vec2 rect;
    glm::vec2 scale;
    glm::vec2 spritePos;
};
