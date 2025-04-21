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
    window = glfwCreateWindow(width, height, "Out of Tune", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Set this to be the current OpenGL context */
    glfwMakeContextCurrent(window);
    /* Initialize glad library */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    return 0;
}

void GameWindow::makeCurrentContext() {
    glfwMakeContextCurrent(window);
}

void GameWindow::update() {
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

ORect GameWindow::getInnerSize() {
    int width, height;

    /**
    * glfwGetWindowSize takes a window and stores its content area width and height in passed variables.
    * Important things to keep in mind, width and height are returned in screen coordinates, NOT PIXELS.
    * Additionally, if you ever wanna account for the borders and title bars too, use glfwGetWindowFrameSize instead.
    */
    glfwGetWindowSize(window, &width, &height);

    return ORect(width, height);
}

