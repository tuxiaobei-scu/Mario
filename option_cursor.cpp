#include "option_cursor.h"
#include "global.h"
#include "graphics.h"
#include "menu.h"

Option_cursor::Option_cursor()
{
	icon = newimage();
	getimage(icon, "resources\\graphics\\title_screen.png", 3, 155, 8, 8);
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
			if (PLAYERS_NUM == 1) //Ë«ÈËÔÝÎ´¿ª·¢
				menu.setrunstate(false);
			break;
		}
	}
	return render();
}
Option_cursor option_cursor;