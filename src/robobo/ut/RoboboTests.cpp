#include "RoboboTests.h"
#include "EncoderISR.h"
#include "Globals.h"
#include "DCMotor.h"

using ::testing::_;
using ::testing::Return;

ArduinoMock * RoboboTests::arduino = NULL;


TEST_F(RoboboTests, PID_proportional_1)
{
    DCMotor dc1(1,2,3,4,5);
    Globals *i = Globals::getInstance();
    i->dc1 = &dc1;
   
    dc1.setPosition(100);
    dc1.encoderPosition=0;
    dc1.kP = 0.5;
    EXPECT_CALL(*arduino, analogWrite(dc1.voltagePin, 50));
    encoder1_ISR();
    ASSERT_EQ(dc1.direction,1);
}

TEST_F(RoboboTests, PID_proportional_2)
{
    // This scenario test control output when controller determined need for
    // switching direction. Expectation is that HBridge Pins will change
    Globals *i = Globals::getInstance();
    DCMotor dc1(1,2,3,4,5);
    i->dc1 = &dc1;

    dc1.setPosition(-100);
    dc1.encoderPosition=0;
    dc1.kP = 0.5;

    EXPECT_CALL(*arduino, analogWrite(dc1.voltagePin, 50));
    EXPECT_CALL(*arduino, digitalWrite(dc1.hBridgeAPin, 0));
    EXPECT_CALL(*arduino, digitalWrite(dc1.hBridgeBPin, 1));
    encoder1_ISR();
    ASSERT_EQ(dc1.direction,-1);
}

TEST_F(RoboboTests, store_previous_value_1) 
{
    Globals *i = Globals::getInstance();
    DCMotor dc1(1,2,3,4,5);
    i->dc1 = &dc1;

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderAPrevVal,1);
    ASSERT_EQ( dc1.encoderBPrevVal,1);

}

TEST_F(RoboboTests, store_previous_value_2) 
{
    Globals *i = Globals::getInstance();
    DCMotor dc2(1,2,3,4,5);
    i->dc2 = &dc2;

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderAPrevVal,1);
    ASSERT_EQ( dc2.encoderBPrevVal,1);

}

TEST_F(RoboboTests, move_right_1) {

    Globals *i = Globals::getInstance();
    DCMotor dc1(1,2,3,4,5);
    i->dc1 = &dc1;
    dc1.encoderPosition = 0;
    dc1.encoderAVal = 1;
    dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,4);

}

TEST_F(RoboboTests, move_left_1) {

    Globals *i = Globals::getInstance();
    DCMotor dc1(1,2,3,4,5);
    i->dc1 = &dc1;
    dc1.encoderPosition = 0;
    dc1.encoderAVal = 1;
    dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,-1);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,-2);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,-3);

    EXPECT_CALL(*arduino, digitalRead(dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( dc1.encoderPosition,-4);

}

TEST_F(RoboboTests, move_right_2) {

    Globals *i = Globals::getInstance();
    DCMotor dc2(1,2,3,4,5);
    i->dc2 = &dc2;

    dc2.encoderPosition = 0;
    dc2.encoderAVal = 1;
    dc2.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( dc2.encoderPosition,4);

}

