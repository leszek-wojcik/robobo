#include "Arduino.h"
#include "Globals.h"

void encoder1_ISR()
{
    Globals::instance->encoder1aVal = digitalRead(Globals::instance->encoder1aPin);
    Globals::instance->encoder1bVal = digitalRead(Globals::instance->encoder1bPin);
}


void encoder2_ISR()
{
    Globals::instance->encoder2aVal = digitalRead(Globals::instance->encoder1aPin);
    Globals::instance->encoder2bVal = digitalRead(Globals::instance->encoder1aPin);
}
