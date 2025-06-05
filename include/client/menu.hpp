#pragma once
#include <memory>
#include <vector>
#include "canvasimage.hpp"
#include "playbutton.hpp"
#include "quitbutton.hpp"
#include "leftportraitbutton.hpp"
#include "rightportraitbutton.hpp"
#include <GLFW/glfw3.h>

class Menu {
  public:
    Menu(int playerId);
    ~Menu();
    void onMouseCallBack(GLFWwindow* window, int button, int action, int mods);
    void init(GLFWwindow* window);
    void run();
    void render();
    void changeCharacter(int val);

  public:
    GLFWwindow* window;
    unsigned int selectedCharacter = 0;
    unsigned bool availableCharacters[4] = {true, true, true, true};
  private:
    int playerId;
    int hoveredButton = -1;

    glm::vec2 spriteMap[4] = {glm::vec2(0.0f, 0.0f), glm::vec2(644.0f, 0.0f),
                               glm::vec2(0.0f, 826.0f), glm::vec2(644.0f, 826.0f)};

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
    LeftPortraitButton* leftButton;
    RightPortraitButton* rightButton;
    std::vector<Button*> buttons;
};
