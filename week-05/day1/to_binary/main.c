#include <stdio.h>

void int_to_bin_digit(int in, int count)
{
	unsigned long long mask;
	int i;
	int result;
	for (i = 0; i <= count; i++) {
        mask = 1U << (count-i);
		result = (in & mask) ? 1 : 0;
		printf("%d", result);
		//in = in < 1;
	}
}

int main()
{
	int_to_bin_digit(15, 31);
	return 0;
}
