#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main() {

    int count;
    int* pointer = NULL;

    printf("Type in the count number!\n");
    scanf("%d",&count);
    pointer = calloc(count,sizeof(int));

    for (int i=0; i<count; i++) {
        printf("Give me the %d. number\n",(i+1));
        scanf("%d",&pointer[i]);
    }
    int osszeg;
    for (int j=0; j<count; j++) {

        osszeg += pointer[j];
    }
    float atlag = (float)osszeg/count;
    printf("The average number is: %f.\n",atlag);

    free(pointer);

  return 0;
}
