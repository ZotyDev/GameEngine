#pragma once

#define BIT(x)				1 << x

#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API __declspec(dllexport)
	#else
		#define UE_API __declspec(dllimport)
	#endif
	
	#include <Windows.h>

	#define GLFW_INCLUDE_VULKAN
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>

#else
	#error UnnamedEngine only support Windows!
#endif

#ifdef UE_DEBUG
	#define UE_LOG_INFO(...)		UE::Logger::ue_log("[", UE::LocalTime::GetHour(), ":", UE::LocalTime::GetMinute(), ":", UE::LocalTime::GetSecond(), "]", "[UnnamedEngine][INFO] : ",  __VA_ARGS__)
	#define UE_LOG_WARN(...)		UE::Logger::ue_log("[", UE::LocalTime::GetHour(), ":", UE::LocalTime::GetMinute(), ":", UE::LocalTime::GetSecond(), "]", "[UnnamedEngine][WARN] : ",  __VA_ARGS__)
	#define UE_LOG_ERROR(...)		UE::Logger::ue_log("[", UE::LocalTime::GetHour(), ":", UE::LocalTime::GetMinute(), ":", UE::LocalTime::GetSecond(), "]", "[UnnamedEngine][ERROR] : ",  __VA_ARGS__)
	#define UE_LOG_FATAL(...)		UE::Logger::ue_log("[", UE::LocalTime::GetHour(), ":", UE::LocalTime::GetMinute(), ":", UE::LocalTime::GetSecond(), "]", "[UnnamedEngine][FATAL] : ",  __VA_ARGS__)
#else
	#define UE_LOG_INFO(...)
	#define UE_LOG_WARN(...)
	#define UE_LOG_ERROR(...)
	#define UE_LOG_FATAL(...)
#endif

#include "Pch.h"

namespace UE
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}