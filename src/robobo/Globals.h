#ifndef ROBOBO_GLOBALS_INCLUDED
#define ROBOBO_GLOBALS_INCLUDED

#include "Arduino.h"
class Motor
{
    public:
        // Encoders
        uint8_t encoderAPin;
        uint8_t encoderAVal;
        uint8_t encoderAPrevVal;

        uint8_t encoderBPin;
        uint8_t encoderBVal;
        uint8_t encoderBPrevVal;

        int32_t encoderPos;
};

class Globals
{
    private:
        Globals();
    public:
        static Globals* instance; 
        static Globals* getInstance();
        static Globals* createInstance();

        Motor dc1;
        Motor dc2;

        // Encoders
        //uint8_t encoder1aPin;
        //uint8_t encoder1aVal;
        //uint8_t encoder1aPrevVal;

        //uint8_t encoder1bPin;
        //uint8_t encoder1bVal;
        //uint8_t encoder1bPrevVal;

        //int32_t encoder1pos;

        uint8_t encoder2aPin;
        uint8_t encoder2aVal;
        uint8_t encoder2aPrevVal;

        uint8_t encoder2bPin;
        uint8_t encoder2bVal;
        uint8_t encoder2bPrevVal;

        int32_t encoder2pos;
        
        // Serial
        long serialSpeed; 

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
