#ifndef UNITTESTSGLOBALS_INCLUDED
#define UNITTESTSGLOBALS_INCLUDED

#include "Arduino.h"
#include "gmock/gmock.h"
#include "Robobo.h"
#include "ArduinoMock.h"
#include "FreeRTOSMock.h"
#include "PIDMock.h"
#include <iostream>
#include "ArduinoMock.h"
#include "FreeRTOSMock.h"

extern ArduinoMock *arduino;
extern FreeRTOSMock *rtos;

#endif
