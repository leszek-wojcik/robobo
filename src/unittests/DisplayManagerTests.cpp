#include "DisplayManager.h"
#include "LiquidCrystal.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <functional>
#include "UnitTestsGlobals.h"

using ::testing::_;
using ::testing::Return;
using namespace std;

class DisplayManagerTests : public ::testing::Test
{
    public:

        LiquidCrystal *lcd;

        DisplayManagerTests() 
        { 
        }

        virtual void SetUp()
        { 
            rtos    = new::testing::NiceMock<FreeRTOSMock>();
            arduino = new::testing::NiceMock<ArduinoMock>();
            lcd = new LiquidCrystal(1,2,3,4,5,6);
        }

        virtual void TearDown()
        { 
            delete rtos;
            delete arduino;
            delete lcd;
        }

};

TEST_F(DisplayManagerTests, RoboboVerionDisplay)
{

    EXPECT_CALL(*lcd, print(ROBOBO_VERSION_STRING));
    EXPECT_CALL(*lcd, begin(_,_));
    DisplayManager mgr("DM", 1, lcd);

}

TEST_F(DisplayManagerTests, registerDisplayData)
{

    EXPECT_CALL(*lcd, print(ROBOBO_VERSION_STRING));
    EXPECT_CALL(*lcd, begin(_,_));
    DisplayManager mgr("DM", 1, lcd);
    int handle1;
    mgr.registerDisplayData(&handle1, "test1");

    int handle2;
    mgr.registerDisplayData(&handle2, "test2");

    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test1"));
    mgr.displayHeader(handle1);

    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test2"));
    mgr.displayHeader(handle2);

}

TEST_F(DisplayManagerTests, DisplayValue)
{

    EXPECT_CALL(*lcd, print(ROBOBO_VERSION_STRING));
    EXPECT_CALL(*lcd, begin(_,_));
    DisplayManager mgr("DM", 1, lcd);
    int handle1;
    mgr.registerDisplayData(&handle1, "test1");


    EXPECT_CALL(*lcd, setCursor(1,0));
    EXPECT_CALL(*lcd, print("20"));
    mgr.postData(handle1,20);
    mgr.displayValue(handle1);

}

TEST_F( DisplayManagerTests, PeriodExpiry )
{

    EXPECT_CALL(*lcd, print(ROBOBO_VERSION_STRING));
    EXPECT_CALL(*lcd, begin(_,_));
    DisplayManager mgr("DM", 1, lcd);
    int handle1;
    int handle2;
    mgr.registerDisplayData(&handle1, "test1");
    mgr.registerDisplayData(&handle2, "test2");

    mgr.postData(handle1,10);
    mgr.postData(handle2,20);

    EXPECT_CALL(*lcd, clear());
    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test1"));
    EXPECT_CALL(*lcd, setCursor(0,1));
    EXPECT_CALL(*lcd, print("10"));
    mgr.switchData();
    EXPECT_CALL(*lcd, clear());
    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test2"));
    EXPECT_CALL(*lcd, setCursor(0,1));
    EXPECT_CALL(*lcd, print("20"));
    mgr.switchData();
    EXPECT_CALL(*lcd, clear());
    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test1"));
    EXPECT_CALL(*lcd, setCursor(0,1));
    EXPECT_CALL(*lcd, print("10"));
    mgr.switchData();
    EXPECT_CALL(*lcd, clear());
    EXPECT_CALL(*lcd, setCursor(0,0));
    EXPECT_CALL(*lcd, print("test2"));
    EXPECT_CALL(*lcd, setCursor(0,1));
    EXPECT_CALL(*lcd, print("20"));
    mgr.switchData();

}
