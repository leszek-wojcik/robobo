#ifndef ROBOBO_MOTOR_INCLUDED
#define ROBOBO_MOTOR_INCLUDED

#include "FreeRTOS.h"
#include "ActiveObject.h"
#include "ControlStrategy.h"

class Motor 
{
    public:
        virtual void setPosition(int32_t)=0;
        virtual int32_t getRequestedPosition()=0;
        virtual int32_t getCurrentPosition()=0;
        virtual void setDirectionLeft()=0;
        virtual void setDirectionRight()=0;
        virtual void stop()=0;
        virtual bool isStopped()=0;
        virtual void encoderInterrupt()=0;
        virtual void reset()=0;
        virtual void setControlStrategy(ControlStrategy *)=0;
        virtual void report()=0;
        virtual void setVoltage(uint8_t)=0;

};
#endif 
