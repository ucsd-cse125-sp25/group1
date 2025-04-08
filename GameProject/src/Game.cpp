#include "Game.h"

Game::Game() {
	gameWindow = new GameWindow(1600, 900);
    gameWindow->open();
}

Game::~Game() {
    delete gameWindow;
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