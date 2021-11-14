#pragma once
#include "graphics.h"	
class Menu
{
private:
	int start_time;
	bool isshow = true;

	PIMAGE title;
	MUSIC music;

	bool render();
	void reset();
public:
	bool update();
	void setshowstate(bool show);
	Menu();
};

