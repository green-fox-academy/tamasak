#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "freq_meas.h"
#define F_CPU 16000000UL

// TODO:
// Write the interrupt handlers
//INT0 External Interrupt Request 0
volatile const uint16_t cntr_max = 65535; //max 65535
volatile uint16_t overflow_num = 0;
volatile uint16_t overflow_tmp = 0;
volatile uint16_t cnt_state = 0;
volatile uint16_t cnt_state_prev = 0;
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
ISR(TIMER1_OVF_vect) 
{
	overflow_num++;
}
ISR(TIMER1_CAPT_vect)
{
	cnt_state_prev = cnt_state;
	cnt_state = ICR1;
	overflow_tmp = overflow_num;
	overflow_num = 0;
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
	cli();
	int16_t ovf = overflow_tmp;
	overflow_tmp = 0;
	uint16_t state = cnt_state;
	uint16_t state_prev = cnt_state_prev;
	sei();
	cnt_state = ICR1; // interruptnal a szamlalo allasa
	uint32_t steps = ovf * 65535 + state - state_prev;
	//float period_time = (float)steps * (8 / F_CPU); // 8 -> prescaler
	float freq = F_CPU / 8 / (float)steps;
	//printf("%d %d %d %u\n", cnt_state, cnt_state_prev, ovf, steps);
	return (freq);
}