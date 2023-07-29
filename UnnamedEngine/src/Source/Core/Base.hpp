#pragma once

#include <memory>
#include <vector>

#include "Core/PlatformIndependenceLayer/PlatformDetection.hpp"

// Get the proper debugbreak function
#if defined(UE_DEBUG)
    #if defined(UE_PLATFORM_WINDOWS)
        #define UE_DEBUG_BREAK() __debugbreak()
    
    #elif defined(UE_PLATFORM_LINUX)
        #include <signal.h>
        #define UE_DEBUG_BREAK() raise(SIGTRAP)

    #elif defined(UE_PLATFORM_MACOS)
        #include <csignal>
        #define UE_DEBUG_BREAK() std::raise(SIGTRAP)

    #elif defined(UE_PLATFORM_ANDROID)
        #include <signal.h>
        #define UE_DEBUG_BREAK() raise(SIGTRAP)

    #elif defined(UE_PLATFORM_EMSCRIPTEN)
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

#define UE_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Core/PlatformIndependenceLayer/Types.hpp"

namespace UE
{
    // A Scope is a unique pointer that cannot have more than one owner
    template<typename T>
    using Scope = std::unique_ptr<T>;

    // Creates a Scope using the input args
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    // A Ref is a shared pointer that can have more than one owner, but free()
    // is called on the data if the owner count gets to 0
    template<typename T>
    using Ref = std::shared_ptr<T>;

    // Creates a Ref using the input args
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // UEResult is a abstraction used to return both data and result code
    template<typename T = void>
    class UEResult
    {
    public:
        using _UEResult = UEInt8;
        enum : _UEResult
        {
            Error     = -1,
            Success   = 0,
            Warn      = 1,
            Undefined = UE_INT8_MAX
        };

    public:
        UEResult()                          : Result(UEResult::Undefined) {}
        UEResult(T value)                   : Result(UEResult::Success), Value(value) {}
        UEResult(T value, _UEResult result) : Result(result), Value(value) {}
        UEResult(_UEResult result)          : Result(result) {}

        // Implicit operator
        operator UEBool() const
        {
            return (Result != UEResult::Error && Result != UEResult::Undefined);
        }

        UEResult& operator = (_UEResult result)
        {
            Result = result;
            return *this;
        }

    public:
        _UEResult Result;
        T Value;
    };

    // Implementation for UEBool
    template<>
    class UEResult<UEBool>
    {
    public:
        using _UEResult = UEInt8;
        enum : _UEResult
        {
            Error     = -1,
            Success   = 0,
            Warn      = 1,
            Undefined = UE_INT8_MAX
        };

    public:
        UEResult()                               : Result(UEResult::Undefined) {}
        UEResult(UEBool value)                   : Result(UEResult::Success), Value(value) {}
        UEResult(UEBool value, _UEResult result) : Result(result), Value(value) {}
        UEResult(_UEResult result)               : Result(result) {}

        // Implicit operator
        operator UEBool() const
        {
            return (Result != UEResult::Error && Result != UEResult::Undefined) && Value;
        }

        UEResult& operator = (_UEResult result)
        {
            Result = result;
            return *this;
        }

    public:
        _UEResult Result;
        UEBool Value;
    };

    // Implementation without data
    template<>
    class UEResult<void>
    {
    public:
        using _UEResult = UEInt8;
        enum : _UEResult
        {
            Error     = -1,
            Success   = 0,
            Warn      = 1,
            Undefined = UE_INT8_MAX
        };

    public:
        UEResult()                 : Result(UEResult::Undefined) {}
        UEResult(_UEResult result) : Result(result) {}

        // Implicit operator
        operator UEBool() const
        {
            return (Result != UEResult::Error && Result != UEResult::Undefined);
        }
        
        UEResult& operator = (_UEResult result)
        {
            Result = result;
            return *this;
        }

    public:
        _UEResult Result;
    };

    // Args that are passed to the engine at the start
    struct EntryArgs
    {
        UEUint32              Count = 0;
        std::vector<UEString> List;
    };
}

#include "uepch.hpp"
#include "Core/Log.hpp"
#include "Core/Assert.hpp"