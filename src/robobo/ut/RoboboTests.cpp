#include "RoboboTests.h"
#include "EncoderISR.h"
#include "Robobo.h"
#include "DCMotor.h"
#include <iostream>

using ::testing::_;
using ::testing::Return;
using namespace std;

ArduinoMock * RoboboTests::arduino = NULL;
FreeRTOSMock * RoboboTests::rtos = NULL;
ArduinoSerialMock Serial;

TEST_F(RoboboTests, Timer)
{
    EXPECT_CALL(*rtos, xTimerCreate(_,1,1,_,ActiveObjectCallback));
    DCMotor dcm3(1,2,3,4,5);
}

TEST_F(RoboboTests, PID_proportional_1)
{
    dcm1->setPosition(100);
    dcm1->kP = 0.5;
    EXPECT_CALL(*arduino, analogWrite(dcm1->voltagePin, 50));
    encoder1_ISR();
    ASSERT_EQ(dcm1->direction,1);
}

TEST_F(RoboboTests, PID_proportional_2)
{
    // This scenario test control output when controller determined need for
    // switching direction. Expectation is that HBridge Pins will change

    dcm1->setPosition(-100);
    dcm1->encoderPosition=0;
    dcm1->kP = 0.5;
    dcm1->direction = 0;

    EXPECT_CALL(*arduino, analogWrite(dcm1->voltagePin, 50));
    EXPECT_CALL(*arduino, digitalWrite(dcm1->hBridgeAPin, 0));
    EXPECT_CALL(*arduino, digitalWrite(dcm1->hBridgeBPin, 1));

    encoder1_ISR();
    ASSERT_EQ(dcm1->direction,-1);
}

TEST_F(RoboboTests, store_previous_value_1) 
{
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderAPrevVal,1);
    ASSERT_EQ( dcm1->encoderBPrevVal,1);

}

TEST_F(RoboboTests, store_previous_value_2) 
{

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderAPrevVal,1);
    ASSERT_EQ( dcm2->encoderBPrevVal,1);

}


TEST_F(RoboboTests, move_right_1) {

    dcm1->encoderPosition = 0;
    dcm1->encoderAVal = 1;
    dcm1->encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

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
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-1);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-2);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dcm1->encoderPosition,-3);

    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm1->encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

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
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dcm2->encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dcm2->encoderPosition,4);

}

