#pragma once
#include "global.h"
#include <algorithm>
#include <iostream>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
class Collider
{
private:
	bool isrun = false;
	bool isshow = false;
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	double checkonfloor(double prex, double prey);
	double checkceiling(double prex, double prey);
	double checkleftright();
	const int collide_re[10][10] = {
		{3, 3, 1}, 
		{3, 0, 3},
		{1, 3, 0}
	};
	//0不检测，1仅1检测，2仅排斥，3排斥且检测
	//0 人物，1 砖块，2 栗子
	//-1空图层，与任何物体不发生碰撞
protected:
	int id;
	bool freeze = true;
	bool is_jump = false;
	double width, height;
	double vx = 0, vy = 0; //当前速度
	double fx = 0, fy = 0; //当前外力
	double f = 15; //摩檫力
	double m = 1;  //物体的质量
	double maxwx = 20, maxwy = 20; //最大功率
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
	bool last_direction = false; // false右, true 左
	virtual bool report_collision(int direction, Collider* target, int target_collider_layer) = 0;
public:
	double x, y;   //当前位置
	virtual Costume getcostume() = 0;
	virtual std::pair<double, double> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //碰撞图层
	void calc();
	bool operator < (const Collider& c);
	void start();
	std::string name;
};

