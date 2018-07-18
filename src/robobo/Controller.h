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
        TimerHandle_t initTimer;
        TimerHandle_t calibrationTimer;
        int dc1PosHandle;
        int controlerHandle;
        int seconds;
        int pos;

    public:
        Controller(Motor *a, Motor *b):
            a(a), b(b), pos(0), seconds(0), ActiveObject("cntrl_task", tskIDLE_PRIORITY)
        {
            Serial.println("Controller start");


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
            a->setVoltage(19);

            calibrationTimer = createTimer(
                    std::function<void()>(bind(&Controller::calibrationCheck, this)),
                    3000);


        }

        void calibrationCheck()
        {
            Serial.println("Calibration check");
            if (a->isEmergencyStopped())
            {
                a->reset();
                stopTimer(calibrationTimer);
                calibrationTimer = createTimer(
                        std::function<void()>(bind(&Controller::mainFunc, this)),
                        1000);
                a->enableControlStrategy();
            }
        }

        void mainFunc()
        {
            seconds--;
            pos =  140 * seconds;
            a->setRequestedPosition(pos);
            Serial.println(seconds%60);
        }


};
#endif 
