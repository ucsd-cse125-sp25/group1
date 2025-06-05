#pragma once
#include "button.hpp"

class LeftPortraitButton : public Button {
  public:
    LeftPortraitButton(glm::vec2 spritePos);
    ~LeftPortraitButton();
    void onClick() override;
};
