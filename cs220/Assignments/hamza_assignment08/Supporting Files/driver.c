#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include <sorter.c>

static Node arrNodes[100] = {0};

/*Returns a node address on the heap*/
Node *malloc_node(){
    return (Node *)malloc(sizeof(Node));
}


/*Returns a Node * head which contains a list of n nodes, connecting from Node *prev. If clean list is desired, use NULL as prev*/
Node *create_heap_list(int n, Node *prev){
    Node *firstHead = malloc_node();
    Node *head = firstHead;
    int i;
    for (i = 0; i < n-1; i++) {
        Node *next;
        next = malloc_node();
        head->next = next;
        head->prev = prev;
        prev = head;
        head = next;
    }
    head->prev = prev;
    return firstHead;
}

void print_node_addresses_forwards(Node *head){
    while(head){
        if(head->next) printf("%p->",head);
        else printf("%p\n", head);
        head = head->next;
    }
}
void print_node_addresses_backwards(Node *tail){
    while(tail){
        if(tail->prev) printf("%p->",tail);
        else printf("%p\n", tail);
        tail = tail->prev;
    }
}
Node *tail_of_node_list(Node *head){
    while(head->next){
        head = head->next;
    }
    return head;
}

/*Returns 1 if list in order, 0 if list not in order. */
unsigned int check_if_list_in_order(Node *head){
    unsigned int i = 1;
    Node *current = head;
    while(current->next && i != 0){
        if(!(current > current->next)) i = 0;
        current = current->next;
    }
    return i;
}

int main(){
    Node *head = create_heap_list(1, NULL);
    Node *current = head;
    Node bigNode;
    current->next = &bigNode;
    bigNode.prev = current;
    current = current->next;
    
    int j = 0;
    int length_of_list = 20;
    srandom((unsigned int)time(NULL));
    for (j = 0; j < length_of_list; j++){
        int r = rand() % 2;
        if (r == 0){
            current->next = &arrNodes[j];
            arrNodes[j].prev = current;
            current = current->next;
        }
        if (r == 1){
            current->next = create_heap_list(1, current);
            current = current->next;
        }
    }
    
    
    printf("Original List: ");
    print_node_addresses_forwards(head);
    printf("%u\n", check_if_list_in_order(head));

    

    Node *orderedListHead = sort_node(head);
    printf("Ordered List: ");
    print_node_addresses_forwards(orderedListHead);
    printf("%u\n", check_if_list_in_order(orderedListHead));

    
}
