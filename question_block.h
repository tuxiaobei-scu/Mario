//问号砖
#pragma once
#include "collider.h"
class Question_block :
    public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct;
	Collider* target; //顶出出现对象的地址
	int used_time = 0;
	bool change_run = false, change_freeze = false;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Question_block(char* s, double x, double y);
};

