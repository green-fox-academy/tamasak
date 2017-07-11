/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LED_MATRIX_COLS		5
#define LED_MATRIX_ROWS		7

/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void led_matrix_update_thread(void const *argument);
void led_matrix_waterfall_thread(void const *argument);
void adc_speed(void);
void StartApplication (void);
#endif /* __LED_MATRIX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
