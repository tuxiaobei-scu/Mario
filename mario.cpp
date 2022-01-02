#include "mario.h"
#include "keymsg.h"
#include "load_screen.h"
#include "level.h"
#include "musicplayer.h"
#include "headers.h"
Mario::Mario()
{
	id = ++COLLIDER_ID;
	setpos(2, 12 + 2 / 16.0, 1, 14.0 / 16.0);
	sy = -1.0 / 16.0;
	freeze = false;
	maxwx = 100, maxwy = 1000;
	out_of_range = false;
	animation_time = level.now_time;
	name = "mario";
	show_layer = 3;
}

void Mario::render(double x, double y) {
	Costume ct = getcostume();
	if (ct.a < 0 || ct.b < 0 || ct.c < 0) return;
	if (change_time && !level.finish_time && !level.death_time) {
		int c = level.now_time - change_time;
		if (c < 500) { //角色改变动画
			PIMAGE ret = newimage();
			int a = ct.a;
			bool flag = (a == 2);
			if (a == 2) a = 1;
			copyimage(ret, camera.gp[a][ct.b][ct.c]);
			double ty = 0;
			if (c < 100) ty = 20;
			else if (c < 200) ty = 10;
			else if (c < 300) ty = 30;
			else if (c < 400) ty = 25;
			else ty = 45;
			if (flag) {
				zoomImage(ret, 0, 90 - ty);
				y -= 45 - ty + 5;
			}
			else {
				zoomImage(ret, 0, 45 + ty);
				y += 45 - ty - 10;
			}
			putimage_withalpha(NULL, ret, (int)x, (int)y);
			delimage(ret);
			return;
		} else if (c < 1500) {
			if ((c / 100) & 1) return;
		}
		else{
			if ((c / 50) & 1) return;
		}
	}
	putimage_withalpha(NULL, camera.gp[ct.a][ct.b][ct.c], (int)x, (int)y);
	return;
}

void Mario::downgrade()
{
	if (mario_level == 3) {
		change_level(1);
	}
	else if (mario_level == 1) {
		change_level(2);
	}
	else {
		level.death();
		return;
	}
	musicplayer.play("sound-pipe");
}

void Mario::change_level(int target)
{
	if (mario_level == target) return;
	ct.a = target;
	mario_level = target;
	if (target == 1 || target == 3) {
		y -= 7.0 / 16.0;
		height = 28.0 / 16.0;
		is_squat = false;
		squat();
		standup();
	}
	else {
		y += 7.0 / 16.0;
		sy = -1.0 / 16.0;
		if (is_squat) {
			is_squat = false;
			y -= 7.0 / 16.0;
		}
		height = 14.0 / 16.0;
	}
	change_time = level.now_time;
	freeze = true;
	change_ct = ct;
}

bool Mario::standup() 
{
	if (mario_level == 2) return false;
	if (!is_squat) false;
	double lsty = y;
	y -= 7.0 / 16.0;
	sy = -4.0 / 16.0;
	height = 28.0 / 16.0;
	auto c = get_all_contacts();
	for (auto b : c) {
		if (b->y >= y || b->collider_layer != 1) continue; //如果碰撞体在人物下方，则忽略
		y = max(y, b->y + (height + b->height) / 2);
	}
	c = get_all_contacts();
	bool flag = false;
	for (auto b : c) {
		if (b->collider_layer == 1) {
			flag = true;
			break;
		}
	}
	if (flag) { //起立失败
		y = lsty;
		sy = -18.0 / 16.0;
		height = 14.0 / 16.0;
		return false;
	}
	is_squat = false;
	return true;
}

void Mario::squat()
{
	if (mario_level == 2) return;
	if (is_squat) false;
	is_squat = true;
	ct.c = 5;
	input_direction = 0;
	y += 7.0 / 16.0;
	sy = -18.0 / 16.0;
	height = 14.0 / 16.0;
}

bool Mario::update()
{
	if (y > 20) {
		level.death();
		return false;
	}
	//状态改变取消冻结判定
	if (change_time) {
		if (freeze && level.now_time - change_time > 500) {
			freeze = false;
		}
		else if (level.now_time - change_time > 2500) {
			change_time = 0;
		}
		
	}
	bool flag;
	key_msg keyMsg;
	//摸旗动画
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
	//冲刺判断
	flag = keymsg.getmsg(keyMsg, 'Z');
	if (flag && level.now_time - keymsg.down_time['Z'] >= 200) {
		if (keyMsg.msg == key_msg_down && !is_squat)
			is_dash = true, maxwx = 150;
	}
	if (!keymsg.is_down['Z']) {
		is_dash = false;
		maxwx = 100;
	}
	//下蹲
	flag = keymsg.getmsg(keyMsg, key_down);
	if ((mario_level == 1 || mario_level == 3) && flag) {
		if (keyMsg.msg == key_msg_down && !is_squat) 
			squat();
	}
	if (is_squat && !keymsg.is_down[key_down])
		standup();
	if (onfloor && is_squat) fx = 0, input_direction = 0;
	//向左移动
	flag = keymsg.getmsg(keyMsg, key_left);
	if (flag || keymsg.is_down[key_left]) {
		if (keyMsg.msg == key_msg_down || keymsg.is_down[key_left]) {
			if (input_direction == 0) {
				if ((!onfloor || !is_squat)) {
					input_direction = -1;
					fx = -30;
				}
				else {
					last_direction = true;
				}
				
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
	if (flag || keymsg.is_down[key_right]) {
		if (keyMsg.msg == key_msg_down || keymsg.is_down[key_right]) {
			if (input_direction == 0) {
				if (!onfloor || !is_squat) {
					input_direction = 1;
					fx = 30;
				}
				else {
					last_direction = false;
				}
				
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
	if (!isshow) return Costume{-1, -1, -1};
	if (state == "pole_fall") { //如果摸旗，从旗杆滑落
		if (level.now_time - animation_time >= 100 && fabs(vy) > 1) {
			animation_time = level.now_time;
			ct.c = (ct.c == 7) ? 8 : 7; //如果滑落两个造型中切换
		}
	}else if (level.death_time) { //死亡状态
		ct = Costume{ 2, 0, 5 };
		double c = (level.now_time - level.death_time - 800) / 1000.0;
		if (c > 0) {
			sy = ( c * c - c) * 15; //用抛物线退出
		}
		
	}
	else if (is_squat && mario_level != 2 && level.now_time - change_time >= 500) { //下蹲
		ct = Costume{ mario_level, last_direction, 5 };
	}
	else if (state == "walk") {  //行走
		if (fabs(vx) < 1) ct = Costume{ mario_level, last_direction, 6 }; //无速度，站立
		else {
			if ((vx < 0) ^ (fx < 0) && fabs(fx) > 1 && fabs(vx) > 1) ct = Costume{ mario_level, last_direction, 3 }, animation_time = level.now_time; //转向
			else {
				if (ct.c >= 0 && ct.c <= 2) {
					if (level.now_time - animation_time >= 150 - maxwx / 2 && !freeze)
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
	case 1: //如果碰撞为砖块
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
	case 2: //如果碰撞为板栗
		if (direction == BOTTOM) { //如果碰撞方向为下方（即马里奥在板栗的上方）
			vy = -20;              //反弹 
			y = target->y - (height + target->height) / 2.0;
			musicplayer.play("sound-stomp");
		}
		else if (!change_time) { //如果不在造型改变的无敌时间
			downgrade(); //丢失状态
		}
		break;
	case 3: //如果摸到旗杆
		if (level.finish_time) break;
		pole_direction = (x > target->x);
		animation_time = level.now_time;
		standup();
		x = level.map_range - 9.5 - 0.375 + 0.75 * pole_direction;
		state = "pole_fall";
		fy = -50, fx = 0;
		y = max(y, 4);
		vy = 7, vx = 0;
		int sc;
		if (y < 6) {
			sc = 4000;
		}
		else if (y < 9) {
			sc = 800;
		}
		else if (y < 12) {
			sc = 200;
		}
		else {
			sc = 100;
		}
		ct = Costume{ mario_level, pole_direction, 7 };
		level.finish();
		score.add_score(level.map_range - 8.5, 12.5, sc, true);
		break;
	case 4: //如果碰撞对象时蘑菇或问号砖
		if (target->name != "question_block") {
			change_level(1); //如果是蘑菇，变为大状态
			score.add_score(x, y, 1000);
		}
	}
	return true;
}