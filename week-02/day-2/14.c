#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t number = 254;
	uint8_t result;

	result = number + 23;
	// Check the result with printf
	printf("%d\n", result);

 	// What happened?!
 	// 8 bit is not enough, the maximum number is 255

	// Try again with different datatype
	uint16_t result_16 = number + 23;
	// Check the result with printf
	printf("%d\n", result_16);

	// What happened and why?
	// In 16 bits we can handle numbers up to 2^16 - 1, so it can write out to correct number

	//----------------------------------------
	int8_t number_negative = number;
	// Check the result with printf
	printf("%d\n", number_negative);

	// What happened and why?
	// int8_t can handle numbers between -128 and 127, if a number is >127 and < 255 it is defined as a negative number

    return 0;
}
