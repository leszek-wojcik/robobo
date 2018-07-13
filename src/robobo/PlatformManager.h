#ifndef PLATFORM_MANAGER_INCLUDED
#define PLATFORM_MANAGER_INCLUDED

#include "ActiveObject.h"
#include "DisplayManager.h"

class PlatformManager: public ActiveObject
{
    private:
        DisplayManager *disp;
        std::map<ActiveObject*, int> handles;
        std::map<ActiveObject*, int>::iterator handlesIt;

    public:
        PlatformManager(string name, UBaseType_t priority, DisplayManager*);
        void registerForReports(ActiveObject *);
        TimerHandle_t refreshTimer; 
        void collect(void);

};

#endif
