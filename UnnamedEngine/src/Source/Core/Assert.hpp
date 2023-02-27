#pragma once

#include "Core/Base.hpp"
#include "Core/Log.hpp"
#include <filesystem>

#ifdef UE_ENABLE_ASSERTS
    #define UE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { UE_LOG##type##ERROR(msg, __VA_ARGS__); UE_DEBUG_BREAK(); } }
    #define UE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) UE_INTERNAL_ASSERT_IMPL(type, check, "Assert Failed: {0}", __VA_ARGS__)
    #define UE_INTERNAL_ASSERT_NO_MSG(type, check) UE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", UE_STRINGFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define UE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define UE_INTERNAL_ASSERT_GET_MACRO(...) UE_EXPAND_MACRO(UE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, UE_INTERNAL_ASSERT_WITH_MSG, UE_INTERNAL_ASSERT_NO_MSG))

    #define UE_ASSERT_APP(...) UE_EXPAND_MACRO(UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_APP_, __VA_ARGS__))
    #define UE_ASSERT_CORE(...) UE_EXPAND_MACRO(UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
    #define UE_ASSERT_APP(...)
    #define UE_ASSERT_CORE(...)
#endif