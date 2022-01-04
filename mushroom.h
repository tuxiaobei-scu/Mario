//Ä¢¹½
#pragma once
#include "collider.h"

class Mushroom :
	public Collider
{
private:
	double sx = 0, sy = 0;
	int direction;
	Costume ct;
	int animation_time = -1;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Mushroom(char* s);
};
