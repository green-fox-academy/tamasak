#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    float Pi = 3.14;
    char letter = 't';

    int *ptr_number = &number;
    float *ptr_Pi = &Pi;
    char *ptr_letter = &letter;

    printf("%d\t", ptr_number);
    printf("%d\t", ptr_Pi);
    printf("%d\n", ptr_letter);

    printf("%d\t", &number);
    printf("%d\t", &Pi);
    printf("%d\n", &letter);

    printf("%d\t", *ptr_number);
    printf("%f\t", *ptr_Pi);
    printf("%s\n", ptr_letter);

    printf("%d\t", number);
    printf("%f\t", Pi);
    printf("%c\n", letter);



    return 0;
}
