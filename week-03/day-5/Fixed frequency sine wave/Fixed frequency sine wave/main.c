#include "ADC_driver.h"
#include "UART_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "MCP4821_driver.h"


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
#define PI 3.14159265

volatile uint16_t cntr;
const uint16_t cntr_max = 2000;
float result;

void SystemInit() {
	// Call the DAC driver init function
	MCP4821_Init();
	// Initialize the LED pin as output
	LED_DDR |= 1 << LED_DDR_POS;
	// Set the LED to off as deafault
	LED_PORT &= ~(1 << LED_PORT_POS);

	// Call the DAC driver init function
	ADC_Init();

	// Call the UART driver init function
	// Keep in mind that the UART will run at 115200 baud/sec
	UART_Init();

	// Enable interrupts globally, UART uses interrupts
	TCCR0B |= 1 << CS02;
	TCCR0B &= ~(1 << CS01);
	TCCR0B |= 1 << CS00;

	// Set OC register to a default value
	TCCR0A |= 1 << WGM01;
	OCR0A = 255;

	// Enable OCR0A interrupt
	TIMSK0 |= 1 << OCIE0A;

	// Enable interrupts globally
	sei();
}

ISR(TIMER0_COMPA_vect) {
	
	if(cntr < cntr_max) {
		cntr++;
		} else {
		cntr = 0;
	}
	float degree = cntr * 0.001 * PI;
	result = sin(degree);
}

int main(void) {
	uint16_t adc_data;

	// Don't forget to call the init function :)
	SystemInit();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	/*
	char buffer[20];
	double voltage;
	gets(buffer);
	voltage = atof (buffer);
	if (voltage <0) {
		voltage = 0;		
	}
	if (voltage > 4.096) {
		voltage = 4.096;
	}*/
	
	// DAC test data
	// gain = 2, data is 0xFFF so the output voltage should be 4.048V
	MCP4821_Data_t DAC_data;
	DAC_data.start_zero = 0;
	DAC_data.dont_care = 0;
	DAC_data.gain = 0;
	DAC_data.shutdown = 1;
	//DAC_data.data = voltage*1024;
	//DAC_data.data = 0xFFF;

	// Send the data structure
	MCP4821_SendData(&DAC_data);
	
	int16_t sinwave;
	
	while (1) {
		sinwave = result*50;
		//printf("%d\r\n", sinwave);
		// ADC tester code
		//adc_data = ADC_Read();
		//printf("%d\r\n", (DAC_data.data));
		//UART_SendCharacter(DAC_data.data >> 2);
		//_delay_ms(10);
		UART_SendCharacter(sinwave);
	}
}
