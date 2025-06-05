#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "canvasimage.hpp"
#include "uielement.hpp"

class KeyDisplay : public CanvasImage {
  public:
    KeyDisplay(glm::vec2 pos);
    ~KeyDisplay();
    void onCollectKey();
    void onRemoveKey();

  private:
    unsigned int collectedKeys = 0;
    glm::vec2 spriteMap[4] = {glm ::vec2(0.0f, 1024.0f), glm ::vec2(1024.0f, 1024.0f),
                              glm ::vec2(0.0f, 0.0f), glm ::vec2(1024.0f, 0.0f)};
};
