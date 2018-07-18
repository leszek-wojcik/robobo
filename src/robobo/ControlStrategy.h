#ifndef CONTROL_STRATEGY_INCLUDED
#define CONTROL_STRATEGY_INCLUDED

#include "ActiveObject.h"

class ControlStrategy: public ActiveObject
{
    public: 
        virtual int32_t calculateControl(int32_t diff) = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;

};

#endif
