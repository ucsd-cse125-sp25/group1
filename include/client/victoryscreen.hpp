#pragma once
#include "canvasimage.hpp"

class VictoryScreen : public CanvasImage {
  public:
    VictoryScreen(glm::vec2 pos);
    ~VictoryScreen();
    void onWindowUpdate(int width, int height) override;
};
