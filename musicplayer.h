//音乐播放管理
#pragma once
#include "graphics.h"
#include <map>
#include <iostream>
class Musicplayer
{
private:
	std::map<std::string, MUSIC*> musics;
public:
	bool play(std::string s); //播放音乐
	bool stop(std::string s); //停止音乐
	bool checkend(std::string s); //判断播放是否结束
	bool SetVolume(std::string s, double v); //设置音乐音量
	bool isplay(std::string s); //判断是否在播放
	Musicplayer();
};

extern Musicplayer musicplayer;
