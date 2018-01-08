#include "DCMotor.h"
#include "EncoderISR.h"
#include "grey.h"


void DCMotor::setPinModes(void)
{
	pinMode(encoderAPin, INPUT );
	pinMode(encoderBPin, INPUT );
    pinMode(hBridgeAPin, OUTPUT);
    pinMode(hBridgeAPin, OUTPUT);
    pinMode(voltagePin,  OUTPUT);
}


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

void DCMotor::setDirectionRight(void)
{
    digitalWrite(hBridgeAPin, 1);
    digitalWrite(hBridgeBPin, 0);
}

void DCMotor::setDirectionLeft(void)
{
    digitalWrite(hBridgeAPin, 0);
    digitalWrite(hBridgeBPin, 1);
}

void DCMotor::setVoltage(uint8_t val)
{
    analogWrite(voltagePin, val);
}


void DCMotor::setPosition(int32_t x)
{
    //TODO: implement
    return;
}
int32_t DCMotor::getPosition()
{

    //TODO: implement
    return 0;
}
