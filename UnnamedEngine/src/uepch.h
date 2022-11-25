#pragma once

/* Files */
/*============================================================*/
#include <filesystem>
#include <fstream>

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

/* Data Types */
/*============================================================*/
#include <string>

/* Containers */
/*============================================================*/
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <vector>
#include <initializer_list>
#include <unordered_map>
#include <map>
#include <tuple>
#include <optional>
#include <stack>

/* Parsing */
/*============================================================*/
#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

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