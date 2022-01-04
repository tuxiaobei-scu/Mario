//怪物：板栗
#pragma once
#include "collider.h"
class Chestnut :
    public Collider
{
private:
	double sx = 0, sy = 0;
	int direction;
	Costume ct;
	int animation_time = -1;
	int state = 0; //0正常，1冻结，2死亡
	bool killed = false; //是否被击杀
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	void kill(int direction);
	Chestnut(char* s);
};

