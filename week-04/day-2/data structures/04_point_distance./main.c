#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} point_t;

// TODO:
// Create a function the constructs a Point (returns a pointer to a new point)
// It should take it's x and y coordinate as parameter
struct point_t *construct (int x, int y)
{
    point_t *point;
    point = (point_t*) malloc(sizeof(point_t));
    point->x = x;
    point->y = y;
    return point;
}


// TODO:
// Create a function that takes 2 Points as a pointer and returns the distance between them
float distance (point_t *pt1, point_t *pt2)
{
    point_t *point;
    point = (point_t*) malloc(sizeof(point_t));
    point->x = pt1->x - pt2->x;
    point->y = pt1->y - pt2->y;

    float dist = sqrt(point->x * point->x + point->y * point->y);
    return dist;
}

int main()
{
    printf("%f\n", distance(construct(2,4), construct(5,8)));
    return 0;
}
