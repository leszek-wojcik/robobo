#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"


Robobo::Robobo()
{
    //Serial
    serialSpeed=9600;
    instance = this;

}

void Robobo::createSetupV1(void)
{
    dc1 = new DCMotor(19, 20, 22, 24, 2);
	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 0,   0, 0); 

}

Robobo *Robobo::instance = NULL;
