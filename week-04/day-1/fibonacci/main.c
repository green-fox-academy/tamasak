#include <stdio.h>
#include <stdlib.h>

/* Write a function which is called "get_fibonacci_number". It returns the "N"th
 * Fibonacci number, where "N" is received as a paramter.
 * For example:
 *  - get_fibonacci_number(1) returns 0
 *  - get_fibonacci_number(2) returns 1
 *  - get_fibonacci_number(3) returns 1
 *  - get_fibonacci_number(4) returns 2
 *  - get_fibonacci_number(5) returns 3
 *  - get_fibonacci_number(6) returns 5
 *
 *  If the function gets invalid parameter it returns -1.
 */

/*
Using that function create a program, which gets a number from the user, and
prints out the "N"th Fibonacci number, where "N" is the user given number.
Alert the user if he/she entered invalid value.
*/

int main()
{
    printf("Type in a number.\n");
    int number;
    scanf("%d", &number);

    int a = 0;
    int b = 0;
    int c = 1;
    int i;

    if (number == 1) {
        printf("The %d. fibonacci number is 0.\n", number);
    } else if (number == 2) {
        printf("The %d. fibonacci number is 1.\n", number);
    } else if (number > 2) {
        for (i = 0; i < (number-2); i++) {
            a = b;
            b = c;
            c = a + b;
            if ( i == ( number -3 )) {
                printf("The %d. fibonacci number is %d.\n", number, c);
            }
        }
    } else {
        printf("You gave me an invalid value.\n");
        return -1;
    }
}
