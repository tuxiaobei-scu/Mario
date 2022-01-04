//½ð±Ò
#pragma once
#include "collider.h"

class Coin :
	public Collider
{
private:
	double sx = 0, sy = 0;
	int animation_time = -1;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	Coin(char* s);
};