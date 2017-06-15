#ifndef CONTROL_H_
#define CONTROL_H_
int16_t p_control(uint16_t rpm, float p_value);
int16_t pi_control(uint16_t rpm, float p_value, float i_value);



#endif