#include "headers.h"
#include "global.h"
#include "graphics.h"
#include "add_score.h"
#include "musicplayer.h"
#include "level.h"
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

void Score::add_score(double x, double y, int score, bool type)
{
	Collider* t = new Add_score(x, y, score, type);
	level.mp[5][(int)x].push_back(t);
	SCORE += score;
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
	putimage_withalpha(NULL, costumes[now_costume], 260, 66);
	char s[20];
	sprintf(s, "x%02d", COIN_TOTAL);
	xyprintf(280, 61, s);
	return true;
}

bool Coins::update() {
	if (!isrun) return false;
	int cl = clock();
	if (cl - animation_time > 200) {
		animation_time = cl;
		now_costume++;
		if (now_costume >= costumes_num) now_costume = 0;
	}
	return render();
}

Coins coins;

bool World_name::render() {
	if (!isshow) return false;
	xyprintf(400, 30, "WORLD");
	xyprintf(400, 61, LEVEL_NAME.c_str());
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
	char s[10];
	if (level.finish_time) { //关卡时间结算，转为分数
		int c = level.now_time - level.finish_time;
		if (c > 2500) { 
			if (end_show_time > 0) {
				if (!count_down) {
					musicplayer.play("sound-count_down");
					count_down = true;
				}
				if ((c / 20) & 2) {
					end_show_time--;
					SCORE += 50;
				}
			}
			else {
				if (count_down) {
					musicplayer.stop("sound-count_down");
					count_down = false;
				}
			}
		}
		sprintf(s, "%03d", end_show_time);
		xyprintf(625, 61, s);
	} else if (!level.freeze) {
		sprintf(s, "%03d", max(level.limit_time - ((level.now_time - level.start_time) / 1000), 0));
		xyprintf(625, 61, s);
	}
	else if (level.death_time) {
		sprintf(s, "%03d", max(level.limit_time - ((level.death_time - level.start_time) / 1000), 0));
		xyprintf(625, 61, s);
	}
	return true;
}

bool Timer::update() {
	if (!isrun) return false;
	return render();
}

Timer timer;