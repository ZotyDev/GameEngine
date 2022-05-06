#include "uepch.h"
#include "PlatformIndependenceLayer/FileSystem.h"

namespace UE
{
	Scope<FileSystemPlatform> FileSystem::s_FileSystemPlatform = FileSystemPlatform::Create();
}