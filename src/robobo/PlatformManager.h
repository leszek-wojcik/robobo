#ifndef PLATFORM_MANAGER_INCLUDED
#define PLATFORM_MANAGER_INCLUDED

#include "ActiveObject.h"
#include "DisplayManager.h"

class PlatformManager: public ActiveObject
{
        DisplayManager *disp;

    public:
        TimerHandle_t refreshTimer; 
        void collect(void);
        PlatformManager(string name, UBaseType_t priority, DisplayManager*);

};

#endif
