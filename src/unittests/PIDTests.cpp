#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "PID.h"
#include "ArduinoMock.h"
#include "RoboboTests.h"

using ::testing::_;
using ::testing::Return;
using namespace std;

TEST_F(RoboboTests, PID_Proportional_1)
{
    PID pid(3,0,0,dcm1);
    ASSERT_EQ(pid.calculateControl(1), 3);
}

TEST_F(RoboboTests, PID_Integral_1)
{
    int32_t val;

    PID pid(0,3,0,dcm1);
    EXPECT_CALL(*arduino, micros()).WillOnce(Return(0));
    pid.calculateControl(1);

    EXPECT_CALL(*arduino, micros()).WillOnce(Return(100));
    val = pid.calculateControl(1);
    ASSERT_EQ( val , 300);
}

