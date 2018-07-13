#include "PlatformManager.h"
#include "Arduino.h"

void PlatformManager::collect()
{

    for( auto elem : handles)
    {
        UBaseType_t mark = uxTaskGetStackHighWaterMark(taskHandles[elem.first]);

        disp->executeMethod(std::function<void()>(
            std::bind(&DisplayManager::postData, disp, elem.second, mark)));
    }

}

PlatformManager::PlatformManager(string name, UBaseType_t priority, DisplayManager *disp): 
        ActiveObject( name, priority ),
        disp(disp)
{
    refreshTimer = createTimer(
            std::function<void()>(
                std::bind(&PlatformManager::collect, this)),
            2000);
}


void PlatformManager::registerForReports(ActiveObject *o)
{
    int handle;
    if (taskSCHEDULER_RUNNING == xTaskGetSchedulerState())
    {
        disp->executeMethodSynchronously(std::function<void()>(std::bind(&DisplayManager::registerDisplayData,disp,&handle,o->name,"")));
    }
    else
    {
        disp->registerDisplayData(&handle,o->name,"");
    }

    Serial.println ((long) o);
    handles[o] = handle ;
}
