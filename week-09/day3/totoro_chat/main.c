#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "message.h"
#include "discovery.h"
#include "broadcast.h"
#include <string.h>
#include "basics.h"
#include <pthread.h>
#include <unistd.h>
#include <termios.h>



int main()
{
    info_storeage storeage;
    init(&storeage);
    pthread_t broad_listen;
    pthread_create(&broad_listen, NULL, broadcast_listen, NULL);
    pthread_join(broad_listen, NULL);

    //pthread_create(&inc_x_thread, NULL, test_thread, NULL);

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
		    pthread_t disco_req;
            pthread_create(&disco_req, NULL, discovery_request, NULL);
            pthread_join(disco_req, NULL);
            //discovery_request();
		} else if (ch == 109) { //m Send message
			//send_message();
		}

	}
    return 0;
}
/*void test_thread (void)
{
    //while (1) {
        printf("1\n");
        sleep(1);
    //}
}*/
