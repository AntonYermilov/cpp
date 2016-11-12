#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"
#include "bmp.h"

int crop_rotate(const char* fin, const char* fout, int x, int y, int w, int h) {
	BMP* bmp = bmp_create();
	int err;

	err = bmp_load(fin, bmp);
	if (err)
		return err;

	err = crop(bmp, x, y, w, h);
	if (err)
		return err;

	rotate(bmp);

	err = bmp_save(fout, bmp);
	if (err)
		return err;
	
	bmp_destroy(bmp);

	return 0;
}

int insert(const char* fin, const char* fout, const char* key_txt, const char* msg_txt) {
	BMP* bmp = bmp_create();
	int err;
	
	err = bmp_load(fin, bmp);
	if (err)
		return err;

	err = insert_msg(key_txt, msg_txt, bmp);
	if (err)
		return err;

	err = bmp_save(fout, bmp);
	if (err)
		return err;

	bmp_destroy(bmp);

	return 0;
}

int extract(const char* fin, const char* key_txt, const char* msg_txt) {
	BMP* bmp = bmp_create();
	int err;
	
	err = bmp_load(fin, bmp);
	if (err)
		return err;

	err = extract_msg(key_txt, msg_txt, bmp);
	if (err)
		return err;
	
	bmp_destroy(bmp);

	return 0;
}

int main(int argc, char** argv) {
	int err = 0;
	if (strcmp(argv[1], "crop-rotate") == 0)
		err = argc != 8 || crop_rotate(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
	if (strcmp(argv[1], "insert") == 0)
		err = argc != 6 || insert(argv[2], argv[3], argv[4], argv[5]);
	if (strcmp(argv[1], "extract") == 0)
		err = argc != 5 || extract(argv[2], argv[3], argv[4]);

	return err;
}
