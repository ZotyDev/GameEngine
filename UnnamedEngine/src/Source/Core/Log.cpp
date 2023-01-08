#include "uepch.hpp"
#include "Core/Log.hpp"

#if defined(UE_PLATFORM_WINDOWS)
    #pragma warning(push, 0)
        #include <spdlog/sinks/dup_filter_sink.h>
        #include <spdlog/sinks/stdout_color_sinks.h>
		#include <spdlog/sinks/basic_file_sink.h>
        #include <spdlog/sinks/rotating_file_sink.h>
        #include <spdlog/sinks/daily_file_sink.h>
    #pragma warning(pop)
#elif defined(UE_PLATFORM_WEB)
    
#endif

namespace UE
{
#if defined(UE_PLATFORM_WINDOWS)
    Ref<spdlog::logger> Log::s_EngineLogger;
    Ref<spdlog::logger> Log::s_AppLogger;

    static UEUint32 DupFilterSeconds = 60;

    void Log::Init()
    {
        auto LoggerDupFilter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(DupFilterSeconds));
        auto MtConsoleLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto LoggerFile = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs/UnnamedEngine.log", 1048576 * 100, 10, true);

        MtConsoleLogger->set_pattern("%^[%T][%l] %n: %v%$");
        LoggerFile->set_pattern("[%T][%l] %n %v");

        LoggerDupFilter->add_sink(MtConsoleLogger);
        LoggerDupFilter->add_sink(LoggerFile);

        s_EngineLogger = CreateRef<spdlog::logger>("UnnamedEngine", LoggerDupFilter);
        s_AppLogger = CreateRef<spdlog::logger>("UnnamedServer", LoggerDupFilter);

        spdlog::register_logger(s_EngineLogger);
        spdlog::register_logger(s_AppLogger);

        s_EngineLogger->set_level(spdlog::level::trace);
        s_AppLogger->set_level(spdlog::level::trace);

        s_EngineLogger->flush_on(spdlog::level::trace);
        s_AppLogger->flush_on(spdlog::level::trace);
    }
#endif
}