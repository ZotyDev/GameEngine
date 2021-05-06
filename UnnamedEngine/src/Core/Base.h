#pragma once

#include <memory>

#include "Core/PlatformDetection.h"

#ifdef UE_DEBUG
	#if defined(UE_PLATFORM_WINDOWS)
		#define UE_DEBUG_BREAK() __debugbreak()

		#define UE_BYTESWAP_16(x) _byteswap_ushort(x)
		#define UE_BYTESWAP_32(x) _byteswap_ulong(x)
		#define UE_BYTESWAP_64(x) _byteswap_uint64(x)
	#elif defined(UE_PLATFORM_LINUX)
		#include <signal.h>
		#define UE_DEBUG_BREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!'"
	#endif
	#define UE_ENABLE_ASSERTS
#else
	#define UE_DEBUG_BREAK()
#endif

#define UE_EXPAND_MACRO(x) x
#define UE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define UE_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

namespace UE
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Core/Log.h"
#include "Core/Assert.h"
#include "Core/PlatformUtilities.h"