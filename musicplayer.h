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
	Musicplayer();
};

extern Musicplayer musicplayer;
