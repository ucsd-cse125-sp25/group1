#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GraphicsEngine/GameWindow.h>
#include <GraphicsEngine/GEngine.h>
class Game
{
public:
	Game();
	~Game();
	void run();
	void onCreate();
	void onUpdate();
	bool isGameRunning();
private:
	GEngine* graphicsEngine;
	GameWindow* gameWindow;
	std::shared_ptr<OVertexArrayObject> triangleVAO;
};

