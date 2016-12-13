#include "stddef.h"

char * strcpy(char * destination, const char * source) {
	size_t pos = 0;
	while (*(source + pos) != 0) {
		*(destination + pos) = *(source + pos);	
		pos++;
	}
	*(destination + pos) = 0;

	return destination;
}

char * strcat(char * destination, const char * source) {
	size_t destination_end = 0;	
	while (*(destination + destination_end) != 0)
		destination_end++;

	size_t pos = 0;
	while (*(source + pos) != 0) {
		*(destination + destination_end + pos) = *(source + pos);
		pos++;
	}
	*(destination + destination_end + pos) = 0;

	return destination;
}

int strcmp(const char * str1, const char * str2) {
	size_t pos = 0;
	while (*(str1 + pos) != 0 && *(str2 + pos) != 0 && *(str1 + pos) == *(str2 + pos))
		pos++;

	if (*(str1 + pos) == 0 && *(str2 + pos) == 0)
		return 0;
	return (unsigned char)(*(str1 + pos)) < (unsigned char)(*(str2 + pos)) ? -1 : 1;
}

size_t strlen(const char * str) {
	size_t len = 0;
	while (*(str + len) != 0)
		len++;
	return len;
}
