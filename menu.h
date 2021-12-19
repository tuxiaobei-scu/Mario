#pragma once
#include "graphics.h"
#include <vector>
#include <iostream>
class Menu
{
private:
	bool isshow = true;
	bool isrun = true;
	PIMAGE title;
	MUSIC music; //由于此音乐涉及初始化，不通过播放器播放

	bool render();
	void reset();
public:
	bool update();
	void stop();
	void start();
	Menu();
};
extern Menu menu;

class Option_cursor
{
private:
	bool render();
	bool isshow = true;
	bool isrun = true;
	int level_id = -1;
	PIMAGE icon;
	std::vector<std::string>levels;
public:
	bool update();
	Option_cursor();
};
extern Option_cursor option_cursor;
