#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */
int *array_resize(int *array, int size, int size_new)
{
    int *ptr = NULL;
    ptr = calloc(size_new, sizeof(int));
    if (size < size_new) {
        for (int i = 0; i < size; i++)
            ptr[i] = array[i];
    } else {
        for (int i = 0; i < size_new; i++)
            ptr[i] = array[i];
    }
    for (int i = 0; i < size_new; i++)
        printf("%d\n", ptr[i]);
    return *ptr;
}

int main()
{
    int array[] = {0, 3, 6, 8};
    array_resize(array, 4, 5);

    return 0;
}
