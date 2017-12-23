#include "RoboboTests.h"
#include "EncoderISR.h"
#include "Globals.h"
using ::testing::_;
using ::testing::Return;

ArduinoMock * RoboboTests::arduino = NULL;

TEST_F(RoboboTests, store_previous_value_1) 
{

    Globals *i = Globals::getInstance();

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1aPrevVal,1);
    ASSERT_EQ( i->encoder1bPrevVal,1);

}

TEST_F(RoboboTests, store_previous_value_2) 
{

    Globals *i = Globals::getInstance();

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2aPrevVal,1);
    ASSERT_EQ( i->encoder2bPrevVal,1);

}

TEST_F(RoboboTests, move_right_1) {

    Globals *i = Globals::getInstance();
    i->encoder1pos = 0;
    i->encoder1aVal = 1;
    i->encoder1bVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,0);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,1);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,2);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,3);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,4);

}

TEST_F(RoboboTests, move_left_1) {

    Globals *i = Globals::getInstance();
    i->encoder1pos = 0;
    i->encoder1aVal = 1;
    i->encoder1bVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,0);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,-1);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(0));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,-2);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,-3);

    EXPECT_CALL(*arduino, digitalRead(i->encoder1aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder1bPin))
        .WillOnce(Return(1));
    encoder1_ISR();

    ASSERT_EQ( i->encoder1pos,-4);

}

TEST_F(RoboboTests, move_right_2) {

    Globals *i = Globals::getInstance();
    i->encoder2pos = 0;
    i->encoder2aVal = 1;
    i->encoder2bVal = 1;

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2pos,0);

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2pos,1);

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(0));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2pos,2);

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(0));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2pos,3);

    EXPECT_CALL(*arduino, digitalRead(i->encoder2aPin))
        .WillOnce(Return(1));
    EXPECT_CALL(*arduino, digitalRead(i->encoder2bPin))
        .WillOnce(Return(1));
    encoder2_ISR();

    ASSERT_EQ( i->encoder2pos,4);

}

