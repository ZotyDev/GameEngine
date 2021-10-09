#pragma once

namespace UE
{
	std::string ToBinary(UEUint64 n);

	void FlushTargetBitStream(UEUint64& target, UEUint8& targetSize, std::vector<UEUint64>& container);

	template<typename T>
	UEUint8 CalculateRequiredBits(T data)
	{
		// Check if data equals to 1 or 0
		UEUint64 ToBeTested = UEUint64(data);
		if (ToBeTested == 0 || ToBeTested == 1)
		{
			return 1;
		}

		// UEUint64 Tester1 = 0xAAAAAAAAAAAAAAAA;
		// UEUint64 Tester2 = 0xCCCCCCCCCCCCCCCC;
		// UEUint64 Tester3 = 0xF0F0F0F0F0F0F0F0;
		// UEUint64 Tester4 = 0xFF00FF00FF00FF00;
		// UEUint64 Tester5 = 0xFFFF0000FFFF0000;
		// UEUint64 Tester6 = 0xFFFFFFFF00000000;

		UEUint8 RequiredBits = 1;
		RequiredBits += (ToBeTested & 0xAAAAAAAAAAAAAAAA) ? 1 : 0;
		RequiredBits += (ToBeTested & 0xCCCCCCCCCCCCCCCC) ? 2 : 0;
		RequiredBits += (ToBeTested & 0xF0F0F0F0F0F0F0F0) ? 4 : 0;
		RequiredBits += (ToBeTested & 0xFF00FF00FF00FF00) ? 8 : 0;
		RequiredBits += (ToBeTested & 0xFFFF0000FFFF0000) ? 16 : 0;
		RequiredBits += (ToBeTested & 0xFFFFFFFF00000000) ? 32 : 0;

		return RequiredBits;
	}

	template<typename T>
	void WriteBitStream(T source, UEUint8 size, UEUint64& target, UEUint8& targetSize, std::vector<UEUint64>& container)
	{
		// check if overflow needs to be used
		if (targetSize + size > 64)
		{
			T Holder = source;

			// calculate how many bits fit inside target
			UEUint8 PossibleAtOverflow = (targetSize + size) - 64;
			UEUint8 PossibleAtTarget = size - PossibleAtOverflow;

			// resume holder to possible bits only
			Holder >>= PossibleAtOverflow;

			// shift target to left by the possbile bits
			target <<= PossibleAtTarget;

			// put the possible bits inside target
			target |= Holder;

			FlushTargetBitStream(target, targetSize, container);

			// get rid of already packed bits
			Holder = source;
			Holder <<= PossibleAtTarget;
			Holder >>= PossibleAtTarget;

			// put the remaining bits into target
			target |= Holder;

			return;
		}
		else
		{
			// shift target to left by the size
			target <<= size;
		}

		// put bits inside target
		target |= source;

		// increment target size
		targetSize += size;

		// check if target is full
		if (targetSize == 64)
		{
			FlushTargetBitStream(target, targetSize, container);
		}
	}

	template<typename T>
	void ReadBitStream(T& target, UEUint8 size, UEUint64& source, UEUint8 sourceSize, std::vector<UEUint64>& container)
	{
		// copy the source of data

		// get rid of everything not needed

		// put data inside value

		// copy the source of data

		// get rid of the data already used

		// check if there is more data inside the container
		if (container.size() > 0)
		{
			// 
		}
	}
}