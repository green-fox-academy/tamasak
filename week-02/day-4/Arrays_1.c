#include <stdio.h>

int main() {
    char my_name_array[] = "My Name";

	//TODO:
    // Print out the array character-by-character
    int i;
    int length = sizeof(my_name_array);

    for (i=0; i< length; i++) {

        printf("%c\n",my_name_array[i]);
    }

    return 0;
}