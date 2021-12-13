#include "camera.h"
#include "graphics.h"
#include "global.h"
#include "collider.h"
#include "level.h"
#include <cstdio>


Camera::Camera()
{
	FILE* fp = fopen("graphics.txt", "r");
	int x, y, width, heigh, n, ny, m, mx;
	PIMAGE img = newimage();
	char s[50], s1[50];
	gp.resize(1);
	gp_type.resize(1);
	while (~fscanf(fp, "%s%d%d%d%d%d%d%d%d%s", s, &x, &y, &width, &heigh, &n, &ny, &m, &mx, s1)) {
		std::vector<std::vector<PIMAGE>>v;
		v.resize(n);
		getimage(img, s);
		for (auto& p : v) p.resize(m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				v[i][j] = newimage();
				getimage(v[i][j], img, x + j * mx, y + i * ny, width, heigh);
				zoomImage(v[i][j], 2.5);
			}
		}
		if (gp.size() < 4) {
			v.resize(n << 1);
			for (auto& p : v) p.resize(m);
			for (int i = n; i < (n << 1); i++) {
				for (int j = 0; j < m; j++) {
					v[i][j] = newimage();
					copyimage(v[i][j], v[i - n][j]);
					mirror_image(v[i][j]);
				}
			}
		}
		if (std::string(s1) == "Pole") {
			for (int i = 0; i < n; i++) {
				PIMAGE img = newimage(20, 60);
				copyimage(img, v[i][0]);
				delimage(v[i][0]);
				v[i][0] = newimage(20, 380);
				putimage(v[i][0], 0, 0, img);
				for (int j = 0; j < 8; j++) {
					putimage(v[i][0], 0, 60 + j * 40, 20, 40, img, 0, 20);
				}
				delimage(img);
			}
		}
		gp.push_back(v);
		std::string s2 = s1;
		gp_type.push_back(s2);
	}
	finish_init = true;
}

bool Camera::render()
{
	if (!isshow) return false;
	
	int l = max(0.0, floor(nowx));
	int r = l + 22;
	for (int i = 0; i < MAX_LEVEL_LAYER; i++) {
		for (int j = l; j <= r; j++) {
			for (Collider* c : level.mp[i][j]) {
				if (!level.freeze) c->update();
				std::pair<double, double>pos = c->getpos();
				c->render((pos.first - nowx) * 40, (pos.second - nowy) * 40);
				//Costume ct = c->getcostume();
				//putimage_withalpha(NULL, gp[ct.a][ct.b][ct.c], (int)((pos.first - nowx) * 40), (int)((pos.second - nowy) * 40));
			}
		}
		for (Collider* c : level.actors[i]) {
			if (c->id == level.mario->id) continue;
			if (!level.freeze) c->update();
			std::pair<double, double>pos = c->getpos();
			c->render((pos.first - nowx) * 40, (pos.second - nowy) * 40);
			//Costume ct = c->getcostume();
			//putimage_withalpha(NULL, gp[ct.a][ct.b][ct.c], (int)((pos.first - nowx) * 40), (int)((pos.second - nowy) * 40));
		}
		if (level.mario->show_layer == i) {
			if (!level.freeze) level.mario->update();
			std::pair<double, double>pos = level.mario->getpos();
			level.mario->render((pos.first - nowx) * 40, (pos.second - nowy) * 40);
			//Costume ct = level.mario->getcostume();
			//putimage_withalpha(NULL, gp[ct.a][ct.b][ct.c], (int)((pos.first - nowx) * 40), (int)((pos.second - nowy) * 40));
		}
	}
}

bool Camera::update()
{
	if (!isrun) return false;
	return render();
}

void Camera::start()
{
	isrun = true;
	isshow = true;
}

void Camera::movecam(double x, double y)
{
	nowx = x, nowy = y;
}
Camera camera;