#pragma once

#include "Core/Base.hpp"

#pragma warning(push, 0)
    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace UE
{
    class Log
    {
    public:
        static void Init();
        static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
        static Ref<spdlog::logger>& GetAppLogger()    { return s_AppLogger; }
    private:
        static Ref<spdlog::logger> s_EngineLogger;
        static Ref<spdlog::logger> s_AppLogger;
    };
}

// Windows logging
//#if defined(UE_PLATFORM_WINDOWS)
#define UE_LOG_INIT()             ::UE::Log::Init()

#define UE_LOG_CORE_TRACE(...)    ::UE::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define UE_LOG_CORE_DEBUG(...)    ::UE::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define UE_LOG_CORE_INFO(...)     ::UE::Log::GetEngineLogger()->info(__VA_ARGS__)
#define UE_LOG_CORE_WARN(...)     ::UE::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define UE_LOG_CORE_ERROR(...)    ::UE::Log::GetEngineLogger()->error(__VA_ARGS__)
#define UE_LOG_CORE_CRITICAL(...) ::UE::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define UE_LOG_APP_TRACE(...)     ::UE::Log::GetAppLogger()->trace(__VA_ARGS__)
#define UE_LOG_APP_DEBUG(...)     ::UE::Log::GreAppLogger()->trace(__VA_ARGS__)
#define UE_LOG_APP_INFO(...)      ::UE::Log::GetAppLogger()->info(__VA_ARGS__)
#define UE_LOG_APP_WARN(...)      ::UE::Log::GetAppLogger()->warn(__VA_ARGS__)
#define UE_LOG_APP_ERROR(...)     ::UE::Log::GetAppLogger()->error(__VA_ARGS__)
#define UE_LOG_APP_CRITICAL(...)  ::UE::Log::GetAppLogger()->critical(__VA_ARGS__)
//#elif defined(UE_PLATFORM_WEB)
//    #define CAT( A, B ) A ## B
//    #define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
//    
//    #define GET_COUNT( _1, _2, COUNT, ... ) COUNT
//    #define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, MANY, 1 )
//    
//    #define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)
//
//    #define UE_LOG_INIT()
//
//    #define _UE_LOG_CORE_TRACE_1(arg)    emscripten_log(EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//    #define _UE_LOG_CORE_DEBUG_1(arg)    emscripten_log(EM_LOG_DEBUG | EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//    #define _UE_LOG_CORE_INFO_1(arg)     emscripten_log(EM_LOG_INFO | EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//    #define _UE_LOG_CORE_WARN_1(arg)     emscripten_log(EM_LOG_WARN | EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//    #define _UE_LOG_CORE_ERROR_1(arg)    emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//    #define _UE_LOG_CORE_CRITICAL_1(arg) emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format("{}", arg).c_str())
//
//    #define _UE_LOG_CORE_TRACE_MANY(fmt, ...)    emscripten_log(EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__).c_str())
//    #define _UE_LOG_CORE_DEBUG_MANY(fmt, ...)    emscripten_log(EM_LOG_DEBUG | EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__).c_str())
//    #define _UE_LOG_CORE_INFO_MANY(fmt, ...)     emscripten_log(EM_LOG_INFO | EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__).c_str())
//    #define _UE_LOG_CORE_WARN_MANY(fmt, ...)     emscripten_log(EM_LOG_WARN | EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__).c_str())
//    #define _UE_LOG_CORE_ERROR_MANY(fmt, ...)    emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__).c_str())
//    #define _UE_LOG_CORE_CRITICAL_MANY(fmt, ...) emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format(fmt, __VA_ARGS__.)c_str())
//
//    #define UE_LOG_CORE_TRACE(...)            VA_SELECT(_UE_LOG_CORE_TRACE, __VA_ARGS__)
//    #define UE_LOG_CORE_DEBUG(...)            VA_SELECT(_UE_LOG_CORE_DEBUG, __VA_ARGS__)
//    #define UE_LOG_CORE_INFO(...)             VA_SELECT(_UE_LOG_CORE_INFO, __VA_ARGS__)
//    #define UE_LOG_CORE_WARN(...)             VA_SELECT(_UE_LOG_CORE_WARN, __VA_ARGS__)
//    #define UE_LOG_CORE_ERROR(...)            VA_SELECT(_UE_LOG_CORE_ERROR, __VA_ARGS__)
//    #define UE_LOG_CORE_CRITICAL(...)         VA_SELECT(_UE_LOG_CORE_CRITICAL, __VA_ARGS__)
//
//    #define UE_LOG_APP_TRACE(...)
//    #define UE_LOG_APP_DEBUG(...)
//    #define UE_LOG_APP_INFO(...)
//    #define UE_LOG_APP_WARN(...)
//    #define UE_LOG_APP_ERROR(...)
//    #define UE_LOG_APP_CRITICAL(...)
//#else
//    #define UE_LOG_INIT()
//
//    #define UE_LOG_CORE_TRACE(...)
//    #define UE_LOG_CORE_DEBUG(...)
//    #define UE_LOG_CORE_INFO(...)
//    #define UE_LOG_CORE_WARN(...)
//    #define UE_LOG_CORE_ERROR(...)
//    #define UE_LOG_CORE_CRITICAL(...)
//
//    #define UE_LOG_APP_TRACE(...)
//    #define UE_LOG_APP_DEBUG(...)
//    #define UE_LOG_APP_INFO(...)
//    #define UE_LOG_APP_WARN(...)
//    #define UE_LOG_APP_ERROR(...)
//    #define UE_LOG_APP_CRITICAL(...)
//#endif