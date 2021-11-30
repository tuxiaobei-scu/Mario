#include "collider.h"
#include "level.h"
#include "global.h"
#include "camera.h"


void Collider::setpos(double x, double y, double width, double height) {
	this->width = width, this->height = height;
	this->x = x + width / 2, this->y = y + height / 2;
}

std::pair<double, double> Collider::getpos() {
	std::pair<int, int> p = getctpos();
	return std::make_pair(x + p.first - width / 2, y + p.second - height / 2);
}

bool Collider::operator < (const Collider& c) {
	if (fabs(x - c.x) > EPS) return x < c.x;
	return y < c.y;
}

void Collider::calc()
{
	if (freeze) return;
	double fx_real = fx, fy_real = fy;
	if (fx_real * vx > maxwx) fx_real = maxwx / vx;
	//if (fy * vy > maxwy) fy = maxwy / vy;
	double ax, ay = fy / m + GRAVITY;
	
	if (fabs(vx) > 1) ax = (vx > 0 ? fx_real - f : fx_real + f) / m, last_direction = vx < 0;
	else {
		if (fabs(fx_real) > f) ax = fx_real / m;
		else ax = 0, vx = 0;
	}
	
	double tim = (clock() - level.last_time) / 1000.0;
	vx += tim * ax, vy += tim * ay;
	double prex = x, prey = y;
	move(x, y, tim * vx, tim * vy);
	if (!out_of_range) {
		if (x < width / 2) x = width / 2;
		if (x > level.map_range - width / 2) x = level.map_range - width / 2;
	}
	double lstx = x, lsty = y;
	y = checkonfloor(prex, prey);
	if (fabs(y - lsty) > EPS) vy = 0, onfloor = true;
	else {
		onfloor = false;
		y = checkceiling(prex, prey);
	}
	x = checkleftright();
	if (fabs(x - lstx) > EPS) vx = 0;
	//if (checkleftright()) x = lstx, vx = 0;
	if (collider_layer == 0) {
		camera.movecam(min(max(0, x - 10), level.map_range - 10), 0);
	}
}

bool Collider::checkcollide(double x, double y, const Collider* b)
{
	if (fabs(x - b->x) < (this->width + b->width) / 2 && fabs(y - b->y) < (this->height + b->height) / 2) return true;
	return false;
}
double Collider::checkleftright()
{
	int l = max(0, x - 3), r = min(l + 6, 499);
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (auto b : level.mp[i][j]) {
				int p = (vx > 0) ? 1 : -1;
				if (b->collider_layer == 1 && checkcollide(x + 0.01 * p, y, b)) {
					return b->x - (width + b->width) / 2 * p;
				}
			}
		}
	}
	return x;
}
double Collider::checkceiling(double prex, double prey)
{
	int l = max(0, x - 3), r = min(l + 6, 499);
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (auto b : level.mp[i][j]) {
				if (b->collider_layer == 1 && prey >= b->y + (height + b->height) / 2 && fabs(prex - b->x) < (this->width + b->width) / 2 - EPS && checkcollide(x, y - 0.01, b)) {
					report_collision(TOP, b);
					report_collision(BOTTOM, this);
					vy = 0;
					return b->y + (height + b->height) / 2;
				}
			}
		}
	}
	return y;
}
double Collider::checkonfloor(double prex, double prey)
{
	int l = max(0, x - 3), r = min(l + 6, 499);
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (auto b : level.mp[i][j]) {
				if (b->collider_layer == 1 && prey <= b->y - (height + b->height) / 2 && fabs(prex - b->x) < (this->width + b->width) / 2 - EPS && checkcollide(x, y + 0.01, b))
					return b->y - (height + b->height) / 2;
			}
		}
	}
	return y;
}


bool Collider::move(double& x, double& y, double dx, double dy)
{
	double tx = x + dx, ty = y + dy;
	int l = max(0, tx - 3), r = min(l + 6, 499);
	bool flag = false;
	/*
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (auto b : level.mp[i][j]) {
				double cx = fabs(x - b->x), cy = fabs(y - b->y); //获取碰撞体中心点距离
				double totw = (this->width + b->width) / 2, toth = (this->height + b->height) / 2;
				if (cx >= totw || cy >= toth) continue; //不存在碰撞
				if (totw - cx < toth - cy) { //在x方向上的碰撞
					double p = tx < b->x ? b->x - totw : b->x + totw;
					if (fabs(p - x) < fabs(tx - x)) tx = p;
				}
				else { //在y方向上的碰撞
					double p = ty < b->y ? b->y - toth : b->y + toth;
					if (fabs(p - y) < fabs(ty - y)) ty = p;
					//exit(ty * 1000);
				}
				
			}
		}
	}
	*/
	x = tx, y = ty;
	return flag;
}
