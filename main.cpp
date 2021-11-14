#include "graphics.h"
#include "menu.h"
#include "global.h"
#include <cstdio>

int main()
{
	// 绘图窗口初始化
	initgraph(800, 600);
	setbkcolor(EGERGB(107, 140, 255));
	setcaption("Super mario Bros");

	setfont(-30, 20, "FixedsysTTF");
	setcolor(WHITE);				//文字的颜色
	setbkmode(TRANSPARENT);			//设置文字背景色为透明	
	Menu menu;
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		menu.update();
		SCORE += 1;
	}
}
