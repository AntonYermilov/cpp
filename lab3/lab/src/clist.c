#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "clist.h"

void init_list(struct intrusive_list * my_list) {
	my_list->head = NULL;
}

void add_node(struct intrusive_list * my_list, struct intrusive_node * node) {
	if (my_list->head == NULL) {
		my_list->head = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		node->next = my_list->head;
		my_list->head->prev = node;
		node->prev = NULL;
		my_list->head = node;
	}
}

struct intrusive_node * remove_node(struct intrusive_list * my_list, struct intrusive_node * node) {
	struct intrusive_node * next_node = node->next;
	if (node == my_list->head) {
		my_list->head = node->next;
		if (my_list->head != NULL)
			my_list->head->prev = NULL;
	} else {
		if (node->prev != NULL)
			node->prev->next = node->next;
		if (node->next != NULL)
			node->next->prev = node->prev;
	}
	return next_node;
}

int get_length(struct intrusive_list * my_list) {
	int len = 0;
	struct intrusive_node * cur = my_list->head;
	while (cur != NULL) {
		len++;
		cur = cur->next;
	}
	return len;
}
