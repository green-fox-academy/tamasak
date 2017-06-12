#include <avr/io.h>
#include "fastPWM.h"
#include <util/delay.h>
#include "ADC_driver.h"
#include "UART_driver.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
	init_led();
	timer0_init();
	ADC_Init();
	UART_init();
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	while (1) {
		uint16_t voltage = ADC_Read() / 4;
		char buffer[20];
		gets(buffer);
		voltage = atof (buffer);
		set_duty_cycle(voltage);
		printf("%d\n", voltage);
	}
}