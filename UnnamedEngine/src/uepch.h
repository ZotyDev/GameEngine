#pragma once

#include "Core/PlatformDetection.h"

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
#include <time.h>
#include <iostream>
#include <random>
#include <bitset>

#include "Core/Base.h"

#include "Core/Log.h"

#ifdef UE_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
	// I feel like a ape
	#ifdef SendMessage
		#undef SendMessage
	#endif
#endif