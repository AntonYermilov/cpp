#ifndef __BMP_H__
#define __BMP_H__

#include "stdint.h"

#define HEADER_SIZE 54

#pragma pack(push, 1)
typedef struct {
	uint16_t bfType;
	int bfSize;
	int bfReserved;
	int bfOffBits;

	int biSize;
	int biWidth;
	int biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
} BMPheader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	BMPheader header;
	unsigned char* image;
	int w, h;
} BMP;
#pragma pack(pop)

BMP* bmp_create();
void bmp_destroy(BMP* free);

int bmp_load(const char* fname, BMP* bmp);
int bmp_save(const char* fname, BMP* bmp);
int crop(BMP* bmp, int x, int y, int w, int h);
void rotate(BMP* bmp);

int insert_msg(const char* key_txt, const char* msg_txt, BMP* bmp);
int extract_msg(const char* key_txt, const char* msg_txt, BMP* bmp);

#endif
