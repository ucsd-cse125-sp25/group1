#pragma once
#include <Math/ORect.h>

class GEngine {
public:
	int test;
	GEngine();
	~GEngine();
	void clear();
	void setViewport(const ORect& size);

};