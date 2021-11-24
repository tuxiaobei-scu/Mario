#include "collider.h"
#include "level.h"
#include "global.h"


void Collider::setpos(int x, int y) {
	this->x = x, this->y = y;
}

std::pair<double, double> Collider::getpos() {
	std::pair<int, int> p = getctpos();
	return std::make_pair(x + p.first, y + p.second);
}

bool Collider::operator < (const Collider& c) {
	if (fabs(x - c.x) > EPS) return x < c.x;
	return y < c.y;
}

void Collider::calc()
{
	if (freeze) return;
	if (fx * vx > maxwx) fx = maxwx / vx;
	if (fy * vy > maxwy) fy = maxwy / vy;
	double ax, ay = fy / m + GRAVITY;
	if (fabs(fx) < f) ax = 0;
	else ax = (fx > 0 ? fx - f : fx + f) / m;
	double tim = (clock() - level.last_time) / 1000.0;
	vx += tim * ax, vy += tim * ay;
	x += tim * vx, y += tim * vy;
}