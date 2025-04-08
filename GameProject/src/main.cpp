#include <iostream>
#include <GLFW/glfw3.h>
#include <Game.h>
int main() {
    /* Initialize the library, must be initialized before declaring Game */
    if (!glfwInit())
        return -1;

    Game* game = new Game();

    /* Starting Game Loop */
    std::cout << "Game loop ongoing..." << std::endl;
    while (game->isGameRunning())
    {
        game->run();
    }
    delete game;
    /* Terminate library */
    glfwTerminate();
    std::cout << "Game loop ended" << std::endl;
    return 0;
}