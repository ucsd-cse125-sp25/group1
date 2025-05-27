#include "canvas.hpp"

Canvas::Canvas() {
    crosshair = new Crosshair(crosshairPos);
    crosshair->setHidden(true);
    elements.insert({crosshair->getName(), crosshair});

    timerdisplay = new TimerDisplay(timerPos);
    elements.insert({timerdisplay->getName(), timerdisplay});

    compass = new Compass(compassPos);
    elements.insert({compass->getName(), compass});
}

Canvas::~Canvas() {
    delete crosshair;
    delete timerdisplay;
}

void Canvas::draw(Shader& shader) {
    shader.use();
    crosshair->draw(shader);
    timerdisplay->draw(shader);
    compass->draw(shader);
}

void Canvas::updateWindow(int width, int height) {
    timerdisplay->onWindowUpdate(width, height);
    crosshair->onWindowUpdate(width, height);
    compass->onWindowUpdate(width, height);
}

CanvasElement* Canvas::findElement(const std::string name) {
    return elements[name];
}
