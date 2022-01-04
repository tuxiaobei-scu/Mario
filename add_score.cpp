#include "add_score.h"
#include "level.h"
std::pair<double, double> Add_score::getctpos()
{
	return std::make_pair(sx, sy);
}

Add_score::Add_score(double x, double y, int score, bool type)
{
	this->x = x, this->y = y;
	this->score = score, this->type = type;
	height = 0, width = 0;
	show_layer = 5;
	collider_layer = -1;
	appear_time = level.now_time;
}

bool Add_score::update()
{
	int c = level.now_time - appear_time;
	if (!type) {
		if (c > 750) level.remove(this);
		else {
			alpha = 255 - c / 3; //½¥³ö
			sy = -0.5 - c / 500.0;
		}
	}
	else {
		sy = -min(8.0 * c / 1500.0, 9) * 0.95;
		if (c > 2055) {
			level.remove(this);
		}
		else if (c > 1800) {
			alpha = 255 - (c - 1800); //½¥³ö
		}
	}
	return true;;
}

void Add_score::render(double x, double y) {
	setfont(-20, 10, "FixedsysTTF");
	setcolor(EGEACOLOR(alpha, WHITE));
	char s[10];
	sprintf(s, "%d", score);
	int w = textwidth(s);
	ege_drawtext(s, x - (w / 2.0) * 1.21, y);
	setfont(-30, 20, "FixedsysTTF");
	setcolor(WHITE);
	return;
}