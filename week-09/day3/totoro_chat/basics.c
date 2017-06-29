#include "basics.h"
#include <time.h>
#include <termios.h>

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
void print_list (void)
{
    printf("TOTOTRO CHAT\n====================\nCommands:\n");
	printf("h\tDisplay this help info\n");
	printf("e\tExit\n");
	printf("n\tSet user name\n");
	printf("l\tList known users\n");
	printf("d\tSend discovery request\n");
	printf("m\tSend message\n");
	printf("\n");
}

void set_username(info_storeage *storeage)
{
    printf("Type in your name\n");
    gets(storeage->array[storeage->length + 1].name);
    storeage->array[storeage->length + 1].ipaddress = 0;
    storeage->array[storeage->length + 1].port = 54321;
    storeage->length += 1;
    printf(Your name has been set\n);
}
void init(info_storeage *storeage)
{
    //storeage->array = NULL;
    storeage->length = 0;
    print_list();
}
void list_users(info_storeage *storeage)
{
    printf("IP\t\tport\tname\t\n");
    for (int i = 0; i <= storeage->length; i++) {
        printf("%d\t%d\t%s", storeage->array[i].ipaddress, storeage->array.port, storeage->array.name);
    }
}
