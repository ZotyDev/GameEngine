#include "uepch.h"
#include "Files/Loader/LoaderHelper.h"

namespace UE
{
	uint32_t LoaderReadAndConvert(char* src, uint32_t size)
	{
		uint32_t Holder = 0;
		if (UE_IS_NATIVE_BIG_ENDIAN())
		{
			for (int i = 0; i < size; ++i)
			{
				reinterpret_cast<char*>(&Holder)[3 - 1] = src[i];
			}
		}
		else
		{
			std::memcpy(&Holder, src, size);
		}
		return Holder;
	}
}