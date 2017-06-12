#include <avr/io.h>
#include "fastPWM.h"
#include <util/delay.h>

int main(void)
{
	init_led();
	timer0_init();
	
	while (1) {
		set_duty_cycle(10);
		_delay_ms(1000);
		set_duty_cycle(100);
		_delay_ms(1000);
	}
}

