#include "Arduino.h"
#include "gmock/gmock.h"

class ArduinoMock
{
    public: 
        virtual ~ArduinoMock(){}
        MOCK_METHOD1(digitalRead, uint8_t (uint8_t pin) );
};

class RoboboTests : public ::testing::Test
{
    public:
        static ArduinoMock *arduino;
        RoboboTests() { }
        virtual void SetUp(){ arduino = new::testing::NiceMock<ArduinoMock>(); }
        virtual void TearDown(){ delete arduino; }
        

};


