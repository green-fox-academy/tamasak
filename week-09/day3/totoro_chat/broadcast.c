
// ha jon broadcast, akkor fogad es visszakuldi a nevet, portot...

// ha TOTORO discovery_port_number jon, akkor
// TCP message to ip_of_discovery_request:discovery_port_number
// printf my_name message_port_number.
/*

    IP is 255.255.255.255, this is the broadcast IP
    port is 12345, this can not be modified!
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 12345	// the port users will be connecting to
#define MAXBUFLEN 255


int broadcast_listen(void)
{
	int sockfd;
	struct sockaddr_in my_addr;	// my address information
	struct sockaddr_in their_addr; // connector's address information
	socklen_t addr_len;
	int numbytes;
	char buf[MAXBUFLEN];
    char s[INET6_ADDRSTRLEN];
    int n;
    int newsockfd;

    while (1) {

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        my_addr.sin_family = AF_INET;		 // host byte order
        my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
        my_addr.sin_port = htons(MYPORT);	 // short, network byte order
        memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

        if (bind(sockfd, (struct sockaddr *)&my_addr,
            sizeof(struct sockaddr)) == -1) {
            perror("bind");
            exit(1);
        }

        addr_len = sizeof(struct sockaddr);
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }
        newsockfd = accept(sockfd,
                 (struct sockaddr *) &their_addr,
                 &addr_len);
        /*printf("listener: got packet from %s\n",
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s));*/

        char input [256];
        strcpy(input, buf);
        char *totoro = strtok(input, " ");
        char *portnum = strtok(NULL, "\0");
        int port_int = atoi(portnum);
        char send_message[255];
        strcat (send_message," 54321");
        //their_addr.sin_port = htons(port_int);
        n = write(newsockfd,send_message,sizeof(send_message));

        close(sockfd);
    }

	return 0;
}
