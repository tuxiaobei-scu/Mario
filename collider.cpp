#include "collider.h"
#include "level.h"
#include "global.h"
#include "camera.h"

void Collider::render(double x, double y) {
	Costume ct = getcostume();
	if (ct.a < 0 || ct.b < 0 || ct.c < 0) return;
	putimage_withalpha(NULL, camera.gp[ct.a][ct.b][ct.c], (int)x, (int)y);
	return;
}

bool Collider::report_collision(int direction, Collider* target, int target_collider_layer)
{
	return false;
}

bool Collider::update()
{
	return false;
}

void Collider::kill(int direction)
{
	return;
}

Costume Collider::getcostume() {
	return Costume{ -1, -1, -1 };
}

void Collider::setpos(double x, double y, double width, double height) {
	this->width = width, this->height = height;
	this->x = x + width / 2, this->y = y + height / 2;
}

std::pair<double, double> Collider::getpos() {
	std::pair<double, double> p = getctpos();
	return std::make_pair(x + p.first - width / 2, y + p.second - height / 2);
}

bool Collider::operator < (const Collider& c) {
	if (fabs(x - c.x) > EPS) return x < c.x;
	return y < c.y;
}

bool Collider::checklastcollision(Collider* target)
{
	return collision_history[collision_history_pos ^ 1].count(target) != 0;
}


void Collider::calc()
{
	if (freeze || !isrun) return;
	double fx_real = fx, fy_real = fy;
	if (fx_real * vx > maxwx) fx_real = maxwx / vx;
	double ax, ay = fy / m + GRAVITY; //计算加速度
	if (fabs(vx) > 1) { //判断面向方向
		ax = (vx > 0 ? fx_real - f : fx_real + f) / m;
		if (onfloor) last_direction = vx < 0;
	}
	else {
		if (fabs(fx_real) > f) {
			ax = fx_real / m;
			if (onfloor) last_direction = fx_real < 0;
		}
		else ax = 0, vx = 0;
	}
	double tim = (level.now_time - level.last_time) / 1000.0; //和上一帧相差时间
	vx += tim * ax, vy += tim * ay; //计算速度
	vx = min(vx, maxwx);
	double prex = x, prey = y;
	move(x, y, tim * vx, tim * vy); //移动
	if (!out_of_range) { //禁止出界
		if (x < width / 2) x = width / 2;
		if (x > level.map_range - width / 2) x = level.map_range - width / 2;
	}
	double lstx = x, lsty = y;
	std::pair<double, bool> ret = checkonfloor(prex, prey); //判断是否在地板上
	if (fabs(lsty - y) <= EPS) y = ret.first;
	if (ret.second) vy = 0, onfloor = true;
	else {
		onfloor = false;
		lsty = y;
		ret = checkceiling(prex, prey); //判断是否碰到顶
		if (fabs(lsty - y) <= EPS) y = ret.first;
	}
	lstx = x;
	ret = checkleftright(); //判断左右
	if (fabs(lstx - x) <= EPS) x = ret.first;
	if (ret.second) vx = 0;
	//if (checkleftright()) x = lstx, vx = 0;
	if (collider_layer == 0) {
		camera.movecam(min(max(0, x - 10), level.map_range - 20), 0); //移动摄像机
	}
	collision_history[collision_history_pos ^ 1].clear(); //滚动记录碰撞历史
	collision_history_pos ^= 1;
}

bool Collider::checkcollide(double x, double y, const Collider* b)
{
	if (fabs(x - b->x) < (this->width + b->width) / 2 && fabs(y - b->y) < (this->height + b->height) / 2) return true;
	//如果两个角色横向距离小于宽度之和的一半，这判定碰撞
	return false;
}

std::vector<Collider*> Collider::get_all_contacts() 
{
	std::vector<Collider*> ret;
	if (collider_layer == -1) return ret;
	int l = max(0, x - 3), r = min(l + 6, level.map_range);
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (auto b : level.mp[i][j]) {
				if ((collide_re[collider_layer][b->collider_layer] & 2) && checkcollide(x, y, b))
					ret.push_back(b);
			}
			
		}
		for (auto b : level.actors[i]) {
			if (b->id == this->id) continue;
			if ((collide_re[collider_layer][b->collider_layer] & 2) && checkcollide(x, y, b))
				ret.push_back(b);
		}
	}
	return ret;
}

std::pair<double, bool> Collider::checkleftright()
{
	if (collider_layer == -1) std::make_pair(x, false);
	int l = max(0, x - 3), r = min(l + 6, level.map_range);
	std::vector<Collider*> v;
	int p = (fabs(vx) >= 0.1 && vx > 0) || (fx > 0) ? 1 : -1; //判断检测左/右碰撞
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++)
			v.insert(v.end(), level.mp[i][j].begin(), level.mp[i][j].end());
		v.insert(v.end(), level.actors[i].begin(), level.actors[i].end()); //加入候选检测
	}
	double px = x;
	bool flag = false;
	for (auto b : v) {
		if (b->id == this->id || b->collider_layer == -1 || !b->isrun) continue;
		int flag1 = collide_re[collider_layer][b->collider_layer];
		int flag2 = collide_re[b->collider_layer][collider_layer];
		if (b->x > x && p == -1) continue;
		if ((flag1 || flag2) && checkcollide(x, y, b)) {
			int a_collider_layer = collider_layer;
			int b_collider_layer = b->collider_layer;
			if ((flag1 & 1) || (flag2 & 1))
				collision_history[collision_history_pos].insert(b);
			if (flag1 & 1) report_collision(2 - p, b, b_collider_layer); //报告碰撞
			if (flag2 & 1) b->report_collision(2 + p, this, a_collider_layer);
			//if (flag1 & 2) return std::make_pair(b->x - (width + b->width) / 2 * p, true);

			if (flag1 & 2) { //设置新的x坐标
				flag = true;
				if (p == 1) {
					px = min(b->x - (width + b->width) / 2, px);
				}
				else {
					px = max(b->x + (width + b->width) / 2, px);
				}
			}
		}
	}
	return std::make_pair(px, flag);
}
std::pair<double, bool> Collider::checkceiling(double prex, double prey)
{
	if (collider_layer == -1) return std::make_pair(y, false);
	if (vy > 0) return std::make_pair(y, false);
	int l = max(0, x - 3), r = min(l + 6, level.map_range);
	std::vector<Collider*> v;
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++)
			v.insert(v.end(), level.mp[i][j].begin(), level.mp[i][j].end());
		v.insert(v.end(), level.actors[i].begin(), level.actors[i].end());
	}
	double py = y;
	bool flag = false;
	for (auto b : v) {
		if (b->id == this->id || b->collider_layer == -1 || !b->isrun) continue;
		int flag1 = collide_re[collider_layer][b->collider_layer];
		int flag2 = collide_re[b->collider_layer][collider_layer];
		if ((flag1 || flag2) && prey >= b->y + (height + b->height) / 2 && fabs(prex - b->x) < (this->width + b->width) / 2 - EPS && checkcollide(x, y - 0.01, b)) {
			int a_collider_layer = collider_layer;
			int b_collider_layer = b->collider_layer;
			if ((flag1 & 1) || (flag2 & 1))
				collision_history[collision_history_pos].insert(b);
			if (flag1 & 1) report_collision(TOP, b, b_collider_layer);
			if (flag2 & 1) b->report_collision(BOTTOM, this, a_collider_layer);
			if (flag1 & 2) vy = 0;
			if (flag1 & 2) py = max(py, b->y + (height + b->height) / 2), flag = true;
		}
	}
	return std::make_pair(py, flag);
}
std::pair<double, bool> Collider::checkonfloor(double prex, double prey)
{
	if (collider_layer == -1) return std::make_pair(y, false);
	if (vy < 0) return std::make_pair(y, false);
	int l = max(0, x - 3), r = min(l + 6, level.map_range);
	std::vector<Collider*> v;
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) 
			v.insert(v.end(), level.mp[i][j].begin(), level.mp[i][j].end());
		v.insert(v.end(), level.actors[i].begin(), level.actors[i].end());
	}
	double py = y;
	bool flag = false;
	for (auto b : v) {
		if (b->id == this->id || b->collider_layer == -1 || !b->isrun) continue;
		int flag1 = collide_re[collider_layer][b->collider_layer];
		int flag2 = collide_re[b->collider_layer][collider_layer];
		if ((flag1 || flag2) && prey <= b->y - (height + b->height) / 2 && fabs(prex - b->x) < (this->width + b->width) / 2 - EPS && checkcollide(x, y + 0.01, b)) {
			int a_collider_layer = collider_layer;
			int b_collider_layer = b->collider_layer;
			if ((flag1 & 1) || (flag2 & 1))
				collision_history[collision_history_pos].insert(b);
			if (flag1 & 1) report_collision(BOTTOM, b, b_collider_layer);
			if (flag2 & 1) b->report_collision(TOP, this, a_collider_layer);
			if (flag1 & 2) py = min(py, b->y - (height + b->height) / 2), flag = true;
		}

	}
	return std::make_pair(py, flag);
}


bool Collider::move(double& x, double& y, double dx, double dy)
{
	double tx = x + dx, ty = y + dy;
	int l = max(0, tx - 3), r = min(l + 6, level.map_range);
	bool flag = false;
	x = tx, y = ty;
	return flag;
}
