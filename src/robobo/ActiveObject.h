#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include "Arduino_FreeRTOS.h"
#include "timers.h"

class ActiveObject
{
    void startTimer (
            void *method, 
            const TickType_t xTimerPeriod, 
            const UBaseType_t uxAutoReload );
};

void ActiveObjectCallback( TimerHandle_t xTimer );

#endif
