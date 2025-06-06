#pragma once
#include "button.hpp"

class PlayButton : public Button {
  public:
    PlayButton(glm::vec2 spritePos);
    ~PlayButton();
    void onClick() override;
};
