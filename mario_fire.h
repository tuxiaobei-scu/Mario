//ÂíÀï°Â»ğÑæÇò
#pragma once
#include "collider.h"

class Mario_fire :
	public Collider
{
private:
	double sx = 0, sy = 0;
	int death_time = 0;
	void fire_death();  //»ğÇòãıÃğ
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	void render(double x, double y);
	Mario_fire(double x, double y, int direction);
};