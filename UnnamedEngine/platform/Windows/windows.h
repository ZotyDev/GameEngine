#pragma once

#include "Core/PlatformDetection.h"

#ifdef UE_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>

	#include <WinSock2.h>
	#include <WS2tcpip.h>
#endif