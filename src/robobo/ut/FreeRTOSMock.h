#ifndef FREERTOSMOCK_INCLUDED
#define FREERTOSMOCK_INCLUDED
#include "gmock/gmock.h"
#include <iostream>
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
};

#endif
