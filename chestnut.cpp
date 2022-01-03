#include "chestnut.h"
#include "headers.h"
#include "global.h"
#include "level.h"
#include "death_animation.h"
#include "musicplayer.h"

Chestnut::Chestnut(char* s)
{
	sscanf(s, "%d", &direction); //一个参数，运动方向
	fx = 0;
	ct = Costume{ 5, 0, 0 };
	collider_layer = 2;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 0.75, height = 1;
	maxwx = 50;
	name = "chestnut";
	show_layer = 3;
}

bool Chestnut::update()
{
	if (!isrun) return false;
	if (x < 0 || x > level.map_range || y > 16)
		level.remove(this);
	if (state == 2 && level.now_time - animation_time > 500) {
		level.remove(this);
	}
	if (fabs(fx) < EPS && onfloor) fx = 75 * direction;
	return false;
}

std::pair<double, double> Chestnut::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Chestnut::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	if (state == 0) {
		int cl = level.now_time;
		if (cl - animation_time > 150) {
			ct.c ^= 1;
			animation_time = cl;
		}
	}
	if (state == 2) {
		ct = Costume{ 5, 0, 2 };
	}
	return ct;
}

bool Chestnut::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	if (state != 0) return false;
	switch (target_collider_layer) {
	case 0: //如果碰到马里奥
		if (target->freeze) break;
		if (level.mario->invincible_state_time) break;
		if (direction == TOP) { //如果是被踩到的，死亡
			sy = 0.25;
			state = 2;
			animation_time = level.now_time;
			freeze = true;
			score.add_score(x, y, 200);
			collider_layer = -1;
		}
		break;
	case 1: //如果碰到砖块，反弹
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) 
			fx = -fx, vx = -vx, this->direction = -this->direction;
		break;
	case 2: //如果碰到其他对向行走板栗，反弹
		if (fx < 0 != target->fx < 0) {
			if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0) || (direction == BOTTOM)) {
				fx = -fx, vx = -vx, this->direction = -this->direction;
			}
		}
		//if ((direction == LEFT && vx < 0 && (target->vx > 0 || target->freeze)) || (direction == RIGHT && fx > 0 && (target->fx < 0 || target->freeze))) 
		//	fx = -fx, vx = -vx, this->direction = -this->direction;
		break;
	}
	return true;
}

void Chestnut::kill(int direction)
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
	level.actors[5].push_back(new Death_animation(Costume{ 5, 0, 0 }, x, y, p, -10));
	isrun = false;
	freeze = true;
	level.remove(this);
}
