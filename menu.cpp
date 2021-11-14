//主页菜单
#include "global.h"
#include "menu.h"
#include "graphics.h"	
#include "score.h"
#include "timer.h"
#include "coins.h"
#include "world_name.h"
#include "option_cursor.h"
#include <cstdio>
#include <iostream>

void Menu::reset()
{
	NOW_SCENR = 0;
	isshow = true;
	music.Play();
}

Menu::Menu()
{
	
	title = newimage();
	getimage(title, "resources\\graphics\\title_screen.png", 1, 60, 176, 88);
	zoomImage(title, 2.5);
	music.OpenFile("resources\\music\\start.mp3");
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

void Menu::setrunstate(bool run)
{
	if (run) reset();
	else {
		music.Stop();
		isrun = false;
	}
}
Menu menu;