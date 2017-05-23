#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function which receives a string as parameter, and returns
// the numbers of characters in the string.
// Don't use the strlen() function!

int number_of_characters(char *string)
{
    int length = 0;
    for (int i = 0; (string[length] != '\0'); i++)
        length++;
    return length;
}

int main()
{
    char string[] = "abcdefghijk";
    printf("%d\n", number_of_characters(string));
    return 0;
}
