#ifndef ROBOBO_INCLUDED
#define ROBOBO_INCLUDED

#include "Arduino.h"
#include "MotorI.h"
#include "ControlStrategy.h"

/**
Robobo class is simple wrapper around global values that are accessible from
everywhere in programs

Global class is singleton implemented. Robobo allows to create only one
instance of class.  Constructor of object is responsible to use all hard-coded
values through out program
*/
class Robobo
{
    public:
        Robobo();
        void createSetupV1(void);

        MotorI *dc1;
        MotorI *dc2;
        ControlStrategy *pid1;
        ControlStrategy *pid2;
        
        // Serial
        long serialSpeed; 
        static Robobo *instance;

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
