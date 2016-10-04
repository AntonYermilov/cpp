#include "stddef.h"

void * memcpy(void * destination, const void * source, size_t num) {
	char* i = (char*)(destination);
	char* j = (char*)(source);
	while (num--) {
		*i = *j;
		i++, j++;
	}
	return destination;
}
