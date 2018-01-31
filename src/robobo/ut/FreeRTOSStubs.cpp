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
