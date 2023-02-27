#include <Core/Base.hpp>
#include <gtest/gtest.h>

namespace UE
{
    TEST(UEResult, Init_No_Parameters)
    {
        UEResult<int> Result;
        EXPECT_FALSE(Result);
        EXPECT_EQ(Result.Result, UEResult<>::Undefined);
    }

    TEST(UEResult, Init_Error_State)
    {
        UEResult<int> Result(UEResult<>::Error);
        EXPECT_FALSE(Result);
        EXPECT_EQ(Result.Result, UEResult<>::Error);
    }

    TEST(UEResult, Init_Success_State)
    {
        UEResult<int> Result(UEResult<>::Success);
        EXPECT_TRUE(Result);
        EXPECT_EQ(Result.Result, UEResult<>::Success);
    }

    TEST(UEResult, Init_Warn_State)
    {
        UEResult<int> Result(UEResult<>::Warn);
        EXPECT_TRUE(Result);
        EXPECT_EQ(Result.Result, UEResult<>::Warn);
    }

    TEST(UEResult, Init_Data)
    {
        UEResult<int> Result(0);
        EXPECT_TRUE(Result);
        EXPECT_EQ(Result.Result, UEResult<>::Success);
        EXPECT_EQ(Result.Value, 0);
    }
}