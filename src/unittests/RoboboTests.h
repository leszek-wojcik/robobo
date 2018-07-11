#include "Arduino.h"
#include "gmock/gmock.h"
#include "Robobo.h"
#include "DCMotor.h"
#include "ArduinoMock.h"
#include "FreeRTOSMock.h"
#include "PIDMock.h"
#include <iostream>

using namespace std;

class RoboboTests : public ::testing::Test, public Robobo
{
    public:
        static ArduinoMock *arduino;
        static FreeRTOSMock *rtos;
        static ArduinoSerialMock Serial;
        static PIDMock *pid1;
        static PIDMock *pid2;

        DCMotor *dcm1;
        DCMotor *dcm2;

        RoboboTests() 
        { 
            arduino = new::testing::NiceMock<ArduinoMock>();
            rtos    = new::testing::NiceMock<FreeRTOSMock>();
            pid1    = new::testing::NiceMock<PIDMock>();
            pid2    = new::testing::NiceMock<PIDMock>();

            // We need to configure parent class object
            dcm1 = new DCMotor(1,2,3,4,5,"dcm1");
            dcm1->setControlStrategy(pid1);
            dcm2 = new DCMotor(11,12,13,14,15,"dcm2");
            dcm2->setControlStrategy(pid2);
            dc1 = dcm1;
            dc2 = dcm2;
        }

        virtual void SetUp()
        { 
            arduino = new::testing::NiceMock<ArduinoMock>();
            rtos = new::testing::NiceMock<FreeRTOSMock>();
            pid1 = new::testing::NiceMock<PIDMock>();
            pid2 = new::testing::NiceMock<PIDMock>();
            dcm1->reset();
            dcm2->reset();
        }

        virtual void TearDown()
        { 
            delete arduino; 
            delete rtos; 
            delete pid1;
            delete pid2;
            
        }

};


