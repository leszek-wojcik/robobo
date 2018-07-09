#ifndef DISPLAY_MANAGER_INCLUDED
#define DISPLAY_MANAGER_INCLUDED

#include "ActiveObject.h"
#include "LiquidCrystal.h"

// Class is active object with reference to LiquidCrystal. It delegates
// calls to LiquidCrystal object.

class DisplayManager: public ActiveObject
{
    private:
        LiquidCrystal *myLcd;
        TimerHandle_t refreshTimer;
        int couter;

    public:
        DisplayManager(string name, UBaseType_t priority, LiquidCrystal *lcd);
        void refresh();
        void print(string);
};

#endif
