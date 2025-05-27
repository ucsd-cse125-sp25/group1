#pragma once
#include <string>
#include "shader.hpp"
class CanvasElement {
  public:
    virtual void draw(Shader& shader) = 0;
    virtual void setHidden(bool val) = 0;
    virtual void onWindowUpdate(int width, int height) = 0;
    virtual std::string getName() = 0;
};
