#pragma once

/* Platform Detection */
/*============================================================*/
#include "Core/PlatformDetection.h"

/* Utils */
/*============================================================*/
#include <functional>

/* Random */
/*============================================================*/
#include <random>

/* Bitwise */
/*============================================================*/
#include <bitset>

/* Multi-Threading */
/*============================================================*/
#include <thread>
#include <condition_variable>
#include <future>

/* Time */
/*============================================================*/
#include <ctime>
#include <time.h>
#include <chrono>

/* Stream */
/*============================================================*/
#include <iostream>
#include <sstream>
#include <fstream>

/* Data Types */
/*============================================================*/
#include <string>

/* Containers */
/*============================================================*/
#include <list>
#include <queue>
#include <deque>
#include <vector>

/* Engine Stuff */
/*============================================================*/
#include "Core/Base.h"
#include "Core/Log.h"

/* Platform Specific */
/*============================================================*/
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