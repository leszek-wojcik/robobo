#include "Arduino.h"
#include "Robobo.h"
#include "ISR.h"

void encoderDc1_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc1->encoderInterrupt();
}

void encoderDc2_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc2->encoderInterrupt();
}

void limitSwitchDc1_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc1->emergencyStop();
    i->dc1->setCalibrationDone(true);
    Serial.print("ISR1");
}

void limitSwitchDc2_ISR()
{
    Robobo *i = Robobo::instance; 
    i->dc2->emergencyStop();
    i->dc2->setCalibrationDone(true);
    Serial.print("ISR2");
}
