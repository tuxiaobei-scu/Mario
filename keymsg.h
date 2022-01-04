//键盘信息管理
#pragma once
#include "graphics.h"
#include <vector>
class Keymsg
{
private:
	std::vector<key_msg>msg; //键盘消息列表
public:
	void update();
	bool getmsg(key_msg& m, int key);
	bool is_down[256]; //是否被按下
	int down_time[256]; //按下的时间
};

extern Keymsg keymsg;
