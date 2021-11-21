#pragma once
#include "collider.h"
#include "global.h"
#include <vector>
#include <iostream>
class Mario :
	public Collider
{
private:
	std::string state = "walk";
	std::vector<Costume>frames[3];
	int sx = 0, sy = 0;
	Costume ct;
public:
	Costume getcostume();
	std::pair<int, int> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Mario();
	int show_layer = 0;
};

