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
struct buffer *circular_buffer(int array[], int len)
{
    struct circular_buffer *ptr = (struct circular_buffer*) calloc(len, sizeof(*circular_buffer));
    for (int i = 0; i < len; i++) {
        ptr[i] = &array[i];
    }
    return *ptr;
};

// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and reallocate it's array as well. (copying it's values)
//struct buffer_resize *circular_buffer()

// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer

// TODO:
// Try all the functions in the main function, plase deallocate any buffer and the array inside it after using them

int main()
{

    return 0;
}
