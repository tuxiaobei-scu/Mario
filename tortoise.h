//乌龟
#pragma once
#include "collider.h"

class Tortoise :
	public Collider
{
private:
	double sx = 0, sy = 0;
	int direction;
	Costume ct;
	int animation_time = -1;
	int state = 0; //0走路，1睡觉静止，2滑动
	int sleep_time; //睡眠开始时间
	bool killed = false; //是否被击杀
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	void kill(int direction);
	Tortoise(char* s);
};
