#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

void average_number()
{
    printf("count\n");
    int count;
    scanf("%d", &count);

    int *pointer = calloc(count,sizeof(int));
    for (int i = 0; i < count; i++) {
        printf("write a number\n");
        scanf("%d", &pointer[i]);
    }
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += pointer[i];
    }
    float aver = (float)sum / count;
    printf("%f\n", aver);
    free(pointer);
}

int main()
{
    average_number();
    return 0;
}
