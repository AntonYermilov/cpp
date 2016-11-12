#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"
#include "ctype.h"
#include "bmp.h"

BMP* bmp_create() {
	BMP* bmp = malloc(sizeof(BMP));
	return bmp;
}

void bmp_destroy(BMP* bmp) {
	free(bmp->image);
	free(bmp);
}

int bmp_load(const char* fname, BMP* bmp) {
	FILE* fin = fopen(fname, "rb");
	if (fin == NULL)
		return 1;

	fread(bmp, 1, 2, fin);
	fread((int*)(bmp) + 1, 1, sizeof(BMPheader) - 4, fin);

	bmp->w = (bmp->header.biWidth * 3 + 3) & (-4);
	bmp->h = bmp->header.biHeight;
	bmp->image = malloc(bmp->w * bmp->h);
	fread(bmp->image, 1, bmp->w * bmp->h, fin);
	fclose(fin);

	return 0;
}

int bmp_save(const char* fname, BMP* bmp) {
	FILE* fout = fopen(fname, "wb");
	if (fout == NULL)
		return 1;

	fwrite(bmp, 1, 2, fout);
	fwrite((int*)(bmp) + 1, 1, sizeof(BMPheader) - 4, fout);
	fwrite(bmp->image, 1, bmp->w * bmp->h, fout);
	fclose(fout);

	return 0;
}

int crop(BMP* bmp, int x, int y, int w, int h) {
	if (x < 0 || y < 0 || x + w > bmp->header.biWidth || y + h > bmp->header.biHeight)
		return 2;
	
	BMP* bmp_copy = malloc(sizeof(BMP));
	memcpy(bmp_copy, bmp, sizeof(BMPheader));

	
	bmp_copy->w = (w * 3 + 3) & (-4);
	bmp_copy->h = h;
	bmp_copy->header.bfSize = bmp_copy->w * bmp_copy->h + bmp_copy->header.bfOffBits;
	bmp_copy->header.biWidth = w;
	bmp_copy->header.biHeight = h;
	bmp_copy->image = malloc(bmp_copy->w * bmp_copy->h);
	memset(bmp_copy->image, 0, bmp_copy->w * bmp_copy->h);

	int y_real = bmp->h - h - y;
	for (int i = y_real; i < y_real + h; i++)
		memcpy(&bmp_copy->image[bmp_copy->w * (i - y_real)], &bmp->image[bmp->w * i + x * 3], w * 3);

	free(bmp->image);
	memcpy(bmp, bmp_copy, sizeof(BMP));
	free(bmp_copy);

	return 0;
}

void rotate(BMP* bmp) {
	int w = bmp->header.biWidth;
	int h = bmp->header.biHeight;
	BMP* bmp_copy = malloc(sizeof(BMP));
	memcpy(bmp_copy, bmp, sizeof(BMPheader));

	bmp_copy->w = (h * 3 + 3) & (-4);
	bmp_copy->h = w;
	bmp_copy->header.bfSize = bmp_copy->w * bmp_copy->h + bmp_copy->header.bfOffBits;
	bmp_copy->header.biWidth = h;
	bmp_copy->header.biHeight = w;
	bmp_copy->image = malloc(bmp_copy->w * bmp_copy->h);
	memset(bmp_copy->image, 0, bmp_copy->w * bmp_copy->h);

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			memcpy(&bmp_copy->image[bmp_copy->w * (w - x - 1) + 3 * y], &bmp->image[bmp->w * y + 3 * x], 3);
	
	free(bmp->image);
	memcpy(bmp, bmp_copy, sizeof(BMP));
	free(bmp_copy);
}

int insert_msg(const char* key_txt, const char* msg_txt, BMP* bmp) {
	FILE* key = fopen(key_txt, "r");
	FILE* msg = fopen(msg_txt, "r");

	if (key == NULL || msg == NULL)
		return 1;

	bool done = false;
	while (!done) {
		char symb;
		fread(&symb, 1, 1, msg);
		if (isalpha(symb))
			symb -= 'a';
		if (symb == ' ')
			symb = 26;
		if (symb == '.')
			symb = 27;
		if (symb == ',')
			symb = 28;

		for (int bit = 0; bit < 5; bit++) {
			int x, y;
			char color;

			done |= fscanf(key, "%d %d %c ", &x, &y, &color) != 3;
			if (done)
				break;

			if (color == 'B')
				color = 0;
			if (color == 'G')
				color = 1;
			if (color == 'R')
				color = 2;

			int pos = bmp->w * y + x * 3 + color;
			bmp->image[pos] = (bmp->image[pos] & (-2)) | ((symb & (1 << bit)) != 0);
		}
	}

	fclose(key);
	fclose(msg);

	return 0;
}

int extract_msg(const char* key_txt, const char* msg_txt, BMP* bmp) {
	FILE* key = fopen(key_txt, "r");
	FILE* msg = fopen(msg_txt, "w");

	if (key == NULL || msg == NULL)
		return 1;

	char symb;
	for (int i = 0; ; i++) {
		int x, y;
		char color;
		if (i % 5 == 0)
			symb = 0;

		if (fscanf(key, "%d %d %c ", &x, &y, &color) != 3)
			break;

		if (color == 'B')
			color = 0;
		if (color == 'G')
			color = 1;
		if (color == 'R')
			color = 2;

		int pos = bmp->w * y + x * 3 + color;
		int bit = bmp->image[pos] & 1;
		symb |= bit << (i % 5);

		if (i % 5 == 4) {
			if (symb < 26)
				symb += 'a';
			if (symb == 26)
				symb = ' ';
			if (symb == 27)
				symb = '.';
			if (symb == 28)
				symb = ',';

			fprintf(msg, "%c", symb);
		}
	}

	fclose(key);
	fclose(msg);

	return 0;
}

