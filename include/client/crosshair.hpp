#pragma once
#include <glm/glm.hpp>
#include "canvasimage.hpp"

class Crosshair : public CanvasImage {
  public:
    Crosshair(glm::vec2 pos);
    ~Crosshair();
};
