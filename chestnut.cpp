#include "chestnut.h"
#include "global.h"
#include "level.h"

Chestnut::Chestnut(FILE* fp)
{
	fscanf(fp, "%d", &direction);
	fx = 0;
	ct = Costume{ 5, 0, 0 };
	collider_layer = 2;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 1, height = 1;
	maxwx = 50;
	name = "chestnut";
}

bool Chestnut::update()
{
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
	if (state != 0) return false;
	switch (target_collider_layer) {
	case 0:
		if (target->freeze) break;
		if (direction == TOP) {
			sy = 0.25;
			state = 2;
			animation_time = level.now_time;
			freeze = true;
			collider_layer = -1;
		}
		break;
	case 1:
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) fx = -fx, vx = -vx, this->direction = -this->direction;
		break;
	case 2:
		if ((direction == LEFT && fx < 0 && target->fx > 0) || (direction == RIGHT && fx > 0 && target->fx < 0)) fx = -fx, vx = -vx, this->direction = -this->direction;
		break;
	}
	return true;
}
