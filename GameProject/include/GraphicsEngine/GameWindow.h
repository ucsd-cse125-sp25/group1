#pragma once
#include <GLFW/glfw3.h>
#include <string>
class GameWindow
{
public:
	GLFWwindow* window;

	GameWindow(int width, int height);
	~GameWindow();

	int open();
	void update();

private:
	int width, height;
};