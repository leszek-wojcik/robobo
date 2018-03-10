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

        MOCK_METHOD0(xTaskGetTickCount, TickType_t ());

        MOCK_METHOD3( xQueueGenericCreate, QueueHandle_t (const UBaseType_t,
                                const UBaseType_t ,
                                const uint8_t ) );

        MOCK_METHOD4( xQueueGenericReceive, BaseType_t ( QueueHandle_t , 
                                void * const , 
                                TickType_t , 
                                const BaseType_t ) );

        MOCK_METHOD8( xTaskGenericCreate, BaseType_t ( TaskFunction_t , 
                                const char * const , 
                                const uint16_t , 
                                void * const , 
                                UBaseType_t , 
                                TaskHandle_t * const , 
                                StackType_t * const , 
                                const MemoryRegion_t * const ) );

        MOCK_METHOD4( xQueueGenericSend, BaseType_t ( QueueHandle_t , 
                                const void * const , 
                                TickType_t , 
                                const BaseType_t ));

};
#endif
