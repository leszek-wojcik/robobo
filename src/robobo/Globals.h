#ifndef ROBOBO_GLOBALS_INCLUDED
#define ROBOBO_GLOBALS_INCLUDED

#include "Arduino.h"
#include "MotorI.h"

/**
Globals class is simple wrapper around global values that are accessible from
everywhere in programs

Global class is singleton implemented. Globals allows to create only one
instance of class.  Constructor of object is responsible to use all hard-coded
values through out program
*/
class Globals
{
    private:
        /** Privte constructor allows to create object only from static method of class */
        Globals();
    public:
        static Globals* instance; 
        static Globals* getInstance();
        static Globals* createInstance();

        MotorI *dc1;
        MotorI *dc2;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
