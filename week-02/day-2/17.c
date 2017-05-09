#include <stdio.h>

int main() {
	float w = 24;
	int out = 0;
	// if w is even increment out by one
	int x = w;

	if (( x % 2 ) == 0) {
        out += 1;
        }

    printf ("out= %d\n", out);

	return 0;
}
