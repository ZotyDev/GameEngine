#pragma once

namespace UE
{
	class FileSystemPlatform
	{
	public:
		enum class Platform
		{
			None = 0,
			Windows = 1,
			Emscripten = 2
		};

	public:
		virtual ~FileSystemPlatform() = default;

		virtual void Init() = 0;

		virtual UEResult<> FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters, UEBool folderOnly) = 0;
		//virtual UEResult FileSelectorDialog(UEPath& receivedPath, const std::vector<std::pair<UEString, UEString>>& filters) = 0;

		virtual UEBool Exists(const UEPath& path) = 0;
		virtual UEResult<> ReadToBuffer(const UEPath& path, UEString& buffer) = 0;

		virtual UEResult<> MakeSureFolder(const UEPath& path) = 0;
		virtual UEResult<> MakeSureFile(const UEPath& path) = 0;

		virtual UEResult<> GetUserDataFolder(UEPath& path) = 0;

		static Platform GetPlatform() { return s_Platform; }
		static Scope<FileSystemPlatform> Create();
	private:
		static Platform s_Platform;
	};
}