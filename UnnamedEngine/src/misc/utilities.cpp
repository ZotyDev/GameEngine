#include "utilities.h"

namespace UE
{
	bool FileExists(const char* path)
	{
		std::ifstream file(path);
		return (bool)file;
	};

	std::int32_t _convert_to_int(char* buffer, std::size_t len)
	{
		std::int32_t a = 0;
		if (IsBigEndian())
		{
			for (std::size_t i = 0; i < len; ++i)
			{
				reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
			}
		}
		else
		{
			std::memcpy(&a, buffer, len);
		}

		return a;
	};
}