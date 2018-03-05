#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"


Robobo::Robobo()
{
    //Serial
    serialSpeed=9600;
    instance = this;
    dc1 = NULL;
    dc2 = NULL;

}

void Robobo::createSetupV1(void)
{
    dc1 = new DCMotor(19, 20, 22, 24, 2);
    dc1->enableReports(2000);

	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 0,   0, 0); 

    if (dc1 == NULL || dc2 == NULL)
    {
        Serial.println(" Allocation problem ");
    }
}

Robobo *Robobo::instance = NULL;
