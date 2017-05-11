#include <stdio.h>

int main() {
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

	//TODO:
    // Print out the two arrays character-by-character
    int i1;
    int length1 = sizeof(char_array);

    for (i1=0; i1< length1; i1++) {

        printf("%c\n",char_array[i1]);
    }

    int i2;
    int length2 = sizeof(char_array_the_same);

    for (i2=0; i2< length2; i2++) {

        printf("%c\n",char_array_the_same[i2]);
    }

	//TODO:
    // What is the difference between the arrays?
    
    //The char_array_the_same array contains a \0 at the end. (1 character longer)

    return 0;
}
