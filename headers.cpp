#include "headers.h"
#include "global.h"
#include "graphics.h"
#include <ctime>
#include <cstdio>

bool Score::render() {
	if (!isshow) return false;
	xyprintf(75, 30, "MARIO");
	char s[10];
	sprintf(s, "%06d", SCORE);
	xyprintf(75, 61, s);
	return true;
}

bool Score::update() {
	if (!isrun) return false;
	return render();
}
Score score;

Coins::Coins()
{
	animation_time = clock();
	now_costume = 0;
	for (int i = 0; i < costumes_num; i++) costumes[i] = newimage();
	PIMAGE item_objects = newimage();
	getimage(item_objects, "resources\\graphics\\item_objects.png");
	getimage(costumes[0], item_objects, 3, 98, 10, 14);
	getimage(costumes[1], item_objects, 19, 98, 10, 14);
	getimage(costumes[2], item_objects, 35, 98, 10, 14);
	getimage(costumes[3], item_objects, 51, 98, 10, 14);
	for (int i = 0; i < 4; i++) zoomImage(costumes[i], 1.5);
	delimage(item_objects);
}

bool Coins::render() {
	if (!isshow) return false;
	putimage_withalpha(NULL, costumes[now_costume], 280, 66);
	char s[20];
	sprintf(s, "x%02d", COIN_TOTAL);
	xyprintf(300, 61, s);
	return true;
}

bool Coins::update() {
	if (!isrun) return false;
	if (clock() - animation_time > 200) {
		animation_time = clock();
		now_costume++;
		if (now_costume >= costumes_num) now_costume = 0;
	}
	return render();
}

Coins coins;

bool World_name::render() {
	if (!isshow) return false;
	xyprintf(450, 30, "WORLD");
	xyprintf(472, 61, LEVEL_NAME);
	return true;
}

bool World_name::update() {
	if (!isrun) return false;
	return render();
}
World_name world_name;

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