#ifndef ROBOBO_DCMOTOR_INCLUDED
#define ROBOBO_DCMOTOR_INCLUDED

#include "Arduino.h"
#include "Motor.h"
#include "ActiveObject.h"
#include "ControlStrategy.h"
#include "PID.h"
#include <string>

using namespace std;
/**
Motor class is to represent all data associated with DC Motor. 

Motor class captures two wires from DC motor encoder. Stores previous and
current value of encoder signal.     
*/
class DCMotor : public Motor
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
                    uint8_t voltagePinV,
                    string name="\0");

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
        int32_t dcOutput;
        uint8_t stoped;

        // Internal
        string motorName;
        

        // Interface functions
        void setPosition(int32_t);
        int32_t getCurrentPosition();
        void stop(void);
        void enableReports(TickType_t period);

        void setControlStrategy(ControlStrategy *strategy);
        void report(void);

        /** This method is called on interrupt associated with encoder */
        void encoderInterrupt(void);

    private:

        ControlStrategy *control;
    
        void setDirectionRight(void);
        void setDirectionLeft(void);
        void setVoltage(uint8_t val);



    friend int main(void);

};

#endif
