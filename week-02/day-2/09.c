#include <stdio.h>

int main() {
	int i = 53625;
	// tell if it has 11 as a divisor
	if ((i %= 11) == 0) {
        printf("yes\n");
	}
	return 0;
}
