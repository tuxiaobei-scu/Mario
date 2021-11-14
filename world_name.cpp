#include "world_name.h"
#include "graphics.h"
#include <cstdio>
bool World_name::render() {
	if (!isshow) return false;
	xyprintf(450, 30, "WORLD");
	xyprintf(472, 61, "1-1");
	return true;
}

bool World_name::update() {
	if (!isrun) return false;
	return render();
}
World_name world_name;