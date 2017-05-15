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
	
	TCCR1B |= 1 << CS12;
	
	}

ISR(PCINT0_vect){
	

	
	/*while (1) {
		_delay_ms(100);
		PIND |= 1 << PIND0;
		PIND |= 1 << PIND1;
		_delay_ms(100);
		PIND |= 1 << PIND1;
		PIND |= 1 << PIND2;
		_delay_ms(100);
		PIND |= 1 << PIND2;
		PIND |= 1 << PIND3;
		_delay_ms(100);
		PIND |= 1 << PIND3;
		PIND |= 1 << PIND4;
		_delay_ms(100);
		PIND |= 1 << PIND4;
		PIND |= 1 << PIND0;
	}*/

}

int main(void)
{
	
	init();
	
	while (1) {
		
		if ((TIFR1 & 1<<TOIE1) == 1){
			PIND |= 1 << PIND0;
			PIND |= 1 << PIND1;
			TIFR1 |= 1 << TOIE1;
		}
					
	}
}