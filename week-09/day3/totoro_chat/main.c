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

typedef struct {
    user_info array[50];
    int length;
} info_storeage

int main()
{
    info_storeage storeage;
    init(&storeage);

    pthread_t inc_x_thread;

    while (1) {
		int ch;
		ch = getch();
		if (ch == 104) { //h
			print_list();
		} else if (ch == 101) { //e exit
			break;
		} else if (ch == 110) { //n set user name
			set_username(&storeage);
		} else if (ch == 108) { //l list known users
			list_users(&storeage);
		} else if (ch == 100) { //d Send discovery request
            pthread_create(&inc_x_thread, NULL, &discovery_request, NULL);
		} else if (ch == 109) { //m Send message
			//send_message();
		}

	}
    return 0;
}
