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

		static UEResult<> FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters, UEBool folderOnly = false)
		{
			return s_FileSystemPlatform->FileSelectorDialog(receivedPath, filters, folderOnly);
		}

		static UEBool DoesFileExists(const UEPath& path)
		{
			return s_FileSystemPlatform->Exists(path);
		}

		static UEResult<> ReadToBuffer(const UEPath& path, UEString& buffer)
		{
			return s_FileSystemPlatform->ReadToBuffer(path, buffer);
		}

		static UEResult<> MakeSureFolder(const UEPath& path)
		{
			return s_FileSystemPlatform->MakeSureFolder(path);
		}

		static UEResult<> MakeSureFile(const UEPath& path)
		{
			return s_FileSystemPlatform->MakeSureFile(path);
		}

		static UEResult<> GetUserDataFolder(UEPath& path)
		{
			return s_FileSystemPlatform->GetUserDataFolder(path);
		}

	private:
		static Scope<FileSystemPlatform> s_FileSystemPlatform;
	};
}