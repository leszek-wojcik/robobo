#include "Globals.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"


Globals::Globals()
{

    dc1 = new DCMotor(19, 20, 22, 24, 2);
	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 0,   0, 0); 

    //Serial
    serialSpeed=115200;
}

Globals* Globals::getInstance() 
{
    if (Globals::instance == NULL)
        Globals::instance = new Globals();

    return Globals::instance;
}

Globals* Globals::createInstance()
{
    return Globals::getInstance();
}

Globals* Globals::instance=NULL; 
