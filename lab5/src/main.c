#include "position.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

int binary_repr(int x) {
	if (x < 0)
		x = x & ((1 << 24) - 1);
	return x;
}

int text_repr(int x) {
	if (x & (1 << 23))
		x = (x ^ (1 << 23)) - (1 << 23);
	return x;
}

void loadtext(const char* from, struct intrusive_list* list) {
	FILE* data = fopen(from, "rt");
	int x, y;
	while (fscanf(data, "%d %d ", &x, &y) == 2) {
		add_position(list, x, y);
	}
	fclose(data);
}

void loadbin(const char* from, struct intrusive_list* list) {
	FILE* data = fopen(from, "rb");
	int x = 0, y = 0;
	while (fread(&x, 3, 1, data) == 1) {
		assert(fread(&y, 3, 1, data) == 1);
		add_position(list, text_repr(x), text_repr(y));
		x = 0, y = 0;
	}
	fclose(data);
}

void savetext(const char* to, struct intrusive_list* list) {
	struct intrusive_node* head = &list->head;
	struct intrusive_node* node = head->next;

	FILE* out = fopen(to, "wt");
	for (; node != head; node = node->next) {
		struct position_node* pnode = get_position(node);
		fprintf(out, "%d %d\n", pnode->x, pnode->y);
	}
	fclose(out);
}

void savebin(const char* to, struct intrusive_list* list) {
	struct intrusive_node* head = &list->head;
	struct intrusive_node* node = head->next;

	FILE* out = fopen(to, "wb");
	for (; node != head; node = node->next) {
		struct position_node* pnode = get_position(node);
		int x = binary_repr(pnode->x), y = binary_repr(pnode->y);
		fwrite(&x, 3, 1, out);
		fwrite(&y, 3, 1, out);
	}
	fclose(out);
}

void print_node(const void* node, const void* fmt) {
	struct position_node* pnode = get_position((struct intrusive_node*)(node));
	printf((char*)(fmt), pnode->x, pnode->y);
}

void count_len(const void* node, const void* cur) {
	(*(int*)(cur))++;
}

void apply(struct intrusive_list* list, void (*op)(const void*, const void*), const void* arg) {
	struct intrusive_node* head = &list->head;
	struct intrusive_node* node = head->next;

	for (; node != head; node = node->next) {
		op((void*)(node), arg);
	}
}

void print(const char* fmt, struct intrusive_list* list) {
	apply(list, print_node, (void*)(fmt));
	printf("\n");
}

void count(struct intrusive_list* list) {
	int len = 0;
	apply(list, count_len, (void*)(&len));
	printf("%d\n", len);
}

int main(int argc, char* argv[]) {

	struct intrusive_list my_list;
	init_list(&my_list);

	if (strcmp(argv[1], "loadtext") == 0) {
		loadtext(argv[2], &my_list);
	} else {
		loadbin(argv[2], &my_list);
	}

	if (strcmp(argv[3], "savetext") == 0) {
		savetext(argv[4], &my_list);
	}

	if (strcmp(argv[3], "savebin") == 0) {
		savebin(argv[4], &my_list);
	}

	if (strcmp(argv[3], "print") == 0) {
		print(argv[4], &my_list);
	}

	if (strcmp(argv[3], "count") == 0) {
		count(&my_list);
	}

	remove_all(&my_list);

    return 0;
}
