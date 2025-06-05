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
    void joinQueue();
    bool queuePlayer(int id);
    void dequeuePlayer(int id);
  public:
    GLFWwindow* window;

    unsigned int selectedCharacter = 0;
    bool availableCharacters[4] = {true, true, true, true};
    bool ready = false; 
  private:
    int playerId;
    unsigned int queuedPlayers = 0;
    int hoveredButton = -1;
    bool allPlayerStatus[4] = {false, false, false, false};

    glm::vec2 spriteMap[4] = {glm::vec2(0.0f, 0.0f), glm::vec2(644.0f, 0.0f),
                              glm::vec2(644.0f, 826.0f), glm::vec2(0.0f, 826.0f)};

    std::unique_ptr<Shader> uiShader;
    UITexture backgroundTexture = {"../src/client/ui/lobby_wallpaper.png",
                                   glm::vec2(1600.0f, 900.0f), glm::vec2(1600.0f, 900.0f)};
    UITexture logoTexture = {"../src/client/ui/logo.png", glm::vec2(775.0f, 580.0f),
                             glm::vec2(775.0f, 580.0f)};
    UITexture portraitTexture = {"../src/client/ui/lobby_frame.png", glm::vec2(1288.0f, 1652.0f),
                                 glm::vec2(644.0f, 826.0f)};
    UITexture p1Texture = {"../src/client/ui/one_status.png", glm::vec2(644.0f, 92.0f),
                                 glm::vec2(322.0f, 92.0f)};
    UITexture p2Texture = {"../src/client/ui/two_status.png", glm::vec2(644.0f, 92.0f),
                           glm::vec2(322.0f, 92.0f)};
    UITexture p3Texture = {"../src/client/ui/three_status.png", glm::vec2(644.0f, 92.0f),
                           glm::vec2(322.0f, 92.0f)};
    UITexture p4Texture = {"../src/client/ui/four_status.png", glm::vec2(644.0f, 92.0f),
                           glm::vec2(322.0f, 92.0f)};

    std::vector<CanvasElement*> elements;
    CanvasImage* background;
    CanvasImage* logo;
    CanvasImage* portrait;
    CanvasImage* p1Status;
    CanvasImage* p2Status;
    CanvasImage* p3Status;
    CanvasImage* p4Status;
    
    std::vector<Button*> buttons;
    PlayButton* playButton;
    QuitButton* quitButton;
    LeftPortraitButton* leftButton;
    RightPortraitButton* rightButton;
};
