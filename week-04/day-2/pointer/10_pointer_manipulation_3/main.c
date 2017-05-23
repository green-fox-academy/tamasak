#include <stdio.h>

int main()
{
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.

    int tmp = *hight_number_pointer;
    int tmp2 = *low_number_pointer;
    //*low_number_pointer = *hight_number_pointer;
    *low_number_pointer = tmp;
    *hight_number_pointer = tmp2;

    printf("%d, %d", low_number, high_number);

    return 0;
}
