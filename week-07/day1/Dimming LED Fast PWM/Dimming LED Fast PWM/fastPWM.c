#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "fastPWM.h"

void timer0_init(void)
{
	TCCR0A |= 1 << COM0A1; //non-inverting mode
	TCCR0A |= 1 << WGM00;
	TCCR0A |= 1 << WGM01;
	//TCCR0B |= 1 << CS00;
	//TCCR0B |= 1 << CS02; // prescaler
	TIMSK0 |= 1 << TOIE0; // Enable the TC0 overflow interrupt
	sei();	// Enable the interrupts globally
}

void set_duty_cycle(uint8_t duty)
{
	if (duty > 100)
		duty = 100;
	else if (duty < 0)
		duty = 0;
	OCR0A = duty;
}
void init_led(void)
{
	DDRD |= 1 << DDRD6;
	PORTD |= 1 << PORTD6;
}
