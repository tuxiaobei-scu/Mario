#include "mario.h"
#include "keymsg.h"
Mario::Mario()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			frames[i].push_back(Costume{ i, 0, j });
		}
	}
	id = ++COLLIDER_ID;
	setpos(2, 5, 1, 1);
	freeze = false;
	maxwx = 50, maxwy = 50;
}

bool Mario::update()
{
	key_msg keyMsg;
	bool flag = keymsg.getmsg(keyMsg, key_left);
	if (flag) {
		if (keyMsg.msg == key_msg_down) {
			if (input_direction == 0) {
				input_direction = -1;
				fx = -20;
			}
		}
		else if (keyMsg.msg == key_msg_up) {
			if (input_direction == -1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	flag = keymsg.getmsg(keyMsg, key_right);
	if (flag) {
		if (keyMsg.msg == key_msg_down) {
			if (input_direction == 0) {
				input_direction = -1;
				fx = 20;
			}
		}
		else if (keyMsg.msg == key_msg_up) {
			if (input_direction == -1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	

	return false;
}

std::pair<int, int> Mario::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mario::getcostume()
{
	return ct;
}