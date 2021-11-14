#pragma once
#include "graphics.h" 
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
