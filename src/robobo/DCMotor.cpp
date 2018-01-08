#include "DCMotor.h"
#include "EncoderISR.h"
#include "grey.h"


void DCMotor::encoderInterrupt(void)
{
    int8_t diff;

    encoderAPrevVal = encoderAVal;
    encoderBPrevVal = encoderBVal;

    encoderAVal = digitalRead(encoderAPin);
    encoderBVal = digitalRead(encoderBPin);

    diff =  greyValue(encoderAVal, encoderBVal) - 
            greyValue(encoderAPrevVal, encoderBPrevVal);

    if (diff == 3)
    {
        diff = -1;
    }
    else if (diff == -3)
    {
        diff = 1;
    }

    encoderPos += diff;

}

void DCMotor::setPosition(int32_t x)
{
    return;
}
int32_t DCMotor::getPosition()
{
    return 0;
}
