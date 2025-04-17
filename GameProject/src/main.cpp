#include <GraphicsEngine/GameWindow.h>
#include <Game.h>
#include <iostream>

int main() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    try
    {
        Game* game = new Game();

        std::cout << "Game loop ongoing..." << std::endl;
        game->onCreate();
        /* Loop until the user closes the window */
        while (game->isGameRunning())
        {
            game->run();
        }
        delete game;
        std::cout << "Game loop ended." << std::endl;
    }
    catch (const std::exception& e) {
        std::wclog << e.what() << std::endl;
        return -1;
    }

    return 0;
}