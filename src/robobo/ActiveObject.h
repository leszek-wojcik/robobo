#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include <FreeRTOS.h>
#include "timers.h"
#include "queue.h"
#include "MethodRequest.h"

class ActiveObject
{
    private:
        QueueHandle_t queue; 

    public: 
        ActiveObject();

        TimerHandle_t createTimer (
                MethodRequestBase *mr, 
                const TickType_t xTimerPeriod, 
                const UBaseType_t uxAutoReload );

        uint8_t executeMethod(MethodRequestBase *mr);

};

void ActiveObjectTimerCallback( TimerHandle_t xTimer );
void ActiveObjectTaskFunction( void * );

#endif
