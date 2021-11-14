#include "global.h"
#include "score.h"
#include "graphics.h"
#include <cstdio>
bool Score::render() {
	if (!isshow) return false;
	xyprintf(75, 30, "MARIO");
	char s[10];
	sprintf(s, "%06d", SCORE);
	xyprintf(75, 61, s);
	return true;
}

bool Score::update() {
	if (!isrun) return false;
	return render();
}
Score score;