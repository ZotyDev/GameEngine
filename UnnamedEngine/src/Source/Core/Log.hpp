#pragma once

#include "Core/Base.hpp"

#if defined(UE_PLATFORM_WINDOWS)
    #pragma warning(push, 0)
        #include <spdlog/spdlog.h>
        #include <spdlog/fmt/ostr.h>
    #pragma warning(pop)
#elif defined(UE_PLATFORM_WEB)
    #include <emscripten.h>
    #include <spdlog/fmt/fmt.h>
#endif

namespace UE
{
    #if defined(UE_PLATFORM_WINDOWS)
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

    #elif defined(UE_PLATFORM_WEB)

    #endif
}

// Windows logging
#if defined(UE_PLATFORM_WINDOWS)
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
#elif defined(UE_PLATFORM_WEB)
    #define UE_LOG_INIT()

    #define UE_LOG_CORE_TRACE(...)    emscripten_log(EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())
    #define UE_LOG_CORE_DEBUG(...)    emscripten_log(EM_LOG_DEBUG | EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())
    #define UE_LOG_CORE_INFO(...)     emscripten_log(EM_LOG_INFO | EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())
    #define UE_LOG_CORE_WARN(...)     emscripten_log(EM_LOG_WARN | EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())
    #define UE_LOG_CORE_ERROR(...)    emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())
    #define UE_LOG_CORE_CRITICAL(...) emscripten_log(EM_LOG_ERROR | EM_LOG_CONSOLE, fmt::format(__VA_ARGS__).c_str())

    #define UE_LOG_APP_TRACE(...)
    #define UE_LOG_APP_DEBUG(...)
    #define UE_LOG_APP_INFO(...)
    #define UE_LOG_APP_WARN(...)
    #define UE_LOG_APP_ERROR(...)
    #define UE_LOG_APP_CRITICAL(...)
#else
    #define UE_LOG_INIT()

    #define UE_LOG_CORE_TRACE(...)
    #define UE_LOG_CORE_DEBUG(...)
    #define UE_LOG_CORE_INFO(...)
    #define UE_LOG_CORE_WARN(...)
    #define UE_LOG_CORE_ERROR(...)
    #define UE_LOG_CORE_CRITICAL(...)

    #define UE_LOG_APP_TRACE(...)
    #define UE_LOG_APP_DEBUG(...)
    #define UE_LOG_APP_INFO(...)
    #define UE_LOG_APP_WARN(...)
    #define UE_LOG_APP_ERROR(...)
    #define UE_LOG_APP_CRITICAL(...)
#endif