#ifndef _MERGESORT_H
#define _MERGESORT_H
#include "stddef.h"
	void mergesort(void * base, size_t num, size_t size, int (*cmp)(const void*, const void*));
#endif
