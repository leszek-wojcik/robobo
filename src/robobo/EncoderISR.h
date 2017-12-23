#ifndef ENCODERISR_INCLUDED
#define ENCODERISR_INCLUDED
#include "Arduino.h"

void encoder1_ISR();
void encoder2_ISR();
uint8_t greyValue(uint8_t a, uint8_t b);
#endif
