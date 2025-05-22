#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include "shader.hpp"
#include "uielement.hpp"
#include "uitexture.hpp"

class TimerDisplay {
  public:
    TimerDisplay();
    TimerDisplay(int lMin, int rMin, int lSec, int rSec);
    ~TimerDisplay();
    void draw(Shader& shader);
    void updateTimer(int minutes, int seconds);

  private:
    glm::vec2 pos;
    const float digitGap = .32f;
    const glm::vec2 scale = glm::vec2(.4f, .5f);

    int lMinute_val;
    int rMinute_val;
    int lSecond_val;
    int rSecond_val;

    UITexture uiTexture = {"../src/client/ui/timer-atlas.png", glm::vec2(384.0f, 512.0f),
                           glm::vec2(128.0f, 128.0f)};

    UIElement* lMinute;
    UIElement* rMinute;
    UIElement* lSecond;
    UIElement* rSecond;

    glm::vec2 spriteMap[10] = {glm::vec2(128.0f, 0.0f),   glm::vec2(0.0f, 384.0f),
                               glm::vec2(128.0f, 384.0f), glm::vec2(256.0f, 384.0f),
                               glm::vec2(0.0f, 256.0f),   glm::vec2(128.0f, 256.0f),
                               glm::vec2(256.0f, 256.0f), glm::vec2(0.0f, 128.0f),
                               glm::vec2(128.0f, 128.0f), glm::vec2(256.0f, 128.0f)};
};
