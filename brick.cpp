#include "brick.h"
#include "global.h"

Brick::Brick(char* s)
{
	int a, b;
	sscanf(s, "%d%d", &a, &b);
	ct = Costume{ 4, a, b };
	collider_layer = 1;
	id = ++COLLIDER_ID;
	freeze = true;
	width = 1, height = 1;
	name = "brick";
	show_layer = 4;
}

Brick::Brick(int a, int b)
{
	ct = Costume{ 4, a, b };
	collider_layer = 1;
	id = ++COLLIDER_ID;
	freeze = true;
	width = 1, height = 1;
	name = "brick";
}

bool Brick::update()
{
	return false;
}

std::pair<double, double> Brick::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Brick::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return ct;
}

bool Brick::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}