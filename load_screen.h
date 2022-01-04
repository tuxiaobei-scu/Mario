//¹ý¶É½çÃæ
#pragma once
#include <cstring>
#include <iostream>
#include "graphics.h"
class Load_screen
{
private:
	bool render();
	bool isshow = false;
	bool isrun = false;
	int start_time;
	std::string name;
	PIMAGE mario;
public:
	bool update();
	void start(std::string name);
	void stop();
	Load_screen();
};

extern Load_screen load_screen;

