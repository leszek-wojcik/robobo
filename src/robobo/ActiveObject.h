#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include <FreeRTOS.h>
#include "timers.h"
#include "queue.h"

class MethodRequestBase;

class ActiveObject
{
    public:
        QueueHandle_t mrQueue; 

        ActiveObject();

        TimerHandle_t createTimer (
                MethodRequestBase *mr, 
                const TickType_t xTimerPeriod, 
                const UBaseType_t uxAutoReload );

        uint8_t executeMethod(MethodRequestBase *mr);

        QueueHandle_t getQueue()
        {
            return mrQueue; 
        }


};

void ActiveObjectTimerCallback( TimerHandle_t xTimer );
void ActiveObjectTaskFunction( void * );

#endif
