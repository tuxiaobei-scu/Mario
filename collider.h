#pragma once
#include "global.h"
#include <algorithm>
class Collider
{
private:
	int width, height;
	bool isrun = false;
	bool isshow = false;
	double fx, fy;
protected:
	double x, y;
	double m;
public:
	virtual Costume getcostume() = 0;
	virtual std::pair<int, int> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(int x, int y) {
		this->x = x, this->y = y;
	}
	std::pair<double, double> getpos() {
		std::pair<int, int> p = getctpos();
		return std::make_pair(x + p.first, y + p.second);
	}
	int collider_layer = 0;
};

