#ifndef ROBOBO_CONTROLLER_INCLUDED
#define ROBOBO_CONTROLLER_INCLUDED

#include "FreeRTOS.h"
#include "ActiveObject.h"
#include "Motor.h"
#include <functional>
#include "Arduino.h"
#include "DisplayManager.h"

using namespace std;

class Controller : public ActiveObject
{
    private:
        Motor *a;
        Motor *b;
        TimerHandle_t measureTimer;
        DisplayManager *disp;
        int displayHandle;

    public:
        Controller(Motor *a, Motor *b, DisplayManager *disp):
            a(a), b(b), disp(disp), ActiveObject("cntrl_task")
        {
            Serial.println("Controller start");

            disp->registerDisplayData(&displayHandle,"DC1 Position","");


            measureTimer = createTimer(
                    std::function<void()>(bind(&Controller::alignAttempt, this)),
                    5000);
        }

        void alignAttempt(void)
        {
            int32_t pos = a->getCurrentPosition();
            a->setPosition(pos-1000);

            disp->executeMethod(std::function<void()>(
                        std::bind(&DisplayManager::postData, disp, displayHandle, pos)));
        }

};
#endif 
