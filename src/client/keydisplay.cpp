#include "keydisplay.hpp"
#include <iostream>

KeyDisplay::KeyDisplay(glm::vec2 pos) {
    name = "keydisplay";
    hidden = true;
    position = glm::vec2(pos.x, pos.y);
    scale = glm::vec2(.6f, 1.0f);
    initialSpriteCoords = glm ::vec2(1024.0f, 1024.0f);
    uiTexture = {"../src/client/ui/key-atlas.png", glm::vec2(2048.0f, 2048.0f),
                 glm::vec2(1024.0f, 1024.0f)};
    uiELement =
        new UIElement(glm::vec3(position.x, position.y, 0.0f), scale, spriteMap[0], uiTexture);
}

void KeyDisplay::onCollectKey() {
    if (collectedKeys >= 4)
        return;
    if (hidden)
        hidden = false;
    uiELement->changeSprite(spriteMap[collectedKeys]);
    collectedKeys++;
    
}

void KeyDisplay::onRemoveKey() {
    //collectedKeys--;
    //if(collectedKeys == 0){hidden = true;}
    //uiElement->changeSprite(spriteMap[collectedKeys]);
    if (collectedKeys == 0)
        return;
    collectedKeys--;
    std::cout << "Collected keys: " << collectedKeys << std::endl;
    if (collectedKeys == 0) {
        hidden = true;
    }
    uiELement->changeSprite(spriteMap[collectedKeys]);
}

KeyDisplay::~KeyDisplay() {
    delete uiELement;
}
