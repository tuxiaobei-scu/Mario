#include "brick.h"
#include "global.h"

Brick::Brick(FILE* fp)
{
	int a, b;
	fscanf(fp, "%d%d", &a, &b);
	costumes.push_back(Costume{ 4, a, b });
	ct = Costume{ 4, a, b };
}

bool Brick::update()
{
	return false;
}

std::pair<int, int> Brick::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Brick::getcostume()
{
	return ct;
}
