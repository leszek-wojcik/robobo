#include "Arduino.h"
#include "gmock/gmock.h"
#include "Robobo.h"
#include "DCMotor.h"
#include "ArduinoMock.h"
#include "FreeRTOSMock.h"
#include <iostream>

using namespace std;

class RoboboTests : public ::testing::Test, public Robobo
{
    public:
        static ArduinoMock *arduino;
        static FreeRTOSMock *rtos;
        static ArduinoSerialMock Serial;

        DCMotor *dcm1;
        DCMotor *dcm2;

        RoboboTests() 
        { 
            arduino = new::testing::NiceMock<ArduinoMock>();
            rtos = new::testing::NiceMock<FreeRTOSMock>();

            // We need to configure parent class object
            dcm1 = new DCMotor(1,2,3,4,5);
            dcm2 = new DCMotor(11,12,13,14,15);
            dc1 = dcm1;
            dc2 = dcm2;
        }

        virtual void SetUp()
        { 
            arduino = new::testing::NiceMock<ArduinoMock>();
            rtos = new::testing::NiceMock<FreeRTOSMock>();
            dcm1->reset();
            dcm2->reset();
        }

        virtual void TearDown()
        { 
            delete arduino; 
            delete rtos; 
        }

};


