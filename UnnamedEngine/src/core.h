#pragma once

#include "logger/logger.h"
#include "time/timeManager.h"

#ifdef 

#endif // 


#define LOG_INFO(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][INFO] : ", __VA_ARGS__)
#define LOG_WARN(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][WARN] : ", __VA_ARGS__)
#define LOG_ERROR(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][ERROR] : ", __VA_ARGS__)
#define LOG_FATAL(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][FATAL] : ", __VA_ARGS__)
