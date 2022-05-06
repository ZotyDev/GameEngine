#include "uepch.h"
#include "PlatformIndependenceLayer/FileSystemPlatform.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "Windows/WindowsFileSystem.h"
#endif
#if defined(UE_PLATFORM_WEB)
	#include "\Web\WebFileSystem"
#endif

namespace UE
{
	#if defined(UE_PLATFORM_WINDOWS)
		FileSystemPlatform::Platform FileSystemPlatform::s_Platform = FileSystemPlatform::Platform::Windows;
	#elif defined(UE_PLATFORM_WEB)
		FileSystemPlatform::Platform FileSystemPlatform::s_Platform = FileSystemPlatform::Platform::Web;
	#else
		FileSystemPlatform::Platform FileSystemPlatform::s_Platform = FileSystemPlatform::Platform::None;
		#error Platform::None is not supported!
	#endif

	Scope<FileSystemPlatform> FileSystemPlatform::Create()
	{
		switch (s_Platform)
		{
		case UE::FileSystemPlatform::Platform::None:
			UE_CORE_ASSERT(false, "Platform::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case UE::FileSystemPlatform::Platform::Windows:
			return CreateScope<WindowsFileSystem>();
		#endif
		#if defined(UE_PLATFORM_WEB)
		case UE::FileSystemPlatform::Platform::Emscripten:
			return CreateScope<WebFileSystem>();
		#endif
		}

		UE_CORE_ERROR("Unkown Platform");
		return nullptr;
	}
}