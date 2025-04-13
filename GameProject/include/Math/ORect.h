#pragma once
/* Handles dimensions of view port */
class ORect {
public:
	int width = 0, height = 0, left = 0, top = 0;
	ORect() {
	}
	ORect(int width, int height) : width(width), height(height) {}
	ORect(int left, int top, int width, int height) : left(left), top(top), width(width), height(height) {}
	ORect(const ORect& rect) : left(rect.left), top(rect.top), width(rect.width), height(rect.height) {}
};