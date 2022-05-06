#pragma once

#include "PlatformIndependenceLayer/FileSystemPlatform.h"

namespace UE
{
	class FileSystem
	{
	public:
		static void Init()
		{
			s_FileSystemPlatform->Init();
		}

		static UEBool FileSelectorDialog(UEPath& receivedPath, UEBool folderOnly = false)
		{
			return s_FileSystemPlatform->FileSelectorDialog(receivedPath, folderOnly);
		}

		static UEBool FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters)
		{
			return s_FileSystemPlatform->FileSelectorDialog(receivedPath, filters);
		}

		static UEBool DoesFileExists(const UEPath& path)
		{
			return s_FileSystemPlatform->DoesFileExists(path);
		}

		static UEResult ReadToBuffer(const UEPath& path, UEString& buffer)
		{
			return s_FileSystemPlatform->ReadToBuffer(path, buffer);
		}

	private:
		static Scope<FileSystemPlatform> s_FileSystemPlatform;
	};
}