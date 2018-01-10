#include "RoboboTests.h"
#include "EncoderISR.h"
#include "Globals.h"
using ::testing::_;
using ::testing::Return;

ArduinoMock * RoboboTests::arduino = NULL;


TEST_F(RoboboTests, PID_proportional_1)
{

    Globals *i = Globals::getInstance();
    i->dc1.setPosition(100);
    i->dc1.encoderPosition=0;
    i->dc1.kP = 0.5;
    EXPECT_CALL(*arduino, analogWrite(i->dc1.voltagePin, 50));
    encoder1_ISR();
}

TEST_F(RoboboTests, PID_proportional_2)
{
    // This scenario test control output when controller determined need for
    // switching direction. Expectation is that HBridge Pins will change
    Globals *i = Globals::getInstance();
    i->dc1.setPosition(-100);
    i->dc1.encoderPosition=0;
    i->dc1.kP = 0.5;

    EXPECT_CALL(*arduino, analogWrite(i->dc1.voltagePin, 50));
    EXPECT_CALL(*arduino, digitalWrite(i->dc1.hBridgeAPin, 0));
    EXPECT_CALL(*arduino, digitalWrite(i->dc1.hBridgeBPin, 1));
    encoder1_ISR();
}

TEST_F(RoboboTests, store_previous_value_1) 
{

    Globals *i = Globals::getInstance();

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderAPrevVal,1);
    ASSERT_EQ( i->dc1.encoderBPrevVal,1);

}

TEST_F(RoboboTests, store_previous_value_2) 
{

    Globals *i = Globals::getInstance();

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderAPrevVal,1);
    ASSERT_EQ( i->dc2.encoderBPrevVal,1);

}

TEST_F(RoboboTests, move_right_1) {

    Globals *i = Globals::getInstance();
    i->dc1.encoderPosition = 0;
    i->dc1.encoderAVal = 1;
    i->dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,4);

}

TEST_F(RoboboTests, move_left_1) {

    Globals *i = Globals::getInstance();
    i->dc1.encoderPosition = 0;
    i->dc1.encoderAVal = 1;
    i->dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,-1);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,-2);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,-3);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPosition,-4);

}

TEST_F(RoboboTests, move_right_2) {

    Globals *i = Globals::getInstance();
    i->dc2.encoderPosition = 0;
    i->dc2.encoderAVal = 1;
    i->dc2.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPosition,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPosition,1);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPosition,2);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPosition,3);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPosition,4);

}

