#include "level.h"
#include "collider.h"
#include "brick.h"
#include "camera.h"
#include <iostream>
void Level::start(const char* path)
{
	FILE* fp = fopen(path, "r");
	char s1[50];
	std::string s2;
	while (true) {
		fscanf(fp, "%s", s1);
		s2 = s1;
		if (s2 == "end") break;
		if (s2 == "name") {
			fscanf(fp, "%s", s1);
			name = s1;
			continue;
		}
		if (s2 == "map_range") {
			fscanf(fp, "%d", &map_range);
			continue;
		}
	}
	while (true) {
		int x, y, id;
		fscanf(fp, "%d%d", &x, &y);
		if (x < 0 && y < 0) break;
		fscanf(fp, "%d", &id);
		std::string name = gp_type[id];
		if (name == "Brick") {
			Brick* brick = new Brick(fp);
			brick->Collider::setpos(x, y);
			mp[0][x].push_back(brick);
		}
	}
	camera.start();
}

bool Level::update()
{
	return camera.update();
}



Level level;