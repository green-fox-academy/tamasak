#include <stdio.h>
#include <stdlib.h>

/*
Create a program which writes down the following sentence 100 times:
"I won't cheat on the test!"
Do it with:
    - for loop
    - while loop
    - do while loop
Also create a funtion which does the same.
*/

int main()
{
    for (int i = 0; i < 100; i++) {
        printf("I won't cheat on the test!\n");
    }

    int j = 0;
    while (j < 100) {
       printf("I won't cheat on the test!\n");
       j++;
    }

    int k = 0;
    do {
        printf("I won't cheat on the test!\n");
        k++;
    } while (k < 100);

    return 0;
}
