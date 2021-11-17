#pragma once
#include "collider.h"
#include <vector>
#include <iostream>
class Level
{
private:
	std::string name;
	int map_range;
	bool isshow = false;
	bool isrun = false;
public:
	std::vector<Collider*>mp[5][500];
	void start(const char* path);
	bool update();
};

extern Level level;