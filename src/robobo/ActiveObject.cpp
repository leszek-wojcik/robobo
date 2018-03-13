#include "Arduino.h"
#include "ActiveObject.h"
#include "MethodRequest.h"


ActiveObject::ActiveObject()
{
    mrQueue = xQueueCreate(20,sizeof(MethodRequestBase*));
    xTaskCreate( ActiveObjectTaskFunction,
            "AO", configMINIMAL_STACK_SIZE + 50 ,mrQueue , tskIDLE_PRIORITY, NULL);
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
    return xQueueSend(mrQueue, &mr, 0);
}

void ActiveObjectTimerCallback( TimerHandle_t xTimer )
{
    // At this point we are in timer task context. We need to pass on mr to
    // ActiveObject context via queue
    ActiveObject *ao;
    MethodRequestBase *mr = static_cast<MethodRequestBase*>(pvTimerGetTimerID(xTimer));
    ao =(ActiveObject*) mr->getActiveObject();
    ao->executeMethod(mr);
}

void ActiveObjectTaskFunction( void *q)
{
    QueueHandle_t queue = q;
    void *recvData;
    MethodRequestBase *mr;

    for (;;) 
    {
        xQueueReceive( queue, &recvData, portMAX_DELAY );

        mr = static_cast<MethodRequestBase*>(recvData);

        mr->execute();
        if (mr->isPersistent() == false )
        {
            delete mr;
            mr = NULL;
        }
    }
}
