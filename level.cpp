#include "level.h"
#include "collider.h"
#include "brick.h"
#include "chestnut.h"
#include "camera.h"
#include "mario.h"
#include "load_screen.h"
#include <sys/types.h>
#include "dirent.h"
#include <iostream>
#include <algorithm>

void Level::reset()
{
	for (int i = 0; i < MAX_LEVEL_LAYER; i++)
		for (int j = 0; j < MAX_LEVEL_RANGE; j++) {
			for (auto p : mp[i][j]) delete p;
			mp[i][j].clear();
		}
	for (int i = 0; i < MAX_LEVEL_RANGE; i++) {
		for (auto p : actors[i]) delete p;
		actors[i].clear();
	}
		
	for (int i = 0; i < MAX_LEVEL_RANGE; i++) {
		for (auto p : unrun_actors[i]) delete p;
		unrun_actors[i].clear();
	}
		
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
			brick->Collider::setpos(x, y, 1, 1);
			assert(x < MAX_LEVEL_RANGE);
			mp[0][x].push_back(brick);
		}
		else if (name == "Chestnut") {
			Chestnut* chestnut = new Chestnut(fp);
			chestnut->Collider::setpos(x, y, 1, 1);
			assert(x < MAX_LEVEL_RANGE);
			actors[3].push_back(chestnut);
		}
	}
	Mario* m = new Mario;
	actors[4].push_back(m);
	fclose(fp);
	camera.start();
}

void Level::restart()
{
	start((LEVEL_NAME + ".mio").c_str());
}

void Level::death()
{
	death_sound.Play(0);
	death_time = now_time;
	freeze = true;
	main_theme.Stop();
	LIVES--;
}

bool Level::update()
{
	if (!isrun) return false;
	last_time = now_time;
	now_time = clock();
	if (death_time && now_time - death_time > 3000) {
		death_time = 0;
		level.stop();
		if (LIVES) {
			load_screen.start("begin");
		}
		else {
			load_screen.start("game_over");
		}
		restart();
	}
	if (freeze) return camera.update();
	if (main_theme.GetPlayStatus() == MUSIC_MODE_STOP) {
		main_theme.Play(0);
	}
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (Collider* c : level.actors[i]) {
			c->calc();
		}
	}
	return camera.update();
}

void Level::start()
{
	isrun = true;
	camera.start();
	if (!freeze) {
		start_time = clock();
		now_time = start_time;
		last_time = now_time;
		main_theme.Play(0);
	}
	
}

bool Level::remove(Collider* t) {
	int l = max(0, t->x - 3), r = min(l + 6, level.map_range);
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			auto p = find(level.mp[i][j].begin(), level.mp[i][j].end(), t);
			if (p != level.mp[i][j].end()) {
				level.mp[i][j].erase(p);
				return true;
			}
		}
		auto p = find(level.actors[i].begin(), level.actors[i].end(), t);
		if (p != level.actors[i].end()) {
			level.actors[i].erase(p);
			return true;
		}
	}
	return false;
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
	death_sound.OpenFile("resources\\music\\death.wav");
}

Level level;