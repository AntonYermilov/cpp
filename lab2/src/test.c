#include "stdio.h"
#include "test_str.h"

int main() {
	test_strlen();
	test_strcmp();
	test_strcpy();
	test_strcat();

	printf("OK\n");

	return 0;
}
