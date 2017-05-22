#include <stdio.h>
#include <stdlib.h>

/*
Create a program which ask for a name and an age.
From the age it tells the user when he or she will be 100 years old.
You should only take care of the years (don't bother with the months or days).
*/

int main()
{
    int age;
    char name[200];

    printf("What is your name?\n");
    scanf("%s",name);
    printf("How old are you?\n");
    scanf("%d",&age);

    int x = 100 - age + 2017;
    if (age > 100) {
        printf("You are already older than 100 years.\n");
    } else {
        printf("You will be 100 year old in %d.\n", x);
    }

    return 0;
}
