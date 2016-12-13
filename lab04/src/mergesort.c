#include "str.h"
#include "mem.h"
#include "stddef.h"
#include "stdlib.h"

void mergesort(void* base, size_t len, size_t size, int (*cmp)(const void*, const void*)) {
	if (len <= 1)
		return;
	size_t left = len >> 1, right = (len + 1) >> 1;
	mergesort(base, left, size, cmp);
	mergesort(base + size * left, right, size, cmp);

	char* to_merge = malloc(size * len);
	for (size_t i = 0, j = 0; i < left || j < right;) {
		if (i < left && j < right) {
			if (cmp(base + i * size, base + (left + j) * size) < 0) {
				memcpy(to_merge + (i + j) * size, base + i * size, size);
				i++;
			} else {
				memcpy(to_merge + (i + j) * size, base + (left + j) * size, size);
				j++;
			}
		} else {
			if (i < left) {
				memcpy(to_merge + (i + j) * size, base + i * size, size);
				i++;
			} else {
				memcpy(to_merge + (i + j) * size, base + (left + j) * size, size);
				j++;
			}
		}
	}

	memcpy(base, to_merge, size * len);
	free(to_merge);
}
