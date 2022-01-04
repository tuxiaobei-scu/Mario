//×©¿é
#pragma once
#include "collider.h"
#include "global.h"
#include "graphics.h"
class Brick :
    public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct; //ÔìÐÍ
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Brick(char* s);
	Brick(int a, int b);
};

