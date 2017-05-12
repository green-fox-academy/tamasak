#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void anagram (){

    char word1[100];
    char word2[100];

    printf("Write a word!\n");
    gets(word1);

    printf("Write another word!\n");
    gets(word2);


    int lengthWord1 = strlen (word1);
    int lengthWord2 = strlen (word2);

    if (lengthWord1 != lengthWord2){

        printf("Nope!\n");
        }

    else {
        int i, j, tmp;
        for(i= lengthWord1-1; i>0; i--)
            for(j=0; j<i; j++)
                if(word1[j] > word1[j+1])
                {
                    tmp = word1[j];
                    word1[j] = word1[j+1];
                    word1[j+1] = tmp;
                }

        for(i= lengthWord2-1; i>0; i--)
            for(j=0; j<i; j++)
                if(word2[j] > word2[j+1])
                {
                    tmp = word2[j];
                    word2[j] = word2[j+1];
                    word2[j+1] = tmp;
                }

        int ret = strcmp ( word1, word2 );

        if (ret < 0) {
            printf("Nope!");

        }
        else if (ret > 0) {
            printf("Nope!");
        }
        else {
            printf("I am an anagram");
        }


    }

    return;
}

int main() {

    
    anagram();


    return 0;
}