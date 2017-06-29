
// fogadas
// ha TOTORO discovery_port_number jon, akkor
// TCP message to ip_of_discovery_request:discovery_port_number
// printf my_name message_port_number.
/*

    IP is 255.255.255.255, this is the broadcast IP
    port is 12345, this can not be modified!
*/
/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int);
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int broadcast_listen (void)
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 42042;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
		(struct sockaddr *)&their_addr, &addr_len);
     clilen = sizeof(cli_addr);
     while (1) {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     }
     close(sockfd);
     return 0;
}
*/
/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
/*void dostuff (int sock)
{
    int n;
    char buffer[256];

    bzero(buffer,256);
    n = read(sock,buffer,255);
    // TOTORO port_where_the_program_waits_for_response
    char input [256];
    strcpy(input, buffer);
    char *totoro = strtok(input, " ");
    char *portnum = strtok(NULL, "\0");
    int port_int = atoi(portnum);
    char send_message[255];
    strcat (send_message," 54321");
    // portot ahova kuldom atallitani
    if ((ret = strcmp (totoro, "TOTORO")) == 0) {
        n = write(sock,send_message,sizeof(send_message));
    }


    n = write(sock,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
}
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

#define MYPORT 3865	// the port users will be connecting to
#define MAXBUFLEN 255


int broadcast_listen(void)
{
	int sockfd;
	struct sockaddr_in my_addr;	// my address information
	struct sockaddr_in their_addr; // connector's address information
	socklen_t addr_len;
	int numbytes;
	char buf[MAXBUFLEN];


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

    char input [256];
    strcpy(input, buf);
    char *totoro = strtok(input, " ");
    char *portnum = strtok(NULL, "\0");
    int port_int = atoi(portnum);
    char send_message[255];
    strcat (send_message," 54321");
	//printf("got packet from %s\n",inet_ntoa(their_addr.sin_addr));
	//printf("packet is %d bytes long\n",numbytes);
	buf[numbytes] = '\0';
	//printf("packet contains \"%s\"\n",buf);
	// send_message();

	close(sockfd);

	return 0;
}
