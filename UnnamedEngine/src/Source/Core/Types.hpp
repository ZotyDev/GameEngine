#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

// Lower and upper bounds of types
#define UE_CHAR_MIN   CHAR_MIN
#define UE_CHAR_MAX   CHAR_MAX
#define UE_INT8_MIN   INT_LEAST8_MIN
#define UE_INT8_MAX   INT_LEAST8_MAX
#define UE_INT16_MIN  INT_LEAST32_MIN
#define UE_INT32_MAX  INT_LEAST32_MAX
#define UE_INT64_MIN  INT_LEAST64_MIN
#define UE_INT64_MAX  INT_LEAST64_MAX
#define UE_UINT8_MAX  UINT_LEAST8_MAX
#define UE_UINT16_MAX UINT_LEAST16_MAX
#define UE_UINT32_MAX UINT_LEAST32_MAX
#define UE_UINT64_MAX UINT_LEAST64_MAX

namespace UE
{
    using UEBool = bool;
    using UEChar = char;

    using UEInt8   = std::int_least8_t;
    using UEInt16  = std::int_least16_t;
    using UEInt32  = std::int_least32_t;
    using UEInt64  = std::int_least64_t;

    using UEUint8   = std::uint_least8_t;
    using UEUint16  = std::uint_least16_t;
    using UEUint32  = std::uint_least32_t;
    using UEUint64  = std::uint_least64_t;

    using UEFloat   = float;
    using UEDouble  = double;

    using UECString = char*;
    using UEString  = std::string;

    using UEPath    = std::filesystem::path;
}