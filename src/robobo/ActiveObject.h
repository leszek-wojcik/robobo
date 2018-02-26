#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

//#include "Arduino_FreeRTOS.h"
#include <FreeRTOS.h>
#include "timers.h"
#include <map>

class ActiveObject
{
    private:
        std::map<void *, void*> dataToTimer;

    public: 
        ActiveObject()
        {
        }

        void createTimer (
                void *data, 
                const TickType_t xTimerPeriod, 
                const UBaseType_t uxAutoReload );

        virtual void timerExpiry(void) = 0;
};

void ActiveObjectCallback( TimerHandle_t xTimer );

#endif
