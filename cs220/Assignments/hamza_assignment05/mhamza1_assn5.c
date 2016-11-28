#include <stdio.h>
struct _Node{
    union{
        int n;
        char c;
    } val;
    void *ptr;      /* ptr points to the ptr variable in
                     the next node and NOT the beginning of the Node */
    int var;
};
typedef struct _Node Node;

Node *my_reverse(Node *head){
    Node *currentNode = head;
    Node *prevNode = NULL;
    Node *nextNode;
    while(currentNode->ptr){
            nextNode = (Node *)(currentNode->ptr -8);
	    if(!prevNode) currentNode->ptr = NULL;
	    else currentNode->ptr = &(prevNode->ptr);
            prevNode  = currentNode;
            currentNode = nextNode;
    }
	if(prevNode) currentNode->ptr = &(prevNode->ptr);
	else currentNode->ptr = NULL;
    return currentNode;
}


