#pragma once
#include <GLFW/glfw3.h>
#include <GraphicsEngine/GameWindow.h>
class Game
{
public:
	Game();
	~Game();
	void run();
	bool isGameRunning();
private:
	GameWindow* gameWindow;
};

