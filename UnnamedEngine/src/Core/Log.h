#pragma once

#include "Core/Base.h"

// Ignore all warnings raised inside external headers
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

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		static Ref<spdlog::logger>& GetLuaLogger() { return s_LuaLogger; }
	public:
		static UEResult CreateCustomLogger(const std::string& name);
		static Ref<spdlog::logger> GetCustomLogger(const std::string& name);
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
		static Ref<spdlog::logger> s_LuaLogger;
	private:
		static std::unordered_map<std::string, Ref<spdlog::logger>> s_CustomLoggers;
	};
}

// Core log macros
#define UE_CORE_TRACE(...)		::UE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define UE_CORE_INFO(...)		::UE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define UE_CORE_WARN(...)		::UE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UE_CORE_ERROR(...)		::UE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UE_CORE_CRITICAL(...)	::UE::Log::GetCoreLogger()->critical(__VA_ARGS__)
								
// Client log macros			
#define UE_TRACE(...)			::UE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define UE_INFO(...)			::UE::Log::GetClientLogger()->info(__VA_ARGS__)
#define UE_WARN(...)			::UE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UE_ERROR(...)			::UE::Log::GetClientLogger()->error(__VA_ARGS__)
#define UE_CRITICAL(...)		::UE::Log::GetClientLogger()->critical(__VA_ARGS__)

// Lua log macros
#define UE_LUA_TRACE(...)		::UE::Log::GetLuaLogger()->trace(__VA_ARGS__)
#define UE_LUA_INFO(...)		::UE::Log::GetLuaLogger()->info(__VA_ARGS__)
#define UE_LUA_WARN(...)		::UE::Log::GetLuaLogger()->warn(__VA_ARGS__)
#define UE_LUA_ERROR(...)		::UE::Log::GetLuaLogger()->error(__VA_ARGS__)
#define UE_LUA_CRITICAL(...)	::UE::Log::GetLuaLogger()->critical(__VA_ARGS__)