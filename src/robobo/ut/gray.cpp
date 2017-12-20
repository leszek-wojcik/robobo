#include "gtest/gtest.h"
#include "EncoderISR.h"
 
TEST (GreyLookupTest, Lookuptest) { 
    EXPECT_EQ (1, greyValue(1,1));
    EXPECT_EQ (2, greyValue(0,1));
    EXPECT_EQ (3, greyValue(0,0));
    EXPECT_EQ (4, greyValue(1,0));
}
