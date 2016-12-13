#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "comparator.h"
#include "mergesort.h"
#include "str.h"

int main(int argc, char* argv[]) {

	void* array;

	if (strcmp(argv[1], "int") == 0) {
		array = malloc((argc - 2) * sizeof(int));
		for (int i = 2; i < argc; i++)
			*(int*)(array + (i - 2) * sizeof(int)) = atoi(argv[i]);
		mergesort(array, argc - 2, sizeof(int), int_cmp);
		
		for (int i = 0; i < argc - 2; i++)
			printf("%d ", *(int*)(array + i * sizeof(int)));
		printf("\n");
	}

	if (strcmp(argv[1], "char") == 0) {
		array = malloc((argc - 2) * sizeof(char));
		for (int i = 2; i < argc; i++)
			*(char*)(array + (i - 2) * sizeof(char)) = argv[i][0];
		mergesort(array, argc - 2, sizeof(char), char_cmp);

		for (int i = 0; i < argc - 2; i++)
			printf("%c ", *(char*)(array + i * sizeof(char)));
		printf("\n");
	}

	if (strcmp(argv[1], "str") == 0) {
		array = malloc((argc - 2) * sizeof(char*));
		for (int i = 2; i < argc; i++)
			*(char**)(array + (i - 2) * sizeof(char*)) = argv[i];
		mergesort(array, argc - 2, sizeof(char*), str_cmp);

		for (int i = 0; i < argc - 2; i++)
			printf("%s ", *(char**)(array + i * sizeof(char*)));
		printf("\n");
	}

	free(array);

	return 0;
}
