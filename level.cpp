#include "level.h"
#include "collider.h"
#include "brick.h"
#include "chestnut.h"
#include "camera.h"
#include "mario.h"
#include "load_screen.h"
#include "flagpole.h"
#include "musicplayer.h"
#include "freeze_block.h"
#include "mushroom.h"
#include "coin.h"
#include "tortoise.h"
#include "flower.h"
#include "star.h"
#include "question_block.h"
#include "death_animation.h"
#include "headers.h"
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
		actors[i].clear();
	}
	for (int i = 0; i < MAX_LEVEL_RANGE; i++) {
		for (auto p : unrun_actors[i]) delete p;
		unrun_actors[i].clear();
	}
	delete mario;
	finish_time = 0;
	finish_move = false;
	update_pos = 0;
}



void Level::basic_block() 
{
	Mario* m = new Mario;
	mario = m;
	actors[0].push_back(m);
	/*旗杆部分开始*/
	Flagpole* f = new Flagpole;
	mp[0][map_range - 10].push_back(f);
	for (int i = 1; i <= 10; i++) {
		for (int j = 14; j <= 15; j++) {
			Brick* brick = new Brick(0, 0);
			brick->Collider::setpos(map_range - i, j - 1, 1, 1);
			mp[2][map_range - i].push_back(brick);
		}
	}
	Brick* brick = new Brick(1, 0);
	brick->Collider::setpos(map_range - 10, 12, 1, 1);
	mp[2][map_range - 10].push_back(brick);
	Flag* flag = new Flag();
	flag->Collider::setpos(map_range - 10, 3, 1, 1);
	mp[1][map_range - 10].push_back(flag);
	/*旗杆部分结束*/
	/*城堡部分开始*/
	Freeze_block* freeze_block;
	for (int i = 1; i <= 5; i++) {
		for (int j = 12; j <= 13; j++) {
			freeze_block = new Freeze_block(Costume{ 8, (i == 3), 2 - (i == 3 && j == 12) }, 1);
			freeze_block->Collider::setpos(map_range - i, j - 1, 1, 1);
			mp[1][map_range - i].push_back(freeze_block);
		}
		freeze_block = new Freeze_block(Costume{ 8, (i >= 2 && i <= 4), 0}, 1);
		freeze_block->Collider::setpos(map_range - i, 10, 1, 1);
		mp[1][map_range - i].push_back(freeze_block);
		if (i >= 2 && i <= 4) {
			freeze_block = new Freeze_block(Costume{ 8, 0, 0 }, 1);
			freeze_block->Collider::setpos(map_range - i, 8, 1, 1);
			mp[1][map_range - i].push_back(freeze_block);
		}
	}
	for (int i = 2; i <= 4; i++) {
		freeze_block = new Freeze_block(Costume{ 8, 0, 5 - i }, 1);
		freeze_block->Collider::setpos(map_range - i, 9, 1, 1);
		mp[1][map_range - i].push_back(freeze_block);
	}
	Small_flag* s_flag = new Small_flag();
	s_flag->Collider::setpos(map_range - 3, 9, 1, 1);
	mp[0][map_range - 3].push_back(s_flag);
	/*城堡部分结束*/
}

Collider* Level::addobject(char* s, double x, double y)
{
	assert(x < MAX_LEVEL_RANGE);
	assert(x >= 0);
	int id, pos;
	sscanf(s, "%d%n", &id, &pos);
	s += pos;
	std::string name = camera.gp_type[id];
	if (name == "Brick") {
		Brick* brick = new Brick(s);
		brick->Collider::setpos(x, y, 1, 1);
		mp[3][(int)x].push_back(brick);
		return brick;
	}
	else if (name == "Chestnut") {
		Chestnut* chestnut = new Chestnut(s);
		chestnut->Collider::setpos(x, y, 1, 1);
		unrun_actors[(int)x].push_back(chestnut);
		return chestnut;
	}
	else if (name == "Mushroom") {
		Mushroom* mushroom = new Mushroom(s);
		mushroom->Collider::setpos(x, y, 1, 1);
		unrun_actors[(int)x].push_back(mushroom);
		return mushroom;
	}
	else if (name == "Question_Block") {
		Question_block* question_block = new Question_block(s, x, y);
		question_block->Collider::setpos(x, y, 1, 1);
		mp[4][(int)x].push_back(question_block);
		return question_block;
	}
	else if (name == "Coin") {
		Coin* coin = new Coin(s);
		coin->Collider::setpos(x, y, 1, 1);
		mp[3][(int)x].push_back(coin);
		return coin;
	}
	else if (name == "Tortoise") {
		Tortoise* tortoise = new Tortoise(s);
		tortoise->Collider::setpos(x, y, 1, 1);
		unrun_actors[(int)x].push_back(tortoise);
		return tortoise;
	}
	else if (name == "Flower") {
		Flower* flower = new Flower(s);
		flower->Collider::setpos(x, y, 1, 1);
		unrun_actors[(int)x].push_back(flower);
		return flower;
	}
	else if (name == "Star") {
		Star* star = new Star(s);
		star->Collider::setpos(x, y, 1, 1);
		unrun_actors[(int)x].push_back(star);
		return star;
	}
	return NULL;
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
		double x, y;
		fgets(s, 256, fp);
		if (strlen(s) < 3) continue;
		int pos;
		sscanf(s, "%lf%lf%n", &x, &y, &pos);
		if (x < 0 && y < 0) break;
		addobject(s + pos, x, y);
	}
	fclose(fp);
	basic_block();
	int r = min(22, level.map_range);
	for (int i = update_pos; i <= r; i++) {
		for (auto p : unrun_actors[i]) {
			actors[p->show_layer].push_back(p);
		}
	}
	update_pos = r + 1;
	camera.start();
}

void Level::restart()
{
	start(("level_data\\" + LEVEL_NAME + ".mio").c_str());
}

void Level::finish()
{
	if (finish_time) return;
	musicplayer.play("music-flagpole");
	finish_time = now_time;
	musicplayer.stop(now_music);
	if (invincible) {
		musicplayer.stop("music-invincible");
		invincible = false;
	}
	Freeze_block* freeze_block; //摸旗后在城堡右侧添加砖块
	mario->show_layer = 1;
	for (int i = 1; i <= 2; i++) {
		for (int j = 12; j <= 13; j++) {
			freeze_block = new Freeze_block(Costume{ 8, 0, 2 }, 1);
			freeze_block->Collider::setpos(map_range - i, j - 1, 1, 1);
			mp[2][map_range - i].push_back(freeze_block);
		}
	}
	timer.end_show_time = max(level.limit_time - ((level.finish_time - level.start_time) / 1000), 0);
}

void Level::death()
{
	if (finish_time || death_time) return;
	musicplayer.stop(now_music);
	if (invincible) {
		musicplayer.stop("music-invincible");
		invincible = false;
	}
	musicplayer.play("music-death");
	death_time = now_time;
	freeze = true;
	LIVES--;
}

bool Level::update()
{
	if (!isrun) return false;
	last_time = now_time;
	now_time = clock();
	if (!finish_move && finish_time && now_time - finish_time > 1500) {
		finish_move = true;
		musicplayer.play("music-stage_clear");
	}
	if (finish_time && now_time - finish_time > 8000) { //结束判断
		finish_time = 0;
		level.stop();
		freeze = true;
		load_screen.start("course_clear");
		restart();
	}
	if (death_time && now_time - death_time > 3000) {  //死亡判断
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
	if (limit_time < ((now_time - start_time) / 1000)) {
		LIVES = 1;
		death();
	}
	if (!freeze && !finish_time) { //背景音乐控制
		if (level.mario->invincible_state_time) {
			if (!invincible) {
				musicplayer.stop(now_music);
				musicplayer.play("music-invincible");
				invincible = true;
			}
			
		} else {
			if (invincible) {
				musicplayer.stop("music-invincible");
				invincible = false;
			}
			if (limit_time - ((now_time - start_time) / 1000) > 100) {
				if (musicplayer.checkend(now_music)) {
					musicplayer.play(now_music);
				}
			}
			else {
				if (now_music == "music-main_theme") {
					musicplayer.stop(now_music);
					now_music = "music-out_of_time";
					musicplayer.play(now_music);
				}
				if (musicplayer.checkend(now_music)) {
					if (now_music == "music-out_of_time") {
						musicplayer.stop(now_music);
						now_music = "music-main_theme_sped_up";
						musicplayer.play(now_music);
					}
					else {
						musicplayer.play(now_music);
					}
				}
			}
		}
		
		
	}
	int r = min(max(0.0, floor(camera.nowx)) + 22, level.map_range); //动态加载角色
	for (int i = update_pos; i <= r; i++) {
		for (auto p : unrun_actors[i]) {
			actors[p->show_layer].push_back(p);
		}
	}
	update_pos = r + 1;
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
	if (!freeze && !finish_time) {
		now_music = "music-main_theme";
		musicplayer.SetVolume(now_music, 0.5);
		//musicplayer.play(now_music);
		start_time = clock();
		now_time = start_time;
		last_time = now_time;
	}
	
}

bool Level::remove(Collider* t) {
	int l = max(0, t->x - 3), r = min(l + 6, level.map_range);
	int layer = t->show_layer;
	for (int j = l; j <= r; j++) {
		auto p = find(level.mp[layer][j].begin(), level.mp[layer][j].end(), t);
		if (p != level.mp[layer][j].end()) {
			level.mp[layer][j].erase(p);
			return true;
		}
	}
	auto p = find(level.actors[layer].begin(), level.actors[layer].end(), t);
	if (p != level.actors[layer].end()) {
		level.actors[layer].erase(p);
		return true;
	}
	return false;
}

void Level::stop()
{
	isrun = false;
	musicplayer.stop(now_music);
}

bool Level::running()
{
	return isrun;
}

Level::Level()
{
	return;
}

Level level;