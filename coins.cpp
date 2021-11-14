#include "coins.h"
#include "global.h"
#include "graphics.h"
#include <ctime>
#include <cstdio>

Coins::Coins()
{
	this->animation_time = clock();
	this->now_costume = 0;
	for (int i = 0; i < this->costumes_num; i++) this->costumes[i] = newimage();
	PIMAGE item_objects = newimage();
	getimage(item_objects, "resources\\graphics\\item_objects.png");
	getimage(this->costumes[0], item_objects, 3, 98, 10, 14);
	getimage(this->costumes[1], item_objects, 19, 98, 10, 14);
	getimage(this->costumes[2], item_objects, 35, 98, 10, 14);
	getimage(this->costumes[3], item_objects, 51, 98, 10, 14);
	for (int i = 0; i < 4; i++) zoomImage(this->costumes[i], 1.5);
	delimage(item_objects);
}

bool Coins::render() {
	if (!this->isshow) return false;
	putimage_withalpha(NULL, this->costumes[this->now_costume], 280, 66);
	char s[20];
	sprintf(s, "x%02d", COIN_TOTAL);
	xyprintf(300, 61, s);
	return true;
}

bool Coins::update() {
	if (clock() - this->animation_time > 100) {
		this->animation_time = clock();
		this->now_costume++;
		if (this->now_costume >= this->costumes_num) this->now_costume = 0;
	}
	return this->render();
}

Coins coins;