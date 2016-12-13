#ifndef _POSITION_H
#define _POSITION_H

#include "clist.h"

struct position_node {
    int x;
    int y;
    struct intrusive_node node;
};

struct position_node * get_position(struct intrusive_node *);

void remove_position(struct intrusive_list *, int, int);

void add_position(struct intrusive_list *, int, int);

void show_all_positions(struct intrusive_list *);

void remove_all(struct intrusive_list *);

#endif
