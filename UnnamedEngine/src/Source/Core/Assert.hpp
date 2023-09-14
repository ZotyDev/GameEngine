#pragma once

#include "Core/Base.hpp"
#include "Core/Log.hpp"
#include <filesystem>

#if defined(UE_ENABLE_ASSERTS)
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define UE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { UE_LOG_CORE_ERROR(msg, __VA_ARGS__); UE_DEBUG_BREAK(); } }
	#define UE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) UE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define UE_INTERNAL_ASSERT_NO_MSG(type, check) UE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", UE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define UE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define UE_INTERNAL_ASSERT_GET_MACRO(...) UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, UE_INTERNAL_ASSERT_WITH_MSG, UE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define UE_ASSERT_APP(...)	UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_APP_, __VA_ARGS__) )
	#define UE_ASSERT_CORE(...)	UE_EXPAND_MACRO( UE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define UE_ASSERT_APP(...)
	#define UE_ASSERT_CORE(...)
#endif
