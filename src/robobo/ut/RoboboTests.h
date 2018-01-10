#include "Arduino.h"
#include "gmock/gmock.h"
#include "Globals.h"

class ArduinoMock
{
    public: 
        virtual ~ArduinoMock(){}
        MOCK_METHOD1(digitalRead, uint8_t (uint8_t pin) );
        MOCK_METHOD2(digitalWrite, void (uint8_t pin, uint8_t val) );
        MOCK_METHOD2(analogWrite, void (uint8_t pin, int val) );
};

class RoboboTests : public ::testing::Test
{
    public:
        static ArduinoMock *arduino;
        RoboboTests() { Globals::createInstance(); }
        virtual void SetUp(){ arduino = new::testing::NiceMock<ArduinoMock>();}
        virtual void TearDown(){ delete arduino; }
        

};


