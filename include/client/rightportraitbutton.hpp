#pragma once
#include "button.hpp"

class RightPortraitButton : public Button {
  public:
    RightPortraitButton(glm::vec2 spritePos);
    ~RightPortraitButton();
    void onClick() override;
};
