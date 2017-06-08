#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "Temp_log.h"

void print_usage(void)
{
	printf("Temperature logger\n====================\nCommands:\n");
	printf("h\tShow the command list");
	printf("e\tExit from the program");
	printf("l\tList available ports");
	printf("p\tSet port name");
	printf("w\tSet write filename");
	printf("o\tOpen port");
	printf("s\tStart logging / Stop logging");
	printf("c\tClose port");
	printf("r\tSet read filename");
	printf("a\tCalculate average in given period");
}

