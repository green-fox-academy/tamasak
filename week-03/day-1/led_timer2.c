#include <avr/io.h>            // This header contains the definitions for the io registers
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU    16000000    // This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>        // This header contains the _delay_ms() function


void init(){
	DDRB &= ~(1 << DDRB7);	//gomb

	PCMSK0 |= 1 << PCINT7;
	PCICR |= 1 << PCIE0;
	sei();					//interrupt
		
	DDRD |= 1 << DDRD0;
	DDRD |= 1 << DDRD1;
	DDRD |= 1 << DDRD2;
	DDRD |= 1 << DDRD3;
	DDRD |= 1 << DDRD4;
	PIND |= 1 << PIND0;
	
	TCCR1B |= 1 << CS12;	//timer1 prescaler 1024
	TCCR1B |= 1 << CS10
	
	uint8_t cntr = 0;
	const uint8_t cntr_max = 4;
	int ledAllapot = 0; 
	int gomb = 1;
	
}

ISR(TIMER0_OVF_vect) {
	
	if (cntr < cntr_max) {
		
		cntr++;
	}
	else {
		
		cntr = 0;
			if (ledAllapot < 4){
				ledAllapot++;
				
			}
			else{
				ledAllapot = 0;
			}
	}
	
	
}

ISR(PCINT0_vect){
	
	gomb *= -1;
	

}

int main(void)
{
	
	init();
	
	while(1) {
		PORTD |= 1 << ledAllapot;
		PORTD &= 1 << (~(ledAllapot+1));
		PORTD &= 1 << (~(ledAllapot-1));
	}
}