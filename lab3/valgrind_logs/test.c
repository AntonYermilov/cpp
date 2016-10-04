#include "stdlib.h"
#include "stdio.h"

int main() {
	int n;
	scanf("%d", &n);

	int* a = malloc(n * sizeof(int));
	if (n & 1) {
		free(a);
		printf("I AM FREE!!!");
	}

	return 0;
}
