#pragma once

#include <iostream>

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
#include <ctime>

#define LOG_INFO(x)			std::cout << x << std::endl
#define LOG_WARNING(x)		std::cout << x << std::endl
#define LOG_ERROR(x)		std::cout << x << std::endl
#define LOG_FATAL(x)		std::cout << x << std::endl