#include "DCMotor.h"
#include "EncoderISR.h"
#include "grey.h"
#include "MethodRequest.h"
#include "Robobo.h"

using namespace std;


DCMotor::DCMotor(   uint8_t encoderAPinV, 
                    uint8_t encoderBPinV, 
                    uint8_t hBridgeAPinV,
                    uint8_t hBridgeBPinV,
                    uint8_t voltagePinV ):
    encoderAPin(encoderAPinV),
    encoderBPin(encoderBPinV),
    hBridgeAPin(hBridgeAPinV),
    hBridgeBPin(hBridgeBPinV),
    voltagePin (voltagePinV )
{
    setPinModes();
    reset();

    auto updateControlMR = MR0(DCMotor, *this, updateControl);
    triggerTimer = createTimer(updateControlMR,1,1);
    xTimerStart(triggerTimer,0);

}

void DCMotor::enableReports(TickType_t period)
{
    auto reportMR = MR0(DCMotor, *this, reportMethod);
    reportTimer = createTimer(reportMR,period,1);
    xTimerStart(reportTimer,0);
}

void DCMotor::reportMethod(void)
{
    Robobo *i = Robobo::instance; 
    Serial.println(" - DC Report - ");
    Serial.print(" Id ");
    Serial.println((long)this);
    Serial.print(" Encoder Position ");
    Serial.println(encoderPosition);
    Serial.print(" Requested Position ");
    Serial.println(requestedPosition);
    Serial.println(" ------------- ");
}

void DCMotor::setPinModes(void)
{
	pinMode(encoderAPin, INPUT );
	pinMode(encoderBPin, INPUT );
    pinMode(hBridgeAPin, OUTPUT);
    pinMode(hBridgeBPin, OUTPUT);
    pinMode(voltagePin,  OUTPUT);
}

void DCMotor::reset(void)
{
    encoderAVal = 0;
    encoderBVal = 0;
    encoderAPrevVal = 1;
    encoderBPrevVal = 1;
    encoderPosition = 0;
    requestedPosition = 0;
    direction = 0;
    

    //TODO: This is temporary place
    controllerIntegral = 0;
    kP = 5;
    
}

void DCMotor::updateControl(void)
{
    this->encoderInterrupt();
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
    if (direction <= 0)
    {
        digitalWrite(hBridgeAPin, 1);
        digitalWrite(hBridgeBPin, 0);
        direction = 1;
    }
}

void DCMotor::setDirectionLeft(void)
{
    if (direction >= 0)
    {
        digitalWrite(hBridgeAPin, 0);
        digitalWrite(hBridgeBPin, 1);
        direction = -1;
    }
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
