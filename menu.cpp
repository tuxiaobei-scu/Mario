//主页菜单
#include "global.h"
#include "menu.h"
#include "graphics.h"	
#include "headers.h"
#include "load_screen.h"
#include <cstdio>
#include <iostream>

void Menu::reset()
{
	NOW_SCENR = 0;
	isshow = true;
	music.Play(0);
}

Menu::Menu()
{
	
	title = newimage();
	getimage(title, "resources\\graphics\\title_screen.png", 1, 60, 176, 147);
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
	char topscore[20];
	sprintf(topscore, "TOP - %06d" , TOP_SCORE);
	xyprintf(290, 465, topscore);
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
	getimage(icon, "resources\\graphics\\title_screen.png", 3, 155, 12, 164);
	zoomImage(icon, 2.5);
}

bool Option_cursor::render()
{
	if (!isshow) return false;
	putimage_withalpha(NULL, icon, 240, 320 + 45 * PLAYERS_NUM);
	xyprintf(272, 360, "1 PLAYER GAME");
	xyprintf(272, 405, "2 PLAYER GAME");
	return true;
}

bool Option_cursor::update()
{
	if (!isrun) return false;
	if (kbmsg()) {
		key_msg keyMsg = getkey();
		switch (keyMsg.key) {
		case key_down:	PLAYERS_NUM = 2; break;
		case key_up: 	PLAYERS_NUM = 1; break;
		case key_enter:
			if (PLAYERS_NUM == 1) //双人暂未开发
				menu.stop();
			break;
		}
	}
	return render();
}
Option_cursor option_cursor;