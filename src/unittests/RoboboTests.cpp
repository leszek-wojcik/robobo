#include "RoboboTests.h"
#include "ISR.h"
#include "Robobo.h"
#include "DCMotor.h"
#include <iostream>
#include "PID.h"

using ::testing::_;
using ::testing::Return;
using namespace std;

PIDMock * RoboboTests::pid1 = NULL;
PIDMock * RoboboTests::pid2 = NULL;
ArduinoSerialMock Serial;


TEST_F(RoboboTests, PID_proportional_1)
{
    PID pid("",0,0.5,0,0,dcm1);
    dcm1->setControlStrategy(&pid);
    dcm1->reset();
    dcm1->setRequestedPosition(100);

    EXPECT_CALL(*arduino, analogWrite(dcm1->voltagePin, 50));
    encoderDc1_ISR();
    pid.periodExpiry();
    ASSERT_EQ(dcm1->direction,1);
}

TEST_F(RoboboTests, PID_proportional_2)
{
    // This scenario test control output when controller determined need for
    // switching direction. Expectation is that HBridge Pins will change

    PID pid("",0,0.5,0,0,dcm1);
    dcm1->setRequestedPosition(-100);
    dcm1->encoderPosition=0;
    dcm1->direction = 0;
    dcm1->setControlStrategy(&pid);

    EXPECT_CALL(*arduino, analogWrite(dcm1->voltagePin, 50));
    EXPECT_CALL(*arduino, digitalWrite(dcm1->hBridgeAPin, 0));
    EXPECT_CALL(*arduino, digitalWrite(dcm1->hBridgeBPin, 1));

    encoderDc1_ISR();
    pid.periodExpiry();
    ASSERT_EQ(dcm1->direction,-1);
}

TEST_F(RoboboTests, store_previous_value_1) 
{
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderAPrevVal,1);
    ASSERT_EQ( dcm1->encoderBPrevVal,1);

}

TEST_F(RoboboTests, store_previous_value_2) 
{

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoderDc2_ISR();

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderAPrevVal,1);
    ASSERT_EQ( dcm2->encoderBPrevVal,1);

}

TEST_F(RoboboTests, dont_move) {
    dcm1->encoderPosition = 0;
    dcm1->encoderAVal = 1;
    dcm1->encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();
    ASSERT_EQ( dcm1->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();
    ASSERT_EQ( dcm1->encoderPosition,0);
}

TEST_F(RoboboTests, move_right_1) {

    dcm1->encoderPosition = 0;
    dcm1->encoderAVal = 1;
    dcm1->encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,4);

}

TEST_F(RoboboTests, move_left_1) {

    dcm1->encoderPosition = 0;
    dcm1->encoderAVal = 1;
    dcm1->encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-1);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-2);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-3);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoderDc1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-4);

}

TEST_F(RoboboTests, move_right_2) {

    dcm2->encoderPosition = 0;
    dcm2->encoderAVal = 1;
    dcm2->encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(0));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(0));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoderDc2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,4);

}

