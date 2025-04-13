#include <GraphicsEngine/GameWindow.h>
#include <Game.h>
#include <iostream>

int main() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    Game* game = new Game();

    std::cout << "Game loop ongoing..." << std::endl;
    /* Loop until the user closes the window */
    while (game->isGameRunning())
    {
        game->run();
    }
    delete game;
    std::cout << "Game loop ended." << std::endl;
    return 0;
}