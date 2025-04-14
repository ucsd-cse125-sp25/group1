#include "Game.h"

Game::Game() {
    gameWindow = new GameWindow(1600, 900);
    graphicsEngine = new GEngine();
}

Game::~Game() {
    delete gameWindow;
    glfwTerminate();
}

void Game::onCreate() {
    gameWindow->open();
    graphicsEngine->setViewport(gameWindow->getInnerSize());
    graphicsEngine->clear();
    graphicsEngine->setShaderProgram();

    const float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    triangleVAO = graphicsEngine->createVertexArrayObject({(void*)triangleVertices, sizeof(float)*3,3});
}

void Game::run(){
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(graphicsEngine->shaderProgram);
    graphicsEngine->setVertexArrayObject(triangleVAO);
    graphicsEngine->drawTriangles(3, 0);

    gameWindow->update();

    /* Poll for and process events */
    glfwPollEvents();
}

bool Game::isGameRunning() {
    return !glfwWindowShouldClose(gameWindow->window);
}