#ifndef ROBOBO_GLOBALS_INCLUDED
#define ROBOBO_GLOBALS_INCLUDED

#include "Arduino.h"
#include "Motor.h"

/**
Globals class is simple wrapper around global values that are accessible from
everywhere in programs

Globass class implemented as singleton. Globals allows to create only one
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

        Motor dc1;
        Motor dc2;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
