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
};

extern Keymsg keymsg;
