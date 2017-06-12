#include <avr/io.h>
#include "fastPWM.h"
#include <util/delay.h>
#include "ADC_driver.h"

int main(void)
{
	init_led();
	timer0_init();
	ADC_Init();
	//PORTD |= 1 << PORTD6;
	
	while (1) {
		uint16_t voltage = ADC_Read() / 4; 
		set_duty_cycle(voltage);
	}
}

