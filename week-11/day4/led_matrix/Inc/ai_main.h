/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AI_MAIN_H
#define __AI_MAIN_H

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

/* Exported functions ------------------------------------------------------- */

#define DRAW_TABLE_PIXELS	130
#define DIVIDER		8
#define DRAW_TABLE_SIZE	16

void training_init();
void menu_init();
void recognize_init();
void ai_mode(void);
void ai_train(void);
void ai_recognize(void);
void ai_clear(void);
void variable_init(void);


#endif // ai_main.h
