#include "mushroom.h"
#include "level.h"
Mushroom::Mushroom(FILE* fp)
{
	ct = Costume{ 11, 0, 0 };
	fscanf(fp, "%d%d", &ct.b, &ct.c);
	fscanf(fp, "%d", &direction);
	fx = 0;
	collider_layer = 4;
	id = ++COLLIDER_ID;
	freeze = false;
	width = 1, height = 1;
	maxwx = 75;
	name = "mushroom";
}

bool Mushroom::update()
{
	if (fabs(fx) < EPS && onfloor) fx = 100 * direction;
	return false;
}

std::pair<double, double> Mushroom::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mushroom::getcostume()
{
	return ct;
}

bool Mushroom::report_collision(int direction, Collider* target, int target_collider_layer)
{
	switch (target_collider_layer) {
	case 0:
		level.remove(this);
		break;
	case 1:
		if ((direction == LEFT && fx < 0) || (direction == RIGHT && fx > 0)) fx = -fx, vx = -vx, this->direction = -this->direction;
		break;
	}
	return true;
}