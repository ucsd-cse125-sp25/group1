#include "compass.hpp"
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <iostream>

Compass::Compass(glm::vec2 pos) {
    name = "compass";
    /*glm::vec2 offset = glm::vec2((256.0f - 800.0f)/1600.0f, (450.0f - 256.0f)/900.0f);*/
    position = pos;
    scale = glm::vec2(.30f, .5f);

    uiTexture = {"../src/client/ui/compass_frame.png", glm::vec2(256.0f, 256.0f),
                 glm::vec2(256.0f, 256.0f)};
    uiELement = new UIElement(glm::vec3(position.x, position.y, 0.0f), scale, initialSpriteCoords,
                              uiTexture);

    handsTexture = {"../src/client/ui/compass_hands.png", glm::vec2(256.0f, 256.0f),
                    glm::vec2(256.0f, 256.0f)};
    compassHands = new UIElement(glm::vec3(position.x, position.y, 0.0f), scale,
                                 initialSpriteCoords, handsTexture);
}

Compass::~Compass() {
    delete uiELement;
    delete compassHands;
}

void Compass::rotate(glm::vec3 dir) {
    glm::vec2 head = glm::vec2(0.0f, 1.0f);
    glm::vec2 orientation = glm::normalize(glm::vec2(dir.x, dir.z));
    float product = glm::dot(head, orientation);
    float determinant = head.x * orientation.y - head.y * orientation.x;
    float res = product / (glm::length(head) * glm::length(orientation));
    float angle = atan2f(determinant, product);
    float degrees = angle * (180.0f / 3.141592653589793238463f);
    if (degrees < 0.0f)
        degrees += 360.0f;
    // std::cout << glm::to_string(orientation) << ", " << degrees << std::endl;

    compassHands->rotate(degrees);
}

void Compass::onWindowUpdate(int width, int height) {
    float widthOffset = (1600.0f / (float)width);
    float heightOffset = (900.0f / (float)height);
    uiELement->changeDimensions(glm::vec2(widthOffset, heightOffset));
    compassHands->changeDimensions(glm::vec2(widthOffset, heightOffset));
}

void Compass::draw(Shader& shader) {
    uiELement->draw(shader);
    compassHands->draw(shader);
}
