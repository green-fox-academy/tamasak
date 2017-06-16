#include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"
#include "control.h"
#include "ADC_driver.h"

float integral = 0;
int16_t p_control(uint16_t rpm, float p_value)
{
	float error = (ADC_Read() * 5) - (float)rpm;
	int16_t signal_value = error * p_value;
	if (signal_value < -5000)
	signal_value = -5000;
	else if (signal_value > 5000)
	signal_value = 5000;
	return signal_value;
}
int16_t pi_control(uint16_t rpm, float p_value, float i_value)
{
	float error = (ADC_Read() * 5) - (float)rpm;
	integral += error;
	int16_t signal_value = error * p_value + integral * i_value;
	if (signal_value < 0) {
		signal_value = 0;
		integral -= error;
	} else if (signal_value > 255) {
		signal_value = 255;
		integral -= error;
	}
	return signal_value;
}