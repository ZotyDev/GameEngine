#pragma once

#include "Core.h"
#include "Pch.h"

#ifdef UE_DEBUG
	#define LOG_INFO(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][INFO] : ", __VA_ARGS__)
	#define LOG_WARN(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][WARN] : ", __VA_ARGS__)
	#define LOG_ERROR(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][ERROR] : ", __VA_ARGS__)
	#define LOG_FATAL(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][FATAL] : ", __VA_ARGS__)
#else
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
	#define LOG_FATAL(...)
#endif

namespace UE
{
	namespace Logger
	{
		std::list<std::string> LogList;
		std::ofstream FileOut;

		template<typename Arg>
		UE_API void _construct_string_from_args(std::ostringstream& out, Arg arg)
		{
			out << arg;
		}

		template<typename Arg, typename... Args>
		UE_API void _construct_string_from_args(std::ostringstream& out, Arg arg, Args... args)
		{
			out << arg;
			_construct_string_from_args(out, args...);
		}

		template<typename... Args>
		UE_API void Log(Args... args)
		{
			std::ostringstream out;
			_construct_string_from_args(out, args...);
			LogList.push_back(out.str());
		}

		UE_API void ShowLog(const char* filePath)
		{
			while (!LogList.empty())
			{
				std::string outputString = LogList.front();
				std::cout << outputString << std::endl;

				FileOut.open(filePath, std::ios::app);
				FileOut << outputString << std::endl;
				FileOut.close();

				LogList.pop_front();
			}
		}
	}
}