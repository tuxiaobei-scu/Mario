//摄像机
#pragma once
#include "graphics.h"
#include <iostream>
#include <vector>
class Camera
{
private:
	double targetx, targety;
	int map_range;
	bool isshow = false, isrun = false;
	bool render();
	bool key_d = false;
public:
	bool update();
	void movecam(double x, double y);
	void start();
	void stop();
	bool finish_init = false; //是否完成初始化
	double nowx, nowy; //摄像机位置
	std::vector<std::vector<std::vector<PIMAGE>>>gp; //图片素材
	std::vector<std::string>gp_type; //角色名称
	Camera();
};

extern Camera camera;

