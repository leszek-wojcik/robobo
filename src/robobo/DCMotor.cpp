#include "DCMotor.h"
#include "EncoderISR.h"
#include "grey.h"
#include "MethodRequest.h"
#include "Robobo.h"
#include <functional>

using namespace std;


DCMotor::DCMotor(   uint8_t encoderAPinV, 
                    uint8_t encoderBPinV, 
                    uint8_t hBridgeAPinV,
                    uint8_t hBridgeBPinV,
                    uint8_t voltagePinV,
                    ControlStrategy *strategy):
    encoderAPin(encoderAPinV),
    encoderBPin(encoderBPinV),
    hBridgeAPin(hBridgeAPinV),
    hBridgeBPin(hBridgeBPinV),
    voltagePin (voltagePinV ),
    control(strategy)
{
    setPinModes();
    reset();


    triggerTimer = createTimer(
            std::function<void()>(bind(&DCMotor::updateControl, this)),
            1,
            1);
    xTimerStart(triggerTimer,0);

}

void DCMotor::enableReports(TickType_t period)
{
    reportTimer = createTimer( 
        std::function<void()>(bind(&DCMotor::reportMethod,this)),
        period,
        true);
    xTimerStart(reportTimer,0);
}

void DCMotor::reportMethod(void)
{
    Robobo *i = Robobo::instance; 
    Serial.println(" - DC Report - ");
    Serial.print(" AO ");
    Serial.println((long)(ActiveObject*)this );
    Serial.print(" Id ");
    Serial.println((long)this);
    Serial.print(" Encoder Position ");
    Serial.println(encoderPosition);
    Serial.print(" Requested Position ");
    Serial.println(requestedPosition);
    Serial.print(" DC Output ");
    Serial.println(dcOutput);
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
    dcOutput = 0;
}

void DCMotor::setControlStategy(ControlStrategy *strategy)
{
    control = strategy;
}

void DCMotor::updateControl(void)
{
    this->encoderInterrupt();
}


void DCMotor::encoderInterrupt(void)
{
    int8_t posUpdate;
    int32_t diff;

    encoderAPrevVal = encoderAVal;
    encoderBPrevVal = encoderBVal;

    encoderAVal = digitalRead(encoderAPin);
    encoderBVal = digitalRead(encoderBPin);

    posUpdate =  greyValue(encoderAVal, encoderBVal) - 
            greyValue(encoderAPrevVal, encoderBPrevVal);

    if (posUpdate == 3)
    {
        posUpdate = -1;
    }
    else if (posUpdate == -3)
    {
        posUpdate = 1;
    }

    encoderPosition += posUpdate;
    
    diff = requestedPosition - encoderPosition;

    dcOutput = control->calculateControl(diff);

    if (dcOutput < 0 )
    {
        setDirectionLeft();
    }
    else
    {
        setDirectionRight();
    }

    dcOutput = abs(dcOutput);

    //need to scale target value to range 0-255 PWM
    if (dcOutput >255)
        dcOutput = 255;

    analogWrite(voltagePin, dcOutput);

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
