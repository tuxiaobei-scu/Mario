#pragma once
#include "graphics.h"	
class Menu
{
private:
	int start_time;
	bool isshow = true;
	bool isrun = true;
	PIMAGE title;
	MUSIC music;

	bool render();
	void reset();
public:
	bool update();
	void setrunstate(bool show);
	Menu();
};
extern Menu menu;
