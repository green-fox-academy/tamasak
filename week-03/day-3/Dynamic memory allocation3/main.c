#include <stdio.h>
#include <stdlib.h>

/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on it's paramters.
 * It should take 3 paramters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */

int* Range(int from,int to,int step){
    int* pointer = NULL;
    int j = 0;
    /*for (int i = from; i < to; i + step){
        j++;
    }*/
    j = (to - from)/step;

    pointer = calloc(j,sizeof(int));

    for (int i = 0; i <= j; i++) {
        pointer[i] = (from + (i * step));
        printf("%d\t", pointer[i]);

    }
    return *pointer;
    free(pointer);
}

int main() {

    int from = 4;
    int to = 13;
    int step = 3;

    Range(from, to, step);
    return 0;
}
