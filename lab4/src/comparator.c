#include "str.h"

int int_cmp(const void* a, const void* b) {
	int* pa = (int*)(a);
	int* pb = (int*)(b);
	
	if (*pa == *pb)
		return 0;
	return *pa < *pb ? -1 : 1;
}

int char_cmp(const void* a, const void* b) {
	unsigned char* pa = (unsigned char*)(a);
	unsigned char* pb = (unsigned char*)(b);
	
	if (*pa == *pb)
		return 0;
	return *pa < *pb ? -1 : 1;
}

int str_cmp(const void* a, const void* b) {
	char** pa = (char**)(a);
	char** pb = (char**)(b);
	return strcmp(*pa, *pb);
}

