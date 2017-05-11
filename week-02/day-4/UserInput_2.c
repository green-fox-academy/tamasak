#include <stdio.h>

int main() {
    char buffer[255];   // Buffer variable for user input

    //TODO:
    // Get the user's name with gets

    printf("What is your name?\n");
    gets(buffer);


    //TODO:
    // Print it out with puts

    puts(buffer);

    //TODO:
    // Get the user's pet name with getch

    char pet[255];
    printf("What is pets name?\n");
    gets(pet);


    //TODO:
    // Print it out

    puts(pet);

    return 0;
}
