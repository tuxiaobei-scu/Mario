#pragma once
#include "graphics.h"
#include <map>
#include <iostream>
class Musicplayer
{
private:
	std::map<std::string, MUSIC*> musics;
public:
	bool play(std::string s);
	bool stop(std::string s);
	bool checkend(std::string s);
	bool SetVolume(std::string s, double v);
	Musicplayer();
};

extern Musicplayer musicplayer;
