#include "load_screen.h"
#include "global.h"
#include "graphics.h"
#include "level.h"
#include "menu.h"
#include "musicplayer.h"
#include <ctime>

Load_screen::Load_screen()
{
	mario = newimage();
	getimage1(mario, "resources\\graphics\\mario_bros.png", 320, 8, 335, 31);
	zoomImage(mario, 1.5);
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
	else if (name == "course_clear") {
		xyprintf(280, 300, "COURSE CLEAR");
	}
	return true;
}

bool Load_screen::update()
{
	if (!isrun) return false;
	int tim = name == "begin" ? 2000 : 5000;
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
		musicplayer.play("sound-begin");
	}
	else if (name == "game_over") {
		level.freeze = true;
		musicplayer.play("music-game_over");
	}
	else if (name == "course_clear") {
		option_cursor.levels_top_score[LEVEL_NAME] = max(SCORE, option_cursor.levels_top_score[LEVEL_NAME]);
		musicplayer.play("music-course_clear");
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
	else if (name == "game_over" || name == "course_clear") {
		menu.start();
	}
	
}
Load_screen load_screen;


