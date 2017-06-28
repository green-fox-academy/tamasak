#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "message.h"
#include "discovery.h"
#include "broadcast.h"
#include <string.h>
#include "basics.h"
#include <pthread.h>

typedef struct {
    char name[255];
    uint32_t ipaddress;
    int port;
} user_info;
user_info user_array[50];

int main()
{
    /*
     * Init functions
     */

    print_list();

    while (1) {
		int ch;
		ch = getch();
		if (ch == 104) { //h
			print_list();
		} else if (ch == 101) { //e exit
			break;
		} else if (ch == 110) { //n set user name
			//set_username();
		} else if (ch == 108) { //l list known users
			//list_users();
		} else if (ch == 100) { //d Send discovery request
			//discovery_request();
		} else if (ch == 109) { //m Send message
			//send_message();
		}

	}
    return 0;
}
