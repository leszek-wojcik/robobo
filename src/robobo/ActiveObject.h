#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include "Arduino_FreeRTOS.h"
#include "timers.h"

class ActiveObject
{
    public: 
        ActiveObject()
        {
        }

        void startTimer (
                void *data, 
                const TickType_t xTimerPeriod, 
                const UBaseType_t uxAutoReload );

        virtual void timerExpiry(void) = 0;
};

void ActiveObjectCallback( TimerHandle_t xTimer );

#endif
