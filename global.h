#pragma once
#include "graphics.h"
#include <iostream>
#include <vector>
#define MAX_RUN_SPEED 800.0
#define MAX_WALK_SPEED 6.0

extern int SCORE;
extern int COIN_TOTAL;
extern int LIVES;
extern int TOP_SCORE;
extern int START_TIME;
extern int NOW_SCENR;
extern int PLAYERS_NUM;
extern char LEVEL_NAME[25];
extern std::vector<std::string>gp_type;

struct Costume {
	int a, b, c;
};

extern PIMAGE getZoomImageCopy(PIMAGE pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, float scale);
extern void getimage(PIMAGE pDstImg, LPCSTR pImgFile, int srcX, int srcY, int srcWidth, int srcHeigh);
extern void getimage1(PIMAGE pDstImg, LPCSTR  pImgFile, int srcX, int srcY, int dstX, int dstY);