#ifndef ACTIVEOBJECT_INCLUDED
#define ACTIVEOBJECT_INCLUDED

#include <FreeRTOS.h>
#include "timers.h"
#include "queue.h"
#include <functional>
#include <string>

using namespace std;

class MethodRequestBase;
class MRequest;

class ActiveObject
{
    public:
        QueueHandle_t mrQueue; 

        ActiveObject(string name="\0",UBaseType_t priority=tskIDLE_PRIORITY);

        TimerHandle_t createTimer (  
                const std::function<void()> &f, 
                const TickType_t period, 
                const UBaseType_t reload );

        uint8_t executeMethod(const std::function<void()> &);

        QueueHandle_t getQueue()
        {
            return mrQueue; 
        }

    private:
        uint8_t executeMethod(MRequest *mr);

    friend void ActiveObjectTimerCallback( TimerHandle_t xTimer );
    friend void ActiveObjectTaskFunction( void * );

};

void ActiveObjectTimerCallback( TimerHandle_t xTimer );
void ActiveObjectTaskFunction( void * );

#endif
