#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Math/ORect.h>
#include <iostream>
class GameWindow
{
public:
	GLFWwindow* window;

	GameWindow(int width, int height);
	~GameWindow();

	int open();
	void update();
	void makeCurrentContext();

	ORect getInnerSize();

private:
	int width, height;
};