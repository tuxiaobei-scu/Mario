//Í·²¿ÏÔÊ¾×´Ì¬
#pragma once
#include "graphics.h"
class Score
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
public:
	bool update();
	void add_score(double x, double y, int score, bool type = false);
};

extern Score score;

class Coins
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
	int animation_time;
	const int costumes_num = 4;
	int now_costume;
	PIMAGE costumes[4];
public:
	bool update();
	Coins();
};

extern Coins coins;

class World_name
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
public:
	bool update();
};

extern World_name world_name;

class Timer
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
	bool count_down = false;
public:
	int end_show_time;
	bool update();
};

extern Timer timer;