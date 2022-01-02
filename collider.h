#pragma once
#include "global.h"
#include "camera.h"
#include "graphics.h"
#include <algorithm>
#include <vector>
#include <iostream>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
class Collider
{
private:
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	std::pair<double, bool> checkonfloor(double prex, double prey);
	std::pair<double, bool> checkceiling(double prex, double prey);
	std::pair<double, bool> checkleftright();
	const int collide_re[10][10] = {
		{3, 3, 1, 1, 1, 1},
		{3, 0, 3, 0, 3, 0},
		{1, 3, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0},
		{1, 3, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0}
	};
	//0不排斥不检测，1仅检测，2仅排斥，3排斥且检测
	//0 人物，1 砖块，2 怪物，3 旗杆，4 蘑菇/隐藏砖, 5 金币
	//-1空图层，与任何物体不发生碰撞
protected:
	bool is_jump = false;
	double vx = 0, vy = 0; //当前速度
	double f = 15; //摩檫力
	double m = 1;  //物体的质量
	double maxwx = 20, maxwy = 20; //最大功率
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
	bool last_direction = false; // false右, true 左
	std::vector<Collider*> get_all_contacts();
	virtual bool report_collision(int direction, Collider* target, int target_collider_layer);
	//报告碰撞 (碰撞方向，碰撞对象，碰撞对象碰撞图层)
public:
	int id;
	bool isrun = true;  //是否运行
	bool isshow = true; //是否显示
	double x, y;   //当前位置
	double width, height; //碰撞体宽高
	double fx = 0, fy = 0; //当前外力
	bool freeze = true; //是否处于冻结状态
	virtual Costume getcostume();
	virtual std::pair<double, double> getctpos() = 0;
	virtual bool update();
	virtual void render(double x, double y);
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //碰撞图层
	int show_layer = 0; //显示图层
	void calc();
	bool operator < (const Collider& c);
	void start();
	std::string name;
};