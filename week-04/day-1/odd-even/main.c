#include <stdio.h>
#include <stdlib.h>

/*
Write a program that reads a number form the standard input,
than prints "Odd" if the number is odd, or "Even" it it is even.
*/

int main()
{
    int x;
    scanf("%d",&x);
    //printf("%d\n",x);
    int a = (x / 2);
    //printf("%d\n",a);
    if (a*2 == x) {
        printf("Even");
    }else {
        printf("Odd");
    }

    return 0;
}
