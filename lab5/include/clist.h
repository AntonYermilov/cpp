#ifndef _CLIST_H
#define _CLIST_H

struct intrusive_node {
    struct intrusive_node * next;
    struct intrusive_node * prev;
};

struct intrusive_list {
    struct intrusive_node head;
};

void init_list(struct intrusive_list *);

void add_node(struct intrusive_list *, struct intrusive_node *);

// contract: node != &list->head
void remove_node(struct intrusive_list *, struct intrusive_node *);

int get_length(struct intrusive_list *);

#endif
