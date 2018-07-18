#ifndef ROBOBO_MOTOR_INCLUDED
#define ROBOBO_MOTOR_INCLUDED

#include "FreeRTOS.h"
#include "ActiveObject.h"
#include "ControlStrategy.h"

class Motor 
{
    public:
        virtual void setRequestedPosition(int32_t)=0;
        virtual int32_t getRequestedPosition()=0;
        virtual int32_t getCurrentPosition()=0;
        virtual void setDirectionLeft()=0;
        virtual void setDirectionRight()=0;
        virtual void emergencyStop()=0;
        virtual bool isEmergencyStopped()=0;

        virtual void encoderInterrupt()=0;
        virtual void reset()=0;

        virtual void setControlStrategy(ControlStrategy *)=0;
        virtual void enableControlStrategy() = 0;
        virtual void disableControlStrategy() = 0;

        virtual void report()=0;
        virtual void setVoltage(uint8_t)=0;

        virtual bool isCalibrationDone()=0;
        virtual void setCalibrationDone(bool)=0;

};
#endif 
