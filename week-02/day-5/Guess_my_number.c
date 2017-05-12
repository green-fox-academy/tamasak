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
    for (life; life > 0; life--) {
        int guess;
        scanf("%u", &guess);


        if (guess == number){

            printf("Right!\n");
            life = -1;
        }
        else if (guess > number){
            if (life==1){
                printf("You have lost!\n");
            }

            else {
            printf("Too high! You have %d lifes left\n", (life-1));
            }

        }
        else if (guess < number){
            if (life==1){
                printf("You have lost!\n");
            }
            else{
                printf("Too low! You have %d lifes left\n", (life-1));
            }

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
