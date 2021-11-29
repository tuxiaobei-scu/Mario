#pragma once
#include "global.h"
#include <algorithm>
class Collider
{
private:
	bool isrun = false;
	bool isshow = false;
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	double checkonfloor(double prex, double prey);
	double checkleftright();
protected:
	int id;
	bool freeze = true;
	bool is_jump = false;
	double width, height;
	double x, y;   //当前位置
	double vx = 0, vy = 0; //当前速度
	double fx = 0, fy = 0; //当前外力
	double f = 20; //摩檫力
	double m = 1;  //物体的质量
	double maxwx = 20, maxwy = 20; //最大功率
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
public:
	virtual Costume getcostume() = 0;
	virtual std::pair<int, int> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //碰撞图层
	//0 人物，1 砖块
	void calc();
	bool operator < (const Collider& c);
	void start();
};

