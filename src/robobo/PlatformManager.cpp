#include "PlatformManager.h"
#include "Arduino.h"

void PlatformManager::collect()
{
    disp->executeMethodSynchronously(
            std::function<void()>(std::bind(&DisplayManager::print, disp,"test\0")));
}

PlatformManager::PlatformManager(string name, UBaseType_t priority, DisplayManager *disp): 
        ActiveObject( name, priority ),
        disp(disp)
{
    refreshTimer = createTimer(
            std::function<void()>(std::bind(&PlatformManager::collect, this)),
            2000,
            1);
    xTimerStart(refreshTimer,0);
}

