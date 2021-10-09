#include "uepch.h"
#include "Core/Bitwise.h"

namespace UE
{
	std::string ToBinary(UEUint64 n)
	{
		std::string r;
		while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
		return r;
	}

	void FlushTargetBitStream(UEUint64& target, UEUint8& targetSize, std::vector<UEUint64>& container)
	{
		container.push_back(target);
		target = 0;
		targetSize = 0;
	}
}