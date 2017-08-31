#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"
#include "ctype.h"
#include "bmp.h"

BMP* bmp_create() {
	BMP* bmp = malloc(sizeof(BMP));
	bmp->image = NULL;
	return bmp;
}

void bmp_destroy(BMP* bmp) {
	if (bmp->image)
		free(bmp->image);
	free(bmp);
}

static int width_alignment(int w) {
	return (w * 3 + 3) & (-4);
}

int bmp_load(const char* fname, BMP* bmp) {
	FILE* fin = fopen(fname, "rb");
	if (!fin)
		return 1;

	if (fread(&bmp->header, sizeof(BMPheader), 1, fin) != 1)
		return 2;

	bmp->w = width_alignment(bmp->header.biWidth);
	bmp->h = bmp->header.biHeight;
	bmp->image = malloc(bmp->w * bmp->h);
	
	if (fread(bmp->image, bmp->w * bmp->h, 1, fin) != 1)
		return 2;

	fclose(fin);

	return 0;
}

int bmp_save(const char* fname, BMP* bmp) {
	FILE* fout = fopen(fname, "wb");
	if (!fout)
		return 1;

	if (fwrite(&bmp->header, sizeof(BMPheader), 1, fout) != 1)
		return 2;
	if (fwrite(bmp->image, bmp->w * bmp->h, 1, fout) != 1)
		return 2;

	fclose(fout);

	return 0;
}

static void bmp_update(BMP* bmp, int w, int h) {
	bmp->w = width_alignment(w);
	bmp->h = h;
	bmp->header.bfSize = bmp->w * bmp->h + HEADER_SIZE;
	bmp->header.biWidth = w;
	bmp->header.biHeight = h;
	bmp->header.biSizeImage = bmp->w * bmp->h;
	bmp->image = malloc(bmp->w * bmp->h);
	memset(bmp->image, 0, bmp->w * bmp->h);
}

static bool correct_area(BMP* bmp, int x1, int y1, int x2, int y2) { //x1 <= x2, y1 <= y2
	return x1 >= 0 && x2 <= bmp->header.biWidth && y1 >= 0 && y2 <= bmp->header.biHeight;
}

int crop(BMP* bmp, int x, int y, int w, int h) {
	if (!correct_area(bmp, x, y, x + w, y + h))
		return 2;
	
	BMP* bmp_copy = malloc(sizeof(BMP));
	memcpy(bmp_copy, bmp, sizeof(BMPheader));
	bmp_update(bmp_copy, w, h);	

	int y_real = bmp->h - h - y;
	for (int i = y_real; i < y_real + h; i++) {
		int dst_pos = bmp_copy->w * (i - y_real);
		int src_pos = bmp->w * i + x * 3;
		memcpy(&bmp_copy->image[dst_pos], &bmp->image[src_pos], w * 3);
	}

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
	bmp_update(bmp_copy, h, w);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int dst_pos = bmp_copy->w * (w - x - 1) + 3 * y;
			int src_pos = bmp->w * y + 3 * x;
			memcpy(&bmp_copy->image[dst_pos], &bmp->image[src_pos], 3);
		}
	}
	
	free(bmp->image);
	memcpy(bmp, bmp_copy, sizeof(BMP));
	free(bmp_copy);
}

int insert_msg(const char* key_txt, const char* msg_txt, BMP* bmp) {
	FILE* key = fopen(key_txt, "r");
	FILE* msg = fopen(msg_txt, "r");

	if (!key || !msg)
		return 1;

	bool done = false;
	while (!done) {
		char symb;
		if (fread(&symb, 1, 1, msg) != 1)
			break;
		if (isalpha(symb))
			symb -= 'A';
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

			int pos = bmp->w * (bmp->h - y - 1) + x * 3 + color;
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

	if (!key || !msg)
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

		int pos = bmp->w * (bmp->h - y - 1) + x * 3 + color;
		int bit = bmp->image[pos] & 1;
		symb |= bit << (i % 5);

		if (i % 5 == 4) {
			if (symb < 26)
				symb += 'A';
			if (symb == 26)
				symb = ' ';
			if (symb == 27)
				symb = '.';
			if (symb == 28)
				symb = ',';

			if (fprintf(msg, "%c", symb) != 1)
				return 2;
		}
	}

	fclose(key);
	fclose(msg);

	return 0;
}

