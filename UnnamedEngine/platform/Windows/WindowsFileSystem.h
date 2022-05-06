#pragma once

#include "PlatformIndependenceLayer/FileSystemPlatform.h"

namespace UE
{
	class WindowsFileSystem : public FileSystemPlatform
	{
	public:
		WindowsFileSystem();
		virtual ~WindowsFileSystem() override;

		virtual void Init() override;

		virtual UEBool WindowsFileSystem::DoesFileExists(const UEPath& path) override;
		virtual UEResult WindowsFileSystem::ReadToBuffer(const UEPath& path, UEString& buffer) override;

		virtual UEBool FileSelectorDialog(UEPath& receivedPath, UEBool folderOnly) override;
		virtual UEBool FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters) override;

	private:
	};
}