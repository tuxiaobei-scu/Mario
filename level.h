//关卡管理
#pragma once
#include "collider.h"
#include "global.h"
#include "mario.h"
#include <vector>
#include <iostream>
class Level
{
private:
	bool isshow = true;
	bool isrun = true;
	void reset();
	void basic_block();
	char s[256];
	std::string now_music; //当前背景音乐名称
	int update_pos = 0; //更新最右的位置
	bool invincible = false; //无敌星状态
public:
	std::vector<Collider*>mp[MAX_LEVEL_LAYER + 5][MAX_LEVEL_RANGE + 5]; //静态角色
	std::vector<Collider*>actors[MAX_LEVEL_LAYER + 5]; //动态角色
	std::vector<Collider*>unrun_actors[MAX_LEVEL_RANGE + 5]; //待运行的动态角色
	Collider* addobject(char* s, double x, double y); //在x,y 用命令 s 新增角色
	Mario* mario; //马里奥的地址
	void death(); //死亡
	void finish(); //关卡结束
	void restart(); //重新开始
	void start(const char* path); //读取关卡文件
	void start(); //开始
	void stop(); //停止
	bool remove(Collider* t); //删除角色
	bool update(); //关卡更新
	bool running(); //是否在运行
	bool freeze = true; //是否处于冻结状态
	int map_range; //关卡范围
	int limit_time = 300; //时间限制
	int start_time; //开始时间
	int last_time; //上一帧时间戳
	int now_time; //当前运行时间戳
	int death_time = 0; //死亡时间
	int finish_time = 0; //结束时间
	bool finish_move = false; //是否开始结束移动动画
	Level();
};

extern Level level;