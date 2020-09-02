#include <gtest/gtest.h>

struct LeakingTest : testing::Test {
};

TEST_F(LeakingTest, leakingArray) { 
    auto* arr = new int[10];
    (void)arr;
    EXPECT_TRUE(false != true); 
}
