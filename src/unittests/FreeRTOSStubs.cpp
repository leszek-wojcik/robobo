#include "Arduino_FreeRTOS.h"
#include "timers.h"
#include "RoboboTests.h"
#include <iostream>

using namespace std;

TimerHandle_t xTimerCreate(	const char * const pcTimerName,
        const TickType_t xTimerPeriodInTicks,
        const UBaseType_t uxAutoReload,
        void * const pvTimerID,
        TimerCallbackFunction_t pxCallbackFunction )
{

    return RoboboTests::rtos->xTimerCreate(pcTimerName, xTimerPeriodInTicks,
            uxAutoReload, pvTimerID, pxCallbackFunction);
}

void *pvTimerGetTimerID( const TimerHandle_t xTimer )
{

    return RoboboTests::rtos->pvTimerGetTimerID(xTimer);
}

BaseType_t xTimerGenericCommand( TimerHandle_t xTimer, 
                                const BaseType_t xCommandID, 
                                const TickType_t xOptionalValue, 
                                BaseType_t * const pxHigherPriorityTaskWoken, 
                                const TickType_t xTicksToWait ) 
{

    return RoboboTests::rtos-> xTimerGenericCommand( xTimer, xCommandID,
            xOptionalValue, pxHigherPriorityTaskWoken, xTicksToWait ) ;
}

TickType_t xTaskGetTickCount( void )
{
    return RoboboTests::rtos->xTaskGetTickCount();
}

QueueHandle_t xQueueGenericCreate(  const UBaseType_t uxQueueLength, 
                                    const UBaseType_t uxItemSize, 
                                    const uint8_t ucQueueType )
{
    return RoboboTests::rtos->xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
}

BaseType_t xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeeking )
{
    return RoboboTests::rtos-> xQueueGenericReceive(xQueue,pvBuffer,xTicksToWait,xJustPeeking);
}

BaseType_t xTaskGenericCreate( TaskFunction_t pxTaskCode, const char * const pcName, const uint16_t usStackDepth, void * const pvParameters, UBaseType_t uxPriority, TaskHandle_t * const pxCreatedTask, StackType_t * const puxStackBuffer, const MemoryRegion_t * const xRegions ) 
{
    return RoboboTests::rtos-> xTaskGenericCreate( pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, puxStackBuffer, xRegions );
}

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition )
{
    return RoboboTests::rtos-> xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
}

TaskHandle_t xTaskGetCurrentTaskHandle( void ) 
{
    return RoboboTests::rtos->xTaskGetCurrentTaskHandle();
}

uint32_t ulTaskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait ) 
{
    return RoboboTests::rtos->ulTaskNotifyTake( xClearCountOnExit, xTicksToWait );
}

BaseType_t xTaskGenericNotify( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotificationValue ) 
{
    return RoboboTests::rtos->xTaskGenericNotify( xTaskToNotify, ulValue, eAction, pulPreviousNotificationValue ) ;
}
