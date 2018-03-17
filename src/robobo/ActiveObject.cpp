#include "Arduino.h"
#include "ActiveObject.h"
#include "MethodRequest.h"


ActiveObject::ActiveObject()
{
    mrQueue = xQueueCreate(20,sizeof(MRequest*));
    xTaskCreate( ActiveObjectTaskFunction,
            "AO", configMINIMAL_STACK_SIZE + 50 ,mrQueue , tskIDLE_PRIORITY, NULL);
}


TimerHandle_t ActiveObject::createTimer
     (   const std::function<void()> &f, 
         const TickType_t period, 
         const UBaseType_t reload )
{

    auto mr = new MRequest( this, f);

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

uint8_t ActiveObject::executeMethod(MRequest *mr)
{
    return xQueueSend(mrQueue, &mr, 0);
}

uint8_t ActiveObject::executeMethod(const std::function<void()> &f )
{
    auto mr = new MRequest(this, f);
    return xQueueSend(mrQueue, &mr, 0);
}

void ActiveObjectTimerCallback( TimerHandle_t xTimer )
{
    // At this point we are in timer task context. We need to pass on mr to
    // ActiveObject context via queue
    MRequest *mr = static_cast<MRequest*>(pvTimerGetTimerID(xTimer));
    ActiveObject *ao =  mr->getActiveObject();
    ao->executeMethod(mr);
}

void ActiveObjectTaskFunction( void *q)
{
    QueueHandle_t queue = q;
    MRequest *mr;

    for (;;) 
    {
        xQueueReceive( queue, &mr, portMAX_DELAY );

        (*(mr->func))();
        if (mr->isPersistent() == false )
        {
            delete mr;
            mr = NULL;
        }
    }
}
