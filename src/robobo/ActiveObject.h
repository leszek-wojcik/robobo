#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include <FreeRTOS.h>
#include "timers.h"
#include "MethodRequest.h"
#include <map>

class ActiveObject
{
    private:
        std::map<ActiveObject *, void*> timerToData;

    public: 
        ActiveObject();

        TimerHandle_t createTimer (
                MethodRequestBase *mr, 
                const TickType_t xTimerPeriod, 
                const UBaseType_t uxAutoReload );

        virtual void timerExpiry(void) = 0;
};

void ActiveObjectCallback( TimerHandle_t xTimer );

#endif
