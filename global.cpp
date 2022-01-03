#include "global.h"
#include <cstring>
#include <vector>
#include <algorithm>
int SCORE = 0;
int COIN_TOTAL = 0;
int LIVES = 3;
int TOP_SCORE = 0;
int COLLIDER_ID = 0;
int START_TIME = 0;
int NOW_SCENR = 0;
int PLAYERS_NUM = 1;
double GRAVITY = 50;
bool DEBUG_MODE = false;
std::string LEVEL_NAME = "";

bool Costume::operator == (const Costume& p) {
	return a == p.a && b == p.b && c == p.c;
}

PIMAGE getZoomImageCopy(PIMAGE pimg, int zoomWidth, int zoomHeight)
{
	int width = getwidth(pimg), height = getheight(pimg);
	if (zoomWidth <= 0) {
		zoomWidth = width;
	}
	if (zoomHeight <= 0) {
		zoomHeight = height;
	}
	PIMAGE tempPimg = newimage(zoomWidth, zoomHeight);
	putimage(tempPimg, 0, 0, zoomWidth, zoomHeight, pimg, 0, 0, width, height);
	return tempPimg;
}

void zoomImage(PIMAGE& pimg, int zoomWidth, int zoomHeight)
{
	//和原图像大小一样，不用缩放，直接返回
	if (zoomWidth == getwidth(pimg) && zoomHeight == getheight(pimg))
		return;

	PIMAGE copyImg = getZoomImageCopy(pimg, zoomWidth, zoomHeight);
	delimage(pimg);

	pimg = copyImg;
}

void zoomImage(PIMAGE& pimg, float scale)
{
	if (scale == 1.0f || scale < 0)
		return;

	//计算比例缩放后的尺寸，并近似取整
	int width = int(getwidth(pimg) * scale + 0.5f);
	int height = int(getheight(pimg) * scale + 0.5f);

	zoomImage(pimg, width, height);
}

void getimage(PIMAGE pDstImg, LPCSTR pImgFile, int srcX, int srcY, int srcWidth, int srcHeigh)
{
	PIMAGE pimg1 = newimage();
	getimage(pimg1, pImgFile);
	getimage(pDstImg, pimg1, srcX, srcY, srcWidth, srcHeigh);
	delimage(pimg1);
}

void getimage1(PIMAGE pDstImg, LPCSTR  pImgFile, int srcX, int srcY, int dstX, int dstY)
{
	PIMAGE pimg1 = newimage();
	int srcWidth = dstX - srcX + 1, srcHeigh = dstY - srcY + 1;
	getimage(pimg1, pImgFile);
	getimage(pDstImg, pimg1, srcX, srcY, srcWidth, srcHeigh);
	delimage(pimg1);
}

void mirror_image(PIMAGE& pimg)
{
	color_t* data = getbuffer(pimg);
	int width = getwidth(pimg), height = getheight(pimg);
	for (int i = 0; i < height; i++) {
		std::reverse(data + width * i, data + width * i + width);
	}
}

void copyimage(PIMAGE& pDstimg, PIMAGE psrcimg)
{
	int width = getwidth(psrcimg), height = getheight(psrcimg);
	getimage(pDstimg, psrcimg, 0, 0, width, height);
}