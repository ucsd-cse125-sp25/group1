#include "menu.hpp"

Menu::Menu(int playerId) {
    this->playerId = playerId;
    uiShader =
        std::make_unique<Shader>("../src/client/shaders/ui.vert", "../src/client/shaders/ui.frag");
     //background = new UIElement(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(2.0f, 2.0f),
     //                           glm::vec2(0.0f, 0.0f), backgroundTexture);
    background = new CanvasImage(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(2.0f, 2.0f),
                                 glm::vec2(0.0f, 0.0f), backgroundTexture);
    //elements.push_back(background);
    logo = new CanvasImage(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.2f),
                           glm::vec2(0.0f, 0.0f), logoTexture);

    portrait = new CanvasImage(glm::vec3(0.1f, 0.9f, 0.0f), glm::vec2(0.85f, 1.8f),
                               glm::vec2(0.0f, 0.0f), portraitTexture);
    //elements.push_back(logo);
    playButton = new PlayButton(glm::vec2(-.75f, -.2f));
    buttons.push_back(playButton);

    quitButton = new QuitButton(glm::vec2(-.75f, -.5f));
    buttons.push_back(quitButton);
}
Menu::~Menu() {
    delete background;
    delete logo;
    delete portrait;
    delete playButton;
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
        if (buttons[i]->update(xpos, ypos)){
            hoveredButton = i;
            break;
        }
        hoveredButton = -1;
    }
    if (hoveredButton > -1) {
        if (state == GLFW_PRESS) {
            buttons[hoveredButton]->onClick();
        } else if (state == GLFW_RELEASE) {
            buttons[hoveredButton]->pressed = false;
        } 
    }

    render();
}

void Menu::render() {

    uiShader->use();
    background->draw(*uiShader);
    logo->draw(*uiShader);
    portrait->draw(*uiShader);
        //    playButton->draw(*uiShader);
    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i]->draw(*uiShader);        
    }
    //for (unsigned int i = 0; i < elements.size(); i++)
    //    elements[i]->draw(*uiShader);
}

