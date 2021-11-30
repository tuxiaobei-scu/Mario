#pragma once
#include "graphics.h"
#include <vector>
class Keymsg
{
private:
	std::vector<key_msg>msg;
public:
	bool down_key = false, right_key = false, left_key = false;
	bool S_key = false, Z_key = false;
	void update();
	bool getmsg(key_msg& m, int key);
};

extern Keymsg keymsg;
