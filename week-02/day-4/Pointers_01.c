#include <stdio.h>

int main() {
    int number = 1234;
    //TODO:
    // print the memory address of the variable

    int *poNumber = &number;
    printf("Memory address of number is: %x\n", &poNumber);

    return 0;
}
