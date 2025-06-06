#pragma once
#include "button.hpp"

class QuitButton : public Button {
  public:
    QuitButton(glm::vec2 spritePos);
    ~QuitButton();
    void onClick() override;
};
