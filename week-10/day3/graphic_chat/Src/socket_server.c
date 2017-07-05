/* Includes ------------------------------------------------------------------*/
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>
#include "stm32746g_discovery_lcd.h"

#define ABS(X)  ((X) > 0 ? (X) : -(X))
void draw_thick_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
uint32_t text_color = 0;
uint16_t x_coord_prev = 500;
uint16_t y_coord_prev = 500;
uint16_t x_coord;
uint16_t y_coord;
uint8_t line_width = 4;

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
		LCD_UsrLog("Connected to client\n");

		// Receive the data sent by the client
		int received_bytes;
		do {
			memset(&buff[0], 0, sizeof(buff));
			received_bytes = recv(slave_sock, buff, SERVER_BUFF_LEN, 0);
			if (received_bytes == 0) {
				LCD_UsrLog("Connection closed, waiting for an other connection!\n");
			} else {
				// Terminate the string with zero
				//buff[received_bytes] = '\0';
				//LCD_UsrLog("Received string: %s \n", buff);
				//printf("Received string: %s \n", buff);
				osDelay(2);
				draw_points(buff);
				// Print out the received data
				// Send back the received string
				//send(slave_sock, buff, received_bytes, 0);
			}
			//osDelay(5);
		} while (received_bytes > 0);
	}

	// Cleaning up used memory
	close(slave_sock);
	close(sockfd);



}
int draw_points (char *coordinates)
{
	char buffer[SERVER_BUFF_LEN];
	strcpy(buffer, coordinates);
	char *color;
	color = strtok(buffer, " ");
	if (strcmp(color, "c") == 0) {
		color = strtok(NULL, "\n");
		text_color = strtol(color, NULL, 16);
		text_color += 0xff000000;
		osDelay(2);
	} else if (strcmp(color, "clear") == 0) {
		BSP_LCD_Clear(LCD_COLOR_LIGHTGREEN);
	} else if (strcmp(color, "w") == 0) {
		color = strtok(NULL, "\n");
		line_width = atoi(color);
		osDelay(2);
	} else {
		if (x_coord_prev == 500) {
			BSP_LCD_Clear(LCD_COLOR_LIGHTGREEN);
			x_coord_prev = x_coord;
			y_coord_prev = y_coord;
			x_coord = atoi(strtok(coordinates, " "));
			y_coord = atoi(strtok(NULL, "\n"));
			BSP_LCD_FillCircle(x_coord, y_coord, line_width);
		} else {
			x_coord_prev = x_coord;
			y_coord_prev = y_coord;
			x_coord = atoi(strtok(coordinates, " "));
			y_coord = atoi(strtok(NULL, "\n"));
			osDelay(2);
			BSP_LCD_SetTextColor(text_color);
			BSP_LCD_FillCircle(x_coord, y_coord, line_width);
			draw_thick_line(x_coord, y_coord, x_coord_prev, y_coord_prev);
		}
	}
	//osDelay(5);
	return 0;
}
void draw_thick_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0,
  curpixel = 0;

  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */

  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    num_add = deltay;
    num_pixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    num_add = deltax;
    num_pixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
	BSP_LCD_SetTextColor(text_color);
    BSP_LCD_FillCircle(x, y, line_width);   /* Draw the current pixel */
    num += num_add;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
