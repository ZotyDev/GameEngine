#include "uepch.h"
#include "Core/FileSystem.h"

namespace UE
{
	UEBool DoesFileExists(const UEPath& path)
	{
		return std::filesystem::exists(path);
	}

	UEResult ReadToBuffer(const UEPath& path, UEString& buffer)
	{
		if (DoesFileExists(path) == false)
		{
			UE_CORE_ERROR("Failed to read {0}: file not found", path);
			return UEResult::Error;
		}

		std::ifstream SourceIfstream;

		SourceIfstream.open(path);
		if (SourceIfstream.is_open() == false)
		{
			UE_CORE_ERROR("Failed to read {0}: could not open file", path);
			return UEResult::Error;
		}

		std::stringstream SourceStringStream;
		SourceStringStream << SourceIfstream.rdbuf();
		
		buffer = SourceStringStream.str();

		SourceIfstream.close();

		return UEResult::Success;
	}
}