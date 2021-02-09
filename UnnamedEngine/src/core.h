#pragma once

#define BIT(x)				1 << x

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API __declspec(dllexport)
	#else
		#define UE_API __declspec(dllimport)
	#endif
	
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>

	#include <Windows.h>

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

#include "pch.h"