#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "position.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct position_node * get_position(struct intrusive_node * node) {
    return container_of(node, struct position_node, node);
}

int match_position(struct intrusive_node * node, int x, int y) {
    struct position_node * pnode = get_position(node);
    return pnode->x == x && pnode->y == y;
}

void delete_position(struct intrusive_list * list, struct intrusive_node * node) {
    remove_node(list, node);
    free(get_position(node));
}

void remove_position(struct intrusive_list * list, int x, int y) {
    struct intrusive_node * head = &list->head;
    struct intrusive_node * node = head->next;

    while (node != head) {
        struct intrusive_node * next = node->next;

        if (match_position(node, x, y))
            delete_position(list, node);

        node = next;
    }
}

void add_position(struct intrusive_list * list, int x, int y) {
    struct position_node * pnode = malloc(sizeof(struct position_node));
    pnode->x = x;
    pnode->y = y;

    add_node(list, &pnode->node);
}

// should be called delete_all
void remove_all(struct intrusive_list * list) {
    while (list->head.next != &list->head)
        delete_position(list, list->head.next);
}
