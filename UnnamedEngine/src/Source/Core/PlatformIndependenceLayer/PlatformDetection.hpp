// Platform detection using predefined macros

////////////////////////////////////////////////////////////
// - Web Browser
////////////////////////////////////////////////////////////
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN)
    #define UE_PLATFORM_EMSCRIPTEN

    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <byteswap.h>

    #define UE_BYTESWAP_16(x) bswap_16(x)
    #define UE_BYTESWAP_32(x) bswap_32(x)
    #define UE_BYTESWAP_64(x) bswap_64(x)

////////////////////////////////////////////////////////////
// - Windows x64
////////////////////////////////////////////////////////////
#elif defined(_WIN32)
    #if defined(_WIN64)
        #define UE_PLATFORM_WINDOWS

        #include <stdlib.h>

        #define UE_BYTESWAP_16(x) _byteswap_ushort(x)
        #define UE_BYTESWAP_32(x) _byteswap_ulong(x)
        #define UE_BYTESWAP_64(x) _byteswap_uint64(x)

        #define UE_API_WINSOCK
    #else
        #error "x86 builds are not supported!"
    #endif

////////////////////////////////////////////////////////////
// - Apple Platforms (IPhone and MacOS)
// We need to check all the platforms since all of them
// contain TARGET_OS_MAC (the order is important)
////////////////////////////////////////////////////////////
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"

    ////////////////////////////////////////////////////////////
    // - IPhone
    ////////////////////////////////////////////////////////////
    #elif TARGET_OS_IPHONE == 1
        #define UE_PLATFORM_IOS

        #error "IPhone is not supported!"

    ////////////////////////////////////////////////////////////
    // - MacOS
    ////////////////////////////////////////////////////////////
    #elif TARGET_OS_MAC == 1
        #define UE_PLATFORM_MACOS

        #define UE_BYTESWAP_16(x) _OSSwapInt16(x)
        #define UE_BYTESWAP_32(x) _OSSwapInt32(x)
        #define UE_BYTESWAP_64(x) _OSSwapInt64(x)
    #endif

////////////////////////////////////////////////////////////
// - Linux Platforms (Android and Linux)
// We need to check all for Android before linux since
// android contains __linux__
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// - Android
////////////////////////////////////////////////////////////
#elif defined(__ANDROID__)
    #define UE_PLATFORM_ANDROID

    #error "Android is not supported!"

#elif defined(__linux__)
    #define UE_PLATFORM_LINUX

    #include <byteswap.h>

    #define UE_BYTESWAP_16(x) bswap_16(x)
    #define UE_BYTESWAP_32(x) bswap_32(x)
    #define UE_BYTESWAP_64(x) bswap_64(x)
#else
    #error "Unknown platform!"
#endif
