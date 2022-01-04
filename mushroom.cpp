#include "mushroom.h"
#include "musicplayer.h"
#include "level.h"
Mushroom::Mushroom(char* s)
{
	ct = Costume{ 11, 0, 0 };
	sscanf(s, "%d%d%d", &ct.b, &ct.c, &direction);
	fx = 0;
	collider_layer = 4;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 1, height = 1;
	maxwx = 75;
	name = "mushroom";
	show_layer = 2;
}

bool Mushroom::update()
{
	if (!isrun) return false;
	if (fabs(fx) < EPS && onfloor) fx = 100 * direction;
	return false;
}

std::pair<double, double> Mushroom::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mushroom::getcostume()
{
	if (!isshow) return Costume{-1, -1, -1};
	return ct;
}

bool Mushroom::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	switch (target_collider_layer) {
	case 0: //如果碰到马里奥
		level.remove(this);
		musicplayer.play("sound-powerup");
		break;
	case 1: //如果碰到墙
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) 
			fx = -fx, vx = -vx, this->direction = -this->direction;
			
		break;
	}
	return true;
}