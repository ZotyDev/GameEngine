#include "uepch.h"
#include "Core/Bitwise.h"

namespace UE
{
	UEResult ReadBinaryStream(UEUint64 target, UEUint8 position, UEUint8 wordSize, UEUint64& buffer)
	{
		// validate input
		if (position + wordSize > 65)
		{
			UE_CORE_ERROR("Failed to read binary stream: invalid position {0} and/or wordSize {1}", position, wordSize);
			return UEResult::Error;
		}

		// create mask for reading
		UEUint64 Mask = ~(UEUint64)0;
		Mask <<= 64 - wordSize;
		Mask >>= position - 1;

		// use mask to extract data
		buffer = target & Mask;

		// correct data by offseting it
		buffer >>= 64 - wordSize - position + 1;

		return UEResult::Success;
	}

	UEResult WriteBinaryStream(UEUint64& target, UEUint8 position, UEUint8 wordSize, UEUint64 buffer)
	{
		// validate input
		if (position + wordSize > 65)
		{
			UE_CORE_ERROR("Failed to write binary stream: invalid position {0} and/or wordSize {1}", position, wordSize);
			return UEResult::Error;
		}

		// offset data
		buffer <<= 64 - position - wordSize + 1;

		// insert inside target
		target |= buffer;

		return UEResult::Success;
	}

	void FlushBinaryStream(UEUint64& target, UEUint8& targetPosition, std::deque<UEUint64>& container)
	{
		container.push_back(target);
		target = 0;
		targetPosition = 1;
	}

	void FlushEndBinaryStream(UEUint64& target, UEUint8& targetPosition, std::deque<UEUint64>& container)
	{
		target <<= 64 - targetPosition - 1;
		container.push_back(target);
		target = 0;
		targetPosition = 1;
	}

	std::string ToBinary(UEUint64 n)
	{
		std::string r;
		while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
		return r;
	}

	std::string ToBinaryF(UEUint64 n)
	{
		std::string BinaryString = ToBinary(n);
		if (BinaryString.size() < 64)
		{
			UEUint8 ZerosToAdd = 64 - (UEUint8)BinaryString.size();
			BinaryString.insert(0, std::string(ZerosToAdd, '0'));
		}
		return BinaryString;
	}
}