#include <gtest/gtest.h>

struct OkTest : testing::Test {
};

TEST_F(OkTest, checkIfFalseIsNotTrue) { EXPECT_TRUE(false != true); }

TEST_F(OkTest, checkIfTrueIsNotFalse) { EXPECT_TRUE(true != false); }
