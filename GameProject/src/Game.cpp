#include "Game.h"

Game::Game() {
    //graphicsEngine = new GEngine();
    gameWindow = new GameWindow(1600, 900);
    graphicsEngine = new GEngine();
    gameWindow->open();
    graphicsEngine->setViewport(gameWindow->getInnerSize());
}

Game::~Game() {
    //delete graphicsEngine;
    delete gameWindow;
    glfwTerminate();
}

void Game::onCreate() {
    graphicsEngine->clear();
    gameWindow->open();
}

void Game::run(){
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    gameWindow->update();
    /* Poll for and process events */
    glfwPollEvents();
}

bool Game::isGameRunning() {
    return !glfwWindowShouldClose(gameWindow->window);
}