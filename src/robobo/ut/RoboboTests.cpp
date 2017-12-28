#include "RoboboTests.h"
#include "EncoderISR.h"
#include "Globals.h"
using ::testing::_;
using ::testing::Return;

ArduinoMock * RoboboTests::arduino = NULL;

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
    i->dc1.encoderPos = 0;
    i->dc1.encoderAVal = 1;
    i->dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,1);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,2);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,3);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,4);

}

TEST_F(RoboboTests, move_left_1) {

    Globals *i = Globals::getInstance();
    i->dc1.encoderPos = 0;
    i->dc1.encoderAVal = 1;
    i->dc1.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,-1);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,-2);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,-3);

    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc1.encoderBPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->dc1.encoderPos,-4);

}

TEST_F(RoboboTests, move_right_2) {

    Globals *i = Globals::getInstance();
    i->dc2.encoderPos = 0;
    i->dc2.encoderAVal = 1;
    i->dc2.encoderBVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPos,0);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPos,1);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPos,2);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPos,3);

    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderAPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->dc2.encoderBPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->dc2.encoderPos,4);

}

