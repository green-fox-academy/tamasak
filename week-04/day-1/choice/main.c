//make it work
#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
    printf("- for it's memory address please press 1\n");
    printf("- for it's current value please press 2\n");
    printf("- to double it's value please press 3\n");

    int number = 20;
    int input;
    scanf("%d",&input);

    switch (input) {
    case 1:
        printf("%d\n", &number);
        break;
    case 2:
        printf("%d\n", number);
        break;
    case 3:
        number *= 2;
        printf("%d\n", number);
        break;
    default:
        printf("Invalid input\n");
        break;
    }
    return 0;
}
