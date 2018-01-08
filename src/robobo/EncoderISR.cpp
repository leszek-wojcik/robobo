#include "Arduino.h"
#include "Globals.h"
#include "EncoderISR.h"

void encoder1_ISR()
{
    Globals *i = Globals::instance; 
    i->dc1.encoderInterrupt();
}

void encoder2_ISR()
{
    Globals *i = Globals::instance; 
    i->dc2.encoderInterrupt();
}

