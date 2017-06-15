#include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"
#include "control.h"
#include "ADC_driver.h"

int16_t p_control(uint16_t rpm, float p_value)
{
	float error = (float)rpm - (ADC_Read() * 5);
	int16_t signal_value = error * p_value;
	return signal_value;
}