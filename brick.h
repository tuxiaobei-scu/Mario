#pragma once
#include "collider.h"
#include "global.h"
#include "graphics.h"
class Brick :
    public Collider
{
private:
	int sx = 0, sy = 0;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target);
public:
	Costume getcostume();
	std::pair<int, int> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Brick(FILE* fp);
	int show_layer = 0;
};

