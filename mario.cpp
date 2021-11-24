#include "mario.h"

Mario::Mario()
{
	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j < 7; j++) {
			frames[i].push_back(Costume{ i, 0, j });
		}
	}
}

bool Mario::update()
{
	return false;
}

std::pair<int, int> Mario::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mario::getcostume()
{
	return ct;
}