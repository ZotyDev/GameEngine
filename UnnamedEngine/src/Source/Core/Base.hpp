#pragma once

#include <memory>
#include <vector>

#include "Core/PlatformDetection.hpp"

// Get the proper debugbreak function
#if defined(UE_DEBUG)
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

#include "Core/Types.hpp"

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
        UEResult()                 : Result(UEResult::Undefined) {}
        UEResult(_UEResult result) : Result(result) {}
        UEResult(T value)          : Result(UEResult::Success), Value(value) {}

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

    struct EntryArgs
    {
        UEUint32              ArgCount = 0;
        std::vector<UEString> ArgList;
    };
}

#include "Core/Log.hpp"