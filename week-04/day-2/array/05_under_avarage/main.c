#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the avarage of the elements.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how much elements are under the avarage, and returns with that.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.

double average_of_elements(double *array, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
        sum += array[i];
    double average = sum / length;
    //printf("%f\n", sum);
    //printf("%f\n", average);
    return average;
}

int number_of_elements(double *array, int length)
{
    return length;
}

double under_average(double *array, int length)
{
    int j = 0;
    double array_new[length];
    for (int i = 0; i < length; i++) {
        if (array[i] < average_of_elements(array, length)){
            array_new[j] = array[i];
            j++;
        }
    }
    return array_new;
}

int main()
{
    double array[] = {1.2, 3.14, 1.41, 0.707, 1.73};
    int length;
    length = sizeof(array) / sizeof(array[0]);

    printf("The average of the elements is: %f\n", average_of_elements(array, length));
    printf("The number of the elements are: %d\n", number_of_elements(array, length));
    //printf("The 2. elements under average is %f\n", under_average(array, length));

    return 0;
}
