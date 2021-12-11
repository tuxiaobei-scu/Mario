#pragma once
#include "collider.h"
#include "global.h"
#include <vector>
#include <iostream>
class Mario :
	public Collider
{
private:
	int jump_time = 0;
	std::string state = "walk";
	double sx = 0, sy = 0;
	Costume ct = Costume{2, 0, 6};
	int input_direction = 0;
	int mario_level = 2;
	int animation_time;
	bool jump_key = false;
	bool jump_sound = false;
	bool pole_direction;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Mario();
	int show_layer = 0;
};

