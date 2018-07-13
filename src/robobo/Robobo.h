#ifndef ROBOBO_INCLUDED
#define ROBOBO_INCLUDED

#include "Arduino.h"
#include "Motor.h"
#include "ControlStrategy.h"
#include "Controller.h"
#include "DisplayManager.h"
#include "PlatformManager.h"


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
        void createSetupV2(void);

        Motor *dc1;
        Motor *dc2;
        ControlStrategy *pid1;
        ControlStrategy *pid2;
        Controller *controller;

        DisplayManager *disp;
        LiquidCrystal *lcd;
        PlatformManager *pm;
        
        // Serial
        long serialSpeed; 
        static Robobo *instance;

        friend void encoder1_ISR(void);
        friend void encoder2_ISR(void);
};


#endif
