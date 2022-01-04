//主页菜单
#pragma once
#include "graphics.h"
#include <vector>
#include <map>
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
	std::vector<std::string>levels; //所有关卡名字
public:
	bool update();
	Option_cursor();
	std::map<std::string, int>levels_top_score; //关卡最高分
};
extern Option_cursor option_cursor;
