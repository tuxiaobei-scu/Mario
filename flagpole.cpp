#include "flagpole.h"
#include "level.h"
Flagpole::Flagpole()
{
	collider_layer = 3;
	id = ++COLLIDER_ID;
	freeze = true;
	width = 0.125, height = 9.5;
	name = "flagpole";
	x = level.map_range - 9.5, y = 8.25 - 1;
	sx = -0.125;
	show_layer = 0;
}

bool Flagpole::update()
{
	return false;
}

std::pair<double, double> Flagpole::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Flagpole::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return Costume{6, 0, 0};
}

bool Flagpole::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}

Flag::Flag()
{
	collider_layer = -1;
	id = ++COLLIDER_ID;
	sx = -0.5;
	freeze = true;
	name = "flag";
	show_layer = 1;
}

bool Flag::update()
{
	if (!level.finish_time) return false;
	sy = min(8.0 * (level.now_time - level.finish_time) / 1500.0, 8.0);
	return true;
}

std::pair<double, double> Flag::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Flag::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return Costume{ 7, 0, 0 };
}

bool Flag::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}

Small_flag::Small_flag()
{
	collider_layer = -1;
	id = ++COLLIDER_ID;
	//sx = -0.5;
	freeze = true;
	show_layer = 0;
	name = "small_flag";
}

bool Small_flag::update()
{
	if (!level.finish_time || level.now_time - level.finish_time < 4000) return false;
	sy = -min(2 * (level.now_time - level.finish_time - 4000) / 1500.0, 2);
	return true;
}

std::pair<double, double> Small_flag::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Small_flag::getcostume()
{
	if (!isshow) return Costume{ -1, -1, -1 };
	return Costume{ 10, 0, 0 };
}

bool Small_flag::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}