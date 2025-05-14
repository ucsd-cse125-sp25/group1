#include "timerdisplay.hpp"

TimerDisplay::TimerDisplay() {

	lMinute_val = 1;
	rMinute_val = 0;
	lSecond_val = 0;
	rSecond_val = 0;

	pos = glm::vec2(-1.0f, 1.0f);
	lMinute = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale, spriteMap[lMinute_val], uiTexture);
	rMinute = new UIElement(glm::vec3(pos.x + digitGap, pos.y, 0.0f), scale, spriteMap[rMinute_val], uiTexture);
	lSecond = new UIElement(glm::vec3(pos.x + (digitGap * 2.5f), pos.y, 0.0f), scale, spriteMap[lSecond_val], uiTexture);
	rSecond = new UIElement(glm::vec3(pos.x + (digitGap * 2.5f) + digitGap, pos.y, 0.0f), scale, spriteMap[rSecond_val], uiTexture);
}

TimerDisplay::TimerDisplay(int lMin, int rMin, int lSec, int rSec) {

	lMinute_val = lMin;
	rMinute_val = rMin;
	lSecond_val = lSec;
	rSecond_val = rSec;

	pos = glm::vec2(-1.0f, 1.0f);
	lMinute = new UIElement(glm::vec3(pos.x, pos.y, 0.0f), scale, spriteMap[lMinute_val], uiTexture);
	rMinute = new UIElement(glm::vec3(pos.x + digitGap, pos.y, 0.0f), scale, spriteMap[rMinute_val], uiTexture);
	lSecond = new UIElement(glm::vec3(pos.x + (digitGap * 2.5f), pos.y, 0.0f), scale, spriteMap[lSecond_val], uiTexture);
	rSecond = new UIElement(glm::vec3(pos.x + (digitGap * 2.5f) + digitGap, pos.y, 0.0f), scale, spriteMap[rSecond_val], uiTexture);

}

TimerDisplay::~TimerDisplay() {
	delete lMinute;
	delete rMinute;
	delete lSecond;
	delete rSecond;
}

void TimerDisplay::updateTimer(int minutes, int seconds) {
	int lMin_curr = minutes / 10;
	int rMin_curr = minutes % 10;

	int lSec_curr = seconds / 10;
	int rSec_curr = seconds % 10;

	if (lMinute_val != lMin_curr) {
		lMinute_val = lMin_curr;
		lMinute->changeSprite(spriteMap[lMinute_val]);
	}
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
	lMinute->draw(shader);
	rMinute->draw(shader);
	lSecond->draw(shader);
	rSecond->draw(shader);
}