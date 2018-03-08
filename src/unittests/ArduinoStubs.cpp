#include "Arduino.h"
#include "RoboboTests.h"


void pinMode(uint8_t, uint8_t)
{
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    RoboboTests::arduino->digitalWrite(pin, val);
}

int digitalRead(uint8_t pin )
{
    return RoboboTests::arduino->digitalRead(pin);
}

int analogRead(uint8_t)
{
    return 0;
}
void analogReference(uint8_t mode)
{
}

void analogWrite(uint8_t pin, int val)
{
    RoboboTests::arduino->analogWrite(pin, val);
}

unsigned long int micros(void)
{
    return RoboboTests::arduino->micros();
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) 
{
}
