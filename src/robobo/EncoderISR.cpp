#include "Arduino.h"
#include "Robobo.h"
#include "EncoderISR.h"

void encoder1_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc1->encoderInterrupt();
}

void encoder2_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc2->encoderInterrupt();
}

