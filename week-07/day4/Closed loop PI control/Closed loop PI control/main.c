#include "freq_meas.h"
#include "UART_driver.h"
#include "AC_driver.h"
#include "fastPWM.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ADC_driver.h"
#include "control.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5

void system_init()
{
	LED_DDR |= 1 << LED_DDR_POS;
	AC_driver_init();
	freq_meas_init();
	UART_init();
	interrupt_init();
	timer2_init();
	ADC_Init();
	sei();
}

int main(void)
{

	// Don't forget to call the init function :)
	system_init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM((void *)UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, (void *)UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	// Try printf
	printf("Startup...\r\n");

	// Infinite loop
	while (1) {
		//uint16_t voltage = ADC_Read() / 4;
		set_duty_cycle(p_control(get_rpm(), 0.01));
		_delay_ms(10);
		printf("%.0f RPM\n", get_rpm());
		//int works = (1 << ACO) & ACSR;
		//printf("%d works", works);
	}
}