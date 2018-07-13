#include "PlatformManager.h"
#include "Arduino.h"

void PlatformManager::collect()
{
}

PlatformManager::PlatformManager(string name, UBaseType_t priority, DisplayManager *disp): 
        ActiveObject( name, priority ),
        disp(disp)
{
    refreshTimer = createTimer(
            std::function<void()>(std::bind(&PlatformManager::collect, this)),
            2000);
}

