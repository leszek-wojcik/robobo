#ifndef ROBOBO_MOTOR_INCLUDED
#define ROBOBO_MOTOR_INCLUDED

#include "FreeRTOS.h"
#include "ActiveObject.h"
#include "ControlStrategy.h"

class Motor 
{
    public:
        virtual void setPosition(int32_t)=0;
        virtual int32_t getCurrentPosition()=0;
        virtual void stop(void)=0;
        virtual void encoderInterrupt(void)=0;
        virtual void reset(void)=0;
        virtual void setControlStrategy(ControlStrategy *)=0;
        virtual void report(void)=0;

};
#endif 
