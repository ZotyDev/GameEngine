#pragma once

#include "Core/Base.h"
#include "Core/Log.h"
#include <filesystem>

#ifdef UE_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define UE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { UE##type##ERROR(msg, __VA_ARGS__); UE_DEBUG_BREAK(); } }
#define UE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) UE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define UE_INTERNAL_ASSERT_NO_MSG(type, check) UE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", UE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define UE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define UE_INTERNAL_ASSERT_GET_MACRO(...) UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, UE_INTERNAL_ASSERT_WITH_MSG, UE_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define UE_ASSERT(...)		UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define UE_CORE_ASSERT(...)	UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define UE_ASSERT(...)
#define UE_CORE_ASSERT(...)
#endif