#pragma once
#include "collider.h"
#include "global.h"
#include "mario.h"
#include <vector>
#include <iostream>
class Level
{
private:
	bool isshow = true;
	bool isrun = true;
	void reset();
	void basic_block();
	char s[256];
	std::string now_music;
public:
	std::vector<Collider*>mp[MAX_LEVEL_LAYER + 5][MAX_LEVEL_RANGE + 5];
	std::vector<Collider*>actors[MAX_LEVEL_LAYER + 5];
	std::vector<Collider*>unrun_actors[MAX_LEVEL_RANGE + 5];
	Collider* addobject(char* s, double x, double y);
	Mario* mario;
	void death();
	void finish();
	void restart();
	void start(const char* path);
	void start();
	void stop();
	bool remove(Collider* t);
	bool update();
	bool running();
	bool freeze = true;
	int map_range;
	int limit_time = 300;
	int start_time;
	int last_time;
	int now_time;
	int death_time = 0;
	int finish_time = 0;
	bool finish_move = false;
	Level();
};

extern Level level;