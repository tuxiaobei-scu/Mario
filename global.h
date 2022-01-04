//全局变量和函数
#pragma once
#include "graphics.h"
#include <iostream>
#include <assert.h>
#include <vector>
#define EPS 1e-5
#define MAX_LEVEL_RANGE 500
#define MAX_LEVEL_LAYER 6

extern int SCORE;
extern int COLLIDER_ID;
extern int COIN_TOTAL;
extern int LIVES;
extern int TOP_SCORE;
extern int START_TIME;
extern int NOW_SCENR;
extern int PLAYERS_NUM;
extern bool DEBUG_MODE;
extern double GRAVITY;
extern std::string LEVEL_NAME;

struct Costume {
	int a, b, c;
	bool operator == (const Costume& p);
};

extern PIMAGE getZoomImageCopy(PIMAGE pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, float scale);
extern void getimage(PIMAGE pDstImg, LPCSTR pImgFile, int srcX, int srcY, int srcWidth, int srcHeigh);
extern void getimage1(PIMAGE pDstImg, LPCSTR pImgFile, int srcX, int srcY, int dstX, int dstY);
extern void mirror_image(PIMAGE& pimg);
extern void copyimage(PIMAGE& pDstimg, PIMAGE psrcimg);
extern PIMAGE getZoomImageCopy(PIMAGE pimg, int zoomWidth, int zoomHeight);