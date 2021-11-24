#pragma once
#include "global.h"
#include <algorithm>
class Collider
{
private:
	int width, height;
	bool isrun = false;
	bool isshow = false;
protected:
	int id;
	bool freeze = false;
	double x, y;   //当前位置
	double vx, vy; //当前速度
	double fx, fy; //当前外力
	double f; //摩檫力
	double m = 1;  //物体的质量
	double maxwx = 20, maxwy = 20; //最大功率
	bool static_y;
public:
	virtual Costume getcostume() = 0;
	virtual std::pair<int, int> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(int x, int y);
	std::pair<double, double> getpos();
	int collider_layer = 0;
	//0 人物，1 砖块
	void calc();
	bool operator < (const Collider& c);
	void start();
};

