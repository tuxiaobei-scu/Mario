//马里奥
#pragma once
#include "collider.h"
#include "global.h"
#include <vector>
#include <iostream>
class Mario :
	public Collider
{
private:
	int jump_time = 0; //跳跃开始时间
	std::string state = "walk"; //状态
	double sx = 0, sy = 0;
	Costume ct = Costume{2, 0, 6};
	Costume change_ct;
	int input_direction = 0; //输入方向键方向
	int mario_level = 2;     //马里奥等级，1大马里奥，2小马里奥，3火焰马里奥
	int animation_time = 0;      //动画时间戳
	int change_time = 0;         //改变等级时间戳
	int invincible_animation_time = 0; //无敌动画闪烁时间戳
	int fire_time = 0; //发射火焰时间
	bool jump_key = false;   
	bool jump_sound = false;
	bool pole_direction;     //摸旗方向
	bool is_squat = false; //是否下蹲
	bool is_dash = false; //是否处于冲刺状态
	bool change_size = false; //是否改变状态大小
	void downgrade(); //丢失状态
	bool standup();   //尝试起立
	void squat(); //下蹲
	void change_level(int target);
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Mario();
	void render(double x, double y);
	int mario_fire_num = 0; //发射火焰个数
	int invincible_state_time = 0; //无敌星时间
};