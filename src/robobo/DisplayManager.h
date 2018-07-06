#ifndef DISPLAY_MANAGER_INCLUDED
#define DISPLAY_MANAGER_INCLUDED

#include "ActiveObject.h"
#include "LCDisplay.h"

// Class is active object with reference to LCDisplay. It delegates calls to
// LCDisplay object.

class DisplayManager: public ActiveObject
{
    private:
        LCDisplay *myLcd;
        TimerHandle_t refreshTimer;
        int couter;

    public:
        DisplayManager(string name, UBaseType_t priority, LCDisplay *lcd);
        void refresh();
        void print(string);
};

#endif
