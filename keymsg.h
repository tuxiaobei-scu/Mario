#pragma once
#include "graphics.h"
#include <vector>
class Keymsg
{
private:
	std::vector<key_msg>msg;
public:
	void update();
	bool getmsg(key_msg& m, int key);
	bool is_down[256];
	int down_time[256];
};

extern Keymsg keymsg;
