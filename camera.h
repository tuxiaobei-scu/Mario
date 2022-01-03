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
	bool finish_init = false;
	double nowx, nowy;
	std::vector<std::vector<std::vector<PIMAGE>>>gp; //Í¼Æ¬ËØ²Ä
	std::vector<std::string>gp_type;
	Camera();
};

extern Camera camera;

