#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "PID.h"

using ::testing::_;
using ::testing::Return;
using namespace std;

TEST(PIDTests, PID_Integral_1)
{
    PID pid(0,1,0);
}

