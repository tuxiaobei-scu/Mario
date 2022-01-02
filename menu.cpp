//主页菜单
#include "global.h"
#include "menu.h"
#include "keymsg.h"
#include "graphics.h"	
#include "headers.h"
#include "load_screen.h"
#include "level.h"
#include "camera.h"
#include "dirent.h"
#include <sys/types.h>
#include <cstdio>
#include <iostream>

void Menu::reset()
{
	NOW_SCENR = 0;
	SCORE = 0;
	LIVES = 3;
	isshow = true;
	isrun = true;
	music.Play(0);
	level.freeze = true;
	camera.movecam(0, 0);
	level.start();
}

Menu::Menu()
{
	
	title = newimage();
	getimage1(title, "resources\\graphics\\title_screen.png", 1, 60, 176, 147);
	zoomImage(title, 2.5);
	music.OpenFile("resources\\music\\start.mp3");
	music.SetVolume(0.5);
	music.Play();
}


bool Menu::render()
{
	if (!isshow) return false;
	option_cursor.update();
	//putimage_withalpha(NULL, title, 170, 100, 2, 150, 440, 220); //显示标题
	putimage_withalpha(NULL, title, 170, 100); //显示标题
	return true;
}

bool Menu::update()
{
	if (!isrun) return false;
	if (!isshow) music.Stop();
	else {
		if (music.GetPlayStatus() == MUSIC_MODE_STOP) {
			//从头开始播放
			music.Play(0);
		}
	}
	return render();
}

void Menu::start()
{
	reset();
}

void Menu::stop()
{
	music.Stop();
	isrun = false;
	load_screen.start("begin");
}
Menu menu;

Option_cursor::Option_cursor()
{
	icon = newimage();
	getimage1(icon, "resources\\graphics\\title_screen.png", 3, 155, 12, 164);
	zoomImage(icon, 2.5);
	DIR* dir;
	struct dirent* ptr;
	dir = opendir("level_data"); //打开当前目录
	while ((ptr = readdir(dir)) != NULL) {
		std::string s = ptr->d_name;
		if (s.length() <= 4) continue;
		if (s.substr(s.length() - 4, s.length()) != ".mio") continue;
		s = s.erase(s.length() - 4, s.length());
		levels.push_back(s);
		levels_top_score[s] = 0;
	}
	if (levels.size() > 0) {
		level_id = 0;
		while (!camera.finish_init) Sleep(10);
		level.start(("level_data\\" + levels[0] + ".mio").c_str());
		LEVEL_NAME = levels[0];
	}
	closedir(dir);
}

bool Option_cursor::render()
{
	if (!isshow) return false;
	putimage_withalpha(NULL, icon, 240, 400);
	if (level_id - 1 >= 0)
		xyprintf(272, 350, levels[level_id - 1].c_str());
	if (level_id >= 0)
		xyprintf(272, 395, levels[level_id].c_str());
	if (level_id + 1 < levels.size()) 
		xyprintf(272, 440, levels[level_id + 1].c_str());
	if (LEVEL_NAME != "") {
		char topscore[20];
		sprintf(topscore, "TOP - %06d", levels_top_score[LEVEL_NAME]);
		xyprintf(272, 480, topscore);
	}
	return true;
}

bool Option_cursor::update()
{
	if (!isrun) return false;
	if (level_id != -1) {
		key_msg keyMsg;
		bool flag = keymsg.getmsg(keyMsg, key_down);
		if (flag && keyMsg.msg == key_msg_down &&level_id != levels.size() - 1) {
			level_id++;
			level.start(("level_data\\" + levels[level_id] + ".mio").c_str());
			LEVEL_NAME = levels[level_id];
		}
		flag = keymsg.getmsg(keyMsg, key_up);
		if (flag && keyMsg.msg == key_msg_down && level_id != 0) {
			level_id--;
			level.start(("level_data\\" + levels[level_id] + ".mio").c_str());
			LEVEL_NAME = levels[level_id];
		}
		flag = keymsg.getmsg(keyMsg, key_enter);
		if (flag) menu.stop();

	}
	return render();
}
Option_cursor option_cursor;