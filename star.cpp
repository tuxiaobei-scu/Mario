#include "star.h"
#include "musicplayer.h"
#include "level.h"
Star::Star(char* s)
{
	ct = Costume{ 15, 0, 0 };
	sscanf(s, "%d%d%d", &ct.b, &ct.c, &direction);
	fx = 0;
	collider_layer = 6;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 1, height = 1;
	maxwx = 75;
	name = "star";
	show_layer = 2;
	vy = -20;
	fx = 100 * direction;
}

bool Star::update()
{
	if (!isrun) return false;
	if (x < 0 || x > level.map_range || y > 16) 
		level.remove(this);
	return false;
}

std::pair<double, double> Star::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Star::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return ct;
}

bool Star::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	switch (target_collider_layer) {
	case 0: //如果碰到马里奥
		level.remove(this);
		musicplayer.play("sound-powerup");
		break;
	case 1: //碰到墙壁，反弹
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) {
			fx = -fx, vx = -vx, this->direction = -this->direction;
			x = target->x + (target->width + width) / 2.0 * ((direction == LEFT) ? 1 : -1);
		}
		if (direction == TOP) {
			vy = 0;
			y = target->y + (target->height + height) / 2.0;
		}
		if (direction == BOTTOM) {
			vy = -20;
			y = target->y - (target->height + height) / 2.0;
		}
		break;
	}
	return true;
}