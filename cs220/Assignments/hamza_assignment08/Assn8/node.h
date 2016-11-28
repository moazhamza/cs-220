#ifndef node_h
#define node_h

#include <stdio.h>

struct _Node{
    struct _Node *next;
    struct _Node *prev;
};

typedef struct _Node Node;

#endif /* node_h */
