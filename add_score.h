#pragma once
#include "collider.h"
class Add_score :
    public Collider
{
private:
	double sx = 0, sy = 0;
	bool type;
	int score;
	int alpha = 255;
	int appear_time;
public:
	std::pair<double, double> getctpos();
	bool update();
	Add_score(double x, double y, int score, bool type);
	void render(double x, double y);
};