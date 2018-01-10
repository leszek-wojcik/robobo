#include "Globals.h"
#include "Arduino.h"

Globals::Globals()
{

    dc1.encoderAPin = 19;
    dc1.encoderAVal = 0;
    dc1.encoderAPrevVal = 1;

    dc1.encoderBPin = 20;
    dc1.encoderBVal = 0;
    dc1.encoderBPrevVal = 1;

    dc1.encoderPosition = 0;

    dc1.hBridgeAPin = 22;
    dc1.hBridgeBPin = 24;
    dc1.voltagePin  = 2;


    dc2.encoderAPin=17;
    dc2.encoderAVal=0;
    dc2.encoderAPrevVal=1;

    dc2.encoderBPin=18;
    dc2.encoderBVal=0;
    dc2.encoderBPrevVal=1;

    dc2.encoderPosition = 0;

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
