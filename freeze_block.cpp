#include "freeze_block.h"

Freeze_block::Freeze_block(Costume ct, int show_layer, double width, double hetght)
{
	this->ct = ct;
	this->show_layer = show_layer;
	collider_layer = -1;
	id = ++COLLIDER_ID;
	freeze = true;
	this->width = width, this->height = height;
	name = "freeze_block";
	show_layer = 1;
}

bool Freeze_block::update()
{
	return false;
}

std::pair<double, double> Freeze_block::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Freeze_block::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return ct;
}

bool Freeze_block::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}
