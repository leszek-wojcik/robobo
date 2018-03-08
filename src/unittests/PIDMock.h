#ifndef PIDMOCK_H_INCLUDED
#define PIDMOCK_H_INCLUDED

#include "ControlStrategy.h"

class PIDMock: public ControlStrategy
{
    MOCK_METHOD1 ( calculateControl, int32_t(int32_t) );
};

#endif
