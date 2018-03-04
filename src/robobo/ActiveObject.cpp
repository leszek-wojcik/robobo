#include "Arduino.h"
#include "ActiveObject.h"
#include "MethodRequest.h"


ActiveObject::ActiveObject()
{
}

TimerHandle_t ActiveObject::createTimer
     (   MethodRequestBase *mr, 
         const TickType_t period, 
         const UBaseType_t reload )
{

    return xTimerCreate
        ( "tmr",
          period,
          reload,
          mr,
          ActiveObjectTimerCallback );
}

void ActiveObjectTimerCallback( TimerHandle_t xTimer )
{
    MethodRequestBase *mr = static_cast<MethodRequestBase*>(pvTimerGetTimerID(xTimer));
    mr->execute();
}
