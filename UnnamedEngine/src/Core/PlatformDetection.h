// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define UE_PLATFORM_WINDOWS
	#else 
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif // _WIN64

/*
*  We need to check all the platforms since all of them
*  contain TARGET_OS_MAC (the order is inportant)
*/
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define UE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define UE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#endif

/*
*  We need to check for Android before linux since
*  android contain __linux__
*/
#elif defined(__ANDROID__)
	#define UE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define UE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // End of platform detection
