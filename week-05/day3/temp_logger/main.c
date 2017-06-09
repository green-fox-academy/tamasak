#include <stdio.h>
#include <stdlib.h>
//#include <curses.h>
#include "Temp_log.h"
#include <string.h>
//#include <ncurses.h>
#include "rs232.h"

int main()
{
    init_templog();
    //int log = -1; // if -1 -> not logging, if 1 -> logging
    while (1) {
		int ch;
		ch = getch();
		if (ch == 104) { //h
			print_usage();
		} else if (ch == 101) { //e exit
			break;
		} else if (ch == 108) { //l list ports
			list_ports();
		} else if (ch == 112) { //p set port
			set_port_name();
		} else if (ch == 119) { //w file to write
			set_write_file();
		} else if (ch == 111) { //o open port
			open_port();
		} else if (ch == 115) { //s start logging
            start_stop_log();
		}

	}
    return 0;
}

