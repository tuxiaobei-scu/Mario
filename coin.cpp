#include "coin.h"
#include "level.h"
#include "musicplayer.h"
Coin::Coin(char* s)
{
	freeze = true;
	show_layer = 3;
	collider_layer = 5;
	ct = { 12, 0, 0 };
}

Costume Coin::getcostume() 
{
	if (!isshow) return Costume{ -1, -1, -1 };
	if (level.now_time - animation_time > 200) {
		ct.c = (ct.c + 1) % 3;
		animation_time = level.now_time;
	}
	return ct;
}

std::pair<double, double> Coin::getctpos()
{
	return std::make_pair(sx, sy);
}

bool Coin::report_collision(int direction, Collider* target, int target_collider_layer)
{
	if (!isrun) return false;
	COIN_TOTAL++;
	SCORE += 100;
	musicplayer.play("sound-coin");
	level.remove(this);
	return true;
}