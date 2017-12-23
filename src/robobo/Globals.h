#ifndef ROBOBO_GLOBALS_INCLUDED
#define ROBOBO_GLOBALS_INCLUDED

#include "Arduino.h"

class Globals
{
    private:
        Globals();
    public:
        static Globals* instance; 
        static Globals* getInstance();
        static Globals* createInstance();

        // Encoders
        uint8_t encoder1aPin;
        uint8_t encoder1aVal;
        uint8_t encoder1aPrevVal;

        uint8_t encoder1bPin;
        uint8_t encoder1bVal;
        uint8_t encoder1bPrevVal;

        uint8_t encoder2aPin;
        uint8_t encoder2aVal;
        uint8_t encoder2aPrevVal;

        uint8_t encoder2bPin;
        uint8_t encoder2bVal;
        uint8_t encoder2bPrevVal;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
