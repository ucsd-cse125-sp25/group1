#include <GraphicsEngine/GameWindow.h>
GameWindow::GameWindow(int width, int height) {
	this->width = width;
	this->height = height;
}

GameWindow::~GameWindow() {
    glfwDestroyWindow(window);
}

int GameWindow::open() {

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Game Title", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Set this to be the current OpenGL context */
    glfwMakeContextCurrent(window);
    return 0;
}

void GameWindow::update() {
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

