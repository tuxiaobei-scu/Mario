#include "graphics.h"
#include "keymsg.h"
#include "menu.h"
#include "headers.h"
#include "load_screen.h"
#include "global.h"
#include "level.h"
#include <cstdio>

int main()
{
	// 绘图窗口初始化
	initgraph(800, 600, INIT_RENDERMANUAL);
	setbkcolor(EGERGB(107, 140, 255));
	setfillcolor(EGERGB(0, 0, 0));
	setcaption("Super mario Bros");

	setfont(-30, 20, "FixedsysTTF");
	setcolor(WHITE);				//文字的颜色
	setbkmode(TRANSPARENT);			//设置文字背景色为透明	
	for (; is_run(); delay_fps(120)) {
		cleardevice();
		keymsg.update();
		level.update();
		menu.update();
		load_screen.update();
		score.update(); //显示分数
		timer.update(); //显示时间
		coins.update(); //显示金币
		world_name.update(); //显示关卡名
	}
}
