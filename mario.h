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
	std::vector<Costume>frames[3];
	int sx = 0, sy = 0;
	Costume ct = Costume{2, 0, 6};
	int input_direction = 0;
	bool down_key = false, up_key= false, right_key = false, left_key = false;
public:
	Costume getcostume();
	std::pair<int, int> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Mario();
	int show_layer = 0;
};

