#include "Arduino.h"
#include "ActiveObject.h"
#include "MethodRequest.h"


ActiveObject::ActiveObject()
{
    queue = xQueueCreate(10,sizeof(void*));
    xTaskCreate( ActiveObjectTaskFunction,
            "AO", configMINIMAL_STACK_SIZE + 50 ,queue , tskIDLE_PRIORITY, NULL);
}

TimerHandle_t ActiveObject::createTimer
     (   MethodRequestBase *mr, 
         const TickType_t period, 
         const UBaseType_t reload )
{
    if (reload == 1 )
    {
        mr->setPersistent(true);
    }

    return xTimerCreate
        ( "tmr",
          period,
          reload,
          mr,
          ActiveObjectTimerCallback );
}

uint8_t ActiveObject::executeMethod(MethodRequestBase *mr)
{
    return xQueueSend(queue, mr, 0);
}

void ActiveObjectTimerCallback( TimerHandle_t xTimer )
{
    MethodRequestBase *mr = static_cast<MethodRequestBase*>(pvTimerGetTimerID(xTimer));
    mr->execute();
}

void ActiveObjectTaskFunction( void *q)
{
    QueueHandle_t queue = q;
    MethodRequestBase *mr;

    for (;;) 
    {
        xQueueReceive( queue, &mr, portMAX_DELAY );
        mr->execute();
        if (mr->isPersistent() == false )
        {
            delete mr;
            mr = NULL;
        }
    }
}
