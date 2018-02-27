#ifndef FREERTOSMOCK_INCLUDED
#define FREERTOSMOCK_INCLUDED
#include "gmock/gmock.h"
#include <iostream>
#include "Arduino_FreeRTOS.h"
#include "timers.h"
using namespace std;

class FreeRTOSMock
{
    public: 
        FreeRTOSMock()
        {
        }

        virtual ~FreeRTOSMock(){}
        MOCK_METHOD5(xTimerCreate, 
            TimerHandle_t
             (  const char * const, 
                const TickType_t,
                const  UBaseType_t, 
                void * const , TimerCallbackFunction_t) );

        MOCK_METHOD1(pvTimerGetTimerID, void *(const TimerHandle_t xTimer));

        MOCK_METHOD5(xTimerGenericCommand, BaseType_t (TimerHandle_t , 
                                const BaseType_t , 
                                const TickType_t , 
                                BaseType_t * const , 
                                const TickType_t ) );

        MOCK_METHOD0 (xTaskGetTickCount, TickType_t ());
};

#endif
