#ifndef driver_h
#define driver_h
#include "node.h"

Node *malloc_node();
Node *create_heap_list(int n, Node *prev);
void print_node_addresses_forwards(Node *head);
void print_node_addresses_backwards(Node *tail);
Node *tail_of_node_list(Node *head);
unsigned int check_if_list_in_order(Node *head);


#endif /* driver_h */
