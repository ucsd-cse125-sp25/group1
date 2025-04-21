#include "Game.h"
#include <GraphicsEngine/OVertexAttribute.h>
/**
* Where are we binding VBO?
*/
Game::Game() {
    gameWindow = new GameWindow(1600, 900);
    graphicsEngine = new GEngine();
    gameDurationSeconds = 600.0f;  // game lasts 10 minutes
    timeRemaining = gameDurationSeconds;
}

Game::~Game() {
    delete gameWindow;
    glfwTerminate();
}

void Game::onCreate() {
    gameWindow->open();
    graphicsEngine->setViewport(gameWindow->getInnerSize());
    graphicsEngine->clear();

    const float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f, // Position of Vertex 1
        1, 0, 0,            // Color of Vertex 1

        0.5f, -0.5f, 0.0f,  // Position of Vertex 2
        0, 1, 0,            // Color of Vertex 2

        0.0f, 0.5f, 0.0f,  // ...
        0,0,1
    };

    OVertexAttribute attributeList[] = {
        3,  // Position of vertex
        3   // Color of vertex
    };

    triangleVAO = graphicsEngine->createVertexArrayObject({
        (void*)triangleVertices, 
        sizeof(float)*(3+3),    // 3 position values + 3 color values
        3,

        attributeList,
        2
     });
    shader = graphicsEngine->createShaderProgram({ L"../../GameProject/Assets/Shaders/BasicShader.vert", L"../../GameProject/Assets/Shaders/BasicShader.frag" });
    if (!shader) {
        std::cerr << "Failed to load shader program!" << std::endl;
    }
}

void Game::run(){
    /* Update timer value */
    float timeElapsed = static_cast<float>(glfwGetTime()); // Get time since last frame
    glfwSetTime(0.0); // Reset the time so next `timeElapsed` calculation is accurate
    timeRemaining -= timeElapsed;
    if (timeRemaining <= 0.0f){
        timeRemaining = 0.0f
        // TODO: add logic to end the game
    }

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    //glUseProgram(graphicsEngine->shaderProgram);
    graphicsEngine->setVertexArrayObject(triangleVAO); //Bind VAO
    graphicsEngine->setShaderProgram(shader); // 
    graphicsEngine->drawTriangles(3, 0);
    // TODO: render timer showing timeRemaining seconds

    gameWindow->update();

    /* Poll for and process events */
    glfwPollEvents();
}

bool Game::isGameRunning() {
    return !glfwWindowShouldClose(gameWindow->window);
}