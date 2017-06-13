#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "freq_meas.h"

// TODO:
// Write the interrupt handlers
//INT0 External Interrupt Request 0
uint16_t cntr = 0;
const uint16_t cntr_max = 65535; //max 65535
uint16_t overflow_num = 0;
void interrupt_init(void)
{
	TIMSK1 |= 1 << ICIE1; // enable interrupt
	TIMSK1 |= 1 << TOIE1;
	TCCR1B |= 1 << CS11; // prescaler 8 
	//DDRD |= 1 << DDRD6;
	//PORTD |= 1 << PORTD6;
	//DDRB |= 1 << DDRB5;
	//PORTB |= 1 << PORTB5;
}
ISR(TIMER1_OVF_vect) {
	
	if (cntr < cntr_max) {
		
		cntr++;
	}
	else {
		
		cntr = 0;
		//PINB |= 1 << PINB5;
		overflow_num++;
	}
	
	
}


void freq_meas_init()
{
	/**************
	 * TC1 CONFIG *
	 **************/
	// TODO:
	// Configure the TC1 timer properly :)
	
	
}

// TODO:
// Write this function. It returns the measured frequency in Hz
float get_freq()
{
	
}