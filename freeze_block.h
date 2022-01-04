//²»¶¯µÄ×©¿é
#pragma once
#include "collider.h"
class Freeze_block :
    public Collider
{
private:
	double sx = 0, sy = 0;
	Costume ct;
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	Freeze_block(Costume ct, int show_layer, double width = 0, double hetght = 0);
};

