#include "question_block.h"
#include "musicplayer.h"
#include "level.h"
#include "global.h"

Question_block::Question_block(char* s, double x, double y)
{
	int pos;
	sscanf(s, "%d%n", &isshow, &pos);
	ct = Costume{ 9, 0, 0 };
	if (!isshow)
		collider_layer = 4;
	else
		collider_layer = 1;
	show_layer = 3;
	id = ++COLLIDER_ID;
	freeze = true;
	width = 1, height = 1;
	name = "question_block";
	target = level.addobject(s + pos, x, y); //新增顶出的角色
	target->freeze = true;
	target->isrun = false;
	target->isshow = false;
}

bool Question_block::update()
{
	if (ct.c != 3) return false;
	int c = level.now_time - used_time;
	if (c <= 500) {
		target->y = y - (c / 500.0) - 1.0 / 16.0;
	}
	else if (!change_freeze) {
		target->freeze = false;
		change_freeze = true;
	}
	if (c > 250 && !change_run) {
		target->isrun = true;
		target->isshow = true;
		change_run = true;
	}
	if (c <= 150) {
		sy = (c / 150.0) * (c / 150.0) - (c / 150.0);
	}
	
}

std::pair<double, double> Question_block::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Question_block::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	if (!used_time) {
		if (!isshow) return Costume{ -1, -1, -1 };
		int p = level.now_time / 150 % 5;
		switch (p) {
		case 0:
		case 1:
		case 2:
			ct.c = p;
			break;
		case 3:
			ct.c = 2;
			break;
		case 4:
			ct.c = 1;
			break;
		}
	}
	return ct;
}

bool Question_block::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!used_time && target_collider_layer == 0 && direction == BOTTOM) { //被顶
		ct.c = 3;
		musicplayer.play("sound-powerup_appears");
		used_time = level.now_time;
		collider_layer = 1; //改变图层为砖块
		isshow = true;
		target->y = y + (height + target->height) / 2;
	}
	return false;
}