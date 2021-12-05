#include "mario.h"
#include "keymsg.h"
#include "load_screen.h"
#include "level.h"
#include "musicplayer.h"
Mario::Mario()
{
	id = ++COLLIDER_ID;
	setpos(2, 5, 1, 1);
	freeze = false;
	maxwx = 150, maxwy = 1000;
	out_of_range = false;
	animation_time = clock();
	name = "mario";
}

bool Mario::update()
{

	if (y > 20) {
		level.death();
		return false;
	}
	key_msg keyMsg;
	//向左移动
	bool flag = keymsg.getmsg(keyMsg, key_left);
	if (flag || keymsg.left_key) {
		if (keyMsg.msg == key_msg_down || keymsg.left_key) {
			if (input_direction == 0) {
				input_direction = -1;
				fx = -50;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			if (input_direction == -1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	//向右移动
	flag = keymsg.getmsg(keyMsg, key_right);
	if (flag || keymsg.right_key) {
		if (keyMsg.msg == key_msg_down || keymsg.right_key) {
			if (input_direction == 0) {
				input_direction = 1;
				fx = 50;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			if (input_direction == 1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	flag = keymsg.getmsg(keyMsg, 'X');
	if (onfloor && state != "jump") state = "walk";
	if (!onfloor && state == "walk") state = "fall";
	int ck = clock();
	if (state == "jump" && ck - jump_time > 200){
		state = "fall";
		is_jump = false;
		fy = 0;
	}
	if (state == "jump" && !jump_sound && ck - jump_time >= 150) {
		musicplayer.play("sound-big_jump");
		jump_sound = true;
	}
	if (flag) {
		if (keyMsg.msg == key_msg_down && !jump_key) {
			if (state != "jump" && state != "fall") {
				jump_key = true;
				fy = -200;
				jump_sound = false;
				jump_time = ck;
				state = "jump";
				is_jump = true;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			jump_key = false;
			if (state == "jump") {
				if (ck - jump_time < 150 && !jump_sound) {
					jump_sound = true;
					musicplayer.play("sound-small_jump");
				}
				state = "fall";
				is_jump = false;
				fy = 0;
				jump_time = 0;
				
			}
		}
	}
	return false;
}

std::pair<double, double> Mario::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mario::getcostume()
{
	int change_time = 150 - maxwx / 2;
	if (level.death_time) {
		ct = Costume{ 2, 0, 5 };
		double c = (clock() - level.death_time - 800) / 1000.0;
		if (c > 0) {
			sy = ( c * c - c) * 15;
		}
	} else if (state == "walk") {
		if (fabs(vx) < 1 && fabs(fx) < f) ct = Costume{ mario_level, last_direction, 6 };
		else {
			if ((vx < 0) ^ (fx < 0) && fabs(vx) > 1) ct = Costume{ mario_level, last_direction, 3 }, animation_time = clock();
			else {
				if (ct.c >= 0 && ct.c <= 2) {
					if (clock() - animation_time >= change_time)
						ct = Costume{ mario_level, last_direction, (ct.c + 1) % 3 }, animation_time = clock();
				}
				else {
					ct = Costume{ mario_level, last_direction, 0 };
					animation_time = clock();
				}

			}
		}
	}
	else if (state == "jump" || state == "fall") {
		ct = Costume{ mario_level, last_direction, 4 };
	}
	return ct;
}


bool Mario::report_collision(int direction, Collider* target, int target_collider_layer)
{
	switch (target_collider_layer) {
	case 1:
		if (direction == TOP && target->collider_layer == 1 && state == "jump") {
			if (!jump_sound) {
				jump_sound = true;
				musicplayer.play("sound-small_jump");
			}
			state = "fall";
			is_jump = false;
			fy = 0;
		}
		break;
	case 2:
		if (direction == BOTTOM) {
			vy = -20;
			musicplayer.play("sound-stomp");
		}
		else {
			level.death();
		}
	}
	return true;
}