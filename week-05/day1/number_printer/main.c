#include <stdio.h>
#include <stdint.h>

void printf_numbers(long long from, long long to)
{
	for (long long i = from; i < to; i++)
		printf("%lli,\n", i);
}

int main()
{
	printf_numbers(2147483600, 2147484600);
	return 0;
}
