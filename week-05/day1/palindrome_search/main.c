#include <stdio.h>
#include <string.h>

int is_palindrom(char *a);
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int main()
{
	char original_string[100], current_string[100];
	printf("Enter the string to check if it is a palindrome\n");
	gets(original_string);

	int i, j;
	for (i = 0; i < strlen(original_string) - 1; i++) {
		for (j = 2; i + j < strlen(original_string) + 1; j++) {
			strncpy(current_string, original_string + i, j + 1);
			current_string[j] = 0;
			if (is_palindrom(current_string))
				printf("%s\n", current_string);
		}
	}
	return 0;
}

int is_palindrom(char *a)
{
    char b[100];
	strcpy(b, a);
	strrev(b);
	//printf("%s\n", a);
    //printf("%s\n", b);

	if (strcmp(a, b) == 0)
		return 1;
	else
        return 0;
}
