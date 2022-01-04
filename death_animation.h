//»÷É±ËÀÍö¶¯»­
#pragma once
#include "collider.h"
class Death_animation :
	public Collider
{
private:
	double sx = 0, sy = 0;
	double rad = 0; //Ğı×ª½Ç¶È
	int appear_time;
	Costume ct;
public:
	std::pair<double, double> getctpos();
	bool update();
	Death_animation(Costume ct, double x, double y, double vx, double vy);
	void render(double x, double y);
};