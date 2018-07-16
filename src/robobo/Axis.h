#ifndef AXIS_INCLUDED
#define AXIS_INCLUDED

#include "Motor.h"

// Axis class is used to combine Motor with 2 or 1 end stops. 
class Axis
{
    private:
        Motor *motor;
        int limitSwitch1Pin;
        int limitSwitch2Pin;
        int sw1Location;

    public:
        Axis( Motor *motor, int limitSwitch1Pin, int limitSwitch2Pin): 
            motor(motor), 
            limitSwitch1Pin(limitSwitch1Pin), 
            limitSwitch2Pin(limitSwitch2Pin)
        {
        }

        void executeCalibration()
        {
            // 1) check if any of limit switch pins are open
            // 2) set direction left using small voltage 
            // 3) wait for interrupt 
            // 4) if not get intetrrup for long time increase voltage
            // 5) finally we shoudl be getting limit swich pin 
            //      - record location
            // 6) set direction right using same voltage used previously
            // 7) finally we shoudl be getting limit swich pin 2
            // 8) perform sanity checks over locationsa TBD

            int aSW1 = digitalRead(limitSwitch1Pin);
            int aSW2 = digitalRead(limitSwitch2Pin);
    
            if ( aSW1 == 1 || aSW1 == 1 )
            {
                Serial.println("Calibration Error");
            }

            //attachInterrupt(digitalPinToInterrupt(limitSwitch1Pin),encoder1_ISR, RISING);
            //attachInterrupt(digitalPinToInterrupt(limitSwitch2Pin),encoder1_ISR, RISING);

        } 

};

#endif 
