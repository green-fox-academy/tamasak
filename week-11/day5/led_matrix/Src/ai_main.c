/**
 ******************************************************************************
 * @file    USB_Device/HID_Standalone/Src/main.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    30-December-2016
 * @brief   USB device HID demo main file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "ai_main.h"
#include <math.h>

uint8_t draw_table_size = 16;
uint8_t zero_text[2] = "0";
uint8_t one_text[2] = "1";
uint8_t two_text[2] = "2";
uint8_t three_text[2] = "3";
uint8_t four_text[2] = "4";
uint8_t five_text[2] = "5";
uint8_t six_text[2] = "6";
uint8_t seven_text[2] = "7";
uint8_t eight_text[2] = "8";
uint8_t nine_text[2] = "9";

uint8_t x_coord;
uint8_t y_coord;
uint8_t ind;

int16_t match_cntr[10] = {0,0,0,0,0,0,0,0,0,0};
int16_t recognize_array[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];
int16_t zero_weights[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];
int16_t one_weights[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];
int16_t two_weights[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];
int16_t three_weights[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];
int16_t four_weights[DRAW_TABLE_SIZE][DRAW_TABLE_SIZE];

uint8_t mode;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
void ai_mode(void)
{
	TS_StateTypeDef TS_State;
	variable_init();
	menu_init();
	mode = 0;
	while (1) {
		BSP_TS_GetState(&TS_State);
		HAL_Delay(10);
		if (mode == 0) {
			if (TS_State.touchX[0] >= 154 && TS_State.touchX[0] <= 326 &&
					TS_State.touchY[0] >= 40 && TS_State.touchY[0] <= 126) {
				mode = 1;		//train mode
				training_init();
			} else 	if (TS_State.touchX[0] >= 154 && TS_State.touchX[0] <= 326 &&
					TS_State.touchY[0] >= 146 && TS_State.touchY[0] <= 232) {
				mode = 2;		//recognize mode
				recognize_init();
			}
		}
		BSP_TS_GetState(&TS_State);
		//IF IN "TRAIN" MODE
		if (mode == 1) {
			ai_train();
		}

		//IF IN "RECOGNIZE" MODE
		if (mode == 2) {
			//if push button is pressed
			if (BSP_PB_GetState(BUTTON_KEY) == 1) {
				menu_init();
				mode = 0;
			}
			ai_recognize();

			//if CLEAR is selected
			//BSP_LCD_DrawRect(301, 200, 150, 50);
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 451 &&
					TS_State.touchY[0] >= 200 && TS_State.touchY[0] <= 250) {
				ai_clear();
			}
		}
	}
}
void training_init()
{
	BSP_LCD_Clear(LCD_COLOR_YELLOW);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(71, 71, 130, 130);		//drawing area
	BSP_LCD_DrawLine(272, 0, 272, 272);	//area separator
	BSP_LCD_DrawRect(331, 20, 90, 50); //TRAIN button
	uint8_t train_text[6] = "TRAIN";
	BSP_LCD_DisplayStringAt(334, 30, train_text, LEFT_MODE);
	BSP_LCD_DrawRect(301, 80, 150, 180); //selection table

	BSP_LCD_DisplayStringAt(326, 84, zero_text, LEFT_MODE);
	BSP_LCD_DrawLine(301, 160, 451, 160);	//horizontal line top
	BSP_LCD_DrawLine(301, 210, 451, 210);	//horizontal line bottom
	BSP_LCD_DrawLine(351, 110, 351, 260);	//vertical line left
	BSP_LCD_DrawLine(401, 110, 401, 260);	//vertical line right

	BSP_LCD_DisplayStringAt(316, 125, one_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 125, two_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(416, 125, three_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(316, 175, four_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 175, five_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(416, 175, six_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(316, 225, seven_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 225, eight_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(419, 225, nine_text, LEFT_MODE);
}
void recognize_init()
{
	BSP_LCD_Clear(LCD_COLOR_YELLOW);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(71, 71, 130, 130);		//drawing area
	BSP_LCD_DrawLine(272, 0, 272, 272);		//vertical separator line
	BSP_LCD_DrawRect(301, 20, 150, 50); 	//RECOGNIZE button
	BSP_LCD_SetFont(&Font20);
	uint8_t recognize_text[10] = "RECOGNIZE";
	BSP_LCD_DisplayStringAt(313, 35, recognize_text, LEFT_MODE);
	BSP_LCD_DrawRect(301, 80, 150, 80); 	//result table
	BSP_LCD_DrawLine(301, 110, 451, 110);	//line below "Result:"
	uint8_t result_text[8] = "Result:";
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(317, 84, result_text, LEFT_MODE);
	BSP_LCD_DrawRect(301, 200, 150, 50);	//clear table
	uint8_t clear_text[6] = "CLEAR";
	BSP_LCD_DisplayStringAt(330, 210, clear_text, LEFT_MODE);
	for(int i = 0; i < DRAW_TABLE_SIZE; i++) {
		for (int j = 0; j < DRAW_TABLE_SIZE; j++) {
			recognize_array[i][j] = -1;
		}
	}
}
void menu_init()
{
	BSP_LCD_Clear(LCD_COLOR_YELLOW);
	//display TRAIN button
	BSP_LCD_DrawRect(154, 40, 172, 86);
	char train_text[6] = "TRAIN";
	BSP_LCD_DisplayStringAt(200, 70, train_text, LEFT_MODE);
	//display RECOGNIZE button
	BSP_LCD_DrawRect(154, 146, 172, 86);
	char recognize_text[11] = "RECOGNIZE";
	BSP_LCD_DisplayStringAt(164, 176, recognize_text, LEFT_MODE);
}
void ai_train(void)
{
	TS_StateTypeDef TS_State;
	BSP_TS_GetState(&TS_State);

	if (mode == 1) {
		//if "0" selected
		if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 451 &&
					TS_State.touchY[0] >= 80 && TS_State.touchY[0] <= 110) {
			ind = 0;
			for(int i = 0; i < draw_table_size; i++) {
				for (int j = 0; j < draw_table_size; j++) {
					zero_weights[i][j] = -10;
				}
			}
		}
		//if "1" selected
		if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
								TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
			ind = 1;
			for(int i = 0; i < draw_table_size; i++) {
				for (int j = 0; j < draw_table_size; j++) {
					one_weights[i][j] = -10;
				}
			}

		}
		//if "2" selected
		if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
								TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
			ind = 2;
			for(int i = 0; i < draw_table_size; i++) {
				for (int j = 0; j < draw_table_size; j++) {
					two_weights[i][j] = -10;
				}
			}

		}
		//if "3" selected
		if (TS_State.touchX[0] >= 401 && TS_State.touchX[0] <= 451 &&
								TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
			ind = 3;
			//set stored image structures to 0
			for(int i = 0; i < draw_table_size; i++) {
				for (int j = 0; j < draw_table_size; j++) {
					three_weights[i][j] = -10;
				}
			}

		}
		//if "4" selected
		if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
								TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
			ind = 4;
			//set stored image structures to 0
			for(int i = 0; i < draw_table_size; i++) {
				for (int j = 0; j < draw_table_size; j++) {
					four_weights[i][j] = -10;
				}
			}

		}
		/*

		//if "5" selected
		if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
								TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
			ind = 5;
			BSP_LCD_Clear(LCD_COLOR_RED);
			//set stored image structures to 0
			for(int i = 0; i < 130; i++) {
				for (int j = 0; j < 130; j++) {
					five_image[i][j] = 0;
					five_weights[i][j] = 0;
				}
			}

		}
		//if "6" selected
		if (TS_State.touchX[0] >= 401 && TS_State.touchX[0] <= 451 &&
								TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
			ind = 6;
			BSP_LCD_Clear(LCD_COLOR_BLACK);
			//set stored image structures to 0
			for(int i = 0; i < 130; i++) {
				for (int j = 0; j < 130; j++) {
						six_image[i][j] = 0;
						six_weights[i][j] = 0;
					}
				}
			}
		//if "7" selected
		if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
								TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
			ind = 7;
			BSP_LCD_Clear(LCD_COLOR_BLUE);
			//set stored image structures to 0
			for(int i = 0; i < 130; i++) {
				for (int j = 0; j < 130; j++) {
					seven_image[i][j] = 0;
					seven_weights[i][j] = 0;
				}
			}
		}
		//if "8" selected
		if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
								TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
			ind = 87;
			BSP_LCD_Clear(LCD_COLOR_CYAN);
			//set stored image structures to 0
			for(int i = 0; i < 130; i++) {
				for (int j = 0; j < 130; j++) {
					eight_image[i][j] = 0;
					eight_weights[i][j] = 0;
				}
			}
		}
		//if "9" selected
		if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
								TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
			ind = 9;
			//set stored image structures to 0
			for(int i = 0; i < 130; i++) {
				for (int j = 0; j < 130; j++) {
					nine_image[i][j] = 0;
					nine_weights[i][j] = 0;
				}
			}
		}
		*/


		//if touch is within drawing area, draw ellipse and save coordinates
		if (TS_State.touchX[0] >= 76 && TS_State.touchX[0] <= 196 &&
				TS_State.touchY[0] >= 76 && TS_State.touchY[0] <= 196) {
			BSP_LCD_FillEllipse(TS_State.touchX[0], TS_State.touchY[0], 5, 5);
			//save coordinates to structure
			switch(ind) {
			case 0:
				x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
				y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
				if (zero_weights[x_coord][y_coord] == -10) {
					zero_weights[x_coord][y_coord] = 1;
				} else {
					zero_weights[x_coord][y_coord] += 100;
				}
				break;
			case 1:
				x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
				y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
				if (one_weights[x_coord][y_coord] == -10) {
					one_weights[x_coord][y_coord] = 1;
				} else {
					one_weights[x_coord][y_coord] += 1000;
				}
				break;
			case 2:
				x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
				y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
				if (two_weights[x_coord][y_coord] == -10) {
					two_weights[x_coord][y_coord] = 1;
				} else {
					two_weights[x_coord][y_coord] += 100;
				}
				break;
			case 3:
				x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
				y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
				if (three_weights[x_coord][y_coord] == -10) {
					three_weights[x_coord][y_coord] = 1;
				} else {
					three_weights[x_coord][y_coord] += 100;
				}
				break;
			case 4:
				x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
				y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
				if (four_weights[x_coord][y_coord] == -10) {
					four_weights[x_coord][y_coord] = 1;
				} else {
					four_weights[x_coord][y_coord] += 100;
				}
				break;
				/*
			case 5:
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				five_image[x_coord][y_coord] = 1;
				break;
			case 6:
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				six_image[x_coord][y_coord] = 1;
				break;
			case 7:
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				seven_image[x_coord][y_coord] = 1;
				break;
			case 8:
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				eight_image[x_coord][y_coord] = 1;
				break;
			case 9:
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				nine_image[x_coord][y_coord] = 1;
				break;
				*/
			}
		}


		//if TRAIN is selected
		if (TS_State.touchX[0] >= 331 && TS_State.touchX[0] <= 421 &&
				TS_State.touchY[0] >= 20 && TS_State.touchY[0] <= 70) {
			BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
			BSP_LCD_FillRect(72, 72, 129, 129);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}
	}
	//if push button is pressed
	if (BSP_PB_GetState(BUTTON_KEY) == 1) {
		menu_init();
		mode = 0;
	}
}
void ai_recognize(void)
{
	TS_StateTypeDef TS_State;
	BSP_TS_GetState(&TS_State);
	//if touch is within drawing area, draw ellipse and save coordinates
	if (TS_State.touchX[0] >= 76 && TS_State.touchX[0] <= 196 &&
				TS_State.touchY[0] >= 76 && TS_State.touchY[0] <= 196) {
		BSP_LCD_FillEllipse(TS_State.touchX[0], TS_State.touchY[0], 5, 5);
		//save coordinates to structure
		x_coord = (uint8_t)TS_State.touchX[0] / DIVIDER;
		y_coord = (uint8_t)TS_State.touchY[0] / DIVIDER;
		//rec_image[x_coord][y_coord] = 1;
		recognize_array[x_coord][y_coord] = 1;
		/*if (zero_weights[x_coord][y_coord] > 3) {
			match_cntr[0]++;
		}
		if (one_weights[x_coord][y_coord] > 3) {
			match_cntr[1]++;
		}
		if (two_weights[x_coord][y_coord] > 3) {
			match_cntr[2]++;
		}
		if (three_weights[x_coord][y_coord] > 3) {
			match_cntr[3]++;
		}
		if (four_weights[x_coord][y_coord] > 3) {
			match_cntr[4]++;
		}

		if (five_image[x_coord][y_coord] == 1 && five_weights[x_coord][y_coord] > 100) {
			match_cntr[5]++;
		}
		if (six_image[x_coord][y_coord] == 1 && six_weights[x_coord][y_coord] > 100) {
			match_cntr[6]++;
		}
		if (seven_image[x_coord][y_coord] == 1 && seven_weights[x_coord][y_coord] > 100) {
			match_cntr[7]++;
		}
		if (eight_image[x_coord][y_coord] == 1 && eight_weights[x_coord][y_coord] > 100) {
			match_cntr[8]++;
		}
		if (nine_image[x_coord][y_coord] == 1 && nine_weights[x_coord][y_coord] > 100) {
			match_cntr[9]++;
		}
		*/
	}
	// recognize
	if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 461 &&
			TS_State.touchY[0] >= 20 && TS_State.touchY[0] <= 70) {
		// comprare training arrays with recog array
		for (int i = 0; i < DRAW_TABLE_SIZE; i++){
			for (int j = 0; j < DRAW_TABLE_SIZE; j++){
				if ((recognize_array[i][j] < 0) && (zero_weights[i][j] < 0)) {
					match_cntr[0]++;
				} else {
					match_cntr[0] += recognize_array[i][j] * zero_weights[i][j];
				}
				if ((recognize_array[i][j] < 0) && (one_weights[i][j] < 0)) {
					match_cntr[1]++;
				} else {
					match_cntr[1] += recognize_array[i][j] * one_weights[i][j];
				}
				if ((recognize_array[i][j] < 0) && (two_weights[i][j] < 0)) {
					match_cntr[2]++;
				} else {
					match_cntr[2] += recognize_array[i][j] * two_weights[i][j];
				}
				if ((recognize_array[i][j] < 0) && (three_weights[i][j] < 0)) {
					match_cntr[3]++;
				} else {
					match_cntr[3] += recognize_array[i][j] * three_weights[i][j];
				}
				if ((recognize_array[i][j] < 0) && (four_weights[i][j] < 0)) {
					match_cntr[4]++;
				} else {
					match_cntr[4] += recognize_array[i][j] * four_weights[i][j];
				}
			}
		}
		int16_t max_match = -100;
		int max_ind = -1;
		for (int i = 0; i < 10; i++) {
			if ((match_cntr[i] > max_match) && (match_cntr[i] > 256)) {
				max_match = match_cntr[i];
				max_ind = i;
			}
		}
		//printf("%d", max_match);
		switch(max_ind) {
		case 0:
			BSP_LCD_DisplayStringAt(310, 120, zero_text, LEFT_MODE);
			break;
		case 1:
			BSP_LCD_DisplayStringAt(310, 120, one_text, LEFT_MODE);
			break;
		case 2:
			BSP_LCD_DisplayStringAt(310, 120, two_text, LEFT_MODE);
			break;
		case 3:
			BSP_LCD_DisplayStringAt(310, 120, three_text, LEFT_MODE);
			break;
		/*case 4:
			BSP_LCD_DisplayStringAt(310, 120, four_text, LEFT_MODE);
			break;
		case 5:
			BSP_LCD_DisplayStringAt(310, 120, five_text, LEFT_MODE);
			break;
		case 6:
			BSP_LCD_DisplayStringAt(310, 120, six_text, LEFT_MODE);
			break;
		case 7:
			BSP_LCD_DisplayStringAt(310, 120, seven_text, LEFT_MODE);
			break;
		case 8:
			BSP_LCD_DisplayStringAt(310, 120, eight_text, LEFT_MODE);
			break;
		case 9:
			BSP_LCD_DisplayStringAt(310, 120, nine_text, LEFT_MODE);
			break;
			*/
		default:
			BSP_LCD_SetFont(&Font12);
			uint8_t notrec_text[15] = "Not recognized";
			BSP_LCD_DisplayStringAt(326, 130, notrec_text, LEFT_MODE);
			break;
		}
	}
}
void ai_clear(void)
{
	//clear drawing area
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_FillRect(72, 72, 129, 129);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	//clear match counters
	for (uint8_t i = 0; i < 10; i++) {
		match_cntr[i] = 0;
	}
	//clear Result table
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_FillRect(302, 111, 149, 49);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for(int i = 0; i < DRAW_TABLE_SIZE; i++) {
		for (int j = 0; j < DRAW_TABLE_SIZE; j++) {
			recognize_array[i][j] = -1;
		}
	}
}
void variable_init(void)
{
	for(int i = 0; i < draw_table_size; i++) {
		for (int j = 0; j < draw_table_size; j++) {
			zero_weights[i][j] = -10;
			one_weights[i][j] = -10;
			two_weights[i][j] = -10;
			three_weights[i][j] = -10;
			four_weights[i][j] = -10;
			/*
			five_image[i][j] = 0;
			five_weights[i][j] = 0;
			six_image[i][j] = 0;
			six_weights[i][j] = 0;
			seven_image[i][j] = 0;
			seven_weights[i][j] = 0;
			eight_image[i][j] = 0;
			eight_weights[i][j] = 0;
			nine_image[i][j] = 0;
			nine_weights[i][j] = 0;
			*/
		}
	}
}


