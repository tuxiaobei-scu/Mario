#include "death_animation.h"
#include "level.h"
std::pair<double, double> Death_animation::getctpos()
{
	return std::make_pair(sx, sy);
}

Death_animation::Death_animation(Costume ct, double x, double y, double vx, double vy)
{
	this->x = x, this->y = y;
	height = 0, width = 0;
	show_layer = 5;
	collider_layer = -1;
	appear_time = level.now_time;
	freeze = false;
	this->vx = vx, this->vy = vy;
	this->ct = ct;
}

bool Death_animation::update()
{
	int c = level.now_time - appear_time;
	rad = c / 50.0;
	return true;
}

void Death_animation::render(double x, double y) {
	if (ct.a < 0 || ct.b < 0 || ct.c < 0) return;
	IMAGE* p = newimage(100, 100);
	int width = getwidth(p), height = getheight(p);
	color_t* buffer = getbuffer(p);
	//彩色图转灰度图
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {	
			buffer[x + y * width] = EGEARGB(0, 0, 0, 0); //赋值为全透明图
		}
	}
	putimage_rotate(p, camera.gp[ct.a][ct.b][ct.c], 50, 50, 0.5, 0.5, rad); //旋转绘图
	putimage_withalpha(NULL, p, (int)x - 50, (int)y - 50);
	delimage(p);
	return;
}
