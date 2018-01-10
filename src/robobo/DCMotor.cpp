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

    encoderPosition += diff;
    
    calculatePID();

}

void DCMotor::calculatePID(void)
{
    int32_t diff = requestedPosition - encoderPosition;
    int32_t output = diff * kP;

    // TODO: Here we can avoid unnecessry calls to Arduino. by checking current
    // brdidge status
    if (output < 0 )
    {
        setDirectionLeft();
    }
    else
    {
        setDirectionRight();
    }

    output = abs(output);

    //need to scale target value to range 0-255 PWM
    if (output >255)
        output = 255;

    analogWrite(voltagePin, output);
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

void DCMotor::stop(void)
{
    analogWrite(voltagePin, 0);
    digitalWrite(hBridgeAPin, 0);
    digitalWrite(hBridgeBPin, 0);
}

void DCMotor::setPosition(int32_t x)
{
    requestedPosition = x;
}
int32_t DCMotor::getPosition()
{

    return encoderPosition;
}
