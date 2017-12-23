#include "RoboboTests.h"

ArduinoMock * RoboboTests::arduino = NULL;

TEST_F(RoboboTests, test_name) {
    EXPECT_EQ (1, 1);
}

