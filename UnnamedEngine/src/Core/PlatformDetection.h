// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define UE_PLATFORM_WINDOWS
		#define UE_PLATFORM_GLFW

		#define UE_BYTESWAP_16(x)		_byteswap_ushort(x)
		#define UE_BYTESWAP_32(x)		_byteswap_ulong(x)
		#define UE_BYTESWAP_64(x)		_byteswap_uint64(x)
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
		/* IPhone x64*/
		#define UE_PLATFORM_IOS

		#define UE_BYTESWAP_16(x)		CFSwapInt16(x)
		#define UE_BYTESWAP_32(x)		CFSwapInt32(x)
		#define UE_BYTESWAP_64(x)		CFSwapInt64(x)

		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		/* MacOS x64 */
		#define UE_PLATFORM_MACOS

		#define UE_BYTESWAP_16(x)		CFSwapInt16(x)
		#define UE_BYTESWAP_32(x)		CFSwapInt32(x)
		#define UE_BYTESWAP_64(x)		CFSwapInt64(x)

		#error "MacOS is not supported!"
	#endif

/*
*  We need to check for Android before linux since
*  android contain __linux__
*/
#elif defined(__ANDROID__)
	/* Android x64 */
	#define UE_PLATFORM_ANDROID

	#define UE_BYTESWAP_16(x)			bswap_16(x)
	#define UE_BYTESWAP_32(x)			bswap_32(x)
	#define UE_BYTESWAP_64(x)			bswap_64(x)

	#error "Android is not supported!"
#elif defined(__linux__)
	/* Linux x64 */
	#define UE_PLATFORM_LINUX

	#define UE_BYTESWAP_16(x)			bswap_16(x)
	#define UE_BYTESWAP_32(x)			bswap_32(x)
	#define UE_BYTESWAP_64(x)			bswap_64(x)

	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // End of platform detection
