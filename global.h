#pragma once


#include "graphics.h"

#define MAX_RUN_SPEED 800.0
#define MAX_WALK_SPEED 6.0

extern int SCORE;
extern int COIN_TOTAL;
extern int LIVES;
extern int TOP_SCORE;
extern int START_TIME;
extern int NOW_SCENR;
extern int PLAYERS_NUM;

extern PIMAGE getZoomImageCopy(PIMAGE pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, int zoomWidth, int zoomHeight);
extern void zoomImage(PIMAGE& pimg, float scale);
extern void getimage(PIMAGE pDstImg, LPCSTR  pImgFile, int srcX, int srcY, int srcWidth, int srcHeigh);