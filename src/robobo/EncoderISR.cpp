#include "Arduino.h"
#include "Globals.h"
#include "EncoderISR.h"

void encoder1_ISR()
{
    int8_t diff;
    Globals *i = Globals::instance; 

    i->dc1.encoderAPrevVal = i->dc1.encoderAVal;
    i->dc1.encoderBPrevVal = i->dc1.encoderBVal;

    i->dc1.encoderAVal = digitalRead(i->dc1.encoderAPin);
    i->dc1.encoderBVal = digitalRead(i->dc1.encoderBPin);

    diff =  greyValue(i->dc1.encoderAVal, i->dc1.encoderBVal) - 
            greyValue(i->dc1.encoderAPrevVal, i->dc1.encoderBPrevVal);

    if (diff == 3)
    {
        diff = -1;
    }
    else if (diff == -3)
    {
        diff = 1;
    }

    i->dc1.encoderPos += diff;
}


void encoder2_ISR()
{
    int8_t diff;
    Globals *i = Globals::instance; 

    i->dc2.encoderAPrevVal = i->dc2.encoderAVal;
    i->dc2.encoderBPrevVal = i->dc2.encoderBVal;

    i->dc2.encoderAVal = digitalRead(i->dc2.encoderAPin);
    i->dc2.encoderBVal = digitalRead(i->dc2.encoderBPin);

    diff =  greyValue(i->dc2.encoderAVal, i->dc2.encoderBVal) - 
            greyValue(i->dc2.encoderAPrevVal, i->dc2.encoderBPrevVal);

    if (diff == 3)
    {
        diff = -1;
    }
    else if (diff == -3)
    {
        diff = 1;
    }

    i->dc2.encoderPos += diff;
}

uint8_t greyLookup[2][2] = {{2,1},{3,0}};

uint8_t greyValue(uint8_t a, uint8_t b)
{
    return greyLookup[a][b];
}
