#include "Globals.h"
#include "Arduino.h"

Globals::Globals()
{
    // Encoders
    encoder1aPin=19;
    encoder1aVal=0;

    encoder1bPin=20;
    encoder1bVal=0;

    encoder2aPin=17;
    encoder2aVal=0;

    encoder2bPin=18;
    encoder2bVal=0;

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
