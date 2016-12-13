
int strcmp(const char* ptr1, const char* ptr2) {
	unsigned char* i = (unsigned char*)(ptr1);
	unsigned char* j = (unsigned char*)(ptr2);
	while (*i && *j && *i == *j)
		i++, j++;

	if (*i == *j)
		return 0;
	return *i < *j ? -1 : 1;
}
