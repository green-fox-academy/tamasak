#include <stdio.h>

/* Write a non void function which has a paramters (let's say for example x).
The funtion than returns the "xth" fibonaci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/

int fibonacci (int x);

int main(){

    printf("%d",fibonacci(9));

    return 0;
}

int fibonacci(int x) {

    int a;
    int b = 1;
    int c;

    for (a = 0; x > 1; x--) {
        c = a + b;
        a = b;
        b = c;

    }

    return c;

}
