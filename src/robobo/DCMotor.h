#ifndef ROBOBO_MOTOR_INCLUDED
#define ROBOBO_MOTOR_INCLUDED

#include "Arduino.h"
#include "MotorI.h"


/**
Motor class is to represent all data associated with DC Motor. 

Motor class captures two wires from DC motor encoder. Stores previous and
current value of encoder signal.     
*/
class DCMotor : public MotorI
{
    public:
        /** This function is responsible for seting correct pin modes in
         ** Arduino */
        void setPinModes();

        // Encoders
        uint8_t encoderAPin;
        uint8_t encoderAVal;
        uint8_t encoderAPrevVal;

        uint8_t encoderBPin;
        uint8_t encoderBVal;
        uint8_t encoderBPrevVal;

        uint8_t hBridgeAPin;
        uint8_t hBridgeBPin;
        
        uint8_t voltagePin;

        int32_t encoderPos;

        void setPosition(int32_t);
        int32_t getPosition();

        /** This method is called on interrupt associated with encoder */
        void encoderInterrupt(void);

        //TODO:make private
        void calculatePID(void);
        void setDirectionRight(void);
        void setDirectionLeft(void);
        void setVoltage(uint8_t val);
};

#endif
