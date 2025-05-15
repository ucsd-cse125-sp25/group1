#include "timerdisplay.hpp"

TimerDisplay::TimerDisplay(glm::vec2 position) {

	rMinute_val = 9;
	lSecond_val = 5;
	rSecond_val = 9;

	//pos = glm::vec2(-1.0f, 1.0f);
	pos = position;
	background = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale * 4.0f, glm::vec2(0.0f, 0.0f), backgroundTexture);
	glm::vec2 digitsPos = pos + indent;
	rMinute = new UIElement(glm::vec3(digitsPos.x, digitsPos.y, 0.0f), scale, spriteMap[rMinute_val], uiTexture);
	column = new UIElement(glm::vec3(digitsPos.x + digitGap, digitsPos.y, 0.0f), scale, spriteMap[10], uiTexture);
	lSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.0f), digitsPos.y, 0.0f), scale, spriteMap[lSecond_val], uiTexture);
	rSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.5f) + digitGap, digitsPos.y, 0.0f), scale, spriteMap[rSecond_val], uiTexture);
}

TimerDisplay::TimerDisplay(glm::vec2 position, int rMin, int lSec, int rSec) {

	rMinute_val = rMin;
	lSecond_val = lSec;
	rSecond_val = rSec;

	//pos = glm::vec2(-1.0f, 1.0f);
	pos = position;
	background = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale * 3.5f, glm::vec2(0.0f, 0.0f), backgroundTexture);
	glm::vec2 digitsPos = pos + indent;
	rMinute = new UIElement(glm::vec3(digitsPos.x, digitsPos.y, 0.0f), scale, spriteMap[rMinute_val], uiTexture);
	column = new UIElement(glm::vec3(digitsPos.x + digitGap, digitsPos.y, 0.0f), scale, spriteMap[10], uiTexture);
	lSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.0f), digitsPos.y, 0.0f), scale, spriteMap[lSecond_val], uiTexture);
	rSecond = new UIElement(glm::vec3(digitsPos.x + (digitGap * 2.5f) + digitGap, digitsPos.y, 0.0f), scale, spriteMap[rSecond_val], uiTexture);

}

TimerDisplay::~TimerDisplay() {
	delete background;
	delete rMinute;
	delete column;
	delete lSecond;
	delete rSecond;
}

void TimerDisplay::updateTimer(int minutes, int seconds) {
	int rMin_curr = minutes % 10;

	int lSec_curr = seconds / 10;
	int rSec_curr = seconds % 10;

	if (rMinute_val != rMin_curr) {
		rMinute_val = rMin_curr;
		rMinute->changeSprite(spriteMap[rMinute_val]);
	}

	if (lSecond_val != lSec_curr) {
		lSecond_val = lSec_curr;
		lSecond->changeSprite(spriteMap[lSecond_val]);
	}
	if (rSecond_val != rSec_curr) {
		rSecond_val = rSec_curr;
		rSecond->changeSprite(spriteMap[rSecond_val]);
	}
}

void TimerDisplay::draw(Shader& shader) {
	if (hidden)
		return;
	background->draw(shader);
	rMinute->draw(shader);
	column->draw(shader);
	lSecond->draw(shader);
	rSecond->draw(shader);
}

void TimerDisplay::setHidden(bool val) {
	hidden = val;
}

std::string TimerDisplay::getName() {
	return name;
}