#pragma once
#include <string>
#include <unordered_map>
#include "compass.hpp"
#include "crosshair.hpp"
#include "timerdisplay.hpp"
class Canvas {
  public:
    Canvas();
    ~Canvas();
    void draw(Shader& shader);
    void updateWindow(int width, int height);
    CanvasElement* findElement(const std::string name);

  private:
    std::unordered_map<std::string, CanvasElement*> elements;

    Crosshair* crosshair;
    glm::vec2 crosshairPos = glm::vec2(0.0f, 0.0f);

    TimerDisplay* timerdisplay;
    glm::vec2 timerPos = glm::vec2(-1.0f, 1.0f);

    Compass* compass;
    glm::vec2 compassPos = glm::vec2(0.7f, 1.0f);
};
