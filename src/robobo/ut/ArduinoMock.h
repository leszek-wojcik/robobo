#ifndef ARDUINOMOCK_INCLUDED
#define ARDUINOMOCK_INCLUDED
#include "gmock/gmock.h"

class ArduinoMock
{
    public: 
        virtual ~ArduinoMock(){}
        MOCK_METHOD1(digitalRead, uint8_t (uint8_t pin) );
        MOCK_METHOD2(digitalWrite, void (uint8_t pin, uint8_t val) );
        MOCK_METHOD2(analogWrite, void (uint8_t pin, int val) );
};

#endif
