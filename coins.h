#pragma once
#include "graphics.h"
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