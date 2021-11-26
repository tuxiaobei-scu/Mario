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
		gp.push_back(v);
		//std::string s2 = s1;
		//gp_type.push_back(s2);
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
				c->update();
				std::pair<double, double>pos = c->getpos();
				Costume ct = c->getcostume();
				putimage_withalpha(NULL, gp[ct.a][ct.b][ct.c], (int)(pos.first * 40 - nowx), (int)(pos.second * 40 - nowy));
			}
		}
		for (Collider* c : level.actors[i]) {
			c->update();
			std::pair<double, double>pos = c->getpos();
			Costume ct = c->getcostume();
			putimage_withalpha(NULL, gp[ct.a][ct.b][ct.c], (int)(pos.first * 40 - nowx), (int)(pos.second * 40 - nowy));
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

Camera camera;