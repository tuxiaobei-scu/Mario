#include "level.h"
#include "collider.h"
#include "brick.h"
#include "camera.h"
#include <sys/types.h>
#include "dirent.h"
#include <iostream>

void Level::reset()
{
	for (int i = 0; i < 5; i++) 
		for (int j = 0; j < 500; j++) 
			mp[i][j].clear();
}

void Level::start(const char* path)
{
	reset();
	FILE* fp = fopen(path, "r");
	char s1[50];
	std::string s2;
	while (true) {
		fscanf(fp, "%s", s1);
		s2 = s1;
		if (s2 == "end") break;
		if (s2 == "map_range") {
			fscanf(fp, "%d", &map_range);
			continue;
		}
		if (s2 == "limit_time") {
			fscanf(fp, "%d", &limit_time);
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
	fclose(fp);
	camera.start();
}

bool Level::update()
{
	if (!isrun) return false;
	if (freeze) return camera.update();
	if (main_theme.GetPlayStatus() == MUSIC_MODE_STOP) {
		main_theme.Play(0);
	}
	return camera.update();
}

void Level::start()
{
	isrun = true;
	start_time = clock();
	main_theme.Play(0);
}

void Level::stop()
{
	isrun = false;
	main_theme.Stop();
}

bool Level::running()
{
	return isrun;
}

Level::Level()
{
	main_theme.OpenFile("resources\\music\\main_theme.mp3");
	main_theme.SetVolume(0.5);
}

Level level;