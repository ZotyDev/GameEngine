#include <gtest/gtest.h>

TEST(Testing, Test) 
{
    EXPECT_STRNE("hello", "world");

    EXPECT_EQ(6 * 7, 42);
}