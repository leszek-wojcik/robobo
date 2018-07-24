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
        DisplayManager *disp;
        TimerHandle_t initTimer;
        TimerHandle_t calibrationTimer;
        int secondsHandle;
        int minutesHandle;
        int seconds;
        int minutes;
        int secondPos;
        int minutesPos;


    public:
        Controller(Motor *a, Motor *b, DisplayManager *disp):
            a(a), 
            b(b), 
            secondPos(0), 
            minutesPos(0), 
            seconds(0), 
            disp(disp), 
            ActiveObject("cntrl_task", tskIDLE_PRIORITY)
        {
            Serial.println("Controller start");
 

            disp->registerDisplayData( &secondsHandle, "Seconds", "");
            disp->registerDisplayData( &minutesHandle, "Minutes", "");

            initTimer = createOneTimeTimer(
                    std::function<void()>(bind(&Controller::controllerFunc, this)),
                    3000);
        }


        void controllerFunc(void)
        {
            Serial.println("Controler Init");

            a->emergencyStop();
            a->setCalibrationDone(false);
            a->setDirectionRight();
            a->setVoltage(30);

            b->emergencyStop();
            b->setCalibrationDone(false);
            b->setDirectionRight();
            b->setVoltage(30);

            calibrationTimer = createTimer(
                    std::function<void()>(bind(&Controller::calibrationCheck, this)),
                    3000);


        }

        void calibrationCheck()
        {
            Serial.println("Calibration check");

            if (b->isEmergencyStopped())
            {
                b->reset();
                b->enableControlStrategy();
            }

            if (a->isEmergencyStopped())
            {
                a->reset();
                a->enableControlStrategy();
            }

            if(a->isEmergencyStopped() && b->isEmergencyStopped())
            {
                stopTimer(calibrationTimer);
                calibrationTimer = createTimer(
                        std::function<void()>(bind(&Controller::mainFunc, this)),
                        1000);
            }
        }

        void mainFunc()
        {

            seconds++;
            minutes = seconds/60;

            secondPos = -140 * seconds;
            minutesPos = -140 * minutes;
            a->setRequestedPosition(secondPos);
            b->setRequestedPosition(minutesPos);

            auto f = std::function<void()>(std::bind(&DisplayManager::postData,disp,secondsHandle,abs(seconds%60) ));
            disp->executeMethod (f);
            f = std::function<void()>(std::bind(&DisplayManager::postData,disp,minutesHandle,minutes));
            disp->executeMethod (f);
        }


};
#endif 
