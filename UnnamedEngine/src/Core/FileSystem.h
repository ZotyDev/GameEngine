#pragma once

namespace UE
{
	typedef std::filesystem::path UEPath;

	UEBool DoesFileExists(const UEPath& path);
	UEResult ReadToBuffer(const UEPath& path, UEString& buffer);
}