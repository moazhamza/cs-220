#ifndef Point_h
#define Point_h

#include <stdio.h>


typedef struct Pt{
    float x;
    float y;
    float z;
    struct Pt *nextPt;
} Point;


/* 
 * This function will return 1 if the point passed to it is in a list where there is a loop. A loop occurs when
 * a point is repeated in the list. 
 */
int contains_loop(Point *ptr);
/*
 * This function takes in a list of points and an offset (or an origin), and returns the first element of the 
 * new altered list.
 */
Point *transform_points(Point *point, Point *origin);


#endif /* Point_h */
