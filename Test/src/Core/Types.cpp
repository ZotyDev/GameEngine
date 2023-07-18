#include <Core/PlatformIndependenceLayer/Types.hpp>
#include <gtest/gtest.h>

namespace UE
{
    TEST(Types, UEInt8_Size)
    {
        EXPECT_GE(sizeof(UEInt8) * 8, 8);
    }

    TEST(Types, UEInt16_Size)
    {
        EXPECT_GE(sizeof(UEInt16) * 8, 16);
    }

    TEST(Types, UEInt32_Size)
    {
        EXPECT_GE(sizeof(UEInt32) * 8, 32);
    }

    TEST(Types, UEInt64_Size)
    {
        EXPECT_GE(sizeof(UEInt64) * 8, 64);
    }

    TEST(Types, UEUint8_Size)
    {
        EXPECT_GE(sizeof(UEUint8) * 8, 8);
    }

    TEST(Types, UEUint16_Size)
    {
        EXPECT_GE(sizeof(UEUint16) * 8, 16);
    }

    TEST(Types, UEUint32_Size)
    {
        EXPECT_GE(sizeof(UEUint32) * 8, 32);
    }

    TEST(Types, UEUint64_Size)
    {
        EXPECT_GE(sizeof(UEUint64) * 8, 64);
    }

    TEST(Types, UEFloat_Size)
    {
        EXPECT_GE(sizeof(UEFloat) * 8, 32);
    }

    TEST(Types, UEDouble_Size)
    {
        EXPECT_GE(sizeof(UEDouble) * 8, 64);
    }
}