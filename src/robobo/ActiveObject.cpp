#include "ActiveObject.h"

void ActiveObject::createTimer
     (   void *data, 
         const TickType_t period, 
         const UBaseType_t reload )
{
// Need to assign data in order to execute call later on.
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
}
