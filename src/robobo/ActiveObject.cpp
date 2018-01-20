#include "ActiveObject.h"

void ActiveObject::startTimer
    (   void *method, 
        const TickType_t period, 
        const UBaseType_t reload )
{
    xTimerCreate
        ( "tmr",
          period,
          reload,
          this,
          ActiveObjectCallback );
}

void ActiveObjectCallback( TimerHandle_t xTimer )
{
    ActiveObject *ptr = static_cast<ActiveObject*>(pvTimerGetTimerID(xTimer));
    //TODO: exec function
}
