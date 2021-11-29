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
	maxwx = 150, maxwy = 1000;
	out_of_range = false;
}

bool Mario::update()
{
	key_msg keyMsg;
	//向左移动
	bool flag = keymsg.getmsg(keyMsg, key_left);
	if (flag || left_key) {
		if (keyMsg.msg == key_msg_down || left_key) {
			left_key = true;
			if (input_direction == 0) {
				input_direction = -1;
				fx = -50;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			left_key = false;
			if (input_direction == -1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	//向右移动
	flag = keymsg.getmsg(keyMsg, key_right);
	if (flag || right_key) {
		if (keyMsg.msg == key_msg_down || right_key) {
			right_key = true;
			if (input_direction == 0) {
				input_direction = 1;
				fx = 50;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			right_key = false;
			if (input_direction == 1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	flag = keymsg.getmsg(keyMsg, key_up);
	if (onfloor && state != "jump") state = "walk";
	if (!onfloor && state == "walk") state = "fall";
	if (state == "jump" && clock() - jump_time > 200){
		state = "fall";
		is_jump = false;
		fy = 0;
	}
	if (flag) {
		if (keyMsg.msg == key_msg_down && !up_key) {
			up_key = true;
			if (state != "jump" && state != "fall") {
				fy = -200;
				jump_time = clock();
				state = "jump";
				is_jump = true;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			if (state == "jump") {
				state = "fall";
				is_jump = false;
				fy = 0;
				jump_time = 0;
			}
			up_key = false;
		}
	}
	LEVEL_NAME = state;
	SCORE = vx;
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