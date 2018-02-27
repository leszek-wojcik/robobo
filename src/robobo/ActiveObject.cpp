#include "Arduino.h"
#include "ActiveObject.h"


ActiveObject::ActiveObject()
{
//    Serial.println("Task creation");
//    Serial.println((long)this);
}

TimerHandle_t ActiveObject::createTimer
     (   void *data, 
         const TickType_t period, 
         const UBaseType_t reload )
{

    return xTimerCreate
        ( "tmr",
          period,
          reload,
          this,
          ActiveObjectCallback );
}

void ActiveObjectCallback( TimerHandle_t xTimer )
{
    ActiveObject *ptr = static_cast<ActiveObject*>(pvTimerGetTimerID(xTimer));
    ptr->timerExpiry();
}
