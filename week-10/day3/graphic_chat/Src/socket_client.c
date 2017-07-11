/* Includes ------------------------------------------------------------------*/
#include "socket_client.h"
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>
#include <stdint.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef TS_State;
uint16_t line_th;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void connect_to_server(int *client_sock, unsigned int server_port, char *server_ip)
{
	// Creating client socket
	(*client_sock) = lwip_socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	//if (client_sock < 0)
		//printf("error creating client socket\n");
	//printf("client socket created successfully\n");

	// Creating server address
	struct sockaddr_in addr_in;
	addr_in.sin_family = PF_INET;
	addr_in.sin_port = htons(server_port);
	addr_in.sin_addr.s_addr = inet_addr(server_ip);

	// Connecting the client socket to the server
	//int connect_retval = lwip_connect(*client_sock, (struct sockaddr *)&addr_in, sizeof(addr_in));
	lwip_connect(*client_sock, (struct sockaddr *)&addr_in, sizeof(addr_in));
	//if (connect_retval < 0)
		//printf("error connecting the client socket to the server\n");
	//printf("client socket connected to the server successfully\n");
}

void draw_init(void)


{
	BSP_LCD_Clear(LCD_COLOR_LIGHTGREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
	BSP_LCD_FillRect(10, 5, 80, 80);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(10, 95, 80, 80);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_FillRect(10, 185, 80, 80);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(100, 5, 80, 80);
	BSP_LCD_FillCircle(140, 45, 5);
	BSP_LCD_DrawRect(100, 95, 80, 80);
	BSP_LCD_FillCircle(140, 135, 2);
	BSP_LCD_DrawRect(100, 185, 80, 80);
	BSP_LCD_FillCircle(140, 225, 1);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
	line_th = 5;
}


uint32_t color_select(TS_StateTypeDef TS_State)
{ 	uint32_t color_code;
	if (TS_State.touchY[0] >= 5 && TS_State.touchY[0] <= 85) {
		BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
		color_code = 0xFFFF00FF;
	} else if (TS_State.touchY[0] >= 95 && TS_State.touchY[0] <= 175) {
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
		color_code = 0xFFD3D3D3;
	} else if (TS_State.touchY[0] >= 185 && TS_State.touchY[0] <= 265) {
		BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
		color_code = 0xFFFFFF00;
	}
	return color_code;
}


uint16_t style_select(TS_StateTypeDef TS_State)
{
	if (TS_State.touchY[0] >= 5 && TS_State.touchY[0] <= 85)
		line_th = 5;
	else if (TS_State.touchY[0] >= 95 && TS_State.touchY[0] <= 175)
		line_th = 2;
	else if (TS_State.touchY[0] >= 185 && TS_State.touchY[0] <= 265)
		line_th = 1;
	return line_th;
}


// TODO:
// Implement this function!
void socket_client_thread(void const *argument)
{
	while(!is_ip_ok())
		osDelay(1);
	osDelay(5000);
	//TS_StateTypeDef TS_State;
	// Connect to server
	int client_socket;
	connect_to_server(&client_socket, SERVER_PORT, SERVER_IP);
	// Local variables used in the do-while loop
	int sent_bytes;
	//initialize drawing board
	draw_init();
	char msg[255];
	uint32_t color;
	char color_code[10];
	char style[10];
	uint16_t x_coord;
	uint16_t y_coord;
	char x_coord_char[10];
	char y_coord_char[10];
	char thickness[10];


	while (1) {
		//get touch state
		//char msg[255];
		memset(msg, 0, 255);
		memset(x_coord_char, 0, 10);
		memset(y_coord_char, 0, 10);
		TS_StateTypeDef TS_State;
		BSP_TS_GetState(&TS_State);
		if (TS_State.touchDetected > 0 ) {
			if (TS_State.touchX[0] >= 10 && TS_State.touchX[0] <= 90) {
				color = color_select(TS_State);
				//send selected color
				if (color == LCD_COLOR_MAGENTA)
					strcpy(color_code, "FF00FF");
				else if (color == LCD_COLOR_LIGHTGRAY)
					strcpy(color_code, "D3D3D3");
				else if (color == LCD_COLOR_YELLOW)
					strcpy(color_code, "FFFF00");
				strcpy(msg, "c");
				strcat(msg, " ");
				strcat(msg, color_code);
				strcat(msg, "\n");
				osDelay(100);
				//puts(msg);
				lwip_send(client_socket, msg, strlen(msg), 0);
			} else if (TS_State.touchX[0] >= 100 && TS_State.touchX[0] <= 180) {
				line_th = style_select(TS_State);
				//send selected style
				if (line_th == 5)
					strcpy(thickness, "5");
				else if (line_th == 2)
					strcpy(thickness, "2");
				else if (line_th == 1)
					strcpy(thickness, "1");
				strcpy(msg, "w");
				strcat(msg, " ");
				strcat(msg, thickness);
				strcat(msg, "\n");
				osDelay(100);
				//puts(msg);
				lwip_send(client_socket, msg, strlen(msg), 0);
			}
			else if (TS_State.touchX[0] >= 180 && TS_State.touchX[0] <= 480) {
				BSP_LCD_FillCircle(TS_State.touchX[0],TS_State.touchY[0], line_th);
				x_coord = TS_State.touchX[0];
				y_coord = TS_State.touchY[0];
				sprintf(x_coord_char, "%d", x_coord);
				sprintf(y_coord_char, "%d", y_coord);
				strcpy(msg, x_coord_char);
				strcat(msg, " ");
				strcat(msg, y_coord_char);
				strcat(msg, "\n");
				//puts(msg);
				osDelay(50);
				//send touch state
				lwip_send(client_socket, msg, strlen(msg), 0);
			}
		}
		if (BSP_PB_GetState(BUTTON_KEY) == 1) {
			//memset(msg, 0, 255);
			strcpy(msg, "clear");
			strcat(msg, " ");
			strcat(msg, "\n");
			osDelay(100);
			//puts(msg);
			lwip_send(client_socket, msg, strlen(msg), 0);
			draw_init();
		}
	}
	//lwip_close(client_socket);
	return;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
