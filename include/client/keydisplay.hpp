#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "canvaselement.hpp"
#include "uielement.hpp"

class KeyDisplay : public CanvasElement {
  public:
    KeyDisplay(glm::vec2 position);
    ~KeyDisplay();
    void draw(Shader& shader) override;
    void setHidden(bool val) override;
    std::string getName() override;

  private:
    bool hidden = false;
    std::string name = "keydisplay";
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 initialSpriteCoords = glm::vec2(0.0f, 0.0f);
    std::vector<UIElement*> keys;
    UITexture uiTexture;
};
