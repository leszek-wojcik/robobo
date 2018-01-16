#ifndef ROBOBO_INCLUDED
#define ROBOBO_INCLUDED

#include "Arduino.h"
#include "MotorI.h"

/**
Robobo class is simple wrapper around global values that are accessible from
everywhere in programs

Global class is singleton implemented. Robobo allows to create only one
instance of class.  Constructor of object is responsible to use all hard-coded
values through out program
*/
class Robobo
{
    private:
        /** Privte constructor allows to create object only from static method of class */
        Robobo();
    public:
        static Robobo* instance; 
        static Robobo* getInstance();
        static Robobo* createInstance();

        MotorI *dc1;
        MotorI *dc2;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
