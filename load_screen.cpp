#include "load_screen.h"
#include "global.h"
#include "graphics.h"
#include "level.h"
#include "menu.h"
#include <ctime>

Load_screen::Load_screen()
{
	mario = newimage();
	getimage1(mario, "resources\\graphics\\mario_bros.png", 320, 8, 335, 31);
	zoomImage(mario, 1.5);
	begin_music.OpenFile("resources\\sound\\begin.wav");
	game_over_music.OpenFile("resources\\music\\game_over.mp3");
}

bool Load_screen::render()
{
	if (!isshow) return false;
	bar(0, 0, 800, 600);
	if (name == "begin") {
		xyprintf(280, 200, "WORLD");
		xyprintf(400, 200, LEVEL_NAME.c_str());
		putimage_withalpha(NULL, mario, 330, 300);
		xyprintf(390, 300, "x");
		char s[5];
		sprintf_s(s, "%d", LIVES);
		xyprintf(430, 300, s);
	}
	else if (name == "game_over") {
		xyprintf(300, 300, "GAME OVER");
	}
	return true;
}

bool Load_screen::update()
{
	if (!isrun) return false;
	int tim = name == "game_over" ? 5000 : 2000;
	if (clock() - start_time > tim) {
		stop();
		return false;
	}
	return render();
}

void Load_screen::start(std::string name)
{
	level.stop();
	isshow = true;
	isrun = true;
	start_time = clock();
	this->name = name;
	if (name == "begin") {
		begin_music.Play(0);
	}
	else if (name == "game_over") {
		level.freeze = true;
		game_over_music.Play(0);
	}
}

void Load_screen::stop()
{
	isshow = false;
	isrun = false;
	if (name == "begin") {
		level.freeze = false;
		level.start();
	}
	else if (name == "game_over") {
		menu.start();
	}
	
}
Load_screen load_screen;


