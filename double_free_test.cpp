#include <gtest/gtest.h>

struct DoubleFreeTest : testing::Test {
};

TEST_F(DoubleFreeTest, doubleFreeTest) { 
    auto* arr = new int[10];
    delete [] arr;
    delete [] arr;
    EXPECT_TRUE(false != true); 
}
