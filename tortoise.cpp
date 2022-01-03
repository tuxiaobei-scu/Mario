#include "tortoise.h"
#include "headers.h"
#include "global.h"
#include "level.h"
#include "death_animation.h"
#include "musicplayer.h"

Tortoise::Tortoise(char* s)
{
	sscanf(s, "%d", &direction); //一个参数，运动方向
	fx = 0;
	ct = Costume{ 13, 0, 0 };
	collider_layer = 2;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 0.75, height = 1;
	maxwx = 50;
	name = "tortoise";
	show_layer = 3;
	sy = -0.5;
}

bool Tortoise::update()
{
	if (!isrun) return false;
	if (x < 0 || x > level.map_range || y > 16)
		level.remove(this);
	if (state == 0) {
		if (fabs(fx) < EPS && onfloor) fx = 75 * direction;
	}
	else if (state == 2) {
		if (fabs(fx) < EPS && onfloor) fx = 400 * direction;
	}
	else {
		if (level.now_time - sleep_time > 10000) {
			state = 0;
			freeze = false;
			sy = -0.5;
		}
	}
	
	return false;
}

std::pair<double, double> Tortoise::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Tortoise::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	if (state == 0) {
		int cl = level.now_time;
		if (cl - animation_time > 150) {
			if (direction == 1) {
				ct.c = ct.c == 4 ? 5 : 4;
			}
			else {
				ct.c = ct.c == 2 ? 3 : 2;
			}
			animation_time = cl;
		}
	}
	else if (state == 1 || state == 2) {
		ct = Costume{ 13, 0, 9 };
		if (level.now_time - sleep_time > 9000) {
			ct = Costume{ 13, 0, 8 };
		}
	}
	return ct;
}

bool Tortoise::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	switch (target_collider_layer) {
	case 0: //如果碰到马里奥
		if (level.mario->invincible_state_time) break;
		if (target->freeze) break;
		if (direction == TOP) { //如果是被踩到的，静止运动切换
			score.add_score(x, y, 200);
			if (state != 1) {
				ct = Costume{ 13, 0, 9 };
				state = 1;
				sy = -0.25;
				freeze = true;
				sleep_time = level.now_time;
			}
			else {
				state = 2;
				freeze = false;
				maxwx = 200;
				direction = target->x < x ? 1 : -1; //判断踩的位置
				fx = 400 * direction;
			}
		}
		break;
	case 1: //如果碰到砖块，反弹
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) {
			fx = -fx, vx = -vx, this->direction = -this->direction;
			ct.c = direction == 1 ? 4 : 2;
			animation_time = level.now_time;
		}
		break;
	case 2: //碰到其他怪物
		if (state == 2) { //滚动击杀
			target->kill((direction + 2) & 3);
		}
		else {
			if (fx < 0 != target->fx < 0) {
				if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0) || (direction == BOTTOM)) {
					fx = -fx, vx = -vx, this->direction = -this->direction;
				}
			}
		}
		break;
	}
	return true;
}

void Tortoise::kill(int direction)
{
	if (killed) return;
	musicplayer.play("sound-bump");
	score.add_score(x, y, 200);
	killed = true;
	double p;
	if (direction == RIGHT || direction == LEFT) {
		p = direction == RIGHT ? -15 : 15;
	}
	else {
		p = vx < 0 ? -15 : 15;
	}
	level.actors[5].push_back(new Death_animation(Costume{ 13, 0, 9 }, x, y, p, -10));
	isrun = false;
	freeze = true;
	level.remove(this);
}