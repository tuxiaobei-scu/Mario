#pragma once
#include "collider.h"
#include <vector>
#include <iostream>
class Level
{
private:
	bool isshow = true;
	bool isrun = true;
	MUSIC main_theme;
	void reset();
public:
	std::vector<Collider*>mp[5][500];
	std::vector<Collider>actors[5];
	std::vector<Collider>unrun_actors;
	void start(const char* path);
	void start();
	void stop();
	bool update();
	bool running();
	bool freeze = true;
	int map_range;
	int limit_time = 300;
	int start_time;
	int last_time;
	Level();
};

extern Level level;