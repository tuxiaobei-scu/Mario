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
	int show_layer = 0;
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
	int show_layer = 1;
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
	int show_layer = 0;
};

