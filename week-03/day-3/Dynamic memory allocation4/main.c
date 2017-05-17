#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */
int* Resize (int* array, int size, int new_size);

int main() {
    int size = 6;
    int* array = (int*)calloc(size, sizeof(int));
    array[6] = {1,2,3,4,5,6};
    int new_size = 9;
    Resize(array,size,new_size);
    free(array);

    return 0;
}

int* Resize (int* array, int size, int new_size) {
    int* new_array = (int*)calloc(new_size, sizeof(int));
    int i;
    for (i = 0; i < size; i++) {
        new_array[i] = array[i];
    }
    for (i; i < new_size; i++) {
        new_array[i] = 0;
    }

    for (int i = 0; i < new_size; i++) {
        printf("%d\n", new_array[i]);
    }

}
