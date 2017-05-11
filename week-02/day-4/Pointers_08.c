#include <stdio.h>

int main() {
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.

    int a = *hight_number_pointer;
    int b = *low_number_pointer;

    (*hight_number_pointer) = b;
    (*low_number_pointer) = a;

    printf("low number: %d\n", low_number);
    printf("high number: %d\n", high_number);

    return 0;
}
