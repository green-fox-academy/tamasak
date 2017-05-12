#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void guessNumber(){

    int maxnum;
    printf("Tell me the maximum number!\n");
    scanf("%u",&maxnum);

    int number;
    srand (time(NULL));
    number = (rand() % maxnum)+1;
    //printf("%d\n", number);

    int life = 5;
    printf("Guess a number between 1 and %d. You have %d lifes.\n", maxnum, life);
    while (life >= 0) {
        int guess;
        scanf("%u", &guess);

        if (life==0){
            printf("You have lost!\n");
            life--;
        }
        else if (guess == number){
            printf("Right!\n");
            life = 0;
        }
        else if (guess > number){
            printf("Too high! You have %d lifes left\n", life);
            life--;
        }
        else if (guess < number){
            printf("Too low! You have %d lifes left\n", life);
            life--;
        }
        else {

        }

    }


    return;
}

int main() {

    guessNumber();


    return 0;
}