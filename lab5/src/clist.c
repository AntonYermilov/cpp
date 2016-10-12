#include "clist.h"

void init_list(struct intrusive_list * list) {
    struct intrusive_node * head = &list->head;
    head->next = head;
    head->prev = head;
}

void add_node(struct intrusive_list * list, struct intrusive_node * node) {
    struct intrusive_node * last = list->head.prev;
    struct intrusive_node * head = &list->head;

    node->next = head;
    node->prev = last;

    head->prev = node;
    last->next = node;
}

// contract: node != &list->head
void remove_node(struct intrusive_list * list, struct intrusive_node * node) {
    struct intrusive_node * prev = node->prev;
    struct intrusive_node * next = node->next;

    prev->next = next;
    next->prev = prev;
}

int get_length(struct intrusive_list * list) {
    int length = 0;
    struct intrusive_node * head = &list->head;
    struct intrusive_node * node = head->next;

    for (; node != head; node = node->next)
        ++length;

    return length;
}
