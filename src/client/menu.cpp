#include "menu.hpp"
#include <algorithm>
#include <iostream>
Menu::Menu(int playerId) {
    this->playerId = playerId;
    uiShader =
        std::make_unique<Shader>("../src/client/shaders/ui.vert", "../src/client/shaders/ui.frag");

    background = new CanvasImage(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(2.0f, 2.0f),
                                 glm::vec2(0.0f, 0.0f), backgroundTexture);
    elements.push_back(background);
    
    logo = new CanvasImage(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.2f),
                           glm::vec2(0.0f, 0.0f), logoTexture);
    elements.push_back(logo);
    
    portrait = new CanvasImage(glm::vec3(0.1f, 0.9f, 0.0f), glm::vec2(0.85f, 1.8f), spriteMap[selectedCharacter],
                               portraitTexture);
    elements.push_back(portrait);
    
    p1Status = new CanvasImage(glm::vec3(-.85f, -0.35f, 0.0f), glm::vec2(.4f, .3f),
                               glm::vec2(0.0f, 0.0f), p1Texture);
    p1Status->setHidden(true);
    elements.push_back(p1Status);

    p2Status = new CanvasImage(glm::vec3(-.45f, -0.35f, 0.0f), glm::vec2(.4f, .3f),
                               glm::vec2(0.0f, 0.0f), p2Texture);
    p2Status->setHidden(true);
    elements.push_back(p2Status);

    p3Status = new CanvasImage(glm::vec3(-.85f, -0.7f, 0.0f), glm::vec2(.4f, .3f),
                               glm::vec2(0.0f, 0.0f), p3Texture);
    p3Status->setHidden(true);
    elements.push_back(p3Status);

    p4Status = new CanvasImage(glm::vec3(-.45f, -0.7f, 0.0f), glm::vec2(.4f, .3f),
                               glm::vec2(0.0f, 0.0f), p4Texture);
    p4Status->setHidden(true);
    elements.push_back(p4Status);

    playButton = new PlayButton(glm::vec2(-.75f, -.2f));
    buttons.push_back(playButton);

    quitButton = new QuitButton(glm::vec2(-.75f, -.55f));
    buttons.push_back(quitButton);

    leftButton = new LeftPortraitButton(glm::vec2(0.1f, 0.9f));
    buttons.push_back(leftButton);

    rightButton = new RightPortraitButton(glm::vec2(0.1f, 0.9f));
    buttons.push_back(rightButton);
}
Menu::~Menu() {
    for (unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
    for (unsigned int i = 0; i < buttons.size(); i++)
        delete buttons[i];
}

void Menu::onMouseCallBack(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        playButton->onClick();
}

void Menu::init(GLFWwindow* window) {
    this->window = window;
}

void Menu::run() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    
    for (int i = 0; i < buttons.size(); i++) {
        hoveredButton = -1;
        if (!buttons[i]->active)
            continue;
        if (buttons[i]->update(xpos, ypos)){
            hoveredButton = i;
            break;
        }
    }
    if (hoveredButton > -1) {
        if (state == GLFW_PRESS && !buttons[hoveredButton]->pressed && buttons[hoveredButton]->active) {
            buttons[hoveredButton]->onClick();
            switch (hoveredButton) { 
            case 0:
                joinQueue();
                break;
            case 2:
                changeCharacter(-1);
                break;
            case 3:
                changeCharacter(1);
                break;
            }
        } else if (state == GLFW_RELEASE) {
            buttons[hoveredButton]->pressed = false;
        } 
    }

    render();
}

void Menu::joinQueue() {
    std::cout << "Queued" << std::endl;
    playButton->active = false;
    playButton->hovered = false;
    quitButton->active = false;
    leftButton->active = false;
    rightButton->active = false;
    hoveredButton = -1;

    p1Status->setHidden(false);
    p2Status->setHidden(false);
    p3Status->setHidden(false);
    p4Status->setHidden(false);

    queuePlayer(playerId);
}

void Menu::queuePlayer(int id) {
    allPlayerStatus[id] = true;
    switch (id) { 
    case 0:
        p1Status->changeSprite(glm::vec2(322.0f, 0.0f));
        break;
    case 1:
        p2Status->changeSprite(glm::vec2(322.0f, 0.0f));
        break;
    case 2:
        p3Status->changeSprite(glm::vec2(322.0f, 0.0f));
        break;
    case 3:
        p4Status->changeSprite(glm::vec2(322.0f, 0.0f));
        break;
    }
    queuedPlayers++;
}

void Menu::dequeuePlayer(int id) {
    allPlayerStatus[id] = false;
    switch (id) {
    case 0:
        p1Status->changeSprite(glm::vec2(0.0f, 0.0f));
        break;
    case 1:
        p2Status->changeSprite(glm::vec2(0.0f, 0.0f));
        break;
    case 2:
        p3Status->changeSprite(glm::vec2(0.0f, 0.0f));
        break;
    case 3:
        p4Status->changeSprite(glm::vec2(0.0f, 0.0f));
        break;
    }
    queuedPlayers--;
}

void Menu::changeCharacter(int val) {
    int res = selectedCharacter + val;
    int lowerBound = 0;
    int upperBound = 3;
    selectedCharacter = std::clamp(res, lowerBound, upperBound);
    portrait->changeSprite(spriteMap[selectedCharacter]);
}

void Menu::render() {

    uiShader->use();
    for (unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw(*uiShader);
    for (unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->draw(*uiShader);

}

