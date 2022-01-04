#include "mario_fire.h"
#include "musicplayer.h"
#include "level.h"
void Mario_fire::render(double x, double y) {
	Costume ct = getcostume();
	if (ct.a < 0 || ct.b < 0 || ct.c < 0) return;
	putimage_withalpha(NULL, camera.gp[ct.a][ct.b][ct.c], (int)x, (int)y);
	return;
}

Mario_fire::Mario_fire(double x, double y, int direction)
{
	ct = { 16, 0, 0 };
	show_layer = 3;
	collider_layer = 6;
	id = ++COLLIDER_ID;
	width = 0.25, height = 0.25;
	name = "mario_fire";
	show_layer = 2;
	freeze = false;
	f = 0;
	fx = 400 * direction;
	maxwx = 200;
	this->x = x, this->y = y;
	sx = -0.25, sy = -0.25;
	musicplayer.play("sound-fireball");
}

void Mario_fire::fire_death()
{
	death_time = level.now_time;
	freeze = true;
	ct.c = 1;
}

bool Mario_fire::update()
{
	if (death_time) {
		if (level.now_time - death_time > 100) {
			level.mario->mario_fire_num--;
			level.remove(this);
		}
		else if (level.now_time - death_time > 50) {
			ct.c = 2;
		}
		return true;
	}
	if ((fabs(x - level.mario->x) > 10 && x > 20 && x < level.map_range - 20) || x < 0 || x > level.map_range || y > 16) { //³¬³öÊÓÏß£¬»ðÑæËÀÍö
		level.mario->mario_fire_num--;
		level.remove(this);
		return true;
	}
	return false;
}

std::pair<double, double> Mario_fire::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mario_fire::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return ct;
}

bool Mario_fire::report_collision(int direction, Collider* target, int target_collider_layer)
{
	switch (target_collider_layer)
	{
	case 1:
		if (direction == BOTTOM) { //»ðÇò·´µ¯
			vy = -10;
			y = target->y - (target->height + height) / 2.0;
		}
		else {
			fire_death();
		}
		break;
	case 2:
		target->kill(fx > 0 ? LEFT : RIGHT);
		fire_death();
	}
	return true;
}