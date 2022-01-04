//碰撞盒：所有关于关卡角色类均继承于此类
#pragma once
#include "global.h"
#include "camera.h"
#include "graphics.h"
#include <set>
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
	bool checkcollide(double x, double y, const Collider* b); //判断是否和目标发生碰撞
	bool move(double& x, double& y, double dx, double dy); //尝试移动
	std::pair<double, bool> checkonfloor(double prex, double prey); //是否在地板上
	std::pair<double, bool> checkceiling(double prex, double prey); //是否碰到顶
	std::pair<double, bool> checkleftright(); //判断左右是否碰到墙
	const int collide_re[10][10] = { //碰撞图层关系表示
		{3, 3, 1, 1, 1, 1, 1},
		{3, 0, 3, 0, 3, 0, 1},
		{1, 3, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0},
		{1, 3, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0},
	};
	//0不排斥不检测，1仅检测，2仅排斥，3排斥且检测
	//0 人物，1 砖块，2 怪物，3 旗杆，4 蘑菇/隐藏砖, 5 金币, 6马里奥火焰/无敌星
	//-1空图层，与任何物体不发生碰撞
	std::set<Collider*>collision_history[2]; //历史碰撞记录（滚动）
	int collision_history_pos = 0;
protected:
	bool is_jump = false;
	double f = 15; //摩檫力
	double m = 1;  //物体的质量
	double maxwx = 20, maxwy = 20; //最大功率
	bool static_y;
	bool out_of_range = true; //允许超出地图范围
	bool last_direction = false; // 面向方向，false右, true 左
	std::vector<Collider*> get_all_contacts();
	virtual bool report_collision(int direction, Collider* target, int target_collider_layer);
	//报告碰撞 (碰撞方向，碰撞对象，碰撞对象碰撞图层)
	bool checklastcollision(Collider* target); //判断是否连续报告碰撞
public:
	int id;
	bool isrun = true;  //是否运行
	bool isshow = true; //是否显示
	double x, y;   //当前位置
	double vx = 0, vy = 0; //当前速度
	double width, height; //碰撞体宽高
	double fx = 0, fy = 0; //当前外力
	bool onfloor = false; //是否在地面
	bool freeze = true; //是否处于冻结状态
	virtual Costume getcostume(); //获取造型
	virtual std::pair<double, double> getctpos() = 0; //获取造型位置
	virtual bool update(); //角色更新
	virtual void render(double x, double y); //渲染角色
	virtual void kill(int direction); //击杀角色
	void setpos(double x, double y, double width, double height); //设置位置
	std::pair<double, double> getpos(); //获得位置
	int collider_layer = 0; //碰撞图层
	int show_layer = 0; //显示图层
	void calc(); //碰撞检测主函数
	bool operator < (const Collider& c);
	void start();
	std::string name; //角色名字
};