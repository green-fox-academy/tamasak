/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SOCKET_SERVER_H
#define __SOCKET_SERVER_H

#define SERVER_PORT		54545
#define SERVER_QUEUE_SIZE	2
#define SERVER_BUFF_LEN		64

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void socket_server_thread(void const *argument);
int draw_points (char *coordinates);

/*#include <stdint.h>
#include <stdio.h>
uint32_t text_color;*/

#endif /* __SOCKET_SERVER_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
