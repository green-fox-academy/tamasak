#include <stdio.h>

int main() {
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};

	//TODO:
    // Print out the content of the arrays

    int i1;
    int length1 = sizeof(int_array)/sizeof(int_array[0]);

    for (i1=0; i1< length1; i1++) {

        printf("%d\n",int_array[i1]);
    }

    int i2;
    int length2 = sizeof(float_array)/sizeof(float_array[0]);

    for (i2=0; i2< length1; i2++) {

        printf("%f\n",float_array[i2]);
    }

    return 0;
}
