#include "Arduino.h"
#include "ActiveObject.h"
#include "MethodRequest.h"
#include <iostream>


ActiveObject::ActiveObject(string name, UBaseType_t priority):
    name(name)
{
    TaskHandle_t newTask;
    mrQueue = xQueueCreate(20,sizeof(MRequest*));

    xTaskCreate( ActiveObjectTaskFunction,
            name.c_str(), 
            configMINIMAL_STACK_SIZE + 50,
            mrQueue, 
            priority,
            &newTask);

    taskHandles[this] = newTask;

    Serial.print ("tworze: ");
    Serial.println ((long)newTask);
}


TimerHandle_t ActiveObject::createTimer
     (   const std::function<void()> &f, 
         const TickType_t period )
{
    TimerHandle_t returnTimer;
    auto mr = new MRequest( this, f);
    mr->setPersistent(true);

    returnTimer = xTimerCreate
        ( "tmr",
          period,
          1,
          mr,
          ActiveObjectTimerCallback );

    xTimerStart(returnTimer,0);

    return returnTimer;
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

uint32_t ActiveObject::executeMethodSynchronously(const std::function<void()> &f)
{
    TaskHandle_t callerHandle = xTaskGetCurrentTaskHandle();
    auto mr = new MRequest(this, f, callerHandle);
    xQueueSend(mrQueue, &mr, 0);
    uint32_t returnValue;

    // block until notification from receiver task
    returnValue =  ulTaskNotifyTake( pdTRUE, portMAX_DELAY ); 

    return returnValue;
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

        // If callerID is set this mean that calling task expects notification
        // after function call end
        if (mr->callerID != NULL)
        {

           xTaskNotifyGive( mr->callerID ); 
        }

        if (mr->isPersistent() == false )
        {
            delete mr;
            mr = NULL;
        }
    }
}

std::map<ActiveObject*, TaskHandle_t> ActiveObject::taskHandles;

