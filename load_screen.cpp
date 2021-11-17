#include "load_screen.h"
#include "global.h"
#include "graphics.h"
#include "level.h"
#include <ctime>

Load_screen::Load_screen()
{
	mario = newimage();
	getimage1(mario, "resources\\graphics\\mario_bros.png", 320, 8, 335, 31);
	zoomImage(mario, 1.5);
	music.OpenFile("resources\\sound\\begin.wav");
}

bool Load_screen::render()
{
	if (!isshow) return false;
	bar(0, 0, 800, 600);
	if (name == "begin") {
		xyprintf(280, 200, "WORLD");
		xyprintf(430, 200, LEVEL_NAME);
		putimage_withalpha(NULL, mario, 330, 300);
		xyprintf(390, 300, "x");
		char s[5];
		sprintf_s(s, "%d", LIVES);
		xyprintf(430, 300, s);
	}
	return true;
}

bool Load_screen::update()
{
	if (!isrun) return false;
	if (clock() - start_time > 2000) {
		stop();
		return false;
	}
	return render();
}

void Load_screen::start(std::string name)
{
	isshow = true;
	isrun = true;
	start_time = clock();
	this->name = name;
	if (name == "begin") {
		music.Play(0);
	}
}

void Load_screen::stop()
{
	isshow = false;
	isrun = false;
	level.start("level1.mio");
}
Load_screen load_screen;


