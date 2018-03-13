#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"
#include "PID.h"


Robobo::Robobo()
{
    //Serial
    serialSpeed=9600;
    instance = this;
    dc1 = NULL;
    dc2 = NULL;
    pid1 = NULL;
    pid2 = NULL;

}

void Robobo::createSetupV1(void)
{
    pid1 = new PID(10,0.000001,0);
    dc1 = new DCMotor(19, 20, 22, 24, 2, pid1);
    dc1->enableReports(3000);

	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

//    pid2 = new PID(0,0,0);
//    dc2 = new DCMotor(17, 18, 0, 0, 0, pid2); 
//
//    if (dc1 == NULL || dc2 == NULL)
//    {
//        Serial.println(" Allocation problem ");
//    }
}

Robobo *Robobo::instance = NULL;
