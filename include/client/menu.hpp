#pragma once
#include <memory>
#include <vector>
#include "canvasimage.hpp"
class Menu {
  public:
    Menu(int playerId);
    ~Menu();
    void render();

    //  public:
    //    GLFWwindow* window;

  private:
    int playerId;
    std::unique_ptr<Shader> uiShader;
    UITexture backgroundTexture = {"../src/client/ui/lobby_wallpaper.png",
                                   glm::vec2(1600.0f, 900.0f), glm::vec2(1600.0f, 900.0f)};
    UITexture logoTexture = {"../src/client/ui/logo.png", glm::vec2(775.0f, 580.0f),
                             glm::vec2(775.0f, 580.0f)};

//    std::vector<CanvasElement*> elements;
    CanvasImage* background;
    CanvasImage* logo;
};
