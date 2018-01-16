#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"


Robobo::Robobo()
{

    dc1 = new DCMotor(19, 20, 22, 24, 2);
	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 0,   0, 0); 

    //Serial
    serialSpeed=115200;
}

Robobo* Robobo::getInstance() 
{
    if (Robobo::instance == NULL)
        Robobo::instance = new Robobo();

    return Robobo::instance;
}

Robobo* Robobo::createInstance()
{
    return Robobo::getInstance();
}

Robobo* Robobo::instance=NULL; 
