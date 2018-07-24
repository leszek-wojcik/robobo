#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#include "ControlStrategy.h" 
#include "Arduino.h"
#include "Motor.h"
#include <functional>

class PID: public ControlStrategy
{
    private:
        float kP;
        float kI;
        float kD;
        uint32_t prevMicros;
        int32_t integral; 
        TimerHandle_t triggerTimer;
        Motor *motor;
        TickType_t samplePeriod;

    public:
        PID(string name, UBaseType_t priority, float kP, float kI, float kD, Motor *m, TickType_t sPeriod=1): 
            kP(kP), 
            kI(kI),
            kD(kD),
            prevMicros(0),
            integral(0),
            motor(m),
            samplePeriod(sPeriod)
        {
        }
        void enable()
        {
            triggerTimer = createTimer(
                    std::function<void()>(std::bind(&PID::periodExpiry, this)),
                    samplePeriod);
        }
        void disable()
        {
            stopTimer(triggerTimer);
        }

        void periodExpiry(void)
        {
            int32_t diff;
            int32_t dcOutput;

            diff = motor->getRequestedPosition() - motor->getCurrentPosition();
            dcOutput = calculateControl(diff);

            if (dcOutput < 0 )
            {
                motor->setDirectionLeft();
            }
            else
            {
                motor->setDirectionRight();
            }

            dcOutput = abs(dcOutput);

            //need to scale target value to range 0-255 PWM
            if (dcOutput >255)
                dcOutput = 255;

            if (dcOutput < 7)
                dcOutput = 0;

            if (!motor->isEmergencyStopped())
                motor->setVoltage(dcOutput);
        }

        int32_t calculateControl(int32_t diff) 
        {
            uint32_t now = micros();
            uint32_t timeDelta = now - prevMicros;
            prevMicros = now;

            //TODO: need to address overflow scenario
            integral = integral + diff * timeDelta;
            
            return diff *kP + integral * kI;
        }
};

#endif
