//得分浮动显示模块
#pragma once
#include "collider.h"
class Add_score :
    public Collider
{
private:
	double sx = 0, sy = 0; //造型渲染相对于中心的偏移
	bool type; //是否为终点得分显示
	int score; //显示的得分
	int alpha = 255; //透明度（淡出效果）
	int appear_time; //得分出现时间
public:
	std::pair<double, double> getctpos();
	bool update();
	Add_score(double x, double y, int score, bool type);
	void render(double x, double y);
};