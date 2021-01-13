#pragma once

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API __declspec(dllexport)
	#else
		#define UE_API __declspec(dllimport)
	#endif
#else
	#error Unnamed Engine only support Windows!
#endif