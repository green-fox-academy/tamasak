#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Add two numbers using pointers
*/


int main()
{

    int a  = 20;
    int b = 17;

    int *c = &a;
    int *d = &b;

    int e = *c + *d;
    printf("%d", e);

    return 0;
}
