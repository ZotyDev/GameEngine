#include "uepch.h"
#include "Log.h"

#if defined(UE_PLATFORM_WINDOWS)
	#pragma warning(push 0)
		#include <spdlog/sinks/stdout_color_sinks.h>
		#include <spdlog/sinks/basic_file_sink.h>
	#pragma warning(pop)
#elif defined(UE_PLATFORM_WINDOWS)

#endif

namespace UE 
{
	#if defined(UE_PLATFORM_WINDOWS)
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;
	Ref<spdlog::logger> Log::s_LuaLogger;

	std::unordered_map<std::string, Ref<spdlog::logger>> Log::s_CustomLoggers;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("UnnamedEngine.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = CreateRef<spdlog::logger>("UnnamedEngine", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = CreateRef<spdlog::logger>("VoxelGame", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);

		s_LuaLogger = CreateRef<spdlog::logger>("Lua", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_LuaLogger);
		s_LuaLogger->set_level(spdlog::level::trace);
		s_LuaLogger->flush_on(spdlog::level::trace);
	}

	UEResult<> Log::CreateCustomLogger(const std::string& name)
	{
		auto it = s_CustomLoggers.find(name);
		if (it != s_CustomLoggers.end())
		{
			UE_CORE_ERROR("Failed to create logger {0}: already registered", name);
			return UEResult<>::Error;
		}

		std::vector<spdlog::sink_ptr> LogSinks;
		LogSinks.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
		LogSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("logs/" + name + "/" + name + ".log"));

		LogSinks[0]->set_pattern("%^[%T] %n: %v%$");
		LogSinks[1]->set_pattern("[%T] [%l] %n: %v");

		Ref<spdlog::logger> CustomLogger = CreateRef<spdlog::logger>(name, begin(LogSinks), end(LogSinks));
		spdlog::register_logger(CustomLogger);
		CustomLogger->set_level(spdlog::level::trace);
		CustomLogger->flush_on(spdlog::level::trace);

		s_CustomLoggers.insert({ name, CustomLogger });

		return UEResult<>::Success;
	}

	Ref<spdlog::logger> Log::GetCustomLogger(const std::string& name)
	{
		auto it = s_CustomLoggers.find(name);
		if (it == s_CustomLoggers.end())
		{
			UE_CORE_ERROR("Failed to get logger {0}: not registered");
			return nullptr;
		}

		return it->second;
	}

	#elif defined(UE_PLATFORM_WEB)
	#endif
}