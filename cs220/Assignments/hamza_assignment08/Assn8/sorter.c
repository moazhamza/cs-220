#include "node.h"
#include "sorter.h"

Node *get_largest_element(Node *head){
    Node *current = head;
    Node *largestElement = head;
    while(current){
        if (current > largestElement) largestElement = current;
        current = current->next;
    }
    return largestElement;
}
Node *get_head(Node *aNode){
    while(aNode->prev) aNode = aNode->prev;
    return aNode;
}

Node *sort_node(Node *head){
    Node *largestElement = get_largest_element(head);
    /* Remove links from other members of list while keeping a member of the new list */
    Node *nodeInRemainingList = NULL;
    if(largestElement->prev) {
        nodeInRemainingList = largestElement->prev;
        largestElement->prev->next = largestElement->next;
    }
    if(largestElement->next){
        if(!nodeInRemainingList) nodeInRemainingList = largestElement->next;
        largestElement->next->prev = largestElement->prev;
    }
    if(!largestElement->next && !largestElement->prev) nodeInRemainingList = NULL;

    /* Start new list (OL = Ordered List) */
    Node *headOL = largestElement, *currentOL = largestElement, *prevOL = NULL, *nextOL = NULL;
    currentOL->next = nextOL;
    currentOL->prev = prevOL;
    
    while(nodeInRemainingList){
        head = get_head(nodeInRemainingList);
        largestElement = get_largest_element(head);
        
        nodeInRemainingList = NULL;
        
        if(largestElement->prev) {
            nodeInRemainingList = largestElement->prev;
            largestElement->prev->next = largestElement->next;
        }
        if(largestElement->next){
            if(!nodeInRemainingList) nodeInRemainingList = largestElement->next;
            largestElement->next->prev = largestElement->prev;
        }
        if(!largestElement->next && !largestElement->prev) nodeInRemainingList = NULL;
        
        largestElement->next = NULL;
        largestElement->prev = NULL;
        
        currentOL->next = largestElement;
        largestElement->prev = currentOL;
        currentOL = largestElement;
    }
    
    
    
    return headOL;
}
