#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#include "ControlStrategy.h" 

class PID: public ControlStrategy
{
    private:
        float kP;
        float kI;
        float kD;

    public:
        PID(float kP, float kI, float kD): 
            kP(kP), 
            kI(kI),
            kD(kD)
        {
        }

        int32_t calculateControl(int32_t diff) 
        {
        }
};

#endif
