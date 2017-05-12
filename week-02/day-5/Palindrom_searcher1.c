#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void palindromSearcher(){

    char word1[100];
    char palind[100];

    printf("Type in something!\n");
    gets(word1);

    int lengthWord1 = strlen (word1);
    for (int i = 0; i < (lengthWord1-2); i++){
        if (word1 [i] == word1 [i+2]){
            for (int j = 0; j<3; j++){
                palind[j] = word1 [(i+j)];
            }
            printf("%s,",palind);
        }

    }

    for (int i = 0; i < (lengthWord1-3); i++){
        if ((word1[i] == word1[i+3]) && (word1[i+1] == word1[i+2])){
            for (int j = 0; j<4; j++){
                palind[j] = word1 [(i+j)];
            }
            printf("%s,",palind);
        }

    }


    return;
}

int main() {

    palindromSearcher();


    return 0;
}
