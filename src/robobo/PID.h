#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#include "ControlStrategy.h" 
#include "Arduino.h"

class PID: public ControlStrategy
{
    private:
        float kP;
        float kI;
        float kD;
        uint32_t prevMicros;
        int32_t integral; 

    public:
        PID(float kP, float kI, float kD): 
            kP(kP), 
            kI(kI),
            kD(kD),
            prevMicros(0),
            integral(0)
        {
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
