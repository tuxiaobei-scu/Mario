#include "timer.h"
#include "global.h"
#include "graphics.h"
#include <cstdio>
bool Timer::render() {
	if (!this->isshow) return false;
	xyprintf(625, 30, "TIME");
	return true;
}

bool Timer::update() {
	return this->render();
}

Timer timer;