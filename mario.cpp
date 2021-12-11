#include "mario.h"
#include "keymsg.h"
#include "load_screen.h"
#include "level.h"
#include "musicplayer.h"
Mario::Mario()
{
	id = ++COLLIDER_ID;
	setpos(2, 12, 1, 1);
	freeze = false;
	maxwx = 100, maxwy = 1000;
	out_of_range = false;
	animation_time = level.now_time;
	name = "mario";
	show_layer = 3;
}

bool Mario::update()
{
	if (y > 20) {
		level.death();
		return false;
	}
	//SCORE = fx;
	if (level.finish_time) {
		if (level.finish_move && level.now_time - level.finish_time > 1800) {
			state = "walk";
			fx = 30, fy = 0;
		}else if (level.now_time - level.finish_time > 1500 && !pole_direction) {
			pole_direction = true;
			x = level.map_range - 9.5 - 0.375 + 0.75 * pole_direction;
			ct.b = pole_direction;
		}
		return true;
	}
	key_msg keyMsg;
	//向左移动
	bool flag = keymsg.getmsg(keyMsg, key_left);
	if (flag || keymsg.left_key) {
		if (keyMsg.msg == key_msg_down || keymsg.left_key) {
			if (input_direction == 0) {
				input_direction = -1;
				fx = -30;
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
				fx = 30;
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
	if (state == "jump" && level.now_time - jump_time > 200){
		state = "fall";
		is_jump = false;
		fy = 0;
	}
	if (state == "jump" && !jump_sound && level.now_time - jump_time >= 150) {
		musicplayer.play("sound-big_jump");
		jump_sound = true;
	}
	if (flag) {
		if (keyMsg.msg == key_msg_down && !jump_key) {
			if (state != "jump" && state != "fall") {
				jump_key = true;
				fy = -128 - min((fabs(vx) * 1.65), 10);
				jump_sound = false;
				jump_time = level.now_time;
				state = "jump";
				is_jump = true;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			jump_key = false;
			if (state == "jump") {
				if (level.now_time - jump_time < 150 && !jump_sound) {
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
	if (state == "pole_fall") {
		if (level.now_time - animation_time >= change_time && fabs(vy) > 1) {
			animation_time = level.now_time;
			ct.c = (ct.c == 7) ? 8 : 7;
		}
	}else if (level.death_time) {
		ct = Costume{ 2, 0, 5 };
		double c = (level.now_time - level.death_time - 800) / 1000.0;
		if (c > 0) {
			sy = ( c * c - c) * 15;
		}
		
	} else if (state == "walk") {
		if (fabs(vx) < 1 && fabs(fx) < f) ct = Costume{ mario_level, last_direction, 6 };
		else {
			if ((vx < 0) ^ (fx < 0) && fabs(fx) > 1) ct = Costume{ mario_level, last_direction, 3 }, animation_time = level.now_time;
			else {
				if (ct.c >= 0 && ct.c <= 2) {
					if (level.now_time - animation_time >= change_time)
						ct = Costume{ mario_level, last_direction, (ct.c + 1) % 3 }, animation_time = level.now_time;
				}
				else {
					ct = Costume{ mario_level, last_direction, 0 };
					animation_time = level.now_time;
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
		break;
	case 3:
		if (level.finish_time) break;
		pole_direction = (x > target->x);
		animation_time = level.now_time;
		x = level.map_range - 9.5 - 0.375 + 0.75 * pole_direction;
		state = "pole_fall";
		fy = -50, fx = 0;
		vy = 7, vx = 0;
		ct = Costume{ mario_level, pole_direction, 7 };
		level.finish();
		break;
	}
	return true;
}