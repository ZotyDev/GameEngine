#pragma once

#include <iostream>

#include "logger/logger.h"
#include "time/timeManager.h"

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <time.h>
#include <ctime>

#define LOG_INFO(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][INFO] : ", __VA_ARGS__)
#define LOG_WARN(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][WARN] : ", __VA_ARGS__)
#define LOG_ERROR(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][ERROR] : ", __VA_ARGS__)
#define LOG_FATAL(...)		Logger::Log("[", TimeManager::GetHour(), ":", TimeManager::GetMinute(), ":", TimeManager::GetSecond(), "]","[Engine][FATAL] : ", __VA_ARGS__)
