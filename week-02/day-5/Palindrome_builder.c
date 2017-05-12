#include <stdio.h>
#include <string.h>

void createPalindrome (char *a){

    char word[100];
    char palindrome[100];

    printf("Write a word!\n");
    gets(word);


    int lengthWord = strlen (word);
    int i;
    int j;


    for (i = 0; i < lengthWord; i++) {

            palindrome[i] = word[i];
    }
    printf("%s",palindrome);

    for (j=0; j < lengthWord; j++) {

            palindrome[j] = word [(lengthWord-j-1)];
    }

    printf("%s\n",palindrome);
    //printf("%d\n",lengthWord);

    return;
}

int main() {

    char a[240];
    createPalindrome(a);


    return 0;
}
