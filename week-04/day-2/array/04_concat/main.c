#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/

int main()
{
    char dest_array[] = "dest";
    char source_array[] = "source";
    char array_new[(sizeof(dest_array) + sizeof(source_array))];

    for (int i = 0; i < sizeof(dest_array); i++)
            array_new[i] = dest_array[i];
    for (int i = sizeof(dest_array); i < (sizeof(dest_array) + sizeof(source_array)); i++) {
            array_new[i] = source_array[(i - sizeof(dest_array))];
    }

    for (int i = 0; i < sizeof(array_new); i++)
        printf("%c",array_new[i]);
    printf("\n");

    return 0;
}
