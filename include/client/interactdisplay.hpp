#pragma once
#include <glm/glm.hpp>
#include "canvasimage.hpp"

class InteractDisplay : public CanvasImage {
  public:
    InteractDisplay(glm::vec2 pos);
    ~InteractDisplay();
    void onWindowUpdate(int width, int height) override;
};
