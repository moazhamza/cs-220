#include <stdio.h>
#include <stdlib.h>
#include "point.h"


int contains_loop(Point *ptr){
    if(ptr == NULL) return 0;
    if(ptr->nextPt !=  NULL){
        Point *nextPtr = ptr->nextPt;
        while (nextPtr->nextPt != NULL && ptr->nextPt != NULL){
            if(ptr == nextPtr) return 1;
            else{
                nextPtr = nextPtr->nextPt;
                if(nextPtr->nextPt == NULL) return 0;
                else{
                    nextPtr = nextPtr->nextPt;
                    ptr = ptr->nextPt;
                    continue;
                }
            }
        }
    }
    return 0;
}

Point *transform_points(Point *point, Point *origin){
    Point *newPointPtr = (Point *)malloc(sizeof(Point));
    Point *saveFirstPt = newPointPtr;
    if(point == NULL) return NULL;
    while(point->nextPt != NULL){
        newPointPtr->x = origin->x + point->x;
        newPointPtr->y = origin->y + point->y;
        newPointPtr->z = origin->z + point->z;
        newPointPtr->nextPt = (Point *)malloc(sizeof(Point));
        point = point->nextPt;
        newPointPtr = newPointPtr->nextPt;
    }
    newPointPtr->x = origin->x + point->x;
    newPointPtr->y = origin->y + point->y;
    newPointPtr->z = origin->z + point->z;
    newPointPtr->nextPt = NULL;
    return saveFirstPt;
}
