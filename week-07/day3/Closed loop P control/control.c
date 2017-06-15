#include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"
#include "control.h"
#include "ADC_driver.h"

int16_t p_control(uint16_t rpm, float p_value)
{
	float error = (ADC_Read() * 5) - (float)rpm;
	int16_t signal_value = error * p_value;
	if (signal_value < -5000)
		signal_value = -5000;
	else if (signal_value > 5000)
		signal_value = 5000;
	return = signal_value;
}