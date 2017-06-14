#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "fastPWM.h"

void timer2_init(void)
{
	TCCR2A |= 1 << COM2A1; //non-inverting mode
	TCCR2A |= 1 << WGM20;
	TCCR2A |= 1 << WGM21; // fast pwm mode
	TCCR2B |= 1 << CS20;
	DDRB |= 1 << DDRB3;
	/*TCCR0B |= 1 << CS02; // prescaler
	TIFR0 |= OCF0A; //Timer/Counter0, Output Compare A Match Flag
	TIFR0 |= TOV0; //  Timer/Counter0, Overflow Flag
	TIMSK0 |= 1 << OCIE0A; //Timer/Counter0, Output Compare A Match Interrupt Enable
	TIMSK0 |= 1 << TOIE0; // Enable the TC0 overflow interrupt
	sei();	// Enable the interrupts globally*/
}

void set_duty_cycle(uint8_t duty)
{
	if (duty > 255)
		duty = 255;
	else if (duty < 0)
		duty = 0;
	OCR2A = duty;
	printf("%d\n", duty);
}
/*void init_led(void)
{
	DDRB |= 1 << DDRB3;
	//PORTD |= 1 << PORTD6;
}*/
