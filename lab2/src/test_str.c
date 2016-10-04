#include "assert.h"
#include "str.h"
#include "stdio.h"

void test_strlen() {
	assert(strlen("abc") == 3);
	assert(strlen("") == 0);

	printf("%d\n", strlen(NULL));
}

void test_strcmp() {
	assert(strcmp("abc", "abc") == 0);
	assert(strcmp("ab", "abc") < 0);
	assert(strcmp("abc", "ab") > 0);
	assert(strcmp("abc", "abd") < 0);
	assert(strcmp("abd", "abc") > 0);
	assert(strcmp("", "abc") < 0);
	assert(strcmp("", "") == 0);

	char s1[1], s2[1];
	s1[0] = 129, s2[0] = 127;
	assert(strcmp(s1, s2) > 0);

	//strcmp(NULL, "abc");
}


void test_strcpy() {
	char a[10] = "ab";
	char b[10] = "cd";
	char res1[10] = "abcd";
	char res2[10] = "abd";
	char res3[10] = "cd";
	
	strcpy(a + 2, b);
	for (int i = 0; i < 4; i++)
		assert(a[i] == res1[i]);
	assert(a[4] == 0);

	strcpy(a + 2, b + 1);
	for (int i = 0; i < 3; i++)
		assert(a[i] == res2[i]);
	assert(a[3] == 0);

	strcpy(a, b);
	for (int i = 0; i < 2; i++)
		assert(a[i] == res3[i]);
	assert(a[2] == 0);
}

void test_strcat() {
	char a[10] = "abc";
	char b[10] = "def";
	char res[10] = "abcdef";
	
	strcat(a, b);
	for (int i = 0; i < 6; i++)
		assert(a[i] == res[i]);
	assert(a[6] == 0);
}
