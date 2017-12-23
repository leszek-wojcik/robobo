#include "Arduino.h"
#include "Globals.h"
#include "EncoderISR.h"

void encoder1_ISR()
{
    int8_t diff;
    Globals *i = Globals::instance; 

    i->encoder1aPrevVal = i->encoder1aVal;
    i->encoder1bPrevVal = i->encoder1bVal;

    i->encoder1aVal = digitalRead(i->encoder1aPin);
    i->encoder1bVal = digitalRead(i->encoder1bPin);

    diff =  greyValue(i->encoder1aVal, i->encoder1bVal) - 
            greyValue(i->encoder1aPrevVal, i->encoder1bPrevVal);

    if (diff == 3)
    {
        diff = -1;
    }
    else if (diff == -3)
    {
        diff = 1;
    }
}


void encoder2_ISR()
{
    Globals::instance->encoder2aVal = digitalRead(Globals::instance->encoder2aPin);
    Globals::instance->encoder2bVal = digitalRead(Globals::instance->encoder2aPin);
}

uint8_t greyLookup[2][2] = {{2,1},{3,0}};

uint8_t greyValue(uint8_t a, uint8_t b)
{
    return greyLookup[a][b];
}
