#include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"
#include "control.h"
#include "ADC_driver.h"

int16_t p_control(uint16_t rpm, float p_value)
{
	float error = (float)rpm - reference value;
	return = error * p_value;	
}