#include "flower.h"
#include "musicplayer.h"
#include "level.h"
Flower::Flower(char* s)
{
	ct = Costume{ 14, 0, 0 };
	sscanf(s, "%d%d", &ct.b, &ct.c);
	fx = 0;
	collider_layer = 4;
	freeze = false;
	id = ++COLLIDER_ID;
	width = 1, height = 1;
	name = "flower";
	show_layer = 3;
}

bool Flower::update()
{
	return false;
}

std::pair<double, double> Flower::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Flower::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return ct;
}

bool Flower::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	switch (target_collider_layer) {
	case 0:
		level.remove(this);
		musicplayer.play("sound-powerup");
		break;
	}
	return true;
}