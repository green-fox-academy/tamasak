/*
 * fastPWM.h
 *
 * Created: 6/12/2017 1:03:10 AM
 *  Author: Ákos
 */ 
#define F_CPU    16000000

#ifndef FASTPWM_H_
#define FASTPWM_H_
void timer2_init(void);
void set_duty_cycle(uint8_t duty);
//void init_led(void);
//uint8_t count = 0;




#endif /* FASTPWM_H_ */