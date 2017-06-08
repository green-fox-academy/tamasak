#include <string.h>
#include <stdint.h>
#include "Temp_log.h"
#include <stdio.h>
#include "rs232.h"
#include <curses.h>
#include <ncurses.h>

void init_templog(void)
{
	print_usage();
}

void print_usage(void)
{
	printf("Temperature logger\n====================\nCommands:\n");
	printf("h\tShow the command list\n");
	printf("e\tExit from the program\n");
	printf("l\tList available ports\n");
	printf("p\tSet port name\n");
	printf("w\tSet write filename\n");
	printf("o\tOpen port\n");
	printf("s\tStart logging / Stop logging\n");
	printf("c\tClose port\n");
	printf("r\tSet read filename\n");
	printf("a\tCalculate average in given period\n");
}

void list_ports(void)
{
    comEnumerate();
    comEnumerate_mod();
}
char *set_port_name(void)
{
    printf("Enter the port name\n");
    char tmp[80];
    strcpy(tmp, port);
    gets(port);
    if (comEnumerate_mod2() == 0) {
        printf("Error, no such device\n");
        strcpy(port, tmp);
    }
    return port;
}
void set_write_file(void)
{
    printf("Enter the file name\n");
    char path[80];
    gets(path);
    FILE *file = fopen(path,"a");
    fclose(file);
}
void open_port(void)
{

}
