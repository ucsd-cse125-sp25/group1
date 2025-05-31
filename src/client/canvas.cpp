#include "canvas.hpp"

Canvas::Canvas() {
    crosshair = new Crosshair(crosshairPos);
    crosshair->setHidden(true);
    elements.insert({crosshair->getName(), crosshair});

    timerdisplay = new TimerDisplay(timerPos);
    elements.insert({timerdisplay->getName(), timerdisplay});

    keydisplay = new KeyDisplay(keyPos);
    elements.insert({keydisplay->getName(), keydisplay});

    compass = new Compass(compassPos);
    elements.insert({compass->getName(), compass});

    interactdisplay = new InteractDisplay(interactPos);
    elements.insert({interactdisplay->getName(), interactdisplay});
}

Canvas::~Canvas() {
    for (const auto& pair : elements)
        delete pair.second;
}

void Canvas::draw(Shader& shader) {
    shader.use();
    for (const auto& pair : elements)
        pair.second->draw(shader);
}

void Canvas::updateWindow(int width, int height) {
    for (const auto& pair : elements)
        pair.second->onWindowUpdate(width, height);
}

void Canvas::collectKey() {
    keydisplay->onCollectKey();
}

void Canvas::setInteractHidden(bool val) {
    interactdisplay->setHidden(val);
}

void Canvas::updateTimer(int minutes, int seconds) {
    timerdisplay->updateTimer(minutes, seconds);
}

void Canvas::updateCompass(glm::vec3 direction) {
    compass->rotate(direction);
}

CanvasElement* Canvas::findElement(const std::string name) {
    return elements[name];
}
