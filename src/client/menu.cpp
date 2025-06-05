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
    //elements.push_back(logo);
}
Menu::~Menu() {
    delete background;
    delete logo;
}
void Menu::render() {
    uiShader->use();
    background->draw(*uiShader);
    logo->draw(*uiShader);
    //for (unsigned int i = 0; i < elements.size(); i++)
    //    elements[i]->draw(*uiShader);
}
