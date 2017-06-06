#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

void  palindrome(char *input, int length);

int main()
{
	char input[100];
	printf("please enter a word: \n");
	scanf("%s", input);
	palindrome(&input, strlen(input));
	return 0;
}

void  palindrome(char *input, int length)
{
	printf("%s", input);
	char *pointer;
	int i;
	for (i = 0; i <= length; i++) {
		pointer = input[length - i];
		printf("%c", pointer);
	}
}
