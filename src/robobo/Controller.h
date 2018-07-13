#ifndef ROBOBO_CONTROLLER_INCLUDED
#define ROBOBO_CONTROLLER_INCLUDED

#include "FreeRTOS.h"
#include "ActiveObject.h"
#include "Motor.h"
#include <functional>
#include "Arduino.h"

using namespace std;

class Controller : public ActiveObject
{
    private:
        Motor *a;
        Motor *b;
        TimerHandle_t measureTimer;

    public:
        Controller(Motor *a, Motor *b):
            a(a), b(b)
        {
            Serial.println("Controller start");

            measureTimer = createTimer(
                    std::function<void()>(bind(&Controller::alignAttempt, this)),
                    3000);
        }

        void alignAttempt(void)
        {
            int32_t pos = a->getCurrentPosition();
            b->setPosition(pos);
        }

};
#endif 
