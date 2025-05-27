#pragma once
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "canvaselement.hpp"
#include "uielement.hpp"
#include "uitexture.hpp"


class TimerDisplay : public CanvasElement {
public:
	TimerDisplay(glm::vec2 position);
	TimerDisplay(glm::vec2 position, int rMin, int lSec, int rSec);
	~TimerDisplay();
	void draw(Shader& shader) override;
	void setHidden(bool val) override;
	std::string getName() override;
	void updateTimer(int minutes, int seconds);
	void onWindowUpdate(int width, int height) override;
private:
	void changePosition(glm::vec2 position);
private:

	bool hidden = false;

	std::string name = "timerdisplay";

	glm::vec2 pos, initPos;
	glm::vec2 indent = glm::vec2(.18f, -0.04f);
	float digitGap = .08f;
	const glm::vec2 scale = glm::vec2(.15f, .25f);

	int rMinute_val;
	int lSecond_val;
	int rSecond_val;

	UITexture uiTexture = { "../src/client/ui/timer-atlas.png", glm::vec2(384.0f, 512.0f), glm::vec2(128.0f,128.0f) };
	UITexture backgroundTexture = { "../src/client/ui/timer_background.png",  glm::vec2(1024.0f,1024.0f), glm::vec2(1024.0f,1024.0f) };

	UIElement* rMinute;
	UIElement* column;
	UIElement* lSecond;
	UIElement* rSecond;
	UIElement* background;

	UIElement* elements[5];

	glm::vec2 spriteMap[11] = {
		glm::vec2(128.0f,0.0f),
		glm::vec2(0.0f,384.0f), glm::vec2(128.0f,384.0f), glm::vec2(256.0f,384.0f),
		glm::vec2(0.0f,256.0f), glm::vec2(128.0f,256.0f), glm::vec2(256.0f,256.0f),
		glm::vec2(0.0f,128.0f), glm::vec2(128.0f,128.0f), glm::vec2(256.0f,128.0f),
		glm::vec2(0.0f,0.0f)
	};

};