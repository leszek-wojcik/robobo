#include "Arduino.h"
#include "Robobo.h"
#include "ISR.h"

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

void limitSwitchDc1_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc1->stop();
}

void limitSwitchDc2_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc2->stop();
}
