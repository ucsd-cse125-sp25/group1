#pragma once
#include <memory>
#include <vector>
#include "canvasimage.hpp"
#include "playbutton.hpp"
#include "quitbutton.hpp"
#include <GLFW/glfw3.h>


class Menu {
  public:
    Menu(int playerId);
    ~Menu();
    void onMouseCallBack(GLFWwindow* window, int button, int action, int mods);
    void init(GLFWwindow* window);
    void run();
    void render();

  public:
    GLFWwindow* window;

  private:
    int playerId;
    std::unique_ptr<Shader> uiShader;
    UITexture backgroundTexture = {"../src/client/ui/lobby_wallpaper.png",
                                   glm::vec2(1600.0f, 900.0f), glm::vec2(1600.0f, 900.0f)};
    UITexture logoTexture = {"../src/client/ui/logo.png", glm::vec2(775.0f, 580.0f),
                             glm::vec2(775.0f, 580.0f)};
    UITexture portraitTexture = {"../src/client/ui/lobby_frame.png", glm::vec2(1288.0f, 1652.0f),
                                 glm::vec2(644.0f, 826.0f)};

    //    std::vector<CanvasElement*> elements;
    CanvasImage* background;
    CanvasImage* logo;
    CanvasImage* portrait;
    PlayButton* playButton;
    QuitButton* quitButton;
    std::vector<Button*> buttons;
    int hoveredButton = -1;
};
