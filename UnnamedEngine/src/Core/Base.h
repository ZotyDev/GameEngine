#pragma once

#include <memory>

#include "PlatformIndependenceLayer/PlatformDetection.h"

#ifdef UE_DEBUG
	#if defined(UE_PLATFORM_WINDOWS)
		#define UE_DEBUG_BREAK() __debugbreak()
		
	#elif defined(UE_PLATFORM_LINUX)
		#include <signal.h>
		#define UE_DEBUG_BREAK() raise(SIGTRAP)
	
	#elif defined(UE_PLATFORM_ANDROID)
		#include <signal.h>
		#define UE_DEBUG_BREAK() raise(SIGTRAP)

	#elif defined(UE_PLATFORM_WEB)
		#define UE_DEBUG_BREAK() emscripten_debugger()

	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define UE_ENABLE_ASSERTS
#else
	#define UE_DEBUG_BREAK()
#endif

#define UE_EXPAND_MACRO(x) x
#define UE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define UE_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

#define UE_VALUE_ERROR -1
#define UE_VALUE_SUCCESS 0

#include "PlatformIndependenceLayer/Types.h"

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

	typedef UEInt8 _UEResultT;

	template<typename T = void>
	class UEResult
	{
	public:
		enum : _UEResultT {
			Error = -1,
			Success = 0,
			Warn = 1,
			Undefined = UE_INT8_MAX
		};

	public:
		UEResult()
			: Result(UEResult::Undefined) {}

		UEResult(_UEResultT result)
			: Result(result) {}

		operator UEBool() const
		{
			return (Result == UEResult::Success);
		}

		UEResult& operator = (_UEResultT result)
		{
			Result = result;
			return *this;
		}

		T Value;
		_UEResultT Result;
	};

	template<>
	class UEResult<void>
	{
	public:
		enum : _UEResultT {
			Error = -1,
			Success = 0,
			Warn = 1,
			Undefined = UE_INT8_MAX
		};

	public:
		UEResult()
			: Result(UEResult::Undefined) {}

		UEResult(_UEResultT result)
			: Result(result) {}

		operator UEBool() const
		{
			return (Result == UEResult::Success);
		}

		UEResult& operator = (_UEResultT result)
		{
			Result = result;
			return *this;
		}

		_UEResultT Result;
	};
}

#include "Core/Log.h"
#include "Core/Assert.h"
#include "Core/PlatformUtilities.h"