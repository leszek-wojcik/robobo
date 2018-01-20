#ifndef ROBOBO_MOTOR_INCLUDED
#define ROBOBO_MOTOR_INCLUDED

#include "Arduino.h"
#include "MotorI.h"
#include "ActiveObject.h"


/**
Motor class is to represent all data associated with DC Motor. 

Motor class captures two wires from DC motor encoder. Stores previous and
current value of encoder signal.     
*/
class DCMotor : public MotorI, public ActiveObject
{
    public:
        /** This function is responsible for seting correct pin modes in
         ** Arduino */
        void setPinModes();

        /** Nulls out private areas of class */
        void reset();

        DCMotor(    uint8_t encoderAPinV, 
                    uint8_t encoderBPinV, 
                    uint8_t hBridgeAPinV,
                    uint8_t hBridgeBPinV,
                    uint8_t voltagePinV );

        // Pins
        uint8_t encoderAPin;
        uint8_t encoderBPin;
        uint8_t hBridgeAPin;
        uint8_t hBridgeBPin;
        uint8_t voltagePin;

        // State
        uint8_t encoderAVal;
        uint8_t encoderBVal;
        uint8_t encoderAPrevVal;
        uint8_t encoderBPrevVal;
        int32_t encoderPosition;
        int32_t requestedPosition;
        int8_t  direction;
        int32_t controllerIntegral;
        
        // PID Controller parameters
        float kP;
        float kI;

        // Interface functions
        void setPosition(int32_t);
        int32_t getPosition();
        void stop(void);

        /** This method is called on interrupt associated with encoder */
        void encoderInterrupt(void);

    private:
        void calculatePID(void);
        void setDirectionRight(void);
        void setDirectionLeft(void);
        void setVoltage(uint8_t val);

    friend int main(void);

};

#endif
