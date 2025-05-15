#pragma once
#include <glm/glm.hpp>
#include <string>
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
private:

	bool hidden = false;
	
	std::string name = "timerdisplay";

	glm::vec2 pos;
	glm::vec2 indent = glm::vec2(.18f, -0.04f);
	const float digitGap = .08f;
	const glm::vec2 scale = glm::vec2(.15f, .25f);
	
	int rMinute_val;
	int lSecond_val;
	int rSecond_val;
	
	UITexture uiTexture = { "../src/client/ui/timer-atlas.png", glm::vec2(384.0f, 512.0f), glm::vec2(128.0f,128.0f)};
	UITexture backgroundTexture = { "../src/client/ui/timer_background.png",  glm::vec2(1024.0f,1024.0f), glm::vec2(1024.0f,1024.0f) };

	UIElement* rMinute;
	UIElement* column;
	UIElement* lSecond;
	UIElement* rSecond;
	UIElement* background;

	glm::vec2 spriteMap[11] = {
		glm::vec2(128.0f,0.0f),
		glm::vec2(0.0f,384.0f), glm::vec2(128.0f,384.0f), glm::vec2(256.0f,384.0f),
		glm::vec2(0.0f,256.0f), glm::vec2(128.0f,256.0f), glm::vec2(256.0f,256.0f),
		glm::vec2(0.0f,128.0f), glm::vec2(128.0f,128.0f), glm::vec2(256.0f,128.0f),
		glm::vec2(0.0f,0.0f)
	};

};