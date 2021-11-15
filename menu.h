#pragma once
#include "graphics.h"
class Menu
{
private:
	bool isshow = true;
	bool isrun = true;
	PIMAGE title;
	MUSIC music;

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
	PIMAGE icon;
public:
	bool update();
	Option_cursor();
};
extern Option_cursor option_cursor;
