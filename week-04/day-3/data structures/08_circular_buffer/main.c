#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The lenght of the buffer
struct circular_buffer
{
    int *head;
    int *tail;
    int *readptr;
    int *writeptr;
    int length;
};

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array
struct circular_buffer *new_circular_buffer(int *array, int len)
{
    int *buffer = (int*) calloc(len, sizeof(struct circular_buffer));
    memcpy(buffer, array, len*sizeof(int));
    struct circular_buffer *ret_array = malloc(sizeof(struct circular_buffer));
    ret_array->head = buffer;
    ret_array->readptr = buffer;
    ret_array->writeptr = buffer;
    ret_array->tail = &buffer[len - 1];
    return ret_array;
};

// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and reallocate it's array as well. (copying it's values)
void buffer_resize(struct circular_buffer *array, int len)
{
    int elem_read = (((int)(array->readptr) - (int)(array->head)) / sizeof(int) - 1);
    int elem_write = (((int)(array->writeptr) - (int)(array->head)) / sizeof(int) - 1);

    array->head = realloc(array->head, (len * sizeof(int)));
    array->tail = &(array->head[len - 1]);
    array->readptr = &(array->head[elem_read]);
    array->writeptr = &(array->head[elem_write]);
}

// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer
int even_number(struct circular_buffer *array, int len)
{
    int *buffer = (int*) calloc(len, sizeof(int));
    int j = 0;
    for (int *i = array->head; i <= array->tail; i++) {
        if (*i % 2 == 0){
            buffer[j] = *i;
            j++;
        }
    }
    int *short_buffer = (int*) realloc(buffer, j * sizeof(int));
    struct circular_buffer *ev_num_buffer = new_circular_buffer(short_buffer, j);

    free(short_buffer);

    return ev_num_buffer;
};

// TODO:
// Try all the functions in the main function, plase deallocate any buffer and the array inside it after using them

int main()
{
    struct circular_buffer *buffer;
    int array[5] = {0,1,2,3,4};
    buffer = new_circular_buffer(array, 5);
    for (int *i = buffer->head; i <= buffer->tail; i++) {
        printf("%d\t", *i);
    }
    printf("\n\n");
    buffer_resize(buffer, 4);
    for (int *i = buffer->head; i <= buffer->tail; i++) {
        printf("%d\t", *i);
    }
    printf("\n\n");
    struct circular_buffer *even = even_number(buffer, 4);
    for (int *i = even->head; i <= even->tail; i++) {
        printf("%d\t", *i);
    }

    free(buffer);

    return 0;
}
