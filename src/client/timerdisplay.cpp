#include "timerdisplay.hpp"
#include <algorithm>

TimerDisplay::TimerDisplay(glm::vec2 position) {

    rMinute_val = 9;
    lSecond_val = 5;
    rSecond_val = 9;

    // pos = glm::vec2(-1.0f, 1.0f);
    pos = position;
    initPos = position;
    background = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale * 4.0f, glm::vec2(0.0f, 0.0f),
                               backgroundTexture);
    elements[0] = background;

    glm::vec2 digitsPos = pos + indent;
    rMinute = new UIElement(glm::vec3(digitsPos.x, digitsPos.y, 0.0f), scale,
                            spriteMap[rMinute_val], uiTexture);
    elements[1] = rMinute;

    column = new UIElement(glm::vec3(digitsPos.x + digitGap, digitsPos.y, 0.0f), scale,
                           spriteMap[10], uiTexture);
    elements[2] = column;

    lSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.0f), digitsPos.y, 0.0f), scale,
                            spriteMap[lSecond_val], uiTexture);
    elements[3] = lSecond;

    rSecond =
        new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.5f) + digitGap, digitsPos.y, 0.0f),
                      scale, spriteMap[rSecond_val], uiTexture);
    elements[4] = rSecond;
}

TimerDisplay::TimerDisplay(glm::vec2 position, int rMin, int lSec, int rSec) {

    rMinute_val = rMin;
    lSecond_val = lSec;
    rSecond_val = rSec;

    // pos = glm::vec2(-1.0f, 1.0f);
    pos = position;
    initPos = position;
    background = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale * 3.5f, glm::vec2(0.0f, 0.0f),
                               backgroundTexture);
    elements[0] = background;

    glm::vec2 digitsPos = pos + indent;
    rMinute = new UIElement(glm::vec3(digitsPos.x, digitsPos.y, 0.0f), scale,
                            spriteMap[rMinute_val], uiTexture);
    elements[1] = rMinute;

    column = new UIElement(glm::vec3(digitsPos.x + digitGap, digitsPos.y, 0.0f), scale,
                           spriteMap[10], uiTexture);
    elements[2] = column;

    lSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.0f), digitsPos.y, 0.0f), scale,
                            spriteMap[lSecond_val], uiTexture);
    elements[3] = lSecond;

    rSecond =
        new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.5f) + digitGap, digitsPos.y, 0.0f),
                      scale, spriteMap[rSecond_val], uiTexture);
    elements[4] = rSecond;
}

TimerDisplay::~TimerDisplay() {
    delete background;
    delete rMinute;
    delete column;
    delete lSecond;
    delete rSecond;
}

void TimerDisplay::changePosition() {

    glm::vec2 digitsPos = pos + indent;
    rMinute->changePosition(glm::vec2(digitsPos.x, digitsPos.y));

    column->changePosition(glm::vec2(digitsPos.x + digitGap, digitsPos.y));

    lSecond->changePosition(glm::vec2(digitsPos.x + (digitGap * 2.0f), digitsPos.y));

    rSecond->changePosition(glm::vec2(digitsPos.x + (digitGap * 2.5f) + digitGap, digitsPos.y));
}

void TimerDisplay::onWindowUpdate(int width, int height) {
    // std::cout << "(" << width << "," << height << ")" << std::endl;
    float widthOffset = (1600.0f / (float)width);
    float heightOffset = (900.0f / (float)height);
    for (unsigned int i = 0; i < 5; i++) {
        elements[i]->changeDimensions(glm::vec2(widthOffset, heightOffset));
    }
    if (width < 600) {
        digitGap = .2f;
        indent = glm::vec2(.48f, -0.04f);
    } else if (width < 800) {
        digitGap = .15f;
        indent = glm::vec2(.38f, -0.04f);
    } else if (width < 1000) {
        digitGap = .12f;
        indent = glm::vec2(.28f, -0.04f);
    } else if (width < 1200) {
        digitGap = .1f;
        indent = glm::vec2(.24f, -0.04f);
    } else if (width < 1400) {
        digitGap = .09f;
        indent = glm::vec2(.2f, -0.04f);
    } else if (width <= 1600) {
        digitGap = .07f;
        indent = glm::vec2(.18f, -0.04f);
    } else {
        digitGap = .06f;
        indent = glm::vec2(.15f, -0.04f);
    }
    changePosition();
    /*std::cout << posMod << std::endl;*/
}

void TimerDisplay::updateTimer(int minutes, int seconds) {
    int rMin_curr = minutes % 10;

    int lSec_curr = seconds / 10;
    int rSec_curr = seconds % 10;

    if (rMinute_val != rMin_curr) {
        rMinute_val = rMin_curr;
        rMinute->changeSprite(spriteMap[rMinute_val]);
    }

    if (lSecond_val != lSec_curr) {
        lSecond_val = lSec_curr;
        lSecond->changeSprite(spriteMap[lSecond_val]);
    }
    if (rSecond_val != rSec_curr) {
        rSecond_val = rSec_curr;
        rSecond->changeSprite(spriteMap[rSecond_val]);
    }
}

void TimerDisplay::draw(Shader& shader) {
    if (hidden)
        return;
    background->draw(shader);
    rMinute->draw(shader);
    column->draw(shader);
    lSecond->draw(shader);
    rSecond->draw(shader);
}

void TimerDisplay::setHidden(bool val) {
    hidden = val;
}

std::string TimerDisplay::getName() {
    return name;
}
