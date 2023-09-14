#include "Core/Log.hpp"

#pragma warning(push, 0)
    #include <spdlog/sinks/dup_filter_sink.h>
    #include <spdlog/sinks/stdout_color_sinks.h>
	#include <spdlog/sinks/basic_file_sink.h>
    #include <spdlog/sinks/rotating_file_sink.h>
    #include <spdlog/sinks/daily_file_sink.h>
#pragma warning(pop)

#if defined(UE_PLATFORM_EMSCRIPTEN)
    #include <spdlog/sinks/base_sink.h>
    #include <spdlog/details/null_mutex.h>
#endif

#if defined(UE_PLATFORM_EMSCRIPTEN)
        template<typename Mutex>
        class web_sink : public spdlog::sinks::base_sink<Mutex>
        {
        protected:
            void sink_it_(const spdlog::details::log_msg& msg) override
            {
                spdlog::memory_buf_t formatted;
                spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
                switch (msg.level)
                {
                default:
                case spdlog::level::trace:
                    {
                        emscripten_log(EM_LOG_CONSOLE, fmt::to_string(formatted).c_str());
                        break;
                    }
                case spdlog::level::debug:
                    {
                        emscripten_log(EM_LOG_CONSOLE | EM_LOG_DEBUG, fmt::to_string(formatted).c_str());
                        break;
                    }
                case spdlog::level::info:
                    {
                        emscripten_log(EM_LOG_CONSOLE | EM_LOG_INFO, fmt::to_string(formatted).c_str());
                        break;
                    }
                case spdlog::level::warn:
                    {
                        emscripten_log(EM_LOG_CONSOLE | EM_LOG_WARN, fmt::to_string(formatted).c_str());
                        break;
                    }
                case spdlog::level::err:
                case spdlog::level::critical:
                    {
                        emscripten_log(EM_LOG_CONSOLE | EM_LOG_ERROR, fmt::to_string(formatted).c_str());
                        break;
                    }
                }
            }

            void flush_() override
            {

            }
        };

        using web_sink_mt = web_sink<std::mutex>;
        using web_sink_st = web_sink<spdlog::details::null_mutex>;
#endif

namespace UE
{
    Ref<spdlog::logger> Log::s_EngineLogger;
    Ref<spdlog::logger> Log::s_AppLogger;

    static UEUint32 DupFilterSeconds = 60;

    void Log::Init()
    {
        auto LoggerDupFilter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(DupFilterSeconds));

        #if defined(UE_PLATFORM_WINDOWS) || \
            defined(UE_PLATFORM_MACOS)   || \
            defined(UE_PLATFORM_LINUX)
            // Console logger
            auto ConsoleLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            ConsoleLogger->set_pattern("%^[%T][%l] %n: %v%$");
            LoggerDupFilter->add_sink(ConsoleLogger);

            // File logger
            auto FileLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs/UnnamedEngine.log", 1048576 * 100, 10, true);
            FileLogger->set_pattern("[%T][%l] %n %v");
            LoggerDupFilter->add_sink(FileLogger);
        #elif defined(UE_PLATFORM_EMSCRIPTEN)
            // Web console logger
            auto WebLogger = std::make_shared<web_sink_mt>();
            WebLogger->set_pattern("[%T][%l] %n %v");
            LoggerDupFilter->add_sink(WebLogger);
        #endif

        s_EngineLogger = CreateRef<spdlog::logger>("UnnamedEngine", LoggerDupFilter);
        s_AppLogger = CreateRef<spdlog::logger>("UnnamedServer", LoggerDupFilter);

        spdlog::register_logger(s_EngineLogger);
        spdlog::register_logger(s_AppLogger);

        s_EngineLogger->set_level(spdlog::level::trace);
        s_AppLogger->set_level(spdlog::level::trace);

        s_EngineLogger->flush_on(spdlog::level::trace);
        s_AppLogger->flush_on(spdlog::level::trace);
    }
}
