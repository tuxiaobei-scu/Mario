#pragma once
#include "collider.h"
class Flagpole :
    public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Flagpole();
};

class Flag :
	public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Flag();
};

class Small_flag :
	public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Small_flag();
};

