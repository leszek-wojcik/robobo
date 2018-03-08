#ifndef CONTROL_STRATEGY_INCLUDED
#define CONTROL_STRATEGY_INCLUDED

class ControlStrategy
{
    public: 
        virtual int32_t calculateControl(int32_t diff) = 0;
};

#endif
