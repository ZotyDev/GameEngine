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

		virtual UEBool Exists(const UEPath& path) override;
		virtual UEResult ReadToBuffer(const UEPath& path, UEString& buffer) override;

		virtual UEResult FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters, UEBool folderOnly) override;

		virtual UEResult MakeSureFolder(const UEPath& path) override;
		virtual UEResult MakeSureFile(const UEPath& path) override;

		virtual UEResult GetUserDataFolder(UEPath& path) override;

	private:
	};
}