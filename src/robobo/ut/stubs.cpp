#include "Arduino.h"
#include "RoboboTests.h"


void pinMode(uint8_t, uint8_t)
{
}

void digitalWrite(uint8_t, uint8_t)
{
}

int digitalRead(uint8_t pin )
{
    return RoboboTests::arduino->digitalRead(pin);
    //return 0;
}

int analogRead(uint8_t)
{
    return 0;
}
void analogReference(uint8_t mode)
{
}
void analogWrite(uint8_t, int)
{
}
