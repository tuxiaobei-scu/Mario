#include "timer.h"
#include "global.h"
#include "graphics.h"
#include <cstdio>
bool Timer::render() {
	if (!isshow) return false;
	xyprintf(625, 30, "TIME");
	return true;
}

bool Timer::update() {
	if (!isrun) return false;
	return render();
}

Timer timer;