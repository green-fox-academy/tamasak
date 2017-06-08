#include <stdio.h>
#include <stdlib.h>
//#include <curses.h>
#include "Temp_log.h"
#include <string.h>
//#include <ncurses.h>
#include <termios.h>
#include "rs232.h"

static struct termios old, new;
/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

int main()
{
    init_templog();

    while (1) {
		int ch;
		ch = getch();
		if (ch == 104) { //h
			print_usage();
		} else if (ch == 101) { //e
			break;
		} else if (ch == 108) { //l
			list_ports();
		} else if (ch == 112) { //p
			set_port_name();
		} else if (ch == 119) {
			set_write_file();
		} else if (ch == 111) {
			open_port();
		}

	}
    return 0;
}

