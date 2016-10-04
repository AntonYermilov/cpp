#include "stdbool.h"
#include "string.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct position_node {
	int x, y;
	struct intrusive_node node;
};

void remove_position(struct intrusive_list * my_list, int x, int y) { // removes all (x, y) pairs
	struct intrusive_node * cur = my_list->head;
	while (cur != NULL) {
		struct position_node * point = container_of(cur, struct position_node, node);
		if (point->x == x && point->y == y) {
			cur = remove_node(my_list, cur);
			free(point);
		} else {
			cur = cur->next;
		}
	}
}

void add_position(struct intrusive_list * my_list, int x, int y) {
	struct position_node * point = malloc(sizeof(struct position_node));
	point->x = x;
	point->y = y;
	add_node(my_list, &point->node);
}

void show_all_positions(struct intrusive_list * my_list) {
	struct intrusive_node * cur = my_list->head;
	while (cur != NULL) {
		struct position_node * point = container_of(cur, struct position_node, node);
		printf("(%d %d)", point->x, point->y);
		if (cur->next != NULL)
			printf(" ");
		cur = cur->next;
	}
	printf("\n");
}

void remove_all_positions(struct intrusive_list * my_list) {
	struct intrusive_node * cur = my_list->head;
	while (cur != NULL) {
		struct position_node * point = container_of(cur, struct position_node, node);
		cur = remove_node(my_list, cur);
		free(point);
	}
}

int main() {
	struct intrusive_list my_list;
	init_list(&my_list);

	char query[256];
	int x, y;

	while (true) {
		scanf("%s", query);
		if (strcmp(query, "add") == 0) {
			scanf("%d%d", &x, &y);
			add_position(&my_list, x, y);
			continue;
		}
		if (strcmp(query, "rm") == 0) {
			scanf("%d%d", &x, &y);
			remove_position(&my_list, x, y);
			continue;
		}
		if (strcmp(query, "print") == 0) {
			show_all_positions(&my_list);
			continue;
		}
		if (strcmp(query, "rma") == 0) {
			remove_all_positions(&my_list);
			continue;
		}
		if (strcmp(query, "len") == 0) {
			printf("%d\n", get_length(&my_list));
			continue;
		}
		if (strcmp(query, "exit") == 0) {
			break;
		}
		printf("Unknown command\n");
	}
	
	remove_all_positions(&my_list);

    return 0;
}
