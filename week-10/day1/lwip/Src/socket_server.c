/* Includes ------------------------------------------------------------------*/

#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "main.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	// Server address structure initialization
	struct sockaddr_in addr_in;                          // Inet address structure definition
	addr_in.sin_family = AF_INET;                        // This address is an internet address
	addr_in.sin_port = htons(SERVER_PORT);               // Server port
	addr_in.sin_addr.s_addr = inet_addr("10.27.6.40");      // Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in; // Make a struct sockaddr pointer, which points to the address

	// Creating the socket
	int sockfd;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	// Start binding the socket to the previously set address
	int flag = bind(sockfd, addr, sizeof(*addr));

	// Start listening on with the set socket with a predefined queue size
	flag = listen(sockfd, SERVER_QUEUE_SIZE);
	LCD_UsrLog("Waiting for connections...\n");

	// Create variables which will be used in the while loop
	struct sockaddr client_addr;    // Client address structure
	int slave_sock;              	// Slave socket definition, this will be used to store the incoming socket
	char buff[SERVER_BUFF_LEN];     // Buffer for incoming and outgoing data
	//int cntr = 1; 					// Counter for incoming connections

	while (1) {
		// Accept the connection and save the incoming socket
		slave_sock = accept(sockfd, &client_addr, NULL);

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(slave_sock, buff, SERVER_BUFF_LEN, 0);
			if (received_bytes == 0) {
				LCD_UsrLog("Connection closed, waiting for an other connection!\n");
			} else {
				// Terminate the string with zero
				buff[received_bytes] = '\0';
				// Print out the received data
				LCD_UsrLog("Received string: %s \n", buff);
				// Send back the received string
				send(slave_sock, buff, received_bytes, 0);
				}
		} while (received_bytes > 0);
	}

	// Cleaning up used memory
	close(slave_sock);
	close(sockfd);



}

void broadcast_listener_thread (void const *argument)
{
	/*
    socket()
    setsockopt()
    bind()
    recvfrom()
	*/

	int broadcast = 1;
	// Server address structure initialization
	struct sockaddr_in addr_in;                          // Inet address structure definition
	addr_in.sin_family = AF_INET;                        // This address is an internet address
	addr_in.sin_port = htons(12345);
	addr_in.sin_addr.s_addr = inet_addr(INADDR_ANY);
	//struct sockaddr *addr = (struct socka.addr *)&addr_in; // Make a struct sockaddr pointer, which points to the address

	// Creating the socket
	int sockfd;
	sockfd = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);

	// Setsockopt()
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof (broadcast)) == -1) {
		LCD_UsrLog("Error: setsockopt (SO_BROADCAST)");
		exit(1);
	}

	// Start binding the socket to the previously set address
	int flag = bind(sockfd, (struct sockaddr*)&addr_in, sizeof(addr_in));

	struct sockaddr_in client_addr;
	while(1) {
		int client_addr_len = sizeof(client_addr);
		char buff[255];
		int receive_bytes = recvfrom(sockfd, buff, 255, 0,
									(struct sockaddr*)&client_addr,
									&client_addr_len);
		buff[receive_bytes] = '\0';
		uint32_t client_ip = client_addr.sin_addr.s_addr;

		// get data
		char unique_str[255];
		unique_str[0] = '\0';
		int port;

		if (sscanf(buff, "%s %d", unique_str, &port) < 2) {
			printf("Error: broadcast_listener - sscanf()\n");
		}
		if (strcmp(unique_str, "marharepa") != 0) {
			LCD_UsrLog("%s\n", unique_str);
		}
	}

	// recvfrom()
	//socklen_t addr_len = sizeof their_addr;
	//recvfrom(sockfd, buf, 255 , 0, (struct sockaddr *)&their_addr, &addr_len);


}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
