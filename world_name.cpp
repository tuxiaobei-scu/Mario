#include "world_name.h"
#include "graphics.h"
#include <cstdio>
bool World_name::render() {
	if (!this->isshow) return false;
	xyprintf(450, 30, "WORLD");
	xyprintf(472, 55, "1-1");
	return true;
}

bool World_name::update() {
	return this->render();
}
World_name world_name;